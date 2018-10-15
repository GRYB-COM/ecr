//---------------------------------------------------------------------------
#ifndef ECR_ExceptionsH
#define ECR_ExceptionsH
#include "MANAGER\is_exceptions.h"
namespace ecr{
class ECRException :public mng::ISException{
public:
ECRException(const AnsiString& _Message) :mng::ISException("B³¹d komunikacji z terminalem p³atniczym"),m_Details(_Message){}
	  //! Implementuje ISException::getDetails
virtual AnsiString getDetails() const{return m_Details;}
private:
AnsiString m_Details;
};
class ECRTimeOutException :public ECRException{
public:
ECRTimeOutException() :ECRException("Przekroczony czas po³¹czenia z terminalem"){}
};
class ECRNoConnectionException :public ECRException{
public:
ECRNoConnectionException(const String& _Msg) :ECRException(_Msg){}
ECRNoConnectionException() :ECRException("Brak po³¹cznia po³¹czenia z terminalem"){}
};
class ECRNoProfileListException :public ECRException{
public:
ECRNoProfileListException() :ECRException("Terminal zwróci³ pust¹ listê profili. Proszê sprawdziæ ustawienie us³ugi Multiservice"){}
};
}
//---------------------------------------------------------------------------
#endif
