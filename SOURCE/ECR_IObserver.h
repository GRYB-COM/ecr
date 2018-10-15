//---------------------------------------------------------------------------

#ifndef ECR_IObserverH
#define ECR_IObserverH
//---------------------------------------------------------------------------
namespace ecr{
class Message;
class ITerminal;
class IObserver{
public:
	//INTERFEJS
	  virtual void runOnECR(const Message& _Mess)=0;
	  virtual void runOnMsg(const Message& _Mess)=0;
	  virtual void runOnListen(int & _Counter)=0;
	  virtual ~IObserver(void){};
 protected:
  ITerminal * m_Owner;
};
}
#endif
