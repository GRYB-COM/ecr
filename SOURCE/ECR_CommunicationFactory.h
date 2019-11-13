//---------------------------------------------------------------------------

#ifndef ECR_CommunicationFactoryH
#define ECR_CommunicationFactoryH
//---------------------------------------------------------------------------
namespace ecr{
   class CommunicationInterface;
   class Pars;
   class CommunicationFactory{
   public:
      static CommunicationInterface* create(const Pars&);
   };
}
//---------------------------------------------------------------------------
#endif
