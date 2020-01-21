//---------------------------------------------------------------------------
#pragma hdrstop
#include "postcard_tcpip_terminal.h"
#include "ECR_Message.h"
#include "ECR_Globals.h"
#include "ECR_Exceptions.h"
#include "ECR_CommunicationInterface.h"
#include "message_factory.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
PostcardTCPIPTerminal::PostcardTCPIPTerminal(CommunicationInterface * communication_interface_, MessageFactory* message_factory_)
:communication_interface(communication_interface_),
 message_factory(message_factory_)
{
}
//---------------------------------------------------------------------------
Message PostcardTCPIPTerminal::hello(void)
{
	Message ecr_message = message_factory->createMessage(Globals::miECRPostcardHelloExt,Globals::DEFAULT_TOKEN);
	Message pos_message = message_factory->createMessage(Globals::miPOSPostcardHelloExt,Globals::DEFAULT_TOKEN);
	pos_message.setTimeOut(Globals::TIME_A);
	ecr_message = communication_interface->send(ecr_message, pos_message);
	return ecr_message;

}
//---------------------------------------------------------------------------
Message PostcardTCPIPTerminal::sale(const Currency& _Amount, const short _ProfileId, const Globals::TransKind& _Kind)
{
	Message ecr_message = message_factory->createMessage(_ProfileId > 0 ? Globals::miECRPostcardStartExt : Globals::miECRPostcardStart,Globals::DEFAULT_TOKEN);
	Message pos_message = message_factory->createMessage(Globals::miPOSPostcardFinish,Globals::DEFAULT_TOKEN);
	try
	{
		ecr_message.setAmount(_Amount);
		ecr_message.setTransKind(_Kind);
		ecr_message.setProfileId(_ProfileId);
		ecr_message = communication_interface->send(ecr_message, pos_message);
	}
	catch (...)
	{
	  ecr_message.setTransStatus(Globals::tsTransAbort);
	}
	return ecr_message;

}
//---------------------------------------------------------------------------
Message PostcardTCPIPTerminal::resp(const Globals::RespKind _RK, const unsigned short _Val)
{
	String pinpad_message(_Val);
	Message ecr_message = message_factory->createMessage(Globals::miECRPostcardDisp,Globals::DEFAULT_TOKEN);
	ecr_message.setRespKind(_RK);
	ecr_message.setPinPadMsg(pinpad_message);
	ecr_message.setPPMSize(pinpad_message.Length());
	communication_interface->resp(ecr_message);
	ecr_message.setTransStatus(Globals::tsApproval);
   return ecr_message;

}
//---------------------------------------------------------------------------
String PostcardTCPIPTerminal::getProfileList(const int _TimeOut)
{
	String _Res;
	Message _Mess = message_factory->createMessage(Globals::miECRPostcardPrompt,Globals::DEFAULT_TOKEN);
	Message _CMess = message_factory->createMessage(Globals::miPOSPostcardPrompt,Globals::DEFAULT_TOKEN);
	_CMess.setTimeOut(_TimeOut > Globals::TIME_A ? _TimeOut : Globals::TIME_A);
	_Mess.setPromptReq(Globals::PromptReq::prProfileList);
	_Mess = communication_interface->send(_Mess, _CMess);
	if (_Mess.getTransStatus() == Globals::tsConnErr)
		throw ECRNoConnectionException(Globals::getTransStatDescr(Globals::tsConnErr));

	_Res = _Mess.getPinPadMsg();
	return _Res;

}
//---------------------------------------------------------------------------
PostcardTCPIPTerminal::~PostcardTCPIPTerminal(void)
{
 delete communication_interface;
 delete message_factory;
}
//---------------------------------------------------------------------------

