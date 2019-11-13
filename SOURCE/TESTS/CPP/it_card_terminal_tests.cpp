#include <DUnitX.TestFramework.hpp>
#include <stdio.h>
#include "ECR_Globals.h"
#include "ECR_message_factory.h"
#include "ECR_Message.h"
#include "REPOSITORIES\message_template_repository.h"
#include "REPOSITORIES\field_mask_repository.h"
#include "REPOSITORIES\message_structure_repository.h"
#include "POLICIES\message_string_converter.h"
#include "ECR_Terminal.h"
#include "ECR_Pars.h"
#include "ECR_IObserver.h"
#pragma option --xrtti

class __declspec(delphirtti) ITCardTerminalTests : public TObject
{
public:
  virtual void __fastcall SetUp();
  virtual void __fastcall TearDown();

__published:
  void __fastcall Test1();
  void __fastcall Test2();
  void __fastcall Test3();
  void __fastcall Test4();
  void __fastcall Test5();
  void __fastcall Test6();
};


void __fastcall ITCardTerminalTests::SetUp()
{
}

void __fastcall ITCardTerminalTests::TearDown()
{
}

void __fastcall ITCardTerminalTests::Test1()
{
   AnsiString message_id_as_string("P1");
   unsigned short message_id(  message_id_as_string[1]<<8  );
   message_id += message_id_as_string[2];
   ecr::Globals::MessID messID = static_cast<ecr::Globals::MessID>(message_id);

}

void __fastcall ITCardTerminalTests::Test2()
{
 ecr::MessageStructureRepository * message_structure_repository( new ecr::MessageStructureRepository );
 ecr::FieldMaskRepository * field_mask_repository( new ecr::FieldMaskRepository );
 ecr::MessageStringConverter::Parameters converter_parameters;
   converter_parameters.field_separator_code=ecr::Globals::RS_ITCARD_SEPARATOR;
   converter_parameters.first_field_index =0;
   converter_parameters.message_id_frame_position = ecr::Globals::ITCARD_MESSAGE_ID_FRAME_POSITION;
   converter_parameters.message_id_field_kind     = ecr::Globals::fkItcardMessID;
 ecr::MessageStringConverter * message_string_converter( new ecr::MessageStringConverter(converter_parameters) );
 ecr::MessageTemplateRepository * message_template_repository( new ecr::MessageTemplateRepository );
 ecr::MessageFactory message_factory(message_template_repository,message_string_converter);
 ecr::Message message(  message_factory.createMessage(ecr::Globals::miECRItcardHello,ecr::Globals::DEFAULT_TOKEN)  );

 Dunitx::Testframework::Assert::IsTrue(message.getMessID() == ecr::Globals::miECRItcardHello);
}

class EmptyObserver :public ecr::IObserver{
public:
		virtual void runOnECR(const ecr::Message& _Mess){};
		virtual void runOnMsg(const ecr::Message& message)
      {
       if(message.getMessID() == ecr::Globals::miPOSItcardPrompt || message.getMessID() == ecr::Globals::miPOSItcardSale)
       {
         AnsiString info(message.getPinPadMsg());
         std::cout << "\n";
         std::cout << info.c_str();
       }
      };
		virtual void runOnListen(int & _Counter){};

};

void __fastcall ITCardTerminalTests::Test3()
{
 ecr::Pars ecr_parameters;
 ecr_parameters.communication_mode = ecr::Globals::cmkTest;
 ecr_parameters.terminal_kind      = ecr::Globals::tkiItcardRS;

 EmptyObserver empty_observer;

 ecr::Terminal terminal(ecr_parameters, empty_observer);

 Dunitx::Testframework::Assert::IsTrue(terminal.hello() == ecr::Globals::tsApproval);
}

void __fastcall ITCardTerminalTests::Test4()
{
 ecr::Pars ecr_parameters;
 ecr_parameters.communication_mode = ecr::Globals::cmkTest;
 ecr_parameters.terminal_kind      = ecr::Globals::tkiItcardRS;

 EmptyObserver empty_observer;

 ecr::Terminal terminal(ecr_parameters, empty_observer);

 Dunitx::Testframework::Assert::IsTrue(terminal.sale(0.0,0,ecr::Globals::tkPostcardSale) == ecr::Globals::tsApproval);
}

void __fastcall ITCardTerminalTests::Test5()
{
 try{

 ecr::Pars ecr_parameters;
 ecr_parameters.communication_mode = ecr::Globals::cmkRS;
 ecr_parameters.Port =3;
 ecr_parameters.Host ="COM";
 ecr_parameters.terminal_kind      = ecr::Globals::tkiItcardRS;

 EmptyObserver empty_observer;

 ecr::Terminal terminal(ecr_parameters, empty_observer);

 Dunitx::Testframework::Assert::IsTrue(terminal.hello() == ecr::Globals::tsApproval);
 }
 catch(std::exception& exc){
   Dunitx::Testframework::Assert::Fail(exc.what());
 }
}

void __fastcall ITCardTerminalTests::Test6()
{
 try{

 ecr::Pars ecr_parameters;
 ecr_parameters.communication_mode = ecr::Globals::cmkRS;
 ecr_parameters.Port =3;
 ecr_parameters.Host ="COM";
 ecr_parameters.terminal_kind      = ecr::Globals::tkiItcardRS;

 EmptyObserver empty_observer;

 ecr::Terminal terminal(ecr_parameters, empty_observer);

 Dunitx::Testframework::Assert::IsTrue(terminal.sale(1.22,0,ecr::Globals::tkItcardSale) == ecr::Globals::tsApproval);
 }
 catch(std::exception& exc){
   Dunitx::Testframework::Assert::Fail(exc.what());
 }
}



static void registerTests()
{
  TDUnitX::RegisterTestFixture(__classid(ITCardTerminalTests));
}
#pragma startup registerTests 33