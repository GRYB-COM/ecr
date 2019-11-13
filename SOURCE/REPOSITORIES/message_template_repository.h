//---------------------------------------------------------------------------
#ifndef message_template_repositoryH
#define message_template_repositoryH
#include "..\ECR_Globals.h"
#include <map>
#include <system.hpp>
//---------------------------------------------------------------------------
namespace ecr{

	class MessageTemplateRepository : public std::map<Globals::MessID, String>
	{
	public:
		String get(const Globals::MessID _ID) const ;
		MessageTemplateRepository(void);
	};

}
//---------------------------------------------------------------------------
#endif
