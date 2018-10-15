//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_Factories.h"
#include <boost/assign/std/vector.hpp>
#include <boost/assert.hpp>;
#include "ECR_Globals.h"
#include "ECR_Utils.h"
#include "TerminalIndy.h"
#include "ECR_FieldMasks.h"
using namespace std;
using namespace boost::assign;
using namespace ecr;
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
MessageFCTR& MessageFCTR::instance(void)
{
 static MessageFCTR m_M;
 return m_M;
}
//---------------------------------------------------------------------------
MessageFCTR::MessageFCTR(void)
{
 operator[](Globals::miECRHello)    = Message("|2841011|0|||||");
 operator[](Globals::miPOSHello)    = Message("|2840000|0|||99999999|");
 operator[](Globals::miECRStart)    = Message("|2811011|00|000000000000|||||||||");
 operator[](Globals::miECRStartExt) = Message("|2811111|00|000|000000000000|||||||||||||||||||||||||||||||");
 operator[](Globals::miPOSFinish)   = Message("|2810000||||||");
 operator[](Globals::miECRDisp)     = Message("|2821000|01|001|1|");
 operator[](Globals::miECRPrompt)   = Message("|2821211|01|000||");
 operator[](Globals::miPOSPrompt)   = Message("|2820200|01|000||");
}
//---------------------------------------------------------------------------
Message MessageFCTR::get(const Globals::MessID _ID)const
{
 Message _Mess;
 const_iterator _ItF = find(_ID);
 if(_ItF!=end())
 {
  _Mess = _ItF->second;
 }
 return _Mess;
}
//---------------------------------------------------------------------------
FieldMaskFCTR::FieldMaskFCTR(void)
{
 operator[](Globals::fkNull)        =new NullMask();
 operator[](Globals::fkMessID)      =new MessIDMask();
 operator[](Globals::fkTermStatus)  =new TermStatusMask();
 operator[](Globals::fkTermID)      =new TermIDMask();
 operator[](Globals::fkCipher)      =new CipherMask();
 operator[](Globals::fkTransType)   =new TransTypeMask();
 operator[](Globals::fkAmount)      =new AmountMask();
 operator[](Globals::fkCashBack)    =new CashBackMask();
 operator[](Globals::fkCardType)    =new CardTypeMask();
 operator[](Globals::fkTransStatus) =new TransStatusMask();
 operator[](Globals::fkPLN)         =new PLNMask();
 operator[](Globals::fkPPMsg)       =new PPMsgMask();
 operator[](Globals::fkPPMSize)     =new PPMSizeMask();
 operator[](Globals::fkPPMResp)     =new PPMRespMask();
 operator[](Globals::fkTimeOut)     =new TimeOutMask();
 operator[](Globals::fkZero)        =new ZeroMask();
 operator[](Globals::fkProfileId)   =new ProfileIdMask();
 operator[](Globals::fkPromptReq)   =new PromptReqMask();

}
//---------------------------------------------------------------------------
FieldMaskFCTR::~FieldMaskFCTR(void)
{
 iterator _ItB(begin());
 for(_ItB;_ItB != end();++_ItB)
 {
  delete _ItB->second;
 }
}
//---------------------------------------------------------------------------
FieldMaskFCTR& FieldMaskFCTR::instance(void)
{
 static FieldMaskFCTR m_M;
 return m_M;
}
//---------------------------------------------------------------------------
void FieldMaskFCTR::setMessage(Message& _Mess, const AnsiString& _MessStr) const
{
 StringContainer _Fields = Utils::explode(_MessStr);
 Globals::MessID _MI;
 if(_Mess.getMessID() == Globals::miUnknown) _MI = static_cast<Globals::MessID>(_Fields.getAsInt(1));
 else _MI=  _Mess.getMessID();
 MessStructFCTR::const_iterator _Kinds = MessStructFCTR::instance().find(_MI);
 if(_Kinds == MessStructFCTR::instance().end() ) _Kinds = MessStructFCTR::instance().find(Globals::miUnknown);
 FieldKinds::const_iterator _ItB(_Kinds->second.begin());
 const_iterator _ItFM;
 int _Idx(1);
 for(_ItB;_ItB != _Kinds->second.end();++_ItB)
 {
   _ItFM = find(*_ItB);
   if(_ItFM != end() ) _ItFM->second->setMessage(_Mess,_Fields,_Idx);
   ++_Idx;
 }
}
//---------------------------------------------------------------------------
AnsiString FieldMaskFCTR::getAsString(const Message& _Mess) const
{
AnsiString _Res;
 Globals::MessID _MI;
 if(_Mess.getMessID() == Globals::miUnknown) return _Res;
 else _MI=  _Mess.getMessID();
 MessStructFCTR::const_iterator _Kinds = MessStructFCTR::instance().find(_MI);
 FieldKinds::const_iterator _ItB(_Kinds->second.begin());
 const_iterator _ItFM;
 for(_ItB;_ItB != _Kinds->second.end();++_ItB)
 {
   _ItFM = find(*_ItB);
   _Res += _ItFM->second->getAsString(_Mess);
 }
 return _Res;
}
//---------------------------------------------------------------------------
MessStructFCTR::MessStructFCTR(void)
{
 operator[](Globals::miUnknown)  += Globals::fkMessID,
									Globals::fkNull;
 operator[](Globals::miECRHello) += Globals::fkMessID,
									Globals::fkCipher,
									Globals::fkNull,
									Globals::fkNull,
									Globals::fkNull,
									Globals::fkNull,
									Globals::fkNull;
 operator[](Globals::miPOSHello) += Globals::fkMessID,
									Globals::fkTermStatus,
									Globals::fkNull,
									Globals::fkNull,
									Globals::fkTermID;
 operator[](Globals::miECRStart) += Globals::fkMessID,
									Globals::fkTransType,
									Globals::fkAmount,
									Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkNull,
									Globals::fkPLN,Globals::fkNull,Globals::fkNull,Globals::fkNull;
 operator[](Globals::miECRStartExt) += Globals::fkMessID,Globals::fkTransType,Globals::fkZero,Globals::fkAmount,Globals::fkNull,
									   Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkPLN, Globals::fkNull,
									   Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkNull,
									   Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkProfileId,
									   Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkNull,
									   Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkNull,
									   Globals::fkNull,Globals::fkNull,Globals::fkNull,Globals::fkNull;
 operator[](Globals::miPOSFinish)+= Globals::fkMessID,
									Globals::fkNull,
									Globals::fkCardType,
									Globals::fkTransStatus,Globals::fkNull,Globals::fkNull;
 operator[](Globals::miPinPadDisp)+= Globals::fkMessID,
									Globals::fkPPMSize,
									Globals::fkPPMsg,
									Globals::fkNull,Globals::fkPPMResp,Globals::fkTimeOut;
 operator[](Globals::miECRDisp)  += Globals::fkMessID,
 									Globals::fkPPMResp,
									Globals::fkPPMSize,
									Globals::fkPPMsg,
									Globals::fkNull;
 operator[](Globals::miECRPrompt)+= Globals::fkMessID,
									Globals::fkPromptReq,
									Globals::fkPPMSize,
									Globals::fkPPMsg,
									Globals::fkNull;

 operator[](Globals::miPOSPrompt)+= Globals::fkMessID,
									Globals::fkPromptReq,
									Globals::fkPPMSize,
									Globals::fkPPMsg,
									Globals::fkNull;


}
//---------------------------------------------------------------------------
MessStructFCTR& MessStructFCTR::instance(void)
{
 static MessStructFCTR m_M;
 return m_M;
}
//---------------------------------------------------------------------------
TerminalFCTR& TerminalFCTR::instance(void)
{
 static TerminalFCTR m_M;
 return m_M;
}
//---------------------------------------------------------------------------
TerminalFCTR::TerminalFCTR(void)
{
operator[](Globals::tmkIndy)    = new TerminalIndy();
operator[](Globals::tmkWinSock) = NULL;
operator[](Globals::tmkUSB)     = NULL;
operator[](Globals::tmkRS)      = NULL;
}
//---------------------------------------------------------------------------
TerminalFCTR::~TerminalFCTR(void)
{
 for(iterator _ItB(begin()); _ItB!=end();++_ItB)
 {
  delete _ItB->second;
 }
}
//---------------------------------------------------------------------------
ITerminal& TerminalFCTR::get(const Globals::TermKind& _Kind)
{
 iterator _ItF = find(_Kind);
 if(_ItF==end()) throw Exception("B³êdny rodzaj terminala");
 return *(_ItF->second);
}


