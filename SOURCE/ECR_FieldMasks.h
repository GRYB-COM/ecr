//---------------------------------------------------------------------------
#ifndef ECR_FieldMasksH
#define ECR_FieldMasksH
#include "ECR_IFieldMask.h"

namespace ecr
{
	class NullMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};


	class PostcardMessIDMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class ItcardMessIDMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class ItcardMessTokenMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class TermStatusMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class TermIDMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class EcrIDMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class DocIDMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class CipherMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class TransTypeMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class ItcardTransTypeMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class AmountMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class CashBackMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class CardTypeMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class TransStatusMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class PLNMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class CurrencyCodeMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class PPMsgMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class PPMSizeMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class PPMRespMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class TLVBlockLengthMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};
	class TLVBlockMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class TimeOutMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class ZeroMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class OneMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class ProfileIdMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class PromptReqMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

	class ItcardTransInfoMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};
	class ItcardTransResultInfoMask : public IFieldMask
	{
	public:
		virtual AnsiString getAsString(const Message& , const String& separator)const ;
		virtual void setMessage(Message& _Mess, const StringContainer&, const unsigned);
	};

}//endnmspc
//---------------------------------------------------------------------------
#endif
