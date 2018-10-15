//---------------------------------------------------------------------------
#ifndef ECR_FieldMasksH
#define ECR_FieldMasksH
#include "ECR_Globals.h"
#include "ECR_IFieldMask.h"
namespace ecr{
class NullMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class MessIDMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class TermStatusMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class TermIDMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class CipherMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class TransTypeMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class AmountMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class CashBackMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class CardTypeMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class TransStatusMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class PLNMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};

class PPMsgMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};

class PPMSizeMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};

class PPMRespMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};

class TimeOutMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};

class ZeroMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};
class ProfileIdMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};

class PromptReqMask: public IFieldMask{
public:
	//INTERFEJS
	  virtual AnsiString getAsString(const Message& _Mess)const;
	  virtual void       setMessage(Message& _Mess, const StringContainer&,const unsigned);
};

}//endnmspc
//---------------------------------------------------------------------------
#endif
