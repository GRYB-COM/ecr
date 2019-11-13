//---------------------------------------------------------------------------


#pragma hdrstop

#include "is_exceptions.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

using namespace mng;

const char* const cc_RootName        = "exceptions";
const char* const cc_HostErrorEng    = "unable to complete network request to host \"";
const char* const cc_RuntimeError    = "B³¹d podczas wykonywania programu";
const char* const cc_HostErrorTitle  = "B³¹d podczas nawi¹zywania po³¹czenia z baz¹ danych";
const char* const cc_HostErrorDetBeg = "Nieudana próba po³¹czenia z serwerem bazy danych ";
const char* const cc_HostErrorDetEnd = "spowodowana b³êdem sieci";



/**********
*  Funkcje statyczne
**********/


static bool isHostError(const AnsiString& msg)
{
   return msg.LowerCase().Pos(cc_HostErrorEng) > 0;
}
//---------------------------------------------------------------------------

static AnsiString extractHostAddress(const AnsiString& msg)
{
   AnsiString ip_adr;

   int index_beg=msg.LowerCase().Pos(cc_HostErrorEng);

   if(index_beg > 0)
   {
      index_beg += strlen(cc_HostErrorEng);

      int index_end;

      for(index_end=index_beg+1;index_end <= msg.Length() && msg[index_end] != '\"';++index_end);

      if(index_end <= msg.Length())
      {
         ip_adr = msg.SubString(index_beg,index_end-index_beg);
      }
   }

   return ip_adr;
}
//---------------------------------------------------------------------------

static AnsiString replaceMarkers(const AnsiString& xml,bool skip_space=false)
{
   AnsiString result(xml);

   return result;
}
//---------------------------------------------------------------------------

static AnsiString replaceCarriages(const AnsiString& str,const AnsiString& to_text)
{
   AnsiString result;


   return result;
}
//------------------------------------------------------------------------------

static AnsiString replaceSpaces(const AnsiString& str)
{
   return str;
}
//------------------------------------------------------------------------------



/**********
*  Funkcje sk³adowe klasy: ISException::Info
**********/


ISException::Info::Info()
   : m_msg(), m_details(), m_type(), m_orig(), m_file(), m_func(), m_line(0), m_xml(NULL)
{
}
//---------------------------------------------------------------------------

ISException::Info::Info(TObject* sender,Exception* exc)
   : m_msg(), m_details(), m_type(), m_orig(), m_file(), m_func(), m_line(0), m_xml(NULL)
{
   ISException* ise=dynamic_cast<ISException*>(exc);

   if(ise)
   {
      m_msg     = ise->getMessage();
      m_type    = ise->getType();
      m_orig    = ise->getOriginal();
      m_xml     = ise->toXml();
      m_details = ise->getDetails();
      m_file    = ise->getFile();
      m_func    = ise->getFunction();
      m_line    = ise->getLine();
   }
   else
   {
      m_msg     = cc_RuntimeError;
      m_type    = "Exception";
      m_details = exc->Message;
   }

   if(isHostError(m_msg) || isHostError(m_details) || isHostError(m_orig))
   {
      AnsiString ip_adr(extractHostAddress(m_msg+" "+m_details+" "+m_orig));

      m_msg = cc_HostErrorTitle;
      m_details = cc_HostErrorDetBeg;

      if(!ip_adr.IsEmpty())
      {
         m_details += "(IP: '" + ip_adr + "') ";
      }

      m_details += cc_HostErrorDetEnd;
   }

   if(m_xml == NULL)
   {
      m_xml = createXml(m_type,Now(),m_msg,m_orig,m_details);
   }
}
//---------------------------------------------------------------------------

ISException::Info::~Info()
{
   delete m_xml;
}
//---------------------------------------------------------------------------

xmlLib::XMLSequence* ISException::Info::createXml(const AnsiString& type,const TDateTime& dt,const AnsiString& msg,const AnsiString& orig,const AnsiString& details)
{
   xmlLib::XMLSequence* seq(NULL);
   return seq;
}
//---------------------------------------------------------------------------

AnsiString ISException::Info::getMessage() const
{
   return m_msg;
}
//---------------------------------------------------------------------------

AnsiString ISException::Info::getDetails() const
{
   return m_details;
}
//---------------------------------------------------------------------------

AnsiString ISException::Info::getOriginal() const
{
   return m_orig;
}
//---------------------------------------------------------------------------

AnsiString ISException::Info::getType() const
{
   return m_type;
}
//---------------------------------------------------------------------------

AnsiString ISException::Info::getFile() const
{
   return m_file;
}
//---------------------------------------------------------------------------

AnsiString ISException::Info::getFunction() const
{
   return m_func;
}
//---------------------------------------------------------------------------

int ISException::Info::getLine() const
{
   return m_line;
}
//---------------------------------------------------------------------------

bool ISException::Info::hasDetails() const
{
   return !m_details.IsEmpty();
}
//---------------------------------------------------------------------------

const xmlLib::XMLSequence* ISException::Info::getXml() const
{
   return m_xml;
}
//---------------------------------------------------------------------------

void ISException::Info::display() const
{
}
//---------------------------------------------------------------------------

void ISException::Info::display(const AnsiString& msg,const AnsiString& details) const
{

}
//---------------------------------------------------------------------------

bool ISException::Info::print() const
{
   bool printed=true;

}
//---------------------------------------------------------------------------

bool ISException::Info::send(const AnsiString& user_info,bool disp_comm) const
{
   bool sent=false;
   return sent;
}
//------------------------------------------------------------------------------

AnsiString ISException::Info::getXmlHeader()
{
   AnsiString header;


   return header;
}
//---------------------------------------------------------------------------

AnsiString ISException::Info::getXmlFooter()
{
   return "</" + AnsiString(cc_RootName) + ">";
}
//---------------------------------------------------------------------------

std::ostream& mng::operator<<(std::ostream& fs,const ISException::Info& info)
{
   return fs;
}
//---------------------------------------------------------------------------



/**********
*  Funkcje sk³adowe klasy: ISException
**********/


ISException::ISException(const AnsiString& msg)
   : Exception(msg), m_file(), m_func(), m_line(0), m_orig(msg), m_date(Now())
{
}
//---------------------------------------------------------------------------

ISException::ISException(const AnsiString& msg,const Exception& exc)
   : Exception(exc.Message), m_file(), m_func(), m_line(0), m_orig(msg), m_date(Now())
{
}
//---------------------------------------------------------------------------

ISException::ISException(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line)
   : Exception(msg), m_file(file), m_func(func), m_line(line), m_orig(msg), m_date(Now())
{
}
//---------------------------------------------------------------------------

ISException::ISException(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc)
   : Exception(exc.Message), m_file(file), m_func(func), m_line(line), m_orig(msg), m_date(Now())
{
}
//---------------------------------------------------------------------------

void ISException::complete(xmlLib::XMLSequence* seq) const
{
}
//---------------------------------------------------------------------------

AnsiString ISException::getFile() const
{
   return m_file;
}
//---------------------------------------------------------------------------

AnsiString ISException::getFunction() const
{
   return m_func;
}
//---------------------------------------------------------------------------

int ISException::getLine() const
{
   return m_line;
}
//---------------------------------------------------------------------------

AnsiString ISException::getMessage() const
{
   return m_orig;
}
//---------------------------------------------------------------------------

AnsiString ISException::getOriginal() const
{
   return Message;
}
//---------------------------------------------------------------------------

AnsiString ISException::getType() const
{
   return "ISException";
}
//---------------------------------------------------------------------------

AnsiString ISException::getDetails() const
{
   return Message;
}
//---------------------------------------------------------------------------

xmlLib::XMLSequence* ISException::toXml() const
{
   xmlLib::XMLSequence* seq=NULL;

   try
   {
      seq = ISException::Info::createXml(getType(),m_date,Message,m_orig,getDetails());

   }
   catch(...)
   {
      delete seq;

      seq = NULL;
   }

   return seq;
}
//---------------------------------------------------------------------------

std::ostream& mng::operator<<(std::ostream& fs,const ISException& exc)
{
   return fs;
}
//---------------------------------------------------------------------------



/**********
*  Funkcje sk³adowe klasy: ISEDefault
**********/


ISEDefault::ISEDefault(const AnsiString& msg,const AnsiString& details,const AnsiString& file,const AnsiString& func,int line)
   : ISException(msg,file,func,line), m_details(details)
{
}
//---------------------------------------------------------------------------

ISEDefault::ISEDefault(const AnsiString& msg,const AnsiString& details,const AnsiString& file,const AnsiString& func,int line,const Exception& exc)
   : ISException(msg,file,func,line,exc), m_details(details)
{
}
//---------------------------------------------------------------------------

AnsiString ISEDefault::getType() const
{
   return "ISEDefault";
}
//---------------------------------------------------------------------------

AnsiString ISEDefault::getDetails() const
{
   return m_details;
}
//---------------------------------------------------------------------------



/**********
*  Funkcje sk³adowe klasy: ISEOutOfIndex
**********/


ISEOutOfIndex::ISEOutOfIndex(const AnsiString& msg)
   : ISException(msg)
{
}
//---------------------------------------------------------------------------

ISEOutOfIndex::ISEOutOfIndex(const AnsiString& msg,const Exception& exc)
   : ISException(msg,exc)
{
}
//---------------------------------------------------------------------------

ISEOutOfIndex::ISEOutOfIndex(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line)
   : ISException(msg,file,func,line)
{
}
//---------------------------------------------------------------------------

ISEOutOfIndex::ISEOutOfIndex(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc)
   : ISException(msg,file,func,line,exc)
{
}
//---------------------------------------------------------------------------

AnsiString ISEOutOfIndex::getType() const
{
   return "ISEOutOfIndex";
}
//---------------------------------------------------------------------------



/**********
*  Funkcje sk³adowe klasy: ISEUnknownItem
**********/


ISEUnknownItem::ISEUnknownItem(const AnsiString& msg)
   : ISException(msg)
{
}
//---------------------------------------------------------------------------

ISEUnknownItem::ISEUnknownItem(const AnsiString& msg,const Exception& exc)
   : ISException(msg,exc)
{
}
//---------------------------------------------------------------------------

ISEUnknownItem::ISEUnknownItem(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line)
   : ISException(msg,file,func,line)
{
}
//---------------------------------------------------------------------------

ISEUnknownItem::ISEUnknownItem(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc)
   : ISException(msg,file,func,line,exc)
{
}
//---------------------------------------------------------------------------

AnsiString ISEUnknownItem::getType() const
{
   return "ISEUnknownItem";
}
//---------------------------------------------------------------------------



/**********
*  Funkcje sk³adowe klasy: ISEDatabase
**********/


ISEDatabase::ISEDatabase(const AnsiString& msg) : ISException(msg), m_query()
{
}
//---------------------------------------------------------------------------

ISEDatabase::ISEDatabase(const AnsiString& msg,const Exception& exc)
   : ISException(msg,exc), m_query()
{
}
//---------------------------------------------------------------------------

ISEDatabase::ISEDatabase(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line)
   : ISException(msg,file,func,line), m_query()
{
}
//---------------------------------------------------------------------------

ISEDatabase::ISEDatabase(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const AnsiString& qu)
   : ISException(msg,file,func,line), m_query(qu)
{
}
//---------------------------------------------------------------------------

ISEDatabase::ISEDatabase(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc)
   : ISException(msg,file,func,line,exc), m_query()
{
}
//---------------------------------------------------------------------------

ISEDatabase::ISEDatabase(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc,const AnsiString& qu)
   : ISException(msg,file,func,line,exc), m_query(qu)
{
}
//---------------------------------------------------------------------------

void ISEDatabase::complete(xmlLib::XMLSequence* seq) const
{
}
//---------------------------------------------------------------------------

AnsiString ISEDatabase::getType() const
{
   return "ISEDatabase";
}
//---------------------------------------------------------------------------

AnsiString ISEDatabase::getDetails() const
{
   AnsiString msg;

   if(getOriginal() != getMessage())
   {
      msg = getOriginal();
   }
   else if(!m_query.IsEmpty())
   {
      msg += "Zapytanie: '" + m_query + "'";
   }

   return msg;
}
//---------------------------------------------------------------------------

