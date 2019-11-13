//---------------------------------------------------------------------------

#ifndef message_structure_repositoryH
#define message_structure_repositoryH
#include "..\ECR_Globals.h"
#include <map>
#include <vector>
//---------------------------------------------------------------------------
namespace ecr{
   typedef std::vector<Globals::FieldKind> FieldKinds;
	class MessageStructureRepository : public std::map<Globals::MessID, FieldKinds>
	{
	public:
		MessageStructureRepository(void);
	};

}
//---------------------------------------------------------------------------
#endif
