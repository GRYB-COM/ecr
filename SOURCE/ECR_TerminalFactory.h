//---------------------------------------------------------------------------
#ifndef ECR_TerminalFactoryH
#define ECR_TerminalFactoryH
namespace ecr{
   class TerminalInterface;
   class CommunicationInterface;
   class MessageFactory;
   class Pars;
   class TerminalFactory{
   public:
      static TerminalInterface* create(CommunicationInterface*,MessageFactory*, const Pars&);
      class TerminalCreateException;
   };
}
//---------------------------------------------------------------------------
#endif
