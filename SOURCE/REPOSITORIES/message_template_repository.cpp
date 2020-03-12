//---------------------------------------------------------------------------
#pragma hdrstop
#include "message_template_repository.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
MessageTemplateRepository::MessageTemplateRepository(void)
{
	operator[](Globals::miECRPostcardHello)    = String("|2841011|0|||||");
	operator[](Globals::miECRPostcardHelloExt) = String("|2841111|0|||||1|30313138|1C1000164B41534120552E20492E20494E464F2D53595354454D1C110006323032302E311C120013323032302F30312F30352031363A30303A30301C19000730303436303130|");
	operator[](Globals::miPOSPostcardHello)    = String("|2840000|0|||99999999|");
	operator[](Globals::miPOSPostcardHelloExt) = String("|2840100|0|||99999999|");
	operator[](Globals::miECRPostcardStart)    = String("|2811011|00|000000000000|||||||||");
	operator[](Globals::miECRPostcardStartExt) = String("|2811111|00|000|000000000000|||||||||||||||||||||||||||||||");
	operator[](Globals::miPOSPostcardFinish)   = String("|2810000||||||");
	operator[](Globals::miECRPostcardDisp)     = String("|2821000|01|001|1|");
	operator[](Globals::miECRPostcardPrompt)   = String("|2821211|01|000||");
	operator[](Globals::miPOSPostcardPrompt)   = String("|2820200|01|000||");

   operator[](Globals::miECRItcardHello)      = String( "\x1C""T1""\x1C"" \x1C"" \x1C");
   operator[](Globals::miPOSItcardHello)      = String( "\x1C""T2""\x1C"" \x1C"" \x1C");
   operator[](Globals::miECRItcardSale)       = String( "\x1C""S1""\x1C""S\x1C""kasa Szczebrzeszyn\x1C""k103/1/2019\x1C""100\x1C""100\x1C""0\x1C""PLN\x1C");
   operator[](Globals::miPOSItcardSale)       = String( "\x1C""S2""\x1C""0\x1C""0\x1C");
   operator[](Globals::miECRItcardPars)       = String( "\x1C""D4""\x1C"" \x1C"" \x1C");
   operator[](Globals::miPOSItcardPars)       = String( "\x1C""D5""\x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C"" \x1C");

}
//---------------------------------------------------------------------------
String MessageTemplateRepository::get(const Globals::MessID _ID) const
{
	String _Mess;
	const_iterator _ItF = find(_ID);
	if (_ItF != end())
	{
		_Mess = _ItF->second;
	}
	return _Mess;
}

//---------------------------------------------------------------------------
