//---------------------------------------------------------------------------
#pragma hdrstop
#include "itcard_transaction_infos_repository.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
ItcardTransactionInfosRepository& ItcardTransactionInfosRepository::instance(void)
{
 static ItcardTransactionInfosRepository repo;
 return repo;
}
//---------------------------------------------------------------------------
ItcardTransactionInfosRepository::ItcardTransactionInfosRepository(void)
{
   infos_container[20]  = "Oczekiwanie na dane karty p�atniczej";
   infos_container[30]  = "Sprawdzanie zgodno�ci numeru karty";
   infos_container[40]  = "Oczekiwanie na identyfikator sprzedawcy";
   infos_container[50]  = "Weryfikacja has�a Szefa";
   infos_container[60]  = "Oczekiwanie na wprowadzenie kwoty transakcji";
   infos_container[65]  = "Oczekiwanie na wprowadzenie kwoty cashback";
   infos_container[70]  = "Oczekiwanie na poprzedni� kwot� transakcji";
   infos_container[80]  = "Oczekiwanie na poprzedni kod autoryzacji";
   infos_container[90]  = "Oczekiwanie na wprowadzenie kodu PIN";
   infos_container[100] = "��czenie z hostem autoryzacyjnym";
   infos_container[101] = "��czenie z hostem autoryzacyjnym � pr�ba 2";
   infos_container[102] = "��czenie z hostem autoryzacyjnym � pr�ba 3";
   infos_container[110] = "Autoryzacja g�osowa";
   infos_container[120] = "Sprawdzanie podpisu klienta";
   infos_container[130] = "Sprawdzanie to�samo�ci klienta";
   infos_container[140] = "Drukowanie potwierdzenia (pozytywna autoryzacja)";
   infos_container[155] = "Drukowanie kopii potwierdzenia";
   infos_container[150] = "Drukowanie potwierdzenia (odmowa lub b��d)";
   infos_container[180] = "Uniewa�nienie bie��cej transakcji";
   infos_container[190] = "Drukowanie potwierdzenia uniewa�nienia";
}
//---------------------------------------------------------------------------
AnsiString ItcardTransactionInfosRepository::get(const unsigned short code)const
{
 AnsiString info;
 std::map<unsigned short,AnsiString>::const_iterator iterator(infos_container.find(code));
 if(iterator!=infos_container.end()) info= iterator->second;
 return info;
}
