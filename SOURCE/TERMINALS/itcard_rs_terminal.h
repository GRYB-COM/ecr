//---------------------------------------------------------------------------

#ifndef itcard_rs_terminalH
#define itcard_rs_terminalH
#include "ECR_terminal_interface.h"
namespace ecr{
   class CommunicationInterface;
   class MessageFactory;
   class SalePars;
   class ItcardRSTerminal :public TerminalInterface{
   public:
      ItcardRSTerminal(CommunicationInterface*,MessageFactory*);
      virtual Message hello(void);
		virtual Message sale(const SalePars&);
		virtual Message resp(const Globals::RespKind _RK, const unsigned short _Val);
		virtual String getProfileList(const int _TimeOut);
      virtual ~ItcardRSTerminal(void);
   private:
      CommunicationInterface * communication_interface;
      MessageFactory*          message_factory;
      void validate(Message& ecr_message,const Message& pos_message, const Globals::MessID);
   };
}
//---------------------------------------------------------------------------
#endif
