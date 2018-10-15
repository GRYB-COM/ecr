//---------------------------------------------------------------------------

#ifndef ECR_ITerminalH
#define ECR_ITerminalH
namespace ecr{
class Message;
class Pars;
class IObserver;
class ITerminal{
public:
	//INTERFEJS
	  virtual void    setPars(const Pars& _Pars)=0;
	  virtual void    setObserver(IObserver& _Obs)=0;
	  virtual void    clearObserver(void)=0;
	  virtual Message send(const Message& _Mess, const Message& _CloseMess)=0;
	  virtual void    resp(const Message& _Mess)=0;
   //DESTRUKTOR
     virtual ~ITerminal(){}
};
}//end namespace
//---------------------------------------------------------------------------
#endif
