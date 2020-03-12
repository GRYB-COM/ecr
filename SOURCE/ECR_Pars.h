//---------------------------------------------------------------------------

#ifndef ECR_ParsH
#define ECR_ParsH
#include <system.hpp>
#include "ECR_Globals.h"
namespace ecr
{
	struct Pars
	{
		String Host;
		unsigned short Port;
		String Typ;
		bool Multiservice;
		int Id;
      unsigned listen_time_out;
      Globals::CommunnicationMode communication_mode;
      Globals::TerminalKind terminal_kind;
      Pars(void);
	};
}//endnamespace
//---------------------------------------------------------------------------
#endif
