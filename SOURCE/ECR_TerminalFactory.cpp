//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_TerminalFactory.h"
#include "postcard_tcpip_terminal.h"
#include "itcard_rs_terminal.h"
#include <System.SysUtils.hpp>
#include "ECR_Pars.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
class TerminalFactory::TerminalCreateException :public EInOutError{
TerminalCreateException(void):EInOutError("B³¹d przy tworzeniu obiektu do ob³ugi terminala.\nNieznay rodzaj terminala."){}
friend TerminalFactory;

};
//---------------------------------------------------------------------------
TerminalInterface* TerminalFactory::create(CommunicationInterface* communication_interface, MessageFactory* message_factory, const Pars& pars)
{
 TerminalInterface * terminal_interface(NULL);
 switch(pars.terminal_kind)
 {
    case Globals::tkiPostcardTCIP: terminal_interface = new PostcardTCPIPTerminal(communication_interface,message_factory,pars); break;
    case Globals::tkiItcardRS: terminal_interface = new ItcardRSTerminal(communication_interface,message_factory); break;
    default: throw TerminalCreateException();
 }
 return terminal_interface;
}

