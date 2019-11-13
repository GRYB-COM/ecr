//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_TerminalFactory.h"
#include "postcard_tcpip_terminal.h"
#include "itcard_rs_terminal.h"
#include <System.SysUtils.hpp>
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
class TerminalFactory::TerminalCreateException :public EInOutError{
TerminalCreateException(void):EInOutError("B³¹d przy tworzeniu obiektu do ob³ugi terminala.\nNieznay rodzaj terminala."){}
friend TerminalFactory;

};
//---------------------------------------------------------------------------
TerminalInterface* TerminalFactory::create(const Globals::TerminalKind terminal_kind, CommunicationInterface* communication_interface, MessageFactory* message_factory)
{
 TerminalInterface * terminal_interface(NULL);
 switch(terminal_kind)
 {
    case Globals::tkiPostcardTCIP: terminal_interface = new PostcardTCPIPTerminal(communication_interface,message_factory); break;
    case Globals::tkiItcardRS: terminal_interface = new ItcardRSTerminal(communication_interface,message_factory); break;
    default: throw TerminalCreateException();
 }
 return terminal_interface;
}

