//---------------------------------------------------------------------------
#pragma hdrstop
#include "CommunicationIndy.h"
#include <IdTCPClient.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "ECR_Message.h"
#include <IdGlobal.hpp>
#include "ECR_IObserver.h"
#include "ECR_Exceptions.h"
#include "ECR_TransStatDescr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace ecr;

//---------------------------------------------------------------------------
CommunicationIndy::CommunicationIndy(const Pars& parameters_)
:observer(NULL),
 parameters(parameters_)
{
	indy_tcp_client = new Idtcpclient::TIdTCPClient(NULL);
}

//---------------------------------------------------------------------------
CommunicationIndy::~CommunicationIndy(void)
{
	delete indy_tcp_client;
}
//---------------------------------------------------------------------------
Message CommunicationIndy::send(const Message& message_to_send, const Message& close_message)
{
   Message return_message(close_message);
	try
	{
		try
		{

			prepareTerminal();
         connectToTerminal();
         sendMessageToTerminal(return_message,message_to_send,close_message.getTimeOut(), close_message.getMessID());
		}
		catch (ECRException& exc)
		{
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
		indy_tcp_client->Disconnect(); //connected wywala³o 10053
	}
	return return_message;
}

//---------------------------------------------------------------------------
void CommunicationIndy::prepareTerminal(void)
{
	indy_tcp_client->Host = parameters.Host;
	indy_tcp_client->Port = parameters.Port;
	indy_tcp_client->ConnectTimeout = Globals::TIME_C;
	messages_stack.clear();
}
//---------------------------------------------------------------------------
void CommunicationIndy::connectToTerminal(void)
{
 			indy_tcp_client->Disconnect(); //connected wywala³o 10053
			try
			{
				indy_tcp_client->Connect();
            Sleep(Globals::CONNECTION_WAIT_TIME);
            checkForDisconnect();
         }
         catch(EIdConnClosedGracefully& exc)
         {
            exc.Message = "Terminal nie jest skonfigurowany do pracy z tym komputerem!\nKonieczny kontakt z serwisem.";
            throw;
         }
			catch (EIdAlreadyConnected& exc)
			{
				if (indy_tcp_client->Socket) 		indy_tcp_client->Socket->Close();
				if (indy_tcp_client->IOHandler)  indy_tcp_client->IOHandler->Close();
				if (indy_tcp_client->Socket && !indy_tcp_client->Socket->Opened)  indy_tcp_client->Socket->Open();
				if (indy_tcp_client->IOHandler && !indy_tcp_client->IOHandler->Opened) indy_tcp_client->IOHandler->Open();
			}
}
//---------------------------------------------------------------------------
void CommunicationIndy::checkForDisconnect(void)
{
	indy_tcp_client->IOHandler->CheckForDataOnSource(10);
	indy_tcp_client->IOHandler->CheckForDisconnect(true);
}
//---------------------------------------------------------------------------
void CommunicationIndy::sendMessageToTerminal(Message& return_message, const Message& message_to_send, const int time_out_, const Globals::MessID expected_return_message_ID)
{
  TIdBytes _Buff(getMessAsBytes(message_to_send));
  indy_tcp_client->IOHandler->Write(_Buff, _Buff.Length);

  if (observer) observer->runOnECR(message_to_send);

  int time_out(time_out_);
  if (time_out < 1) time_out = Globals::TIME_B;
  bool error_flag(true);
  for (int time_counter=0; time_counter < time_out; time_counter += Globals::INTERVAL)
  {
    listen(return_message,time_counter);
    if (return_message.getMessID() == expected_return_message_ID &&
    			(return_message.getTransStatus() == Globals::tsApproval || return_message.getTransStatus() == Globals::tsTransAbort)
       )
	 {
		error_flag=false;
		break;
	 }
    sleep();
  }
  if (error_flag)  throw ECRTimeOutException();
}
//---------------------------------------------------------------------------
TIdBytes CommunicationIndy::getMessAsBytes(const Message& message)
{
	AnsiString message_as_string = message.getAsString();
	unsigned short frame_length = message_as_string.Length();
	TIdBytes indy_bytes_frame_buffer, indy_bytes_frame_length_buffer;
	indy_bytes_frame_buffer.Length= frame_length + 2;
	indy_bytes_frame_length_buffer.Length=2;
	CopyTIdInt16(frame_length, indy_bytes_frame_length_buffer, 0);
	indy_bytes_frame_buffer[0]=indy_bytes_frame_length_buffer[1];
	indy_bytes_frame_buffer[1]=indy_bytes_frame_length_buffer[0];
	CopyTIdString(message_as_string, indy_bytes_frame_buffer, 2);

	return indy_bytes_frame_buffer;
}

//---------------------------------------------------------------------------
void CommunicationIndy::listen(Message& return_message,int& attempts_counter)
{
	try
	{
		if (checkInputBuffer())
		{
         AnsiString frame;
        int frame_size(0);
         bool message_readed_flag(false);
			while (!indy_tcp_client->IOHandler->InputBufferIsEmpty())
			{
            message_readed_flag = readByte(frame,frame_size);
            if(message_readed_flag)
            {
						return_message.setFromString(frame);
						if (observer) observer->runOnMsg(return_message);
						frame_size=0;
						frame="";
						messages_stack.push_back(return_message);

            }
         }
         if(message_readed_flag && return_message.getTransStatus()== Globals::tsUnknown) return_message.setTransStatus(Globals::tsApproval);
      }
      if (observer) observer->runOnListen(attempts_counter);
		Application->ProcessMessages();
	}
	catch (...)
	{
		if (indy_tcp_client->Connected()) indy_tcp_client->Disconnect();
		throw;
	}
}
//---------------------------------------------------------------------------
bool CommunicationIndy::checkInputBuffer(void)
{
   bool buffer_filled_flag(false);
	if (indy_tcp_client->Connected() )
   {
   	if(indy_tcp_client->IOHandler)
		{
	  		if (indy_tcp_client->IOHandler->InputBufferIsEmpty()) checkForDisconnect();
			buffer_filled_flag = !indy_tcp_client->IOHandler->InputBufferIsEmpty();
      }
      else buffer_filled_flag =false;
   }
 return buffer_filled_flag;
}
//---------------------------------------------------------------------------
bool CommunicationIndy::readByte(AnsiString& frame, int& frame_size)
{
 bool message_readed_flag(false);
 char readed_byte(indy_tcp_client->IOHandler->ReadByte());
 frame += readed_byte;
 if (frame.Length() >= 2 && frame_size ==0)
 {
	TIdBytes buffer_for_frame_size;
	buffer_for_frame_size.Length=2;
	buffer_for_frame_size[0] = frame.c_str()[1];
	buffer_for_frame_size[1] = frame.c_str()[0];
	frame_size =BytesToShort(buffer_for_frame_size);
 }
 else if (static_cast<unsigned>(frame.Length()) >= frame_size + 2)
 {
  	frame = frame.SubString(3, frame.Length() - 2);
   message_readed_flag =true;
 }
 return message_readed_flag;
}
//---------------------------------------------------------------------------
void CommunicationIndy::sleep(void)
{
 	 Sleep(Globals::INTERVAL);
	 Application->ProcessMessages();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void CommunicationIndy::resp(const Message& response_message_)
{
		try
		{
			Message response_message(response_message_);
			TIdBytes _Buff(getMessAsBytes(response_message));

			if (!indy_tcp_client->Connected()) indy_tcp_client->Connect();
			indy_tcp_client->IOHandler->Write(_Buff, _Buff.Length);

			if (observer) observer->runOnECR(response_message);
		}
		catch (EIdException& exc)
		{
			TransStatDescr::m_LastError = "\r\nOryginalny komunikat systemu:\r\n" + exc.Message;
			indy_tcp_client->Disconnect();
         throw;
      }

}
//---------------------------------------------------------------------------
