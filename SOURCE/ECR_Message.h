//---------------------------------------------------------------------------

#ifndef ECR_MessageH
#define ECR_MessageH
#include "ECR_Globals.h"
namespace ecr{
class MessIDMask;
class TermStatusMask;
class TermIDMask;
class Message{
public:
		//METODY DOSTÊPU
		//GET
		  Globals::MessID 	 getMessID(void) 	  const { return m_MessID;        }
		  int			  	 getTermStatus(void)  const { return m_TermStatus;    }
		  int			  	 getTermID(void) 	  const { return m_TermID;        }
		  Currency        	 getAmount(void) 	  const { return m_Amount;        }
		  Globals::TransKind getTransKind(void)   const { return m_TransKind;     }
		  AnsiString         getAsString(void);//nie mo¿e byæ const
		  int			  	 getCardType(void) 	  const { return m_CardType;      }
		  Globals::TransStat getTransStatus(void) const { return m_TransStatus;   }
		  String             getRawMess(void)     const { return m_RawMess;       }
		  String             getPinPadMsg(void)   const { return m_PinPadMsg;     }
		  int                getPPMSize(void)     const { return m_PPMSize;       }
		  Globals::RespKind  getRespKind(void)    const { return m_RespKind;      }
		  int			  	 getTimeOut(void) 	  const { return m_TimeOut;       }
		  int			  	 getProfileId(void)   const { return m_ProfileId;     }
		  Globals::PromptReq getPromptReq(void)   const { return m_PromptReq;     }
		//SET
		  void setAmount(const Currency& _Am)               { m_Amount      = _Am;  }
		  void setTransKind(const Globals::TransKind& _TK)  { m_TransKind   = _TK;  }
		  void setTransStatus(const Globals::TransStat _TS) { m_TransStatus = _TS;  }
		  void setCardType(const int _C)                    { m_CardType    = _C;   }
		  void setPinPadMsg(const String& _Msg)             { m_PinPadMsg   = _Msg; }
		  void setPPMSize(const int _Si)                    { m_PPMSize     = _Si;  }
		  void setRespKind(const Globals::RespKind& _RK)    { m_RespKind    = _RK;  }
		  void setTimeOut(const int _Ti)                    { m_TimeOut     = _Ti;  }
		  void setProfileId(const int _Pi)                  { m_ProfileId   = _Pi;  }
		  void setPromptReq(const Globals::PromptReq _Re)   { m_PromptReq   = _Re;  }


		  void setFromString(const AnsiString& _Mess);

		  void clear(void);
	   //KONSTRUKTORY
		 Message(void);
		 Message(const AnsiString& _Mess);
	   //OPERATORY
private:
		//ATRYBUTY
		  Globals::MessID 		m_MessID;
		  int             		m_TermStatus;
		  int             		m_TermID;
		  Currency        		m_Amount;
		  Globals::TransKind    m_TransKind;
		  int                   m_CardType;
		  Globals::TransStat    m_TransStatus;
		  String                m_RawMess;
		  String                m_PinPadMsg;
		  int                   m_PPMSize;
		  Globals::RespKind     m_RespKind;
		  int                   m_TimeOut;
		  int                   m_ProfileId;
		  Globals::PromptReq    m_PromptReq;

 friend MessIDMask;
 friend TermStatusMask;
 friend TermIDMask;
};
}//endnamespace
//---------------------------------------------------------------------------
#endif
