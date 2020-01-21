#include <DUnitX.TestFramework.hpp>
#include <stdio.h>
#include "ECR_Globals.h"
#include "ECR_Terminal.h"
#include "ECR_Pars.h"
#include "ECR_IObserver.h"
#include "ECR_Message.h"
#include <System.SysUtils.hpp>
#include "ECR_message_factory.h"
#include "ECR_Message.h"
#include "REPOSITORIES\message_template_repository.h"
#include "REPOSITORIES\field_mask_repository.h"
#include "REPOSITORIES\message_structure_repository.h"
#include "POLICIES\message_string_converter.h"
#include <cstdarg.h>
#pragma option --xrtti

class __declspec(delphirtti) PostCardTerminalTests : public TObject
{
public:
  virtual void __fastcall SetUp();
  virtual void __fastcall TearDown();

__published:
  void __fastcall Test1();
  void __fastcall Test2();
  void __fastcall Test3();
  void __fastcall Test4();
};


void __fastcall PostCardTerminalTests::SetUp()
{
}

void __fastcall PostCardTerminalTests::TearDown()
{
}

class TCPIPEmptyObserver :public ecr::IObserver{
public:
		virtual void runOnECR(const ecr::Message& message)
		{
       	if(message.getMessID() == ecr::Globals::miPOSPostcardHello)
       	{

         	AnsiString info(message.getRawMess());
         	std::cout << "\n";
         	std::cout << info.c_str();
         	std::cout << "\n";
       	}
      }
      virtual void runOnMsg(const ecr::Message& message)
		{
       	if(message.getMessID() == ecr::Globals::miECRPostcardHelloExt)
       	{

         	AnsiString info(message.getAsString());
         	std::cout << "\n";
         	std::cout << info.c_str();
         	std::cout << "\n";
       	}
      }

		virtual void runOnListen(int & _Counter){};

};

void __fastcall PostCardTerminalTests::Test1()
{
 //" KASA U. I. INFO-SYSTEM 2020.1.1.101.105 2020/01/05 16:00:00"
 AnsiString tlv;
 AnsiString c10("KASA U. I. INFO-SYSTEM");
 AnsiString c11("2020.1.1.101.105");
 AnsiString c12("2020/01/05 16:00:00");
 tlv  += (char)0x1C;
 tlv  += (char)0x10;
 tlv  += (char)0x00;
 tlv  += (char) c10.Length();
 tlv  += c10;
 tlv  += (char)0x1C;
 tlv  += (char)0x11;
 tlv  += (char)0x00;
 tlv  += (char) c11.Length();
 tlv  += c11;
 tlv  += (char)0x1C;
 tlv  += (char)0x12;
 tlv  += (char)0x00;
 tlv  += (char) c12.Length();
 tlv  += c12;

 const int tlv_length(tlv.Length());

 const String tlv_length_hex(Format("%.4x",ARRAYOFCONST(( tlv_length))));

 AnsiString tlv_hex;
 for(int i=1;i<=tlv_length; ++i)
 {
   tlv_hex += tlv.Format("%.2x",ARRAYOFCONST(( (Word) tlv[i])));
 }
 Dunitx::Testframework::Assert::IsTrue(tlv_length == 69);
 Dunitx::Testframework::Assert::IsTrue(tlv_length_hex == "0045");
 Dunitx::Testframework::Assert::IsTrue(tlv_hex == "1C1000164B41534120552E20492E20494E464F2D53595354454D1C110010323032302E312E312E3130312E3130351C120013323032302F30312F30352031363A30303A3030");

}

void __fastcall PostCardTerminalTests::Test2()
{

 ecr::MessageStringConverter::Parameters converter_parameters;
   converter_parameters.field_separator_code=ecr::Globals::RS_ITCARD_SEPARATOR;
   converter_parameters.first_field_index =0;
   converter_parameters.message_id_field_kind     = ecr::Globals::fkItcardMessID;
 ecr::MessageStringConverter * message_string_converter( new ecr::MessageStringConverter(converter_parameters) );
 ecr::MessageTemplateRepository * message_template_repository( new ecr::MessageTemplateRepository );
 ecr::MessageFactory message_factory(message_template_repository,message_string_converter);
 ecr::Message message(  message_factory.createMessage(ecr::Globals::miECRPostcardHelloExt,ecr::Globals::DEFAULT_TOKEN)  );


 String tlv_length(message.getTLVBlockLength() );
 Dunitx::Testframework::Assert::IsTrue(tlv_length== "0045");
 Dunitx::Testframework::Assert::IsTrue(message.getTLVBlock() == "1C1000164B41534120552E20492E20494E464F2D53595354454D1C110010323032302E312E312E3130312E3130351C120013323032302F30312F30352031363A30303A3030");

}


void __fastcall PostCardTerminalTests::Test3()
{
	String _Mess;
	ecr::Pars _Pars;
	_Pars.Host = "10.10.10.46";
	_Pars.Port = 3030;
	_Pars.Typ = "TCPIP";
	_Pars.Multiservice = false;
   _Pars.communication_mode = ecr::Globals::cmkTest;
   _Pars.terminal_kind = ecr::Globals::tkiPostcardTCIP;
   TCPIPEmptyObserver empty_observer;
	ecr::Terminal _Term(_Pars,empty_observer);
	ecr::Globals::TransStat _St = _Term.hello();
	Dunitx::Testframework::Assert::IsTrue(_St == ecr::Globals::tsApproval);
}

static void registerTests()
{
  TDUnitX::RegisterTestFixture(__classid(PostCardTerminalTests));
}

struct VarTest{
   AnsiString result;
   VarTest(int count...)
   {
    result="";
    std::va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        result += va_arg(args, AnsiString);
    }
    va_end(args);

   }
};

void __fastcall PostCardTerminalTests::Test4()
{
  VarTest vt(3,AnsiString('a'),AnsiString('b'),AnsiString('c'));
  Dunitx::Testframework::Assert::IsTrue(vt.result == "abc");
}
#pragma startup registerTests 33