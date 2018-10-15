//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_FieldMasks.h"
#include "ECR_Message.h"
#include "Globfunc.h"
#include "ECR_Utils.h"
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
AnsiString NullMask::getAsString(const Message& _Mess)const
{
 return Globals::SEPARATOR;
}
//---------------------------------------------------------------------------
void NullMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
}
//---------------------------------------------------------------------------
AnsiString MessIDMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
			_Res +=_Mess.m_MessID;
 return _Res;
}
//---------------------------------------------------------------------------
void MessIDMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 _Mess.m_MessID = static_cast<Globals::MessID>( _Source.getAsInt(_Idx) );
}
//---------------------------------------------------------------------------
AnsiString TermStatusMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
			_Res +=_Mess.m_TermStatus;
 return _Res;
}
//---------------------------------------------------------------------------
void TermStatusMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 _Mess.m_TermStatus = _Source.getAsInt(_Idx);
}
//---------------------------------------------------------------------------
AnsiString TermIDMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
			_Res +=_Mess.m_TermID;
 return _Res;
}
//---------------------------------------------------------------------------
void TermIDMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 _Mess.m_TermID =_Source.getAsInt(5);
}
//---------------------------------------------------------------------------
AnsiString CipherMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
			_Res +=0;
 return _Res;
}
//---------------------------------------------------------------------------
void CipherMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
  ;
}
//---------------------------------------------------------------------------
AnsiString TransTypeMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
			_Res +=FormatFloat("00", (int)_Mess.getTransKind());
 return _Res;
}
//---------------------------------------------------------------------------
void TransTypeMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
  _Mess.setTransKind(static_cast<Globals::TransKind>(_Source.getAsInt(_Idx)));
}
//---------------------------------------------------------------------------
AnsiString AmountMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 _Res+= FormatFloat("000000000000",   _Mess.getAmount() * 100 );
 return _Res;
}
//---------------------------------------------------------------------------
void AmountMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 _Mess.setAmount(_Source.getAsInt(_Idx)/100);
}
//---------------------------------------------------------------------------
AnsiString CashBackMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res;
}
//---------------------------------------------------------------------------
void CashBackMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 //_Mes =;
}
//---------------------------------------------------------------------------
AnsiString CardTypeMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res;
}
//---------------------------------------------------------------------------
void CardTypeMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 _Mess.setCardType(_Source.getAsInt(_Idx));
}
//---------------------------------------------------------------------------
AnsiString TransStatusMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res;
}
//---------------------------------------------------------------------------
void TransStatusMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 _Mess.setTransStatus(static_cast<Globals::TransStat>( _Source.getAsInt(_Idx)) );
}
//---------------------------------------------------------------------------
AnsiString PLNMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res +985;
}
//---------------------------------------------------------------------------
void PLNMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{

}
//---------------------------------------------------------------------------
AnsiString PPMsgMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res + _Mess.getPinPadMsg();
}
//---------------------------------------------------------------------------
void PPMsgMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 if(_Source.size() > _Idx)
 {
  _Mess.setPinPadMsg(_Source[_Idx]);
 }
}
//---------------------------------------------------------------------------
AnsiString PPMSizeMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res +FormatFloat("000",  _Mess.getPPMSize() );
}
//---------------------------------------------------------------------------
void PPMSizeMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 if(_Source.size() > _Idx)
 {
  _Mess.setPPMSize(_Source.getAsInt(_Idx) );
 }
}
//---------------------------------------------------------------------------
AnsiString PPMRespMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res + FormatFloat("00", static_cast<double>(_Mess.getRespKind()) );
}
//---------------------------------------------------------------------------
void PPMRespMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 if(_Source.size() > _Idx)
 {
  _Mess.setRespKind(static_cast<Globals::RespKind>( _Source.getAsInt(_Idx) ) );
 }
}
//---------------------------------------------------------------------------
AnsiString TimeOutMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res + _Mess.getTimeOut();
}
//---------------------------------------------------------------------------
void TimeOutMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 if(_Source.size() > _Idx)
 {
  _Mess.setTimeOut(_Source.getAsInt(_Idx) );
 }
}
//---------------------------------------------------------------------------
AnsiString ZeroMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res + "000";
}
//---------------------------------------------------------------------------
void ZeroMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
}
//---------------------------------------------------------------------------
AnsiString ProfileIdMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res + FormatFloat("00", static_cast<double>(_Mess.getProfileId()) );
}
//---------------------------------------------------------------------------
void ProfileIdMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 _Mess.setProfileId(_Source.getAsInt(_Idx) );
}
//---------------------------------------------------------------------------
AnsiString PromptReqMask::getAsString(const Message& _Mess)const
{
 AnsiString _Res(Globals::SEPARATOR);
 return _Res + FormatFloat("00", _Mess.getPromptReq() );
}
//---------------------------------------------------------------------------
void PromptReqMask::setMessage(Message& _Mess, const StringContainer& _Source, const unsigned _Idx)
{
 _Mess.setPromptReq(static_cast<Globals::PromptReq>(_Source.getAsInt(_Idx)) );
}
//---------------------------------------------------------------------------

