//---------------------------------------------------------------------------

#ifndef ECR_UtilsH
#define ECR_UtilsH
#include <system.hpp>
#include <vector>

namespace ecr
{
   class Pars;
	class StringContainer : public std::vector<AnsiString>
	{
	public:
		//INTERFEJS
		int getAsInt(const unsigned _Idx, const int _DefValue=-1) const ;
	};

	class Utils
	{
	public:
		static StringContainer explode(const AnsiString & _Source, const AnsiString& separator);
		static StringContainer explode(const AnsiString & _Source, const char start_separator, const char end_separator);
      static AnsiString getSeparator(const Pars&);

	};
}//end nmspc
//---------------------------------------------------------------------------
#endif
