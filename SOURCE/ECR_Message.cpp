//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_Message.h"
#include "message_string_converter.h"
#include "SysUtils.hpp"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
Message::Message(MessageStringConverter* message_string_converter_)
:message_string_converter(new MessageStringConverter(*message_string_converter_) )
{
	clear();
}
//---------------------------------------------------------------------------
Message::Message(const Message& message)
:message_string_converter(NULL)
{
  copy(message);
}

//---------------------------------------------------------------------------
void Message::copy(const Message& message)
{
 clear();
 if(message_string_converter) delete message_string_converter;
 if(message.message_string_converter) message_string_converter = new MessageStringConverter(*message.message_string_converter);
  m_MessID          = message.m_MessID;
  m_TermStatus      = message.m_TermStatus;
  m_TermID          = message.m_TermID;
  m_Amount          = message.m_Amount;
  m_TransKind       = message.m_TransKind;
  m_CardType        = message.m_CardType;
  m_TransStatus     = message.m_TransStatus;
  message_as_string = message.message_as_string;
  m_PinPadMsg       = message.m_PinPadMsg;
  m_PPMSize         = message.m_PPMSize;
  m_RespKind        = message.m_RespKind;
  m_TimeOut         = message.m_TimeOut;
  m_ProfileId       = message.m_ProfileId;
  m_PromptReq       = message.m_PromptReq;
  message_token     = message.message_token;
  ecr_ID            = message.ecr_ID;
  doc_ID            = message.doc_ID;
}
//---------------------------------------------------------------------------
void Message::clear(void)
{
	m_MessID =Globals::miUnknown;
	m_TermStatus =-1;
	m_TermID =-1;
	m_Amount =0.0;
	m_TransKind=Globals::tkUnknown;
	m_CardType=-1;
	m_TransStatus = Globals::tsUnknown;
	message_as_string="";
	m_PinPadMsg="";
	m_PPMSize=-1;
	m_RespKind = Globals::rkUnknown;
	m_TimeOut=-1;
	m_ProfileId=-1;
	m_PromptReq=Globals::prUnknown;
   message_token="";
   ecr_ID ="brak";
   doc_ID ="brak";

}

//---------------------------------------------------------------------------
AnsiString Message::getAsString(void) const
{
      if(!message_string_converter) throw Exception("Nie ma string_convertera");
	AnsiString message_as_string;
   message_string_converter->convertMessageToString(message_as_string,*this);
	return message_as_string;
}
//---------------------------------------------------------------------------
void Message::setFromString(const AnsiString& message_as_string_)
{
   clear();
   message_as_string = message_as_string_;
   if(!message_string_converter) throw Exception("Nie ma string_convertera");
   message_string_converter->convertStringToMessage(*this, message_as_string);
}
//---------------------------------------------------------------------------
Message::~Message(void)
{
  delete message_string_converter;
}
