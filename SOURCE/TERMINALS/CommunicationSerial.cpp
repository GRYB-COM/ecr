//---------------------------------------------------------------------------
#pragma hdrstop
#include "CommunicationSerial.h"
#include "ECR_Message.h"
#include "ECR_IObserver.h"
#include "ECR_Exceptions.h"
#include "ECR_TransStatDescr.h"
#include <VCL.Forms.hpp>
#include "..\LIBRARY\SG\HASH\simple_string_xor_hashing.hpp"
#include "ECR_Utils.h"
#include "..\LIBRARY\SG\IO\serial_port.hpp"
#include <iostream>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace ecr;
namespace IO   = Library::SG::IO;
namespace Hash = Library::SG::Hash;
//---------------------------------------------------------------------------
CommunicationSerial::CommunicationSerial(const Pars& params_)
	:observer(NULL),
   params(params_),
   serial_port(new  IO::SerialPort())
{
}

//---------------------------------------------------------------------------
CommunicationSerial::~CommunicationSerial(void)
{
	delete serial_port;
}
//---------------------------------------------------------------------------
Message CommunicationSerial::send(const Message& send_message, const Message& close_message)
{
  	Message return_message(send_message);
	try
	{
		try
		{
      	prepare();

			serial_port->openSerialPort();

			if (observer)	observer->runOnECR(send_message);
         writeMessage(send_message);
			listen(return_message,close_message);
		}
		catch(IO::SerialPortException& exc)
		{
			return_message.clear();
			return_message.setTransStatus(Globals::tsConnErr);
         const char * serial_error_message(exc.what());
			TransStatDescr::m_LastError = AnsiString("\r\nOryginalny komunikat systemu:\r\n") + AnsiString(serial_error_message);
		}
		catch (ECRException& exc)
		{
			return_message.clear();
			return_message.setTransStatus(Globals::tsConnErr);
			TransStatDescr::m_LastError = "\r\nOryginalny komunikat systemu:\r\n" + exc.getDetails();
		}
		catch (Exception& exc)
		{
			return_message.clear();
			return_message.setTransStatus(Globals::tsConnErr);
			TransStatDescr::m_LastError = "\r\nOryginalny komunikat systemu:\r\n" + exc.Message;
		}
	}
	__finally
	{
		serial_port->closeSerialPort();
	}

	return return_message;
}
//---------------------------------------------------------------------------
void CommunicationSerial::prepare(void)
{
   AnsiString port_name(params.Host);
   //TO DO dla comów  > 8 port_name += "/";
   port_name += params.Port;
   serial_port->setPortName(port_name.c_str());
	messages_stack.clear();
}
//---------------------------------------------------------------------------
void CommunicationSerial::writeMessage(const Message& send_message)
{
 bool is_error(true);
 AnsiString string_message( getMessageAsString(send_message));
 for (int counter=0; counter < Globals::SEND_ATTEMPT_TIMES; ++counter)
 	{
 		serial_port->writeSerialPort(string_message.c_str(),string_message.Length());
      char confirmation(' ');
      for(int timer(0); timer < Globals::CONFIRMATION_WAIT_TIME; timer += Globals::INTERVAL)
      {
      	if(serial_port->inWaiting() >0)
      	{
           serial_port->readSerialPort(&confirmation,1);
           break;
      	}
     		Sleep(Globals::INTERVAL);
   	}
     if(confirmation == IO::SerialPort::ACK)
     {
       is_error =false;
       break;
     }
   }
   if(is_error) throw ECRTimeOutException();
}
//---------------------------------------------------------------------------
void CommunicationSerial::listen(Message& return_message, const Message& close_message)
{
   bool is_error(true);
	 if (!serial_port->isConnected()) throw ecr::ECRNoConnectionException();
    int listen_time_out(close_message.getTimeOut());
	 if(listen_time_out < 1) listen_time_out = Globals::TIME_B;
    int read_cycles(listen_time_out/Globals::INTERVAL);
    AnsiString messages_as_string;
    for(int counter(0); counter < read_cycles;++ counter)
    {
      messages_as_string="";
    	readFromSerial(messages_as_string);
      createMessageFromString(return_message,close_message, messages_as_string);
      if(return_message.getMessID() == close_message.getMessID())
		{
         if(return_message.getTransStatus()== Globals::tsUnknown) return_message.setTransStatus(Globals::tsApproval);
         is_error = false;
         break;
      }
      if(observer) observer->runOnListen(counter);
      Sleep(Globals::INTERVAL);
      }
      if(is_error) throw ECRTimeOutException();

}
//---------------------------------------------------------------------------
void CommunicationSerial::readFromSerial(AnsiString& serial_response)
{
  if(serial_port->isConnected())
  {
   	unsigned partial_buffer_length(serial_port->inWaiting());
		if(partial_buffer_length >0)
   	{
   		char * partial_buffer =  new char[partial_buffer_length];
      	serial_port->readSerialPort(partial_buffer,partial_buffer_length);
      	serial_response += partial_buffer;
      	delete partial_buffer;
   	}
  }
}
//---------------------------------------------------------------------------
void CommunicationSerial::createMessageFromString(Message& return_message,const Message& close_message, const AnsiString& messages_as_string)
{

	StringContainer messages(Utils::explode(messages_as_string,(char) IO::SerialPort::STX,IO::SerialPort::ETX) );
   AnsiString string_message;
   for(StringContainer::const_iterator iterator(messages.begin()); iterator!=messages.end(); ++iterator)
   {
   	string_message =*iterator;
      string_message = string_message.SubString(1,string_message.Length() -1);
      char LRC(iterator->operator [](iterator->Length()));
      if(calculateXOR(string_message) == LRC )
      {
      	char ACK(IO::SerialPort::ACK);
         serial_port->writeSerialPort(&ACK,1 );
         string_message = string_message.SubString(2,string_message.Length() -2);
         return_message.setFromString(string_message);

         if(observer) observer->runOnMsg(return_message);

         messages_stack.push_back(return_message);
      }
      else
      {
      	char NAK(IO::SerialPort::NAK);
         serial_port->writeSerialPort(&NAK,1 );
      }
   }
}
//---------------------------------------------------------------------------
void CommunicationSerial::resp(const Message& response_message)
{
		try
		{
			AnsiString string_message(getMessageAsString(response_message));
			if (!serial_port->isConnected())  serial_port->openSerialPort();
			serial_port->writeSerialPort(string_message.c_str(), string_message.Length());
			if (observer) observer->runOnECR(response_message);
		}
		catch (Exception& exc)
		{
			TransStatDescr::m_LastError = "\r\nOryginalny komunikat systemu:\r\n" + exc.Message;
			serial_port->closeSerialPort();
		}
}
//---------------------------------------------------------------------------
AnsiString CommunicationSerial::getMessageAsString(const Message& message_) const
{
   Message message(message_);
	AnsiString string_message( (char) IO::SerialPort::STX);
   string_message += message.getAsString();
   string_message += (char) IO::SerialPort::ETX;
   string_message += (char) calculateXOR(string_message);
	return string_message;
}
//---------------------------------------------------------------------------
unsigned char CommunicationSerial::calculateXOR(const AnsiString& message_as_string) const
{
  unsigned char hash(Hash::SimpleStringXORHashing(message_as_string.c_str(),message_as_string.Length()-1) );
  return hash;
}
//---------------------------------------------------------------------------

