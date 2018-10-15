//---------------------------------------------------------------------------

#ifndef TerminalIndyH
#define TerminalIndyH
#include "ECR_ITerminal.h"
#include "ECR_Pars.h"
#include "ECR_Message.h"
#include <IdGlobal.hpp>
#include <vector>
namespace Idtcpclient{ class TIdTCPClient; }

namespace Vcl{ namespace Extctrls{ class TTimer; } }
namespace ecr{
class IObserver;
class TerminalIndy :public ITerminal{
public:
	//INTERFEJS
	  virtual void    setPars(const Pars& _Pars) { m_Pars = _Pars;}
	  virtual void    setObserver(IObserver& _Obs) { m_Obs = &_Obs;}
	  virtual void    clearObserver(void)   { m_Obs = NULL;}
	  virtual Message send(const Message& _Mess, const Message& _CloseMess);
	  virtual void    resp(const Message& _Mess);
	//KONSTRUKTOR DESTRUKTOR
	  TerminalIndy(void);
	  virtual ~TerminalIndy(void);

private:
	//ATRYBUTY
	  Pars        m_Pars;
	  IObserver * m_Obs;
	  Message     m_Mess;
	  String      m_MessStr;
	  Message     m_CloseMess;
	  std::vector<Message> m_Stack;
	  unsigned  short m_Size;
	//NARZÊDZIA
	  Idtcpclient::TIdTCPClient * m_Client;
	  //Vcl::Extctrls::TTimer     * m_Timer;
   //METODY POMOCNICZE
	 void prepare( const Message& _CloseMess);
	 Idglobal::TIdBytes getMessAsBytes(Message& _Mess);
	 void listen(int& _Counter);
};
}
//---------------------------------------------------------------------------
#endif
