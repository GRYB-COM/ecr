//---------------------------------------------------------------------------
#ifndef message_string_converterH
#define message_string_converterH
#include <system.hpp>
#include "ECR_Globals.h"
//---------------------------------------------------------------------------
namespace ecr{
   class Message;
   class MessageStructureRepository;
   class FieldMaskRepository;
   class MessageStringConverter{
   public:
      struct Parameters{
         AnsiString 						 field_separator_code;
         unsigned short              first_field_index;
	      unsigned short              message_id_frame_position;
         Globals::FieldKind          message_id_field_kind;
      };
      MessageStringConverter(const Parameters&);
      MessageStringConverter(const MessageStringConverter&);
      void convertStringToMessage(Message&,const AnsiString&);
      void convertMessageToString(AnsiString&,const Message&);
      ~MessageStringConverter(void);
   private:
      MessageStructureRepository* message_structure_repository;
      FieldMaskRepository*        field_mask_repository;
      AnsiString                  field_separator_code;
      unsigned short              first_field_index;
      unsigned short              message_id_frame_position;
      Globals::FieldKind          message_id_field_kind;
   };
}
//---------------------------------------------------------------------------
#endif
