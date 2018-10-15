//---------------------------------------------------------------------------

#ifndef ECR_TransStatDescrH
#define ECR_TransStatDescrH
#include <system.hpp>
#include "ECR_Globals.h"
#include <map>
namespace ecr{
class TerminalIndy;
class TransStatDescr{
public:
		//ITERFEJS
		  static TransStatDescr & instance();
		  String           get(const Globals::TransStat& _Stat);
		//DESTRUKTOR
		  ~TransStatDescr(void){}
private:
		//KONSTRUKTORY OPERATORY
		  TransStatDescr(void);
		  TransStatDescr(const TransStatDescr&);
		  TransStatDescr& operator=(const TransStatDescr&);
		//SK£ADOWE
		  std::map<Globals::TransStat,String> m_Cont;
		  static String m_LastError;
  friend TerminalIndy;
};
}
//---------------------------------------------------------------------------
#endif
