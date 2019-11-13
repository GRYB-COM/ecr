//---------------------------------------------------------------------------

#ifndef ECR_IFieldMaskH
#define ECR_IFieldMaskH
#include <system.hpp>

namespace ecr
{
	class Message;
	class StringContainer;

	class IFieldMask
	{
	public:
		//INTERFEJS
		virtual AnsiString getAsString(const Message&, const String& separator) const =0;
		virtual void        setMessage(Message& _Mess, const StringContainer&, const unsigned)=0;
		//DESTRUKTOR
		virtual ~IFieldMask()
		{
		}
	};
}//end
//---------------------------------------------------------------------------
#endif
