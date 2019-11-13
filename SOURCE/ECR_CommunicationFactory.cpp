//---------------------------------------------------------------------------
#pragma hdrstop
#include "ECR_CommunicationFactory.h"
#include "ECR_Globals.h"
#include "CommunicationIndy.h"
#include "CommunicationSerial.h"
#include "test_communication_interface.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
CommunicationInterface* CommunicationFactory::create(const Pars& params)
{
  switch(params.communication_mode)
  {
     case Globals::cmkIndy: return new CommunicationIndy(params);
     case Globals::cmkRS:   return new CommunicationSerial(params);
     case Globals::cmkTest: return new TestCommunicationInterface;
     default: throw  Exception("Nieznany rodzaj komunikacji z terminalem!");
  }
}
//---------------------------------------------------------------------------

