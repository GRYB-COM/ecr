//---------------------------------------------------------------------------

#ifndef ECR_GlobalsH
#define ECR_GlobalsH
#include <system.hpp>
namespace ecr{
class Globals{
public:
	//KLASY WEWNÊTRZNE
	  enum MessID     {miUnknown=-1,  miECRHello=2841011, miPOSHello=2840000,
					   miECRStart=2811011,miECRStartExt=2811111,miPOSFinish=2810000,
					   miPinPadDisp=2820010, miECRDisp=2821000,
					   miECRPrompt=2821211,miPOSPrompt=2820200
					  };
	  enum FieldKind  {fkNull=0,fkMessID,fkTermStatus, fkTermID, fkCipher, fkTransType,fkAmount,fkCashBack,fkCardType,
					   fkTransStatus,fkPLN, fkPPMsg, fkPPMSize, fkPPMResp,fkTimeOut,fkZero,fkProfileId,fkPromptReq};
	  enum TransKind  {tkUnknown=-1,tkSale=0,tkSaleCash=9,tkCash=12,tkRefund=20};
	  enum TermKind   {tmkIndy, tmkWinSock, tmkUSB, tmkRS};
	  enum TransStat  {tsConnErr=-2,tsUnknown=-1, tsApproval=0, tsRefusal=1000, tsTransSettled=4401, tsTransNotFound=4402,
					   tsAmountNotMatch=4403,tsTransAbort=4407, tsMultiMerchIncorrect=4408, tsTermIsFull=4411,
					   tsLoyalityErr=4409, tsNoLoyality=4410};
	  enum RespKind	  {rkUnknown=-1,rkNoResp=0, rkYesNo,rkAmmount,rkCC,rkAC,rkOpt,rkProfile,rkAnyKey};
	  enum PromptReq  {prUnknown=-1, prProfileList=1};
	//STA£E
	  static const AnsiString SEPARATOR;
	  static const unsigned short TIME_A;
	  static const unsigned       TIME_B;
	  static const unsigned short TIME_C;
	  static const unsigned short INTERVAL;
	//FUNKCJE
      static String getTransStatDescr(const TransStat& _Stat);
};
}//endnamespace
//---------------------------------------------------------------------------
#endif
