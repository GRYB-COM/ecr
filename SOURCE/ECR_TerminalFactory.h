//---------------------------------------------------------------------------
#ifndef ECR_TerminalFactoryH
#define ECR_TerminalFactoryH
#include "ECR_Globals.h"
namespace ecr{
   class TerminalInterface;
   class CommunicationInterface;
   class MessageFactory;
   class TerminalFactory{
   public:
      static TerminalInterface* create(const Globals::TerminalKind, CommunicationInterface*,MessageFactory*);
      class TerminalCreateException;
   };
}
//---------------------------------------------------------------------------
#endif
