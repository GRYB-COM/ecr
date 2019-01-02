//---------------------------------------------------------------------------

#pragma hdrstop

#include "ECR_Globals.h"
#include "ECR_TransStatDescr.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
const AnsiString Globals::SEPARATOR("|");
const unsigned short Globals::TIME_A(5000);
const unsigned Globals::TIME_B(120000);
const unsigned short Globals::TIME_C(15000);
const unsigned short Globals::INTERVAL(100);

//---------------------------------------------------------------------------
String Globals::getTransStatDescr(const TransStat& _Stat)
{
	return ecr::TransStatDescr::instance().get(_Stat);
}
