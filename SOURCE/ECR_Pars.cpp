//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_Pars.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
Pars::Pars(void)
:Port(0),
 Multiservice(false),
 Id(-1),
 communication_mode(Globals::CommunnicationMode::cmkUnknown),
 terminal_kind(Globals::TerminalKind::tkiUnknown),
 listen_time_out(Globals::TIME_B),
 ProtocolVersion(pvUnknown)
{

}
