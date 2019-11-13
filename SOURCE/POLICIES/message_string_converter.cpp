//---------------------------------------------------------------------------
#pragma hdrstop
#include "message_string_converter.h"
#include "ECR_Globals.h"
#include "ECR_Utils.h"
#include "ECR_Message.h"
#include "message_structure_repository.h"
#include "field_mask_repository.h"
#include "ECR_IFieldMask.h"
#include "ECR_FieldMasks.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ecr;
//---------------------------------------------------------------------------
MessageStringConverter::MessageStringConverter(const MessageStringConverter& message_string_converter)
:message_structure_repository(new MessageStructureRepository() ),
 field_mask_repository(new FieldMaskRepository() ),
 field_separator_code(message_string_converter.field_separator_code),
 first_field_index(message_string_converter.first_field_index),
 message_id_frame_position(message_string_converter.message_id_frame_position),
 message_id_field_kind(message_string_converter.message_id_field_kind)
{

}
//---------------------------------------------------------------------------
MessageStringConverter::MessageStringConverter(const Parameters& parameters)
:message_structure_repository(new MessageStructureRepository()),
field_mask_repository(new FieldMaskRepository()),
field_separator_code(parameters.field_separator_code),
first_field_index(parameters.first_field_index),
message_id_frame_position(parameters.message_id_frame_position),
message_id_field_kind(parameters.message_id_field_kind)
{

}
//---------------------------------------------------------------------------
void MessageStringConverter::convertStringToMessage(Message& message,const AnsiString& message_as_string)
{
 	StringContainer message_fields_as_strings = Utils::explode(message_as_string,field_separator_code);
   ItcardMessIDMask mmm;
   mmm.setMessage(message,message_fields_as_strings,message_id_frame_position);
   IFieldMask* message_id_field_mask(&mmm);//(field_mask_repository->find(message_id_field_kind)->second);
   message_id_field_mask->setMessage(message,message_fields_as_strings,message_id_frame_position);


	MessageStructureRepository::const_iterator message_structure_iterator( message_structure_repository->find(message.getMessID()) );
	if (message_structure_iterator == message_structure_repository->end()) message_structure_iterator = message_structure_repository->find(Globals::miUnknown);
	FieldKinds::const_iterator field_kinds_iterator(message_structure_iterator->second.begin());
	FieldMaskRepository::const_iterator field_mask_iterator;
	int field_index_in_message(first_field_index);
	for (field_kinds_iterator; field_kinds_iterator != message_structure_iterator->second.end(); ++field_kinds_iterator)
	{
      Globals::FieldKind field_kind( *field_kinds_iterator );
		field_mask_iterator = field_mask_repository->find(field_kind);
		if (field_mask_iterator != field_mask_repository->end())
			field_mask_iterator->second->setMessage(message, message_fields_as_strings, field_index_in_message);
		++field_index_in_message;
	}
}
//---------------------------------------------------------------------------
void MessageStringConverter::convertMessageToString(AnsiString& message_as_string,const Message& message)
{
	if (message.getMessID() == Globals::miUnknown) return;

   Globals::MessID message_ID;
   message_ID= message.getMessID();
	MessageStructureRepository::const_iterator message_structure_iterator = message_structure_repository->find(message_ID);
	FieldKinds::const_iterator field_kind_iterator(message_structure_iterator->second.begin());
	FieldMaskRepository::const_iterator field_mask_iterator;
	for (field_kind_iterator; field_kind_iterator != message_structure_iterator->second.end(); ++field_kind_iterator)
	{
		field_mask_iterator = field_mask_repository->find(*field_kind_iterator);
		message_as_string += field_mask_iterator->second->getAsString(message,field_separator_code);
	}

}
//---------------------------------------------------------------------------
MessageStringConverter::~MessageStringConverter(void)
{
   delete message_structure_repository;
   delete field_mask_repository;
}
