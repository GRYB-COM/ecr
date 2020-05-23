//---------------------------------------------------------------------------
#pragma hdrstop
#include "TerminalIndy.h"
#include <IdTCPClient.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "ECR_Message.h"
#include <IdGlobal.hpp>
#include "ECR_Factories.h"
#include "ECR_IObserver.h"
#include "ECR_Exceptions.h"
#include "ECR_TransStatDescr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace ecr;

//---------------------------------------------------------------------------
TerminalIndy::TerminalIndy(void) : m_Obs(NULL)
{
	m_Client = new Idtcpclient::TIdTCPClient(NULL);
	//m_Timer  = new Vcl::Extctrls::TTimer(NULL);
	//m_Timer->Interval= Globals::INTERVAL;
	////m_Timer->OnTimer = listen;
}

//---------------------------------------------------------------------------
TerminalIndy::~TerminalIndy(void)
{
	delete m_Client;
	//delete m_Timer;
}

//---------------------------------------------------------------------------
void TerminalIndy::prepare(const Message& _CloseMess)
{
	m_Client->Host = m_Pars.Host;
	m_Client->Port = m_Pars.Port;
	m_Client->ConnectTimeout = Globals::TIME_C;
	m_Stack.clear();
	m_CloseMess = _CloseMess;
}

//---------------------------------------------------------------------------
Message TerminalIndy::send(const Message& __Mess, const Message& _CloseMess)
{
	try
	{
		try
		{
			Message _Mess(__Mess);
			prepare(_CloseMess);
			TIdBytes _Buff(getMessAsBytes(_Mess));
			m_Client->Disconnect(); //connected wywala³o 10053
			try
			{
				m_Client->Connect();
			}
			catch (EIdAlreadyConnected& exc)
			{
				if (m_Client->Socket)
					m_Client->Socket->Close();
				if (m_Client->IOHandler)
					m_Client->IOHandler->Close();
				if (m_Client->Socket && !m_Client->Socket->Opened)
					m_Client->Socket->Open();
				if (m_Client->IOHandler && !m_Client->IOHandler->Opened)
					m_Client->IOHandler->Open();

			}
			m_Client->IOHandler->Write(_Buff, _Buff.Length);
			if (m_Obs)
				m_Obs->runOnECR(_Mess);
			//m_Timer->Enabled = true;
			m_Size =0;
			m_MessStr="";
			bool _Err(true);
			int _TimeOut(m_CloseMess.getTimeOut());
			if (_TimeOut < 1)
				_TimeOut = Globals::TIME_B;
			for (int _Counter=0; _Counter < _TimeOut; _Counter += Globals::INTERVAL)
			{
				listen(_Counter);
				Sleep(Globals::INTERVAL);
				Application->ProcessMessages();
				if (m_Mess.getMessID() == m_CloseMess.getMessID())
				{
					_Err=false;
					break;
				}
			}
			if (_Err)
				throw ECRTimeOutException();
		}
		catch (ECRException& exc)
		{
			m_Mess.clear();
			m_Mess.setTransStatus(Globals::tsConnErr);
			TransStatDescr::m_LastError = "\r\nOryginalny komunikat systemu:\r\n" + exc.getDetails();
		}
		catch (Exception& exc)
		{
			m_Mess.clear();
			m_Mess.setTransStatus(Globals::tsConnErr);
			TransStatDescr::m_LastError = "\r\nOryginalny komunikat systemu:\r\n" + exc.Message;
		}
	}
	__finally
	{
		m_Client->Disconnect(); //connected wywala³o 10053
		//m_Timer->Enabled=false;
		m_MessStr="";

		m_Size=0;
	}
	return m_Mess;
}

//---------------------------------------------------------------------------
void TerminalIndy::resp(const Message& __Mess)
{
	try
	{
		try
		{
			Message _Mess(__Mess);
			//m_Timer->Enabled = false;
			TIdBytes _Buff(getMessAsBytes(_Mess));
			if (!m_Client->Connected())
				m_Client->Connect();
			m_Client->IOHandler->Write(_Buff, _Buff.Length);
			if (m_Obs)
				m_Obs->runOnECR(_Mess);
			//m_Timer->Enabled = true;
		}
		catch (EIdException& exc)
		{
			m_Mess.clear();
			m_Mess.setTransStatus(Globals::tsConnErr);
			TransStatDescr::m_LastError = "\r\nOryginalny komunikat systemu:\r\n" + exc.Message;
			m_Client->Disconnect();
			//m_Timer->Enabled=false;
		}
	}
	__finally
	{
		m_MessStr="";
		m_Size=0;
	}
}

//---------------------------------------------------------------------------
TIdBytes TerminalIndy::getMessAsBytes(Message& _Mess)
{
	AnsiString _BuffStr = _Mess.getAsString();
	unsigned short _Len = _BuffStr.Length();
	TIdBytes _Buff, _BuffSize;
	_Buff.Length= _Len + 2;
	_BuffSize.Length=2;
	CopyTIdShort(_Len, _BuffSize, 0);
	_Buff[0]=_BuffSize[1];
	_Buff[1]=_BuffSize[0];
	CopyTIdString(_BuffStr, _Buff, 2);

	return _Buff;
}

//---------------------------------------------------------------------------
void TerminalIndy::listen(int& _Counter)
{
	try
	{
		if (m_Client->Connected() && m_Client->IOHandler)
		{
			if (m_Client->IOHandler->InputBufferIsEmpty())
			{
				m_Client->IOHandler->CheckForDataOnSource(10);
				m_Client->IOHandler->CheckForDisconnect();
			}
			if (!m_Client->IOHandler->InputBufferIsEmpty())
			{
				char _Byte;
            wchar_t * test;
				TIdBytes _BuffSize;
				_BuffSize.Length=2;
				char _B;
				while (!m_Client->IOHandler->InputBufferIsEmpty())
				{
					_B = m_Client->IOHandler->ReadByte();
					m_MessStr += _B;
					if (m_MessStr.Length() >= 2 && m_Size ==0)
					{
                  test = m_MessStr.c_str();
						_BuffSize[0] = test[1];
						_BuffSize[1] = test[0];
						m_Size =BytesToInt32(_BuffSize, 0);
					}
 					if (static_cast<unsigned short>(m_MessStr.Length()) >= m_Size + 2)
					{
						m_MessStr = m_MessStr.SubString(3, m_MessStr.Length() - 2);
						m_Mess.setFromString(m_MessStr);
						if (m_Obs)
							m_Obs->runOnMsg(m_Mess);
						m_Size=0;
						m_MessStr="";
						m_Stack.push_back(m_Mess);
                  m_MessStr = test;

					}
				}
			}
		}
		if (m_Obs)
			m_Obs->runOnListen(_Counter);
		////m_Timer->Enabled = false;
		Application->ProcessMessages();
	}
	catch (...)
	{
		if (m_Client->Connected())
			m_Client->Disconnect();
		////m_Timer->Enabled=false;
		m_Size=0;
		m_MessStr="";
		throw;
	}
}
//---------------------------------------------------------------------------
