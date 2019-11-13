//---------------------------------------------------------------------------

#ifndef CommunicationSerialH
#define CommunicationSerialH
#include "ECR_CommunicationInterface.h"
#include "ECR_Pars.h"
#include "ECR_Message.h"
#include <vector>

namespace Library{
   namespace SG{
      namespace IO{
         class SerialPort;
      }
   }
}

namespace ecr
{
	class IObserver;

	class CommunicationSerial : public CommunicationInterface
	{
	public:
		virtual void setObserver(IObserver& observer_) { observer  = &observer_; }
      virtual void clearObserver(void)          { 	observer = NULL;  }
		virtual Message send(const Message& send_message, const Message& close_message);
		virtual void resp(const Message& _Mess);
		//KONSTRUKTOR DESTRUKTOR
		CommunicationSerial(const Pars&);
		virtual ~CommunicationSerial(void);

	private:
		//ATRYBUTY
		Pars params;
		IObserver * observer;

		std::vector<Message> messages_stack;

		//unsigned short message_size;

		//NARZÊDZIA
        Library::SG::IO::SerialPort* serial_port;
		//METODY POMOCNICZE
			void prepare(void);
         void writeMessage(const Message&);
			AnsiString getMessageAsString(const Message&) const;
			void listen(Message&,const Message&);
         void readFromSerial(AnsiString&);
         void createMessageFromString(Message&,const Message& close_message,const AnsiString&);
         unsigned char calculateXOR(const AnsiString&)const;
	};
}
//---------------------------------------------------------------------------
#endif
