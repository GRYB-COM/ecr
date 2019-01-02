//---------------------------------------------------------------------------

#pragma hdrstop

#include "ECR_Utils.h"
#include "ECR_Globals.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;

//---------------------------------------------------------------------------
int StringContainer::getAsInt(const unsigned _Idx, const int _DefValue) const
{
	int _Res(_DefValue);
	if (size() > _Idx)
	{
		_Res= at(_Idx).ToIntDef(_DefValue);
	}
	return _Res;
}

//---------------------------------------------------------------------------
StringContainer Utils::explode(const AnsiString & _Source)
{
	StringContainer _Res;
	AnsiString _Buff;
	char _Sign;
	for (int i=1; i <= _Source.Length(); i++)
	{
		_Sign = _Source[i];
		if (Globals::SEPARATOR.Pos(_Sign) > 0)
		{
			_Res.push_back(_Buff);
			_Buff="";
		}
		else
		{
			_Buff += _Sign;
		}
	}
	if (!_Buff.IsEmpty())
	{
		_Res.push_back(_Buff);
	}
	return _Res;
}
//---------------------------------------------------------------------------
