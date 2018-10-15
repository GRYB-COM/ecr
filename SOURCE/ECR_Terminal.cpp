//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_Terminal.h"
#include "ECR_Message.h"
#include "ECR_ITerminal.h"
#include "ECR_Factories.h"
#include "ECR_Globals.h"
#include "ECR_Exceptions.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
Terminal::Terminal(void)
:m_TermID(-1)
{
}
//---------------------------------------------------------------------------
Terminal::~Terminal(void)
{
 TerminalFCTR::instance().get(Globals::tmkIndy).clearObserver();
}
//---------------------------------------------------------------------------
ITerminal& Terminal::prepare(void)
{
 ITerminal & _Term= TerminalFCTR::instance().get(Globals::tmkIndy);
 _Term.setPars(m_Pars);
 return _Term;
}
//---------------------------------------------------------------------------
Globals::TransStat Terminal::hello(void)
{
 ITerminal & _Term= prepare();
 Message _Mess  = MessageFCTR::instance().get(Globals::miECRHello);
 Message _CMess = MessageFCTR::instance().get(Globals::miPOSHello);
 _CMess.setTimeOut(Globals::TIME_A);
 _Mess = _Term.send(_Mess,_CMess);
 if(_Mess.getMessID() == Globals::miPOSHello)
 {
  m_TermID = _Mess.getTermID();
  _Mess.setTransStatus(Globals::tsApproval);
 }
 return _Mess.getTransStatus();
}
//---------------------------------------------------------------------------
Globals::TransStat Terminal::sale(const Currency& _Amount,const short _ProfileId, const Globals::TransKind& _Kind)
{
 Globals::TransStat _Res(Globals::tsUnknown);
 Message _Mess  = MessageFCTR::instance().get(_ProfileId >0 ? Globals::miECRStartExt : Globals::miECRStart);
 Message _CMess = MessageFCTR::instance().get(Globals::miPOSFinish);
 try{
  ITerminal & _Term= prepare();
  _Mess.setAmount(_Amount);
  _Mess.setTransKind(_Kind);
  _Mess.setProfileId(_ProfileId);
  _Mess = _Term.send(_Mess,_CMess);
  _Res  = _Mess.getTransStatus();
 }
 catch(...){
  _Res = Globals::tsTransAbort;
 }
 return _Res;
}
//---------------------------------------------------------------------------
Globals::TransStat Terminal::resp(const Globals::RespKind _RK, const unsigned short _Val)
{
 String _Msg(_Val);
 Message _Mess = MessageFCTR::instance().get(Globals::miECRDisp);
 _Mess.setRespKind(_RK);
 _Mess.setPinPadMsg(_Msg);
 _Mess.setPPMSize(_Msg.Length());
 ITerminal & _Term= TerminalFCTR::instance().get(Globals::tmkIndy);
 _Term.resp(_Mess);
 return Globals::tsApproval;
}
//---------------------------------------------------------------------------
void Terminal::setObserver( IObserver& _Obs)
{
 ITerminal & _Term= TerminalFCTR::instance().get(Globals::tmkIndy);
 _Term.setObserver(_Obs);
}
//---------------------------------------------------------------------------
String Terminal::getProfileList(const int _TimeOut)
{
 String   _Res;
 Message _Mess  = MessageFCTR::instance().get(Globals::miECRPrompt);
 Message _CMess = MessageFCTR::instance().get(Globals::miPOSPrompt);
 _CMess.setTimeOut(_TimeOut > Globals::TIME_A ? _TimeOut : Globals::TIME_A );
 ITerminal & _Term= prepare();
 _Mess.setPromptReq(Globals::PromptReq::prProfileList);
 _Mess = _Term.send(_Mess,_CMess);
 if(_Mess.getTransStatus() == Globals::tsConnErr) throw ECRNoConnectionException(Globals::getTransStatDescr(Globals::tsConnErr));

  _Res  = _Mess.getPinPadMsg();
 return _Res;

}


