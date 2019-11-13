//---------------------------------------------------------------------------
#ifndef message_factoryH
#define message_factoryH
#include "..\ECR_Globals.h"

//---------------------------------------------------------------------------
namespace ecr{
   class Message;
   class MessageTemplateRepository;
   class MessageStringConverter;
	class MessageFactory
	{
	public:
		MessageFactory(MessageTemplateRepository*,MessageStringConverter*);
		Message createMessage(const Globals::MessID message_ID, const String& message_token) const ;
		Message createMessageFromString(const AnsiString& _MessStr) const ;
		~MessageFactory();
   private:
   	MessageTemplateRepository*   message_template_repository;
      MessageStringConverter*      message_string_converter;
	};

}
//---------------------------------------------------------------------------
#endif
