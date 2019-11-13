//---------------------------------------------------------------------------

#pragma hdrstop

#include "itcard_transaction_result_statements_repository.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
ItcardTransactionResultStatementsRepository& ItcardTransactionResultStatementsRepository::instance(void)
{
 static ItcardTransactionResultStatementsRepository repo;
 return repo;
}
//---------------------------------------------------------------------------
ItcardTransactionResultStatementsRepository::ItcardTransactionResultStatementsRepository(void)
{


   infos_container[0]  = "Transakcja zaakceptowana";
   infos_container[1]  = "B³êdne dane karty";
   infos_container[2]  = "Odmowa z karty";
   infos_container[3]  = "Brak karty";
   infos_container[4]  = "Anulowano";
   infos_container[5]  = "B³¹d terminala/pinpada";
   infos_container[6]  = "Rozliczenie nieudane";
   infos_container[7]  = "Odmowa online";
   infos_container[8]  = "B³¹d otwarcia po³¹czenia";
   infos_container[9]  = "B³¹d parsowania odpowiedzi";
   infos_container[10] = "Wyczerpane próby po³¹czenia";
   infos_container[11] = "Automatyczne uniewa¿nienie";
   infos_container[12] = "Rêczne uniewa¿nienie";
   infos_container[13] = "Restart";
   infos_container[14] = "B³¹d dosy³ania";
   infos_container[15] = "Karta odrzucona";
   infos_container[16] = "Nierozliczone transakcje";
   infos_container[17] = "Transakcja niedozwolona";
   infos_container[255] = "Terminal zajêty";
}
//---------------------------------------------------------------------------
AnsiString ItcardTransactionResultStatementsRepository::get(const unsigned short code)const
{
 AnsiString info;
 std::map<unsigned short,AnsiString>::const_iterator iterator(infos_container.find(code));
 if(iterator!=infos_container.end()) info= iterator->second;
 return info;
}
