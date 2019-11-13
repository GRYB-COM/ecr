//---------------------------------------------------------------------------

#ifndef communication_repositoryH
#define communication_repositoryH
#include  "..\ECR_Globals.h"
#include <map>
namespace ecr
{
   class Pars;
	class CommunicationInterface;
	class ComunicationRepository : public std::map<Globals::CommunnicationMode, CommunicationInterface*>
	{
	public:
		CommunicationInterface* get(const Globals::CommunnicationMode&);
		ComunicationRepository(const Pars&);
		~ComunicationRepository(void);
	};

}
#endif
