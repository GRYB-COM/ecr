//---------------------------------------------------------------------------
#pragma hdrstop
#include "message_factory.h"
#include "ECR_Message.h"
#include "message_template_repository.h"
#include "message_string_converter.h"
#include  <SysUtils.hpp>
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
MessageFactory::MessageFactory(MessageTemplateRepository* message_template_repository_, MessageStringConverter* message_string_converter_)
:message_template_repository(message_template_repository_),
 message_string_converter(message_string_converter_)
{
 Randomize();
}
//---------------------------------------------------------------------------
MessageFactory::~MessageFactory(void)
{
 delete message_template_repository;
 delete message_string_converter;
}
//---------------------------------------------------------------------------
Message MessageFactory::createMessage(const Globals::MessID message_ID,const String& message_token) const
{
 AnsiString message_string_template(message_template_repository->get(message_ID));
 Message message(message_string_converter);
 message.m_MessID = message_ID;
 message.setFromString(message_string_template);
 message.message_token = message_token.IsEmpty() ? Format("%.0x", ARRAYOFCONST((Random(Globals::TOKEN_RANGE)))) : message_token;
 return message;
}
//---------------------------------------------------------------------------
Message MessageFactory::createMessageFromString(const AnsiString& message_as_string) const
{
 Message message(message_string_converter);
 message.setFromString(message_as_string);
 return message;

}

//---------------------------------------------------------------------------
