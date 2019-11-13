//---------------------------------------------------------------------------

#pragma hdrstop

#include "ECR_Utils.h"
#include "ECR_Globals.h"
#include "ECR_Pars.h"
#include <SysUtils.hpp>
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
StringContainer Utils::explode(const AnsiString & _Source,const AnsiString& separator)
{
	StringContainer _Res;
	AnsiString _Buff;
	char _Sign;
	for (int i=1; i <= _Source.Length(); i++)
	{
		_Sign = _Source[i];
		if (separator.Pos(_Sign) > 0)
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
StringContainer Utils::explode(const AnsiString & _Source,const char start_separator,const char end_separator )
{
	StringContainer _Res;
	AnsiString _Buff;
	char _Sign;
   bool in_frame(false);
	for (int i=1; i <= _Source.Length(); i++)
	{
		_Sign = _Source[i];
		if (_Sign == start_separator)
		{
        _Buff +=_Sign;
        in_frame=true;
        continue;
		}
		else if(_Sign == end_separator)
		{
         _Buff += _Sign;
         if(_Source.Length()<i+1) _Buff += '~';
			else _Buff += _Source[i+1];
         _Res.push_back(_Buff);
         _Buff="";
         in_frame=false;
         continue;

		}
      else if(in_frame) _Buff += _Sign;
	}
	return _Res;
}
//---------------------------------------------------------------------------
AnsiString Utils::getSeparator(const Pars& parameters)
{
 AnsiString separator;
 if(parameters.terminal_kind == Globals::TerminalKind::tkiPostcardTCIP)     separator = Globals::TCPIP_POSTCARD_SEPARATOR;
 else if (parameters.terminal_kind == Globals::TerminalKind::tkiItcardRS) separator = Globals::RS_ITCARD_SEPARATOR;
 else throw Exception("Brak separatora ramki");
 return separator;
}
//---------------------------------------------------------------------------

