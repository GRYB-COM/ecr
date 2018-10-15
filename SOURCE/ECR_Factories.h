//---------------------------------------------------------------------------

#ifndef ECR_FactoriesH
#define ECR_FactoriesH
#include "ECR_Globals.h"
#include "ECR_IFieldMask.h"
#include <map>
#include <vector>
#include "Ecr_Message.h"
//---------------------------------------------------------------------------
namespace ecr{
class FieldMaskFCTR :public std::map<Globals::FieldKind,IFieldMask*>{
public:
	  //SINGLETON
		static FieldMaskFCTR& instance(void);
	  //INTERFEJS
		void       setMessage(Message& _Mess, const AnsiString& _MessStr)const;
		AnsiString getAsString(const Message& _Mess) const;
	  //DESTRUKTOR
		~FieldMaskFCTR(void);
private:
	//KONSTRUKTOR
	  FieldMaskFCTR(void);
};
//---------------------------------------------------------------------------
class MessageFCTR :public std::map<Globals::MessID, Message >{
public:
	  //SINGLETON
		static  MessageFCTR& instance(void);
		Message              get(const Globals::MessID _ID)const;
private:
	//KONSTRUKTOR
	  MessageFCTR(void);
};
//---------------------------------------------------------------------------
typedef std::vector<Globals::FieldKind> FieldKinds;
class MessStructFCTR :public std::map<Globals::MessID, FieldKinds >{
public:
	  //SINGLETON
		static MessStructFCTR& instance(void);
private:
	//KONSTRUKTOR
	  MessStructFCTR(void);
};
//---------------------------------------------------------------------------
class ITerminal;
class TerminalFCTR :public std::map<Globals::TermKind, ITerminal* >{
public:
	  //SINGLETON
		static TerminalFCTR& instance(void);
	  //INTERFEJS
		ITerminal& get(const Globals::TermKind&);
	  //DESTRUKTOR
		~TerminalFCTR(void);
private:
	//KONSTRUKTOR
	  TerminalFCTR(void);
};

}//end
//---------------------------------------------------------------------------
#endif
