//---------------------------------------------------------------------------

#ifndef field_mask_repositoryH
#define field_mask_repositoryH
#include "..\ECR_Globals.h"
#include <map>
//---------------------------------------------------------------------------
namespace ecr{
   class IFieldMask;
	class FieldMaskRepository : public std::map<Globals::FieldKind,IFieldMask*>
	{
	public:
		IFieldMask* get(const Globals::FieldKind) const ;
		FieldMaskRepository(void);
		~FieldMaskRepository(void);
	};

}
#endif
