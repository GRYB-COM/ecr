//---------------------------------------------------------------------------

#ifndef itcard_transaction_result_statements_repositoryH
#define itcard_transaction_result_statements_repositoryH
#include <system.hpp>
#include <map>
namespace ecr{
   class ItcardTransactionResultStatementsRepository{
   public:
      static ItcardTransactionResultStatementsRepository& instance(void);
      AnsiString get(const unsigned short code)const;
   private:
   	ItcardTransactionResultStatementsRepository(void);
   	ItcardTransactionResultStatementsRepository(const ItcardTransactionResultStatementsRepository&);
      std::map<unsigned short,AnsiString> infos_container;
   };
}
//---------------------------------------------------------------------------
#endif
