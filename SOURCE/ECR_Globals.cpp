//---------------------------------------------------------------------------

#pragma hdrstop

#include "ECR_Globals.h"
#include "ECR_TransStatDescr.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
const AnsiString Globals::TCPIP_POSTCARD_SEPARATOR("|");
const AnsiString Globals::RS_ITCARD_SEPARATOR("\x1C");
const unsigned short Globals::TIME_A(5000);
const unsigned Globals::TIME_B(120000);
const unsigned Globals::TIME_ITCARD_B(60000);
const unsigned short Globals::TIME_C(15000);
const unsigned short Globals::INTERVAL(100);
const unsigned       Globals::TOKEN_RANGE(9999);
const String			Globals::GENERATE_TOKEN("");
const String			Globals::DEFAULT_TOKEN("000001");
const unsigned short Globals::SEND_ATTEMPT_TIMES(3);
const unsigned short Globals::CONFIRMATION_WAIT_TIME(3000);
const unsigned short Globals::POSTCARD_MESSAGE_ID_FRAME_POSITION(1);
const unsigned short Globals::ITCARD_MESSAGE_ID_FRAME_POSITION(1);

//---------------------------------------------------------------------------
String Globals::getTransStatDescr(const TransStat& _Stat)
{
	return ecr::TransStatDescr::instance().get(_Stat);
}
