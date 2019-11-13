//---------------------------------------------------------------------------

#ifndef CommunicationIndyH
#define CommunicationIndyH
#include "ECR_CommunicationInterface.h"
#include "ECR_Pars.h"
#include <IdGlobal.hpp>
#include <vector>

namespace Idtcpclient
{
	class TIdTCPClient;
}

namespace Vcl
{
	namespace Extctrls
	{
		class TTimer;
	}
}

namespace ecr
{
	class IObserver;

	class CommunicationIndy : public CommunicationInterface
	{
	public:
		//INTERFEJS
		virtual void setObserver(IObserver& observer_) { observer = &observer_; }
		virtual void clearObserver(void) { observer = NULL; }
		virtual Message send(const Message& _Mess, const Message& _CloseMess);
		virtual void resp(const Message& _Mess);
		//KONSTRUKTOR DESTRUKTOR
		CommunicationIndy(const Pars&);
		virtual ~CommunicationIndy(void);

	private:
		Idtcpclient::TIdTCPClient * indy_tcp_client;
		IObserver * observer;

		Pars parameters;

		std::vector<Message> messages_stack;

		void prepareTerminal(void);
      void connectToTerminal(void);
      void sendMessageToTerminal(Message&,const Message&,const int, const Globals::MessID);
		Idglobal::TIdBytes getMessAsBytes(const Message& _Mess);
		void listen(Message&,int& _Counter);
      bool checkInputBuffer(void);
      bool readByte(AnsiString& frame, unsigned& frame_size );
      void sleep(void);
	};
}
//---------------------------------------------------------------------------
#endif
