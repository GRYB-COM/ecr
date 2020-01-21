//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_Terminal.h"
#include "ECR_Message.h"
#include "ECR_Exceptions.h"
#include "ECR_CommunicationFactory.h"
#include "ECR_CommunicationInterface.h"
#include "ECR_TerminalFactory.h"
#include "ECR_terminal_interface.h"
#include "message_factory.h"
#include "message_template_repository.h"
#include "ECR_Utils.h"
#include "message_string_converter.h"
#include "ECR_TransStatDescr.h"
#include <dialogs.hpp>
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;

//---------------------------------------------------------------------------
Terminal::Terminal(const Pars& params_,ecr::IObserver& observer )
:terminal_ID(1001),
 params(params_)
{
   CommunicationInterface * communication_interface(CommunicationFactory::create(params));
   communication_interface->setObserver(observer);

   MessageTemplateRepository * message_template_repository(new MessageTemplateRepository );
   String field_separator_code(Utils::getSeparator(params) );
   MessageStringConverter::Parameters converter_parameters;
   converter_parameters.field_separator_code=field_separator_code;
   converter_parameters.first_field_index =params.terminal_kind == Globals::tkiPostcardTCIP ? 1 : 0;
   converter_parameters.message_id_field_kind     = params.terminal_kind == Globals::tkiPostcardTCIP ? Globals::fkPostcardMessID : Globals::fkItcardMessID;
   MessageStringConverter* message_string_converter(new  MessageStringConverter(converter_parameters) );
   MessageFactory* message_factory(new MessageFactory(message_template_repository, message_string_converter) );

   terminal_interface = TerminalFactory::create(params.terminal_kind, communication_interface, message_factory);
}
//---------------------------------------------------------------------------
Terminal::~Terminal(void)
{
   delete terminal_interface;
}
//---------------------------------------------------------------------------
Globals::TransStat Terminal::hello(void)
{
   Globals::TransStat transaction_status(Globals::tsUnknown);
   try{
		Message return_message (terminal_interface->hello());
		transaction_status = return_message.getTransStatus();
      if(transaction_status == Globals::tsApproval) terminal_ID = return_message.getTermID();
   }
  	catch (Exception& exc)
	{
      TransStatDescr::m_LastError =exc.Message;
		transaction_status = Globals::tsConnErr;
	}
  	catch (...)
	{
		transaction_status = Globals::tsConnErr;
      TransStatDescr::m_LastError ="Nieznany b³¹d! (PROCEDURA HELLO) ";

	}
	return transaction_status;

}

//---------------------------------------------------------------------------
Globals::TransStat Terminal::sale(const Currency& amount, const short profile_ID, const Globals::TransKind& trans_kind)
{
	Globals::TransStat transaction_status(Globals::tsUnknown);
	try
	{
		Message return_message = terminal_interface->sale(amount,profile_ID,trans_kind);
		transaction_status = return_message.getTransStatus();

	}
	catch (...)
	{
		transaction_status = Globals::tsConnErr;
      TransStatDescr::m_LastError ="Nieznany b³¹d! (PROCEDURA SALE) ";
	}
	return transaction_status;
}

//---------------------------------------------------------------------------
Globals::TransStat Terminal::resp(const Globals::RespKind response_kind, const unsigned short value)
{
	Message return_message(terminal_interface->resp(response_kind,value));
	return return_message.getTransStatus();
}

//---------------------------------------------------------------------------

String Terminal::getProfileList(const int time_out)
{
	return terminal_interface->getProfileList(time_out);

}
