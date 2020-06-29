//---------------------------------------------------------------------------
#pragma hdrstop
#include "itcard_rs_terminal.h"
#include "ECR_Message.h"
#include "ECR_Globals.h"
#include "ECR_Exceptions.h"
#include "ECR_CommunicationInterface.h"
#include "message_factory.h"
#include <SysUtils.hpp>
#include "ECR_TransStatDescr.h"
#include <dialogs.hpp>

#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
ItcardRSTerminal::ItcardRSTerminal(CommunicationInterface * communication_interface_, MessageFactory* message_factory_)
:communication_interface(communication_interface_),
 message_factory(message_factory_)
{
}
//---------------------------------------------------------------------------
Message ItcardRSTerminal::hello(void)
{
	Message ecr_message = message_factory->createMessage(Globals::miECRItcardHello,Globals::GENERATE_TOKEN);
	Message pos_message = message_factory->createMessage(Globals::miPOSItcardHello,ecr_message.getMessageToken());
	pos_message.setTimeOut(Globals::TIME_A);
	Message return_message(communication_interface->send(ecr_message, pos_message));
   validate(ecr_message, return_message,Globals::miPOSItcardHello);
	return return_message;

}

//---------------------------------------------------------------------------
void ItcardRSTerminal::validate(Message& return_message,const Message& pos_message, const  Globals::MessID mess_ID)
{
    if(return_message.getTransStatus() != Globals::tsApproval) return;
    if(pos_message.getMessID() != mess_ID)
    {
     return_message.setTransStatus(Globals::tsMessIDNotMatch);
     TransStatDescr::m_LastError = "\nPowinien zwróciæ '";
     TransStatDescr::m_LastError += (char) Globals::miPOSItcardHello>>8;
     TransStatDescr::m_LastError += (char) Globals::miPOSItcardHello;
     TransStatDescr::m_LastError += "' a zwróci³: '";
     TransStatDescr::m_LastError += (char) pos_message.getMessID()>>8;
     TransStatDescr::m_LastError += (char) pos_message.getMessID();
      TransStatDescr::m_LastError +="'!";
    }
    else if(return_message.getMessageToken() != pos_message.getMessageToken())
    {
    	return_message.setTransStatus(Globals::tsTokenNotMatch);
      TransStatDescr::m_LastError = "\nPowinien zwróciæ '";
      TransStatDescr::m_LastError += return_message.getMessageToken();
      TransStatDescr::m_LastError += "' a zwróci³: '";
      TransStatDescr::m_LastError +=pos_message.getMessageToken();
      TransStatDescr::m_LastError +="'!";
    }

}
//---------------------------------------------------------------------------
Message ItcardRSTerminal::sale(const SalePars& salePars)
{
	Message ecr_message = message_factory->createMessage(Globals::miECRItcardSale,Globals::GENERATE_TOKEN);
	Message pos_message = message_factory->createMessage(Globals::miPOSItcardSale,ecr_message.getMessageToken());
	ecr_message.setAmount(salePars.Amount);
	ecr_message.setTransKind(salePars.Kind);
	ecr_message.setProfileId(salePars.ProfileId);
   pos_message.setTimeOut(salePars.TimeOut);
   Message return_message(communication_interface->send(ecr_message, pos_message));
   if(return_message.getTransStatus() == Globals::tsTransAbort)
   {
    TransStatDescr::m_LastError = "Transakcja zosta³a przerwana przez terminal z nastêpuj¹cym komunikatem:\n ";
    TransStatDescr::m_LastError += return_message.getPinPadMsg();
   }
	return return_message;
}
//---------------------------------------------------------------------------
Message ItcardRSTerminal::resp(const Globals::RespKind _RK, const unsigned short _Val)
{
	String pinpad_message(_Val);
	Message ecr_message = message_factory->createMessage(Globals::miECRPostcardDisp,Globals::GENERATE_TOKEN);
	ecr_message.setRespKind(_RK);
	ecr_message.setPinPadMsg(pinpad_message);
	ecr_message.setPPMSize(pinpad_message.Length());
	communication_interface->resp(ecr_message);
	ecr_message.setTransStatus(Globals::tsApproval);
   return ecr_message;

}
//---------------------------------------------------------------------------
String ItcardRSTerminal::getProfileList(const int _TimeOut)
{
	String _Res;
	return _Res;

}
//---------------------------------------------------------------------------
ItcardRSTerminal::~ItcardRSTerminal(void)
{
 delete communication_interface;
 delete message_factory;
}
//---------------------------------------------------------------------------

