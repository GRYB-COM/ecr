//---------------------------------------------------------------------------

#ifndef ECR_UtilsH
#define ECR_UtilsH
#include <system.hpp>
#include <vector>

namespace ecr
{
	class StringContainer : public std::vector<AnsiString>
	{
	public:
		//INTERFEJS
		int getAsInt(const unsigned _Idx, const int _DefValue=-1) const ;
	};

	class Utils
	{
	public:
		static StringContainer explode(const AnsiString & _Source);
	};
}//end nmspc
//---------------------------------------------------------------------------
#endif
