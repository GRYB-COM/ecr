//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_Message.h"
#include "ECR_Factories.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
Message::Message(void)
{
 clear();
}
//---------------------------------------------------------------------------
void Message::clear(void)
{
 m_MessID =Globals::miUnknown;
 m_TermStatus =-1;
 m_TermID =-1;
 m_Amount =0.0;
 m_TransKind=Globals::tkUnknown;
 m_CardType=-1;
 m_TransStatus = Globals::tsUnknown;
 m_RawMess="";
 m_PinPadMsg="";
 m_PPMSize=-1;
 m_RespKind = Globals::rkUnknown;
 m_TimeOut=-1;
 m_ProfileId=-1;
 m_PromptReq=Globals::prUnknown;

}
//---------------------------------------------------------------------------
Message::Message(const AnsiString& _Mess)
{
 setFromString(_Mess);
}
//---------------------------------------------------------------------------
AnsiString Message::getAsString(void)
{
 m_RawMess = FieldMaskFCTR::instance().getAsString(*this);
 return m_RawMess;
}
//---------------------------------------------------------------------------
void Message::setFromString(const AnsiString& _Mess)
{
 clear();

 m_RawMess = _Mess;
 FieldMaskFCTR::instance().setMessage(*this,_Mess);
}
//---------------------------------------------------------------------------

