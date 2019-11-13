//---------------------------------------------------------------------------
#pragma hdrstop
#include "field_mask_repository.h"
#pragma package(smart_init)
#include "..\ECR_FieldMasks.h"
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
FieldMaskRepository::FieldMaskRepository(void)
{
	operator[](Globals::fkNull) =new NullMask();
	operator[](Globals::fkPostcardMessID) =new PostcardMessIDMask();
	operator[](Globals::fkTermStatus) =new TermStatusMask();
	operator[](Globals::fkTermID) =new TermIDMask();
	operator[](Globals::fkCipher) =new CipherMask();
	operator[](Globals::fkTransType) =new TransTypeMask();
	operator[](Globals::fkAmount) =new AmountMask();
	operator[](Globals::fkCashBack) =new CashBackMask();
	operator[](Globals::fkCardType) =new CardTypeMask();
	operator[](Globals::fkTransStatus) =new TransStatusMask();
	operator[](Globals::fkPLN) =new PLNMask();
	operator[](Globals::fkPPMsg) =new PPMsgMask();
	operator[](Globals::fkPPMSize) =new PPMSizeMask();
	operator[](Globals::fkPPMResp) =new PPMRespMask();
	operator[](Globals::fkTimeOut) =new TimeOutMask();
	operator[](Globals::fkZero) =new ZeroMask();
	operator[](Globals::fkProfileId) =new ProfileIdMask();
	operator[](Globals::fkPromptReq) =new PromptReqMask();

   operator[](Globals::fkItcardMessID) = new ItcardMessIDMask();
   operator[](Globals::fkItcardMessToken) = new ItcardMessTokenMask();
   operator[](Globals::fkItcardTransType) = new ItcardTransTypeMask();
   operator[](Globals::fkEcrID) = new EcrIDMask();
   operator[](Globals::fkDocID) = new DocIDMask();
   operator[](Globals::fkCurrencyCode) = new CurrencyCodeMask();
   operator[](Globals::fkItcardTransInfo) = new ItcardTransInfoMask();
   operator[](Globals::fkItcardTransResultInfo) = new ItcardTransResultInfoMask();


}

//---------------------------------------------------------------------------
FieldMaskRepository::~FieldMaskRepository()
{
	iterator _ItB(begin());
	for (_ItB; _ItB != end(); ++_ItB)
	{
		delete _ItB->second;
	}
}
//---------------------------------------------------------------------------
IFieldMask* FieldMaskRepository::get(const Globals::FieldKind field_kind) const
{
  IFieldMask* field_mask_interface(NULL);
	const_iterator _ItF = find(field_kind);
	if (_ItF != end())
	{
		field_mask_interface = _ItF->second;
	}
   else throw Exception("Nie znaleziono maski dla podenego pola!");
	return field_mask_interface;
}

//---------------------------------------------------------------------------
