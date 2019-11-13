#!/usr/bin/env python
"""Simulate ECR by FROB PROTOCOL"""

from argparse import ArgumentParser
from serial import Serial
from msvcrt import kbhit, getch
from time import sleep
from socket import socket, AF_INET, SOCK_STREAM
from base64 import b64encode, b64decode
from operator import xor
from functools import reduce
import logging

__license__ = """
Copyright (C) 2018 by APDU Sp. z o.o.

All rights reserved.  No part of this software may be reproduced,
transmitted, transcribed, stored in a retrieval system, or translated
into any language or computer language, in any form or by any means,
electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
without the prior written permission of APDU Sp. z o.o.
"""

STX = 0x02
ETX = 0x03
FS = 0x1C
ACK = 0x06
NACK = 0x15

CHAR_DICT = {
    STX: '[STX]',
    ETX: '[ETX]',
    FS: '[FS]',
    ACK: '[ACK]',
    NACK: '[NACK]',
}


def printable_char(char):
    if char in CHAR_DICT:
        return CHAR_DICT[char]
    elif char < 0x20:
        return '[{}]'.format(hex(char))
    return chr(char)


def printable_bytes(data):
    return ''.join(printable_char(c) for c in data)


def lrc(data):
    return reduce(xor, bytes(data, 'ascii'), ETX)


def frame(fields):
    data = '\x1C'.join(fields) + '\x1C'
    logging.debug("\n\x02{}\x03{}".format(data, chr(lrc(data)))+"\n" )
    return "\x02{}\x03{}".format(data, chr(lrc(data)))

def send_frame(ser, fields):
    answer = frame(fields)
    logging.debug('<-- frame {}'.format(printable_bytes(bytes(answer, 'ascii'))))
    ser.write(bytes(answer, 'ascii'))

def send_ack(ser):
    ser.write(b'\x06')
    logging.debug('..... <-- {}'.format(printable_char(ACK)))

class Ecr(object):

    def __init__(self, port):
        self.port = port
        self.start_trans = False
        self.tokenidx = 0x2800

    def ecrtoken(self):
        self.tokenidx += 1
        return hex(self.tokenidx)[2:]

    def handle_user_input(self, ser):
        if kbhit():
            char = getch().decode('ASCII')
            if char == 'x':
                logging.info('Exit by pressing {char} key')
                exit()
            elif char == 'd':
                send_frame(ser, [self.ecrtoken(), 'D4'])
            elif char == 't':
                send_frame(ser, [self.ecrtoken(), 'T1'])
            elif char == 'q':
                send_frame(ser, [self.ecrtoken(), 'P1'])
            elif char == 's':
                token, ptype, operation = self.ecrtoken(), 'S1', 'S'
                ecrid, ecrinvid = 'ABC1234567890', '6'
                amo, netto, vat, cur = '128', '100', '28', 'PLN'
                cashback, maxcashback = '0', '30000'
                fields = [token, ptype, operation, ecrid, ecrinvid, amo, netto, vat, 'PLN', cashback, maxcashback]
                send_frame(ser, fields)
            elif char == 'c':
                token, ptype, operation = self.ecrtoken(), 'S1', 'S'
                ecrid, ecrinvid = 'ABC1234567890', '6'
                amo, netto, vat, cur = '728', '828', '100', 'PLN'
                cashback, maxcashback = '70000', '30000'
                fields = [token, ptype, operation, ecrid, ecrinvid, amo, netto, vat, 'PLN', cashback, maxcashback]
                send_frame(ser, fields)

    def loop(self, ser):
        data = []
        mode = 0  # 0 - wait for STX, 1 - wait for ETX, 2 - wait for LRC, 3 - frame parse
        fd = None
        while True:
            self.handle_user_input(ser)
            sleep(0.001)
            chars, toread = [], ser.in_waiting
            if toread > 0:
                chars = ser.read(toread)
            for char in chars:
                data.append(char)
                if char == STX:
                    data = [STX]
                    mode = 1
                elif char == ETX and mode == 1:
                    mode = 2
                elif mode == 2:
                    mode = 3
                    logging.info('frame --> {}'.format(printable_bytes(bytearray(data))))
                elif mode == 1:
                    pass
                else:
                    logging.error('..... --> {}'.format(printable_char(char)))
                if mode == 3:
                    mode = 0
                    send_ack(ser)
                    fields = ''.join(chr(c) for c in data[1:-2]).split(chr(FS))
                    token, frame_type = fields[0], fields[1]
                    if frame_type == 'K4':
                        send_frame(ser, [token, 'K0', '0', '2'])
                    elif frame_type == 'K3':
                        send_frame(ser, [token, 'K0', '0'])
                    elif frame_type == 'K7':
                        send_frame(ser, [token, 'K0', '0', '1232'])
                    elif frame_type == 'C1':
                        operation, connid = fields[2], fields[3]
                        ptype = 'C2'
                        if operation == '4':  # open socket
                            fd = socket(AF_INET, SOCK_STREAM)
                            tmo = int(fields[4])
                            fd.settimeout(tmo)
                            ip = fields[8]
                            port = int(fields[9])
                            fd.connect((ip, port))

                            result = '0'
                            send_frame(ser, [token, ptype, connid, result])
                        elif operation == '8':  # close socket
                            if not fd is None:
                                fd.close()
                            result = '0'
                            send_frame(ser, [token, ptype, connid, result])
                        elif operation == '1':  # send
                            tmo = int(fields[4])
                            fd.settimeout(tmo)
                            bdata = b64decode(fields[7])
                            fd.send(bdata)

                            result = '0'
                            send_frame(ser, [token, ptype, connid, result])
                        elif operation == '2' or operation == '3':  # recv or send + recv
                            tmo = int(fields[4])
                            fd.settimeout(tmo)
                            if len(fields) >= 8:
                                senddata = b64decode(fields[7])
                                fd.send(senddata)
                            rdata = fd.recv(int(fields[5]))
                            try:
                                fd.settimeout(0.1)
                                rdata += fd.recv(int(fields[6]))
                            except Exception as e:
                                pass

                            result = '0'
                            send_frame(ser, [token, ptype, connid, result, b64encode(rdata).decode('ascii')])
                    elif frame_type == 'DD':
                        ptype, result, status, free_lines = 'D0', '0', '0', '0'
                        send_frame(ser, [token, ptype, result, status, free_lines])

    def start(self):
        COM_PORT = 'COM{}'.format(self.port)
        with Serial(COM_PORT, 115200, timeout=0.001) as ser:
            logging.debug(f'COM: Serial opened {COM_PORT}\n')
            self.loop(ser)


if __name__ == "__main__":
    parser = ArgumentParser(description='ECR by FROB protocol test')
    parser.add_argument('-p', '--port', required=True,
                        help='Port number on which device is connected')
    args = parser.parse_args()
    logging.basicConfig(format='%(asctime)s %(message)s', level=logging.DEBUG)
    Ecr(args.port).start()
