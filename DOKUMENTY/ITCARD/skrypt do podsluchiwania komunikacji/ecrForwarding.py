#!/usr/bin/env python
"""Simulate ECR by FROB PROTOCOL"""

from argparse import ArgumentParser
from serial import Serial
from time import sleep
from datetime import datetime
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
    try:
        return bytes(chr(char), 'cp1250').decode('cp1250')
    except UnicodeEncodeError:
        return '[{}]'.format(hex(char))


def printable_bytes(data):
    return ''.join(printable_char(c) for c in data)


class Ecr(object):

    def __init__(self, port, port2):
        self.port = port
        self.port2 = port2

    def loop(self, ser, ser2):
        data = []
        data2 = []
        mode = 0
        mode2 = 0
        while True:
            sleep(0.001)
            if ser.is_open:
                chars, toread = [], ser.in_waiting
            else:
                chars, toread = [], 0
            if ser2.is_open:
                chars2, toread2 = [], ser2.in_waiting
            else:
                chars2, toread2 = [], 0
            if toread > 0:
                chars = ser.read(toread)
                ser2.write(chars)
            if toread2 > 0:
                chars2 = ser2.read(toread2)
                ser.write(chars2)

            for char in chars:
                data.append(char)
                if char == STX and mode != 2:
                    if len(data) > 1:
                        logging.info('   ECR ..> {}'.format(printable_bytes(bytearray(data[:-1]))))
                    data = [STX]
                    mode = 1
                elif char == ETX and mode == 1:
                    mode = 2
                elif mode == 2:
                    logging.info('   ECR --> {}'.format(printable_bytes(bytearray(data))))
                    mode = 0
                    data = []
                elif mode == 1:
                    pass
                else:
                    logging.error('   ECR ==> {}'.format(printable_bytes(bytearray(data))))
                    mode = 0
                    data = []
            for char2 in chars2:
                data2.append(char2)
                if char2 == STX and mode2 != 2:
                    if len(data2) > 1:
                        logging.info('pinpad <.. {}'.format(printable_bytes(bytearray(data2[:-1]))))
                    data2 = [STX]
                    mode2 = 1
                elif char2 == ETX and mode2 == 1:
                    mode2 = 2
                elif mode2 == 2:
                    logging.info('pinpad <-- {}'.format(printable_bytes(bytearray(data2))))
                    mode2 = 0
                    data2 = []
                elif mode2 == 1:
                    pass
                else:
                    logging.info('pinpad <== {}'.format(printable_bytes(bytearray(data2))))
                    mode2 = 0
                    data2 = []

    def start(self):
        COM_PORT = 'COM{}'.format(self.port)
        COM_PORT2 = 'COM{}'.format(self.port2)
        ser = Serial(COM_PORT, 115200, timeout=0.001, rtscts=True, dsrdtr=False,
                     inter_byte_timeout=0.0001)
        ser2 = Serial(COM_PORT2, 115200, timeout=0.001, rtscts=True, dsrdtr=False,
                      inter_byte_timeout=0.0001)
        self.loop(ser, ser2)


if __name__ == "__main__":
    parser = ArgumentParser(description='ECR to pinpad FROB protocol forwarder')
    parser.add_argument('-e', '--ecr', required=True,
                        help='Port number on which Ecr is connected')
    parser.add_argument('-p', '--pinpad', required=True,
                        help='Port number on which pinpad is connected')
    args = parser.parse_args()
    logname = 'frob_{}.log'.format(datetime.now().strftime("%Y%m%d"))
    logging.basicConfig(format='%(asctime)s %(message)s', level=logging.DEBUG,
                        handlers=[logging.FileHandler(logname), logging.StreamHandler()])
    Ecr(args.ecr, args.pinpad).start()
