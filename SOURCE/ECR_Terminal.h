//---------------------------------------------------------------------------

#ifndef ECR_TerminalH
#define ECR_TerminalH
#include <system.hpp>
#include "ECR_Pars.h"

namespace ecr
{
   class TerminalInterface;
	class IObserver;

	class Terminal
	{
	public:
		//INTERFEJS
		bool isInitialized(void)
		{
			return terminal_ID > 0;
		}

		int getTermID(void)
		{
			return terminal_ID;
		}
		Globals::TransStat hello(void);
		Globals::TransStat sale(const Currency& _Amount, const short ProfileId, const Globals::TransKind& _Kind);
		Globals::TransStat resp(const Globals::RespKind _RK, const unsigned short _Val);
		String getProfileList(const int _TimeOut);

		//KONSTRUKTOR  DESTRUKTOR
		Terminal(const Pars&, IObserver&);
		~Terminal(void);

	private:
		//SK£ADOWE
		Pars params;
		int terminal_ID;
      TerminalInterface*      terminal_interface;
		//METODY POMOCNICZE
	};
}
//---------------------------------------------------------------------------
#endif
