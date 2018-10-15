//---------------------------------------------------------------------------

#ifndef ECR_ParsH
#define ECR_ParsH
#include <system.hpp>
namespace ecr{
struct Pars{
	String   Host;
	unsigned short Port;
	String Typ;
	bool Multiservice;
	int Id;
};
}//endnamespace
//---------------------------------------------------------------------------
#endif
