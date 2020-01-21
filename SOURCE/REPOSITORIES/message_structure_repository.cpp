//---------------------------------------------------------------------------
#pragma hdrstop
#include "message_structure_repository.h"
#include <boost/assign/std/vector.hpp>
#include <boost/assert.hpp>;
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
using namespace std;
using namespace boost::assign;
//---------------------------------------------------------------------------
MessageStructureRepository::MessageStructureRepository(void)
{
	operator[](Globals::miUnknown) += Globals::fkPostcardMessID, Globals::fkNull;
	operator[](Globals::miECRPostcardHello) += Globals::fkPostcardMessID, Globals::fkCipher, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull;
	operator[](Globals::miECRPostcardHelloExt) += Globals::fkPostcardMessID, Globals::fkCipher, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull,
   	 Globals::fkOne, Globals::fkTLVBlockLength, Globals::fkTLVBlock,Globals::fkNull;
	operator[](Globals::miPOSPostcardHello) += Globals::fkPostcardMessID, Globals::fkTermStatus, Globals::fkNull, Globals::fkNull, Globals::fkTermID;
	operator[](Globals::miPOSPostcardHelloExt) += Globals::fkPostcardMessID, Globals::fkTermStatus, Globals::fkNull, Globals::fkNull, Globals::fkTermID;
	operator[](Globals::miECRPostcardStart) += Globals::fkPostcardMessID, Globals::fkTransType, Globals::fkAmount, Globals::fkNull, Globals::fkNull, Globals::fkNull,
		 Globals::fkNull, Globals::fkPLN, Globals::fkNull, Globals::fkNull, Globals::fkNull;
	operator[](Globals::miECRPostcardStartExt) += Globals::fkPostcardMessID, Globals::fkTransType, Globals::fkZero, Globals::fkAmount, Globals::fkNull, Globals::fkNull,
		 Globals::fkNull, Globals::fkNull, Globals::fkPLN, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull,
		 Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkProfileId, Globals::fkNull, Globals::fkNull, Globals::fkNull,
		 Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull,
		 Globals::fkNull, Globals::fkNull;
	operator[](Globals::miPOSPostcardFinish) += Globals::fkPostcardMessID, Globals::fkNull, Globals::fkCardType, Globals::fkTransStatus, Globals::fkNull, Globals::fkNull;
	operator[](Globals::miPinPadPostcardDisp) += Globals::fkPostcardMessID, Globals::fkPPMSize, Globals::fkPPMsg, Globals::fkNull, Globals::fkPPMResp, Globals::fkTimeOut;
	operator[](Globals::miECRPostcardDisp) += Globals::fkPostcardMessID, Globals::fkPPMResp, Globals::fkPPMSize, Globals::fkPPMsg, Globals::fkNull;
	operator[](Globals::miECRPostcardPrompt) += Globals::fkPostcardMessID, Globals::fkPromptReq, Globals::fkPPMSize, Globals::fkPPMsg, Globals::fkNull;

	operator[](Globals::miPOSPostcardPrompt) += Globals::fkPostcardMessID, Globals::fkPromptReq, Globals::fkPPMSize, Globals::fkPPMsg, Globals::fkNull;

   	operator[](Globals::MessID::miECRItcardHello) += Globals::fkItcardMessToken, Globals::fkItcardMessID, Globals::fkNull;
   	operator[](Globals::MessID::miPOSItcardHello) += Globals::fkItcardMessToken, Globals::fkItcardMessID, Globals::fkNull;
   	operator[](Globals::miECRItcardSale) += Globals::fkItcardMessToken, Globals::fkItcardMessID, Globals::fkItcardTransType,Globals::fkEcrID, Globals::fkDocID,
      	Globals::fkAmount, Globals::fkAmount, Globals::fkZero,Globals::fkCurrencyCode, Globals::fkNull;
   	operator[](Globals::miPOSItcardSale) += Globals::fkItcardMessToken, Globals::fkItcardMessID, Globals::fkItcardTransResultInfo, Globals::fkNull;
   	operator[](Globals::miECRItcardPars) += Globals::fkItcardMessToken, Globals::fkItcardMessID, Globals::fkNull;
   	operator[](Globals::miPOSItcardPars) += Globals::fkItcardMessToken, Globals::fkItcardMessID, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull, Globals::fkNull;
   	operator[](Globals::miPOSItcardPrompt) += Globals::fkItcardMessToken, Globals::fkItcardMessID, Globals::fkItcardTransInfo, Globals::fkNull;
   	operator[](Globals::miPOSItcardPrompt1) += Globals::fkItcardMessToken, Globals::fkItcardMessID, Globals::fkNull, Globals::fkNull, Globals::fkPPMsg, Globals::fkNull;

}

//---------------------------------------------------------------------------
