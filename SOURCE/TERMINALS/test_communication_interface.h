//---------------------------------------------------------------------------

#ifndef test_communication_interfaceH
#define test_communication_interfaceH
#include "ECR_CommunicationInterface.h"
#include <system.hpp>
namespace ecr
{
	class Message;
	class Pars;
	class IObserver;

	class TestCommunicationInterface :public CommunicationInterface
	{
	public:
       TestCommunicationInterface(void) :observer(NULL) {}
		virtual void setObserver(IObserver& observer_) { observer = &observer_; }
		virtual void clearObserver(void) {observer = NULL;}
		virtual Message send(const Message& _Mess, const Message& _CloseMess);
		virtual void resp(const Message& _Mess);
   private:
      IObserver * observer;
	};
}
#endif
