//---------------------------------------------------------------------------

#ifndef itcard_transaction_infos_repositoryH
#define itcard_transaction_infos_repositoryH
#include <system.hpp>
#include <map>
namespace ecr{
   class ItcardTransactionInfosRepository{
   public:
      static ItcardTransactionInfosRepository& instance(void);
      AnsiString get(const unsigned short code)const;
   private:
   	ItcardTransactionInfosRepository(void);
   	ItcardTransactionInfosRepository(const ItcardTransactionInfosRepository&);
      std::map<unsigned short,AnsiString> infos_container;
   };
}
//---------------------------------------------------------------------------
#endif
