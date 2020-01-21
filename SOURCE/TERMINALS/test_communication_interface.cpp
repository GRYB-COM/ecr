//---------------------------------------------------------------------------
#pragma hdrstop
#include "test_communication_interface.h"
#include "ECR_message.h"
#include "ECR_IObserver.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
Message TestCommunicationInterface::send(const Message& message_to_send, const Message& close_message)
{
   Message return_message(close_message);
   if (observer)
   {
      observer->runOnMsg(message_to_send);
   	observer->runOnECR(return_message);
   }
   return_message.setTransStatus(Globals::tsApproval);
	return return_message;
}

//---------------------------------------------------------------------------
void TestCommunicationInterface::resp(const Message& response_message)
{
	if (observer) observer->runOnECR(response_message);
}
//---------------------------------------------------------------------------