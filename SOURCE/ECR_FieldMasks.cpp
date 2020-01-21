//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_FieldMasks.h"
#include "ECR_Message.h"
#include "Globfunc.h"
#include "ECR_Utils.h"
#include "itcard_transaction_infos_repository.h"
#include "itcard_transaction_result_statements_repository.h"
#include <dialogs.hpp>
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
AnsiString NullMask::getAsString(const Message& message, const String& separator) const
{
	return separator;
}

//---------------------------------------------------------------------------
void NullMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
}
//---------------------------------------------------------------------------
AnsiString PostcardMessIDMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	_Res += message.m_MessID;
	return _Res;
}

//---------------------------------------------------------------------------
void PostcardMessIDMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.m_MessID = static_cast<Globals::MessID>(_Source.getAsInt(_Idx));
}

//---------------------------------------------------------------------------
AnsiString ItcardMessIDMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
   char* message_id("  ");
	message_id[0] =  message.m_MessID>>8;
   message_id[1]=   message.m_MessID;
	_Res += message_id;
	return _Res;
}

//---------------------------------------------------------------------------
void ItcardMessIDMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
   AnsiString message_id_as_string(_Source[_Idx]);
   unsigned short message_id(  message_id_as_string[1]<<8 );
   message_id += message_id_as_string[2];
	message.m_MessID = static_cast<Globals::MessID>(message_id);
   message.m_TermID = 1001;
}
//---------------------------------------------------------------------------
AnsiString ItcardMessTokenMask::getAsString(const Message& message, const String& separator) const
{
	return message.getMessageToken();
}

//---------------------------------------------------------------------------
void ItcardMessTokenMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
   AnsiString message_token_as_string(_Source[_Idx]);
   while(message_token_as_string.Length() >1 && message_token_as_string[1] =='0')
   {
    message_token_as_string = message_token_as_string.SubString(2,message_token_as_string.Length()-1 );
   }
   message.message_token = message_token_as_string;
}

//---------------------------------------------------------------------------
AnsiString TermStatusMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	_Res += message.m_TermStatus;
	return _Res;
}

//---------------------------------------------------------------------------
void TermStatusMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.m_TermStatus = _Source.getAsInt(_Idx);
}

//---------------------------------------------------------------------------
AnsiString TermIDMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	_Res += message.m_TermID;
	return _Res;
}

//---------------------------------------------------------------------------
void TermIDMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.m_TermID =_Source.getAsInt(5);
}

//---------------------------------------------------------------------------
AnsiString EcrIDMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	_Res += message.ecr_ID;
	return _Res;
}

//---------------------------------------------------------------------------
void EcrIDMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.doc_ID =_Source[_Idx];
}

AnsiString DocIDMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	_Res += message.doc_ID;
	return _Res;
}

//---------------------------------------------------------------------------
void DocIDMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.doc_ID =_Source[_Idx];
}

//---------------------------------------------------------------------------
AnsiString CipherMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	_Res += 0;
	return _Res;
}

//---------------------------------------------------------------------------
void CipherMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{;
}

//---------------------------------------------------------------------------
AnsiString TransTypeMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	_Res += FormatFloat("00", (int)message.getTransKind());
	return _Res;
}

//---------------------------------------------------------------------------
void TransTypeMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.setTransKind(static_cast<Globals::TransKind>(_Source.getAsInt(_Idx)));
}

//---------------------------------------------------------------------------
AnsiString ItcardTransTypeMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
   char  trans_kind_as_char(static_cast<char>(message.getTransKind()));
	_Res += trans_kind_as_char;
	return _Res;
}

//---------------------------------------------------------------------------
void ItcardTransTypeMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
   AnsiString trans_kind_as_string(_Source[_Idx]);
   if(!trans_kind_as_string.IsEmpty())
   {
    unsigned short trans_kind_as_int( trans_kind_as_string[1]);
	 message.setTransKind(static_cast<Globals::TransKind>(trans_kind_as_int) );
   }
}

//---------------------------------------------------------------------------
AnsiString AmountMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	_Res += FormatFloat("000000000000", message.getAmount() * 100);
	return _Res;
}

//---------------------------------------------------------------------------
void AmountMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.setAmount(_Source.getAsInt(_Idx) / 100);
}

//---------------------------------------------------------------------------
AnsiString CashBackMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res;
}

//---------------------------------------------------------------------------
void CashBackMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	//_Mes =;
}

//---------------------------------------------------------------------------
AnsiString CardTypeMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res;
}

//---------------------------------------------------------------------------
void CardTypeMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.setCardType(_Source.getAsInt(_Idx));
}

//---------------------------------------------------------------------------
AnsiString TransStatusMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res;
}

//---------------------------------------------------------------------------
void TransStatusMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.setTransStatus(static_cast<Globals::TransStat>(_Source.getAsInt(_Idx)));
}

//---------------------------------------------------------------------------
AnsiString PLNMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + 985;
}

//---------------------------------------------------------------------------
void PLNMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{

}

//---------------------------------------------------------------------------
AnsiString CurrencyCodeMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + AnsiString("PLN");
}

//---------------------------------------------------------------------------
void CurrencyCodeMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{

}

//---------------------------------------------------------------------------
AnsiString PPMsgMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + message.getPinPadMsg();
}

//---------------------------------------------------------------------------
void PPMsgMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	if (_Source.size() > _Idx)
	{
		message.setPinPadMsg(_Source[_Idx]);
	}
}

//---------------------------------------------------------------------------
AnsiString PPMSizeMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + FormatFloat("000", message.getPPMSize());
}

//---------------------------------------------------------------------------
void PPMSizeMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	if (_Source.size() > _Idx)
	{
		message.setPPMSize(_Source.getAsInt(_Idx));
	}
}

//---------------------------------------------------------------------------
AnsiString PPMRespMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + FormatFloat("00", static_cast<double>(message.getRespKind()));
}

//---------------------------------------------------------------------------
void PPMRespMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	if (_Source.size() > _Idx)
	{
		message.setRespKind(static_cast<Globals::RespKind>(_Source.getAsInt(_Idx)));
	}
}

//---------------------------------------------------------------------------
AnsiString TimeOutMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + message.getTimeOut();
}

//---------------------------------------------------------------------------
void TimeOutMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	if (_Source.size() > _Idx)
	{
		message.setTimeOut(_Source.getAsInt(_Idx));
	}
}

//---------------------------------------------------------------------------
AnsiString TLVBlockLengthMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + message.getTLVBlockLength();
}

//---------------------------------------------------------------------------
void TLVBlockLengthMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
}

//---------------------------------------------------------------------------
AnsiString TLVBlockMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + message.getTLVBlock();
}

//---------------------------------------------------------------------------
void TLVBlockMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
}

//---------------------------------------------------------------------------
AnsiString ZeroMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + "000";
}

//---------------------------------------------------------------------------
void ZeroMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
}

//---------------------------------------------------------------------------
AnsiString OneMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + "1";
}

//---------------------------------------------------------------------------
void OneMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
}

//---------------------------------------------------------------------------
AnsiString ProfileIdMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + FormatFloat("00", static_cast<double>(message.getProfileId()));
}

//---------------------------------------------------------------------------
void ProfileIdMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.setProfileId(_Source.getAsInt(_Idx));
}

//---------------------------------------------------------------------------
AnsiString PromptReqMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res(separator);
	return _Res + FormatFloat("00", message.getPromptReq());
}

//---------------------------------------------------------------------------
void PromptReqMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.setPromptReq(static_cast<Globals::PromptReq>(_Source.getAsInt(_Idx)));
}
//---------------------------------------------------------------------------
AnsiString ItcardTransInfoMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res("");
	return _Res;
}

//---------------------------------------------------------------------------
void ItcardTransInfoMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
	message.setPinPadMsg(ItcardTransactionInfosRepository::instance().get(_Source[_Idx].ToInt()) );
}
//---------------------------------------------------------------------------
AnsiString ItcardTransResultInfoMask::getAsString(const Message& message, const String& separator) const
{
	AnsiString _Res("");
	return _Res;
}

//---------------------------------------------------------------------------
void ItcardTransResultInfoMask::setMessage(Message& message, const StringContainer& _Source, const unsigned _Idx)
{
   unsigned short result_code( _Source[_Idx].ToInt() );
	message.setPinPadMsg(ItcardTransactionResultStatementsRepository::instance().get(result_code) );
   message.setTransStatus(result_code ==0 ? Globals::tsApproval : Globals::tsTransAbort );

}
//---------------------------------------------------------------------------
