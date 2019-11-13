//---------------------------------------------------------------------------

#ifndef ECR_GlobalsH
#define ECR_GlobalsH
#include <system.hpp>

namespace ecr
{
	class Globals
	{
	public:
		//KLASY WEWNÊTRZNE
		enum MessID
		{
			miUnknown=-1, miECRPostcardHello=2841011, miPOSPostcardHello=2840000, miECRPostcardStart=2811011, miECRPostcardStartExt=2811111,
         miPOSPostcardFinish=2810000, miPinPadPostcardDisp=2820010, miECRPostcardDisp= 2821000, miECRPostcardPrompt=2821211, miPOSPostcardPrompt=2820200,
         miECRItcardHello=0x5431, miPOSItcardHello=0x5432, miECRItcardSale=0x5331, miPOSItcardSale=0x5332, miECRItcardPars=0x4434, miPOSItcardPars=0x4435,
         miPOSItcardPrompt=0x4931,miPOSItcardPrompt1=0x4B33
		};

		enum FieldKind
		{
			fkNull=0, fkPostcardMessID, fkTermStatus, fkTermID,
         fkCipher, fkTransType, fkAmount, fkCashBack, fkCardType,
         fkTransStatus, fkPLN, fkPPMsg, fkPPMSize,
			fkPPMResp, fkTimeOut, fkZero, fkProfileId, fkPromptReq,
         fkItcardMessID, fkItcardMessToken, fkItcardTransType,
         fkEcrID, fkDocID, fkCurrencyCode, fkItcardTransInfo, fkItcardTransResultInfo

		};

		enum TransKind
		{
			tkUnknown=-1, tkPostcardSale=0, tkPostcardSaleCash=9, tkPostcardCash=12, tkPostcardRefund=20,
         tkItcardSale=0x53, tkItcardRefund=0x5A
		};

		enum CommunnicationMode
		{
			cmkUnknown=-1, cmkTest, cmkIndy, cmkWinSock, cmkUSB, cmkRS
		};

		enum TransStat
		{
			tsConnErr=-2, tsUnknown=-1, tsApproval=0, tsRefusal=1000, tsTransSettled=4401, tsTransNotFound=4402,
         tsAmountNotMatch=4403, tsMessIDNotMatch=4404, tsTokenNotMatch=4405,
         tsTransAbort=4407, tsMultiMerchIncorrect=4408, tsTermIsFull=4411, tsLoyalityErr=4409, tsNoLoyality=4410,
		};

		enum RespKind
		{
			rkUnknown=-1, rkNoResp=0, rkYesNo, rkAmmount, rkCC, rkAC, rkOpt, rkProfile, rkAnyKey
		};

		enum PromptReq
		{
			prUnknown=-1, prProfileList=1
		};

      enum TerminalKind
      {
        tkiUnknown=-1, tkiPostcardTCIP, tkiItcardRS
      };

		//STA£E
		static const AnsiString TCPIP_POSTCARD_SEPARATOR;
		static const AnsiString RS_ITCARD_SEPARATOR;
		static const unsigned short TIME_A;
		static const unsigned TIME_B;
		static const unsigned TIME_ITCARD_B;
		static const unsigned short TIME_C;
		static const unsigned short INTERVAL;
      static const unsigned       TOKEN_RANGE;
      static const String			 GENERATE_TOKEN;
      static const String         DEFAULT_TOKEN;
      static const unsigned short SEND_ATTEMPT_TIMES;
      static const unsigned short CONFIRMATION_WAIT_TIME;
      static const unsigned short POSTCARD_MESSAGE_ID_FRAME_POSITION;
      static const unsigned short ITCARD_MESSAGE_ID_FRAME_POSITION;

		//FUNKCJE
		static String getTransStatDescr(const TransStat& _Stat);
	};
}//endnamespace
//---------------------------------------------------------------------------
#endif
