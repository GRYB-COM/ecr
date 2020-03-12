//---------------------------------------------------------------------------

#ifndef ECR_MessageH
#define ECR_MessageH
#include "ECR_Globals.h"

namespace ecr
{
	class ItcardMessIDMask;
	class ItcardMessTokenMask;
	class PostcardMessIDMask;
	class TermStatusMask;
	class TermIDMask;
	class EcrIDMask;
	class DocIDMask;
   class MessageStringConverter;
   class MessageFactory;
	class Message
	{
	public:
      Message(const Message& message);
      Message& operator=(const Message& message)     { copy(message); return *this; }

		Globals::MessID getMessID(void) const 			  {  return m_MessID;       		}
		String getMessageToken(void) const      	     {  return message_token;  		}
		int getTermStatus(void) const          	     {  return m_TermStatus;   		}
		int getTermID(void) const              	     {  return m_TermID;       		}
		String getEcrID(void) const              	     {  return ecr_ID;        		}
		String getDocID(void) const              	     {  return doc_ID;        		}
		String getTLVBlock(void) const              	  {  return tlv_block;       		}
		String getTLVBlockLength(void) const        	  {  return tlv_block_length; 	}
		Currency getAmount(void) const                 {  return m_Amount;       		}
		Globals::TransKind getTransKind(void) const    {  return m_TransKind;    		}
		AnsiString getAsString(void)const;
		int getCardType(void) const                    {  return m_CardType;     		}
		Globals::TransStat getTransStatus(void) const  {  return m_TransStatus;  		}
		String getRawMess(void) const;
		String getPinPadMsg(void) const                {  return m_PinPadMsg;         }
		int getPPMSize(void) const                     {  return m_PPMSize;           }
		Globals::RespKind getRespKind(void) const      {  return m_RespKind;         	}
		int getTimeOut(void) const                     {  return m_TimeOut;           }
		int getProfileId(void) const                   {  return m_ProfileId;         }
		Globals::PromptReq getPromptReq(void) const    {  return m_PromptReq;        	}

		void setAmount(const Currency& _Am) 					 { m_Amount = _Am;  		}
		void setTransKind(const Globals::TransKind& _TK)    { m_TransKind = _TK; 	}
		void setTransStatus(const Globals::TransStat _TS)   { m_TransStatus = _TS;	}
		void setCardType(const int _C) 							 { m_CardType = _C;		}
		void setPinPadMsg(const String& _Msg)  				 {	m_PinPadMsg = _Msg;	}
		void setPPMSize(const int _Si)  							 {	m_PPMSize = _Si;		}
		void setRespKind(const Globals::RespKind& _RK)  	 {	m_RespKind = _RK;		}
		void setTimeOut(const int _Ti)							 { m_TimeOut = _Ti;		}
		void setProfileId(const int _Pi)  						 {	m_ProfileId = _Pi;	}
		void setPromptReq(const Globals::PromptReq _Re)  	 {	m_PromptReq = _Re;	}
      void setFromString(const AnsiString&);
		void clear(void);
      ~Message(void);


	private:
      Message(MessageStringConverter*);
      void copy(const Message&);

      MessageStringConverter* message_string_converter;

		Globals::MessID m_MessID;

		int m_TermStatus;
		int m_TermID;
      String message_token;
		Currency m_Amount;

		Globals::TransKind m_TransKind;

		int m_CardType;

		Globals::TransStat m_TransStatus;

		String message_as_string;
		String m_PinPadMsg;
		int m_PPMSize;
      String ecr_ID;
      String doc_ID;
      const String tlv_block;
      const String tlv_block_length;

		Globals::RespKind m_RespKind;

		int m_TimeOut;
		int m_ProfileId;

		Globals::PromptReq m_PromptReq;

		friend ItcardMessIDMask;
		friend ItcardMessTokenMask;
		friend PostcardMessIDMask;
		friend TermStatusMask;
		friend TermIDMask;
		friend EcrIDMask;
		friend DocIDMask;
      friend MessageFactory;
	};
}//endnamespace
//---------------------------------------------------------------------------
#endif
