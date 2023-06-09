//---------------------------------------------------------------------------

#ifndef postcard_tcpip_terminalH
#define postcard_tcpip_terminalH
#include "ECR_terminal_interface.h"
namespace ecr{
   class CommunicationInterface;
   class MessageFactory;
   class SalePars;
   class Pars;
   class PostcardTCPIPTerminal :public TerminalInterface{
   public:
      PostcardTCPIPTerminal(CommunicationInterface*,MessageFactory*,const Pars&);
      virtual Message hello(void);
		virtual Message sale(const SalePars&);
		virtual Message resp(const Globals::RespKind _RK, const unsigned short _Val);
		virtual String getProfileList(const int _TimeOut);
      virtual ~PostcardTCPIPTerminal(void);
   private:
      CommunicationInterface * communication_interface;
      MessageFactory*          message_factory;
      Pars*                    pars;
   };
}
//---------------------------------------------------------------------------
#endif
