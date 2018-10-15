//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_TransStatDescr.h"
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
String TransStatDescr::m_LastError;

//---------------------------------------------------------------------------
TransStatDescr::TransStatDescr(void)
{
 m_Cont[Globals::tsConnErr]     ="Brak komunikacji z terminalem.";
 m_Cont[Globals::tsUnknown]    ="Terminal zwróci³ kod b³êdu: %d.";
 m_Cont[Globals::tsApproval]   ="Transakcja zosta³a zaakceptowana.";
 m_Cont[Globals::tsRefusal]    ="Transakcja zosta³a odrzucona przez terminal. ";
 m_Cont[Globals::tsTransAbort] ="Operacja zosta³a anulowana b¹dŸ przekroczony zosta³ dopuszczalny czas transakcji.";
 m_Cont[Globals::tsMultiMerchIncorrect] ="Transakcja zosta³a odrzucona z powodu b³êdnej konfiguracji profili sprzedawców.";
 }
 //---------------------------------------------------------------------------
TransStatDescr& TransStatDescr::instance(void)
{
 static TransStatDescr m_M;
 return  m_M;
}
//---------------------------------------------------------------------------
String TransStatDescr::get(const Globals::TransStat& _Stat)
{
 String _Res;
 Globals::TransStat _St(_Stat);
 if(m_Cont.find(_St) == m_Cont.end()) _St=Globals::tsUnknown;
 _Res = m_Cont[_St];
 if(_St ==Globals::tsUnknown)
 {
  _Res = Format(_Res,ARRAYOFCONST(((int)_Stat)));
 }
 else if(_St ==Globals::tsConnErr && !m_LastError.IsEmpty())
 {
  _Res += m_LastError;
 }
 return _Res;
}

