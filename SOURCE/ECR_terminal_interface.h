//---------------------------------------------------------------------------
#ifndef ECR_terminal_interfaceH
#define ECR_terminal_interfaceH
#include "ECR_Globals.h"
//---------------------------------------------------------------------------
namespace ecr{
   class CommunicationInterface;
   class Message;
   class TerminalInterface{
   public:
      virtual Message hello(void)=0;
		virtual Message sale(const Currency& _Amount, const short ProfileId, const Globals::TransKind& _Kind)=0;
		virtual Message resp(const Globals::RespKind _RK, const unsigned short _Val)=0;
		virtual String getProfileList(const int _TimeOut)=0;
      virtual ~TerminalInterface(void){}

   };
}
//---------------------------------------------------------------------------
#endif
