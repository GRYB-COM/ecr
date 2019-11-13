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

   /*! \brief Podstawowa klasa wyj�tk�w
   *
   * Klasa dziedziczy z Exception, dzi�ki czemu mo�e by� rzutowana do tej klasy
   * oraz by� przechwytywana w standardowy spos�b: catch(const Exception& exc).
   * Tre�� komunikatu, kt�r� zawiera klasa Exception w ramach ISException jest
   * okre�lana w nast�puj�cy spos�b:
   * <dl>
   * <li> je�eli do utworzenia obiektu u�ywany jest konstruktor z argumentem typu
   *      'const Exception&' (sta�a referencja do obiektu Exception), to tre��
   *      komunikatu jest r�wna zawarto�ci w�a�ciwo�ci Exception::Message przekazanego
   *      obiektu,
   * <li> je�eli do utworzenia obiektu u�ywany jest konstruktor bez wskazania
   *      obiektu typu Exception, to tre�� komunikatu jest albo pusta albo r�wna
   *      argumentowi zawieraj�cemu informacje o b��dzie.
   * </dl>
   * Przyj�ty spos�b tworzenia obiektu powoduje, �e rzutowanie w d� hierarchii
   * dziedziczenia do klasy Exception zawsze b�dzie przekazywa�o informacj� o
   * oryginalnym komunikacie o b��dzie, gubi�c jednocze�nie szczeg�owe dane
   * zwi�zane z klas� ISException.
   * Aby uzyska� pe�ny zakres informacji udost�nianych przez klas� ISException
   * nale�y przechwytywa� komunikaty o b��dzie za pomoc� sta�ej referencji do
   * ISException: catch(const ISException& exc) { ... }.
   *
   */
   class ISException : public Exception
   {
   public:

      /*! \brief Zadaniem klasy jest przechwycenie w konstruktorze rodzaju zg�oszonego wyj�tku i
      *         udost�pnienie o nim informacji.
      */
      class Info
      {
      public:

         /*! \brief Przechwytuje wyj�tek rozpoznaj�c jego typ
         */
         Info();

         /*! \brief Przekazanie b��du i wskazania do obiektu, kt�ry wyj�tek zg�osi�
         *
         * Do wykorzystania w zdarzeniu TApplication::OnException
         */
         Info(TObject* sender,Exception* exc);

         ~Info();

         /*! \brief Zasadnicza tre�� komunikatu o b��dzie
         *
         * Je�eli przechwycony wyj�tek jest klasy ISException, to funkcja zwraca warto�� odczytan� za
         * pomoc� ISException::getMessage. W przypadku, gdy funkcja ta zwr�ci pusty �a�cuch znak�w albo
         * gdy wyj�tek nie jest klasy ISException zwracany jest napis 'B��d wykonania programu'.
         */
         AnsiString getMessage() const;

         /*! \brief Szczeg�owe informacje na temat b��du
         *
         * W przypadku, gdy wyj�tek jest klasy ISException zwracana jest warto�� odczytana za pomoc�
         * ISException::getDetails(). Gdy warunek nie jest spe�niony, a wyj�tek jest typu Exception,
         * to funkcja zwraca warto�� r�wn� w�a�ciwo�ci Exception::Message.
         */
         AnsiString getDetails() const;

         /*! \brief Tre�� komunikatu pobrana z Exception::Message
         *
         * Je�eli przechwycony wyj�tek jest klasy ISException, to funkcja zwraca warto�� odczytan�
         * za pomoc� ISException::getOriginal. W przeciwnym razie zwracany jest pusty �a�cuch znak�w.
         */
         AnsiString getOriginal() const;

         //! Typ przechwyconego wyj�tku
         AnsiString getType() const;

         //! Nazwa modu�u, w kt�rym zosta� zg�oszony wyj�tek
         AnsiString getFile() const;

         //! Nazwa funkcji, w kt�rej zosta� zg�oszony wyj�tek
         AnsiString getFunction() const;

         //! Numer wiersza, w kt�rym zosta� zg�oszony wyj�tek
         int getLine() const;

         //! Czy s� dost�pne informacje szczeg�owe na temat wyj�tku ?
         bool hasDetails() const;

         //! Informacja o b��dzie w postaci elementu XML
         const xmlLib::XMLSequence* getXml() const;

         //! Wy�wietlenie komunikatu o b��dzie
         void display() const;

         /*! \brief Wy�wietlenie komunikatu o b��dzie
         *
         * Funkcja pozwala na zmian� g��wnego komunikatu oraz szczeg��w
         */
         void display(const AnsiString& msg,const AnsiString& details="") const;

         //! Wydrukowanie komunikatu o b��dzie
         bool print() const;

         /*! \brief Wys�anie opisu b��du bezpo�rednio do serwera INFO-SYSTEM-u
         *
         * \param user_info Uwagi wprowadzone przez operatora
         * \param disp_comm Czy wy�wietla� komunikat o wyniku wys�ania opisu b��du ?
         * \return Czy opis b��du zosta� pomy�lnie przes�any ?
         */
         bool send(const AnsiString& user_info,bool disp_comm) const;

         /*! Zwraca nag��wek pocz�tkowy pliku do zapisywania tre�ci wyj�tk�w
         *
         * Nag��wek zawiera tak�e nazw� g��wnego elementu (korzenia)
         */
         static AnsiString getXmlHeader();

         //! Zwraca znacznik ko�ca dokumentu XML (nazwa g��wnego elementu)
         static AnsiString getXmlFooter();

         //! Zapisanie tre�ci wyjatku do strumienia
         friend std::ostream& operator<<(std::ostream& fs,const ISException::Info& info);

      private:
         AnsiString           m_msg;     //!< Zasadnicza tre�� komunikatu o b��dzie
         AnsiString           m_details; //!< Szczeg�owe informacje o b��dzie
         AnsiString           m_type;    //!< Typ wyj�tku
         AnsiString           m_orig;    //!< Tre�� komunikatu z Exception::Message
         AnsiString           m_file;    //!< 
         AnsiString           m_func;    //!<
         int                  m_line;    //!<
         xmlLib::XMLSequence* m_xml;     //!< B��d w postaci elementu XML

         
         //! Utworzenie elementu XML opisuj�cego wyj�tek
         static xmlLib::XMLSequence* createXml(const AnsiString& type,const TDateTime& dt,const AnsiString& msg,const AnsiString& orig,const AnsiString& details);

         // klasa ISException korzysta z metody <createXml> do utworzenia elementu XML opisuj�cego wyj�tek
         friend ISException;
      };



      /*! \brief Przekazanie tre�ci komunikatu o b��dzie
      *
      * Rzutowanie do Exception da obiekt, kt�rego w�a�ciwo�� Message zawiera tre�� przekazanego
      * argumentu.
      */
      ISException(const AnsiString& msg);

      /*! \brief Przekazanie informacji o b��dzie za pomoc� obiektu Exception oraz
      *          dodatkowej tre�ci komunikatu
      *
      * Rzutowanie do Exception da obiekt, kt�rego zawarto�� b�dzie taka sama, jak zawarto��
      * argumentu exc.
      */
      ISException(const AnsiString& msg,const Exception& exc);

      /*! \brief Przekazanie tre�ci komunikatu o b��dzie z informacj� o miejscu
      *          jego wyst�pienia
      *
      * Rzutowanie do Exception da obiekt, kt�rego w�a�ciwo�� Message zawiera tre�� przekazanego
      * argumentu.
      */
      ISException(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line);

      /*! \brief Przekazanie informacji o b��dzie za pomoc� obiektu Exception oraz
      *          dodatkowej tre�ci komunikatu z informacj� o miejscu jego wyst�pienia
      *
      * Rzutowanie do Exception da obiekt, kt�rego zawarto�� b�dzie taka sama, jak zawarto��
      * argumentu exc.
      */
      ISException(const AnsiString& msg,const AnsiString& file,const AnsiString& func,int line,const Exception& exc);

      
      //! Nazwa modu�u, w kt�rym zosta� zg�oszony wyj�tek
      AnsiString getFile() const;

      //! Nazwa funkcji, z kt�rej zg�oszono wyj�tek
      AnsiString getFunction() const;

      //! Numer linii, z kt�rej zg�oszono wyj�tek
      int getLine() const;

      /*! \brief Tre�� komunikatu przekazanego w postaci �a�cucha znak�w podczas tworzenia obiektu
      *
      * Funkcja getOriginal oraz getMessage zwracaj� t� sam� warto�� w przypadku, gdy obiekt zosta�
      * utworzony bez przekazywania referencji do obiektu klasy Exception.
      */
      AnsiString getMessage() const;

      /*! \brief Tre�� komunikatu o b��dzie przekazanego za po�rednictwem argumentu typu Exception
      *          podczas tworzenia obiektu
      *
      * Je�eli obiekt zosta� utworzony na podstawie przekazanej referencji do obiektu klasy
      * Exception, to �a�cuch znak�w zwracany przez funkcj� b�dzie kopi� warto�ci odczytanej z tego
      * obiektu przez konstruktor. Je�eli powy�szy warunek nie jest spe�niony, to zwr�cony zostanie
      * komunikat przekazany do konstruktora w postaci �a�cucha znak�w.
      */
      AnsiString getOriginal() const;

      /*! \brief Zwraca nazw� typu wyj�tku
      *
      * Warto�� wykorzystywana jest przy zapisywaniu wyj�tku do pliku.
      */
      virtual AnsiString getType() const;

      //! Szczeg�owe informacje na temat b��du, specyficzne dla danego typu wyj�tku
      virtual AnsiString getDetails() const;

      //! Przekszta�cenie wyj�tku w element XML
      xmlLib::XMLSequence* toXml() const;

      //! Zapisanie wyj�tku do strumienia (jako element XML)
      friend std::ostream& operator<<(std::ostream& fs,const ISException& exc);

   protected:
      AnsiString m_file;  //!< Nazwa pliku, w kt�rym zg�oszony zosta� wyj�tek
      AnsiString m_func;  //!< Nazwa funkcji, w kt�rej zg�oszony zosta� wyj�tek
      int        m_line;  //!< Numer linii w funkcji
      AnsiString m_orig;  //!< Tre�� komunikatu o b��dzie przekazanego do kontruktora
                          //!< podczas tworzenia obiektu
      TDateTime  m_date;  //!< Data i czas, kiedy zosta� utworzony obiekt

      /*! \brief Uzupe�nienie przekazanego elementu XML o dane specyficzne dla danej kategorii
      *          wyj�tk�w
      */
      virtual void complete(xmlLib::XMLSequence* seq) const;

   };


   /*! \brief Standardowy wyj�tek z przekazaniem komunikatu og�lnego i szczeg�owego
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
   * Do zastosowania przy metodach i klasach fabrycznych, gdy nast�puje pr�ba
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


   /*! \brief B��d podczas wykonywania operacji na bazie danych
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
