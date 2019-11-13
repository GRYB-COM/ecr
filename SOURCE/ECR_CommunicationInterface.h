//---------------------------------------------------------------------------

#ifndef ECR_CommunicationInterfaceH
#define ECR_CommunicationInterfaceH

namespace ecr
{
	class Message;
	class Pars;
	class IObserver;

	class CommunicationInterface
	{
	public:
		//INTERFEJS
		virtual void setObserver(IObserver& _Obs)=0;
		virtual void clearObserver(void)=0;
		virtual Message send(const Message& _Mess, const Message& _CloseMess)=0;
		virtual void resp(const Message& _Mess)=0;

		//DESTRUKTOR
		virtual ~CommunicationInterface()
		{
		}
	};
}
//---------------------------------------------------------------------------
#endif
