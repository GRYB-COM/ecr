//---------------------------------------------------------------------------
#ifndef ECR_ExceptionsH
#define ECR_ExceptionsH
#include "MANAGER\is_exceptions.h"
namespace ecr{
class ECRException :public mng::ISException{
public:
ECRException(const AnsiString& _Message) :mng::ISException("B��d komunikacji z terminalem p�atniczym"),m_Details(_Message){}
	  //! Implementuje ISException::getDetails
virtual AnsiString getDetails() const{return m_Details;}
private:
AnsiString m_Details;
};
class ECRTimeOutException :public ECRException{
public:
ECRTimeOutException() :ECRException("Przekroczony czas po��czenia z terminalem"){}
};
class ECRNoConnectionException :public ECRException{
public:
ECRNoConnectionException(const String& _Msg) :ECRException(_Msg){}
ECRNoConnectionException() :ECRException("Brak po��cznia po��czenia z terminalem"){}
};
class ECRNoProfileListException :public ECRException{
public:
ECRNoProfileListException() :ECRException("Terminal zwr�ci� pust� list� profili. Prosz� sprawdzi� ustawienie us�ugi Multiservice"){}
};
}
//---------------------------------------------------------------------------
#endif
