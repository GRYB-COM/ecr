//---------------------------------------------------------------------------
#pragma hdrstop
#include "communication_repository.h"
#pragma package(smart_init)
#include "CommunicationIndy.h"
#include "CommunicationSerial.h"
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
ComunicationRepository::ComunicationRepository(const Pars& parameters)
{
	operator[](Globals::cmkIndy) = new CommunicationIndy(parameters);
	operator[](Globals::cmkWinSock) = NULL;
	operator[](Globals::cmkUSB) = NULL;
	operator[](Globals::cmkRS) = new CommunicationSerial(parameters);
}

//---------------------------------------------------------------------------
ComunicationRepository::~ComunicationRepository(void)
{
	for (iterator _ItB(begin()); _ItB != end(); ++_ItB)
	{
		delete _ItB->second;
	}
}
//---------------------------------------------------------------------------
CommunicationInterface* ComunicationRepository::get(const Globals::CommunnicationMode& _Kind)
{
	iterator _ItF = find(_Kind);
	if (_ItF==end())
		throw Exception("B³êdny rodzaj terminala");
	return _ItF->second;
}