//---------------------------------------------------------------------------
#ifndef is_exceptionsH
#define is_exceptionsH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <ostream>
//---------------------------------------------------------------------------

namespace xmlLib
{
   class XMLSequence;
}

namespace mng
{

   /*! \brief Podstawowa klasa wyj¹tków
   *
   * Klasa dziedziczy z Exception, dziêki czemu mo¿e byæ rzutowana do tej klasy
   * oraz byæ przechwytywana w standardowy sposób: catch(const Exception& exc).
   * Treœæ komunikatu, któr¹ zawiera klasa Exception w ramach ISException jest
   * okreœlana w nastêpuj¹cy sposób:
   * <dl>
   * <li> je¿eli do utworzenia obiektu u¿ywany jest konstruktor z argumentem typu
   *      'const Exception&' (sta³a referencja do obiektu Exception), to treœæ
   *      komunikatu jest równa zawartoœci w³aœciwoœci Exception::Message przekazanego
   *      obiektu,
   * <li> je¿eli do utworzenia obiektu u¿ywany jest konstruktor bez wskazania
   *      obiektu typu Exception, to treœæ komunikatu jest albo pusta albo równa
   *      argumentowi zawieraj¹cemu informacje o b³êdzie.
   * </dl>
   * Przyjêty sposób tworzenia obiektu powoduje, ¿e rzutowanie w dó³ hierarchii
   * dziedziczenia do klasy Exception zawsze bêdzie przekazywa³o informacjê o
   * oryginalnym komunikacie o b³êdzie, gubi¹c jednoczeœnie szczegó³owe dane
   * zwi¹zane z klas¹ ISException.
   * Aby uzyskaæ pe³ny zakres informacji udostênianych przez klasê ISException
   * nale¿y przechwytywaæ komunikaty o b³êdzie za pomoc¹ sta³ej referencji do
   * ISException: catch(const ISException& exc) { ... }.
   *
   */
   class ISException : public Exception
   {
   public:

      /*! \brief Zadaniem klasy jest przechwycenie w konstruktorze rodzaju zg³oszonego wyj¹tku i
      *         udostêpnienie o nim informacji.
      */
      class Info
      {
      public:

         /*! \brief Przechwytuje wyj¹tek rozpoznaj¹c jego typ
         */
         Info();

         /*! \brief Przekazanie b³êdu i wskazania do obiektu, który wyj¹tek zg³osi³
         *
         * Do wykorzystania w zdarzeniu TApplication::OnException
         */
         Info(TObject* sender,Exception* exc);

         ~Info();

         /*! \brief Zasadnicza treœæ komunikatu o b³êdzie
         *
         * Je¿eli przechwycony wyj¹tek jest klasy ISException, to funkcja zwraca wartoœæ odczytan¹ za
         * pomoc¹ ISException::getMessage. W przypadku, gdy funkcja ta zwróci pusty ³añcuch znaków albo
         * gdy wyj¹tek nie jest klasy ISException zwracany jest napis 'B³¹d wykonania programu'.
         */
         AnsiString getMessage() const;

         /*! \brief Szczegó³owe informacje na temat b³êdu
         *
         * W przypadku, gdy wyj¹tek jest klasy ISException zwracana jest wartoœæ odczytana za pomoc¹
         * ISException::getDetails(). Gdy warunek nie jest spe³niony, a wyj¹tek jest typu Exception,
         * to funkcja zwraca wartoœæ równ¹ w³aœciwoœci Exception::Message.
         */
         AnsiString getDetails() const;

         /*! \brief Treœæ komunikatu pobrana z Exception::Message
         *
         * Je¿eli przechwycony wyj¹tek jest klasy ISException, to funkcja zwraca wartoœæ odczytan¹
         * za pomoc¹ ISException::getOriginal. W przeciwnym razie zwracany jest pusty ³añcuch znaków.
         */
         AnsiString getOriginal() const;

         //! Typ przechwyconego wyj¹tku
         AnsiString getType() const;

         //! Nazwa modu³u, w którym zosta³ zg³oszony wyj¹tek
         AnsiString getFile() const;

         //! Nazwa funkcji, w której zosta³ zg³oszony wyj¹tek
         AnsiString getFunction() const;

         //! Numer wiersza, w którym zosta³ zg³oszony wyj¹tek
         int getLine() const;

         //! Czy s¹ dostêpne informacje szczegó³owe na temat wyj¹tku ?
         bool hasDetails() const;

         //! Informacja o b³êdzie w postaci elementu XML
         const xmlLib::XMLSequence* getXml() const;

         //! Wyœwietlenie komunikatu o b³êdzie
         void display() const;

         /*! \brief Wyœwietlenie komunikatu o b³êdzie
         *
         * Funkcja pozwala na zmianê g³ównego komunikatu oraz szczegó³ów
         */
         void display(const AnsiString& msg,const AnsiString& details="") const;

         //! Wydrukowanie komunikatu o b³êdzie
         bool print() const;

         /*! \brief Wys³anie opisu b³êdu bezpoœrednio do serwera INFO-SYSTEM-u
         *
         * \param user_info Uwagi wprowadzone przez operatora
         * \param disp_comm Czy wyœwietlaæ komunikat o wyniku wys³ania opisu b³êdu ?
         * \return Czy opis b³êdu zosta³ pomyœlnie przes³any ?
         */
         bool send(const AnsiString& user_info,bool disp_comm) const;

         /*! Zwraca nag³ówek pocz¹tkowy pliku do zapisywania treœci wyj¹tków
         *
         * Nag³ówek zawiera tak¿e nazwê g³ównego elementu (korzenia)
         */
         static AnsiString getXmlHeader();

         //! Zwraca znacznik koñca dokumentu XML (nazwa g³ównego elementu)
         static AnsiString getXmlFooter();

         //! Zapisanie treœci wyjatku do strumienia
         friend std::ostream& operator<<(std::ostream& fs,const ISException::Info& info);

      private:
         AnsiString           m_msg;     //!< Zasadnicza treœæ komunikatu o b³êdzie
         AnsiString           m_details; //!< Szczegó³owe informacje o b³êdzie
         AnsiString           m_type;    //!< Typ wyj¹tku
         AnsiString           m_orig;    //!< Treœæ komunikatu z Exception::Message
         AnsiString           m_file;    //!< 
         AnsiString           m_func;    //!<
         int                  m_line;    //!<
         xmlLib::XMLSequence* m_xml;     //!< B³¹d w postaci elementu XML

         
         //! Utworzenie elementu XML opisuj¹cego wyj¹tek
         static xmlLib::XMLSequence* createXml(const AnsiString& type,const TDateTime& dt,const AnsiString& msg,const AnsiString& orig,const AnsiString& details);

         // klasa ISException korzysta z metody <createXml> do utworzenia elementu XML opisuj¹cego wyj¹tek
         friend ISException;
      };



      /*! \brief Przekazanie treœci komunikatu o b³êdzie
      *
      * Rzutowanie do Exception da obiekt, którego w³aœciwoœæ Message zawiera treœæ przekazanego
      * argumentu.
      */
      ISException(const AnsiString& msg);

      /*! \brief Przekazanie informacji o b³êdzie za pomoc¹ obiektu Exception oraz
      *          dodatkowej treœci komunikatu
      *
      * Rzutowanie do Exception da obiekt, którego zawartoœæ bêdzie taka sama, jak zawartoœæ
      * argumentu exc.
      */
      ISException(const AnsiString& msg,const Exception& exc);

      /*! \brief Przekazanie treœci komunikatu o b³êdzie z informacj¹ o miejscu
      *          jego wyst¹pienia
      *
      * Rzutowanie do Exception da obiekt, którego w³aœciwoœæ Message zawiera treœæ przekazanego
      * argumentu.
      */
      ISException(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line);

      /*! \brief Przekazanie informacji o b³êdzie za pomoc¹ obiektu Exception oraz
      *          dodatkowej treœci komunikatu z informacj¹ o miejscu jego wyst¹pienia
      *
      * Rzutowanie do Exception da obiekt, którego zawartoœæ bêdzie taka sama, jak zawartoœæ
      * argumentu exc.
      */
      ISException(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc);

      
      //! Nazwa modu³u, w którym zosta³ zg³oszony wyj¹tek
      AnsiString getFile() const;

      //! Nazwa funkcji, z której zg³oszono wyj¹tek
      AnsiString getFunction() const;

      //! Numer linii, z której zg³oszono wyj¹tek
      int getLine() const;

      /*! \brief Treœæ komunikatu przekazanego w postaci ³añcucha znaków podczas tworzenia obiektu
      *
      * Funkcja getOriginal oraz getMessage zwracaj¹ t¹ sam¹ wartoœæ w przypadku, gdy obiekt zosta³
      * utworzony bez przekazywania referencji do obiektu klasy Exception.
      */
      AnsiString getMessage() const;

      /*! \brief Treœæ komunikatu o b³êdzie przekazanego za poœrednictwem argumentu typu Exception
      *          podczas tworzenia obiektu
      *
      * Je¿eli obiekt zosta³ utworzony na podstawie przekazanej referencji do obiektu klasy
      * Exception, to ³añcuch znaków zwracany przez funkcjê bêdzie kopi¹ wartoœci odczytanej z tego
      * obiektu przez konstruktor. Je¿eli powy¿szy warunek nie jest spe³niony, to zwrócony zostanie
      * komunikat przekazany do konstruktora w postaci ³añcucha znaków.
      */
      AnsiString getOriginal() const;

      /*! \brief Zwraca nazwê typu wyj¹tku
      *
      * Wartoœæ wykorzystywana jest przy zapisywaniu wyj¹tku do pliku.
      */
      virtual AnsiString getType() const;

      //! Szczegó³owe informacje na temat b³êdu, specyficzne dla danego typu wyj¹tku
      virtual AnsiString getDetails() const;

      //! Przekszta³cenie wyj¹tku w element XML
      xmlLib::XMLSequence* toXml() const;

      //! Zapisanie wyj¹tku do strumienia (jako element XML)
      friend std::ostream& operator<<(std::ostream& fs,const ISException& exc);

   protected:
      AnsiString m_file;  //!< Nazwa pliku, w którym zg³oszony zosta³ wyj¹tek
      AnsiString m_func;  //!< Nazwa funkcji, w której zg³oszony zosta³ wyj¹tek
      int        m_line;  //!< Numer linii w funkcji
      AnsiString m_orig;  //!< Treœæ komunikatu o b³êdzie przekazanego do kontruktora
                          //!< podczas tworzenia obiektu
      TDateTime  m_date;  //!< Data i czas, kiedy zosta³ utworzony obiekt

      /*! \brief Uzupe³nienie przekazanego elementu XML o dane specyficzne dla danej kategorii
      *          wyj¹tków
      */
      virtual void complete(xmlLib::XMLSequence* seq) const;

   };


   /*! \brief Standardowy wyj¹tek z przekazaniem komunikatu ogólnego i szczegó³owego
   */
   class ISEDefault : public ISException
   {
   public:
      ISEDefault(const AnsiString& msg,const AnsiString& details,const AnsiString& file,const AnsiString& func,int line);

      ISEDefault(const AnsiString& msg,const AnsiString& details,const AnsiString& file,const AnsiString& func,int line,const Exception& exc);

      
      //! Implementuje ISException::getType
      virtual AnsiString getType() const;

      //! Implementuje ISException::getDetails
      virtual AnsiString getDetails() const;

   private:
      AnsiString m_details;
   };


   /*! \brief Indeks tablicy spoza zakresu
   */
   class ISEOutOfIndex : public ISException
   {
   public:
      ISEOutOfIndex(const AnsiString& msg);

      ISEOutOfIndex(const AnsiString& msg,const Exception& exc);

      ISEOutOfIndex(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line);

      ISEOutOfIndex(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc);


      //! Implementuje ISException::getType
      virtual AnsiString getType() const;
   };


   /*! \brief Element nieznanego rodzaju
   *
   * Do zastosowania przy metodach i klasach fabrycznych, gdy nastêpuje próba
   * utworzenia obiektu nieznanego rodzaju
   */
   class ISEUnknownItem : public ISException
   {
   public:
      ISEUnknownItem(const AnsiString& msg);

      ISEUnknownItem(const AnsiString& msg,const Exception& exc);

      ISEUnknownItem(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line);

      ISEUnknownItem(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc);

      
      //! Implementuje ISException::getType
      virtual AnsiString getType() const;
   };


   /*! \brief B³¹d podczas wykonywania operacji na bazie danych
   */
   class ISEDatabase : public ISException
   {
   public:
      ISEDatabase(const AnsiString& msg);

      ISEDatabase(const AnsiString& msg,const Exception& exc);

      ISEDatabase(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line);

      ISEDatabase(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const AnsiString& qu);

      ISEDatabase(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc);

      ISEDatabase(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc,const AnsiString& qu);

      
      //! Implementuje ISException::getType
      virtual AnsiString getType() const;

      //! Implementuje ISException::getDetails
      virtual AnsiString getDetails() const;

   protected:

      //! Implementacja funkcji ISException::complete
      virtual void complete(xmlLib::XMLSequence* seq) const;

   private:
      AnsiString m_query;
   };

} // namespace mng


#define ThrowExcIS(msg) throw mng::ISException(msg,__FILE__,__FUNC__,__LINE__)
#define ThrowExcDef(msg,dts) throw mng::ISEDefault(msg,dts,__FILE__,__FUNC__,__LINE__)
#define ThrowExcDefWith(msg,dts,exc) throw mng::ISEDefault(msg,dts,__FILE__,__FUNC__,__LINE__,exc)
#define ThrowExcAs(excName) throw excName(__FILE__,__FUNC__,__LINE__)
#define ThrowExcOf(excName,msg) throw excName(msg,__FILE__,__FUNC__,__LINE__)
#define ThrowExcOf1(excName,msg,arg1) throw excName(msg,__FILE__,__FUNC__,__LINE__,arg1)
#define ThrowExcOfWith(excName,msg,exc) throw excName(msg,__FILE__,__FUNC__,__LINE__,exc)
#define ThrowExcOfWith1(excName,msg,exc,arg1) throw excName(msg,__FILE__,__FUNC__,__LINE__,exc,arg1)

#endif
