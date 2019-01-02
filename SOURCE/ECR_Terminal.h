//---------------------------------------------------------------------------

#ifndef ECR_TerminalH
#define ECR_TerminalH
#include <system.hpp>
#include "ECR_Pars.h"
#include "ECR_Globals.h"

namespace ecr
{
	class ITerminal;
	class IObserver;

	class Terminal
	{
	public:
		//INTERFEJS
		void setPars(const Pars& _Pars)
		{
			m_Pars =_Pars;
		};
		void setObserver(IObserver& _Obs);

		bool isInitialized(void)
		{
			return m_TermID > 0;
		}

		int getTermID(void)
		{
			return m_TermID;
		}
		Globals::TransStat hello(void);
		Globals::TransStat sale(const Currency& _Amount, const short ProfileId=0, const Globals::TransKind& _Kind= Globals::tkSale);
		Globals::TransStat resp(const Globals::RespKind _RK, const unsigned short _Val);
		String getProfileList(const int _TimeOut);

		//KONSTRUKTOR  DESTRUKTOR
		Terminal(void);
		~Terminal(void);

	private:
		//SK£ADOWE
		Pars m_Pars;
		int m_TermID;

		//METODY POMOCNICZE
		ITerminal& prepare(void);
	};
}
//---------------------------------------------------------------------------
#endif
