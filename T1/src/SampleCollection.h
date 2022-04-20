/**
Autor: Henry Cagnini
Matr�cula: 201010352
*/

/**
O SampleCollection � uma classe que pode conter de
2 � 256 amostras. A validade do valor da amostra (se � um valor
entre -128 e 127) � tratada no construtor.
A SampleCollection possui uma classe protegida chamada CosinTransformer,
que � respons�vel por calcular DCT, IDCT, CDCT (compressed DCT) e CIDCT (compressed IDCT -- 
recebe essa terminologia por quest�es pr�ticas, pois a IDCT � calculada da mesma forma.)
*/

#ifndef __SAMPLE__COLLECTION__H__
#define __SAMPLE__COLLECTION__H__

#include <iostream>

#include "Exceptions.h"

const static double rest_coef = 1;
const static double first_coef = 0.7071067811865475;
const static double pi = 3.1415926535897932384626433832795028841971693993751058;

class SampleCollection {

public:
   const static int min_samples = 2, max_samples = 256;
   const static int min_value = -128, max_value = 127;

protected:
   double smps[max_samples], dcts[max_samples], idcts[max_samples], cdcts[max_samples], cidcts[max_samples];
   int nsmps;
   bool hasCDCT, hasCIDCT;

public:
   /**
   Constr�i uma SampleCollection atrav�s de dados inseridos.
   samples - um vetor com length dados amostrados
   length - o tamanho do vetor.
   */
   SampleCollection(double samples[], int length);

   /**
   Constr�i uma SampleCollection atrav�s de outra SampleCollection.
   matrix - a SampleCollection que servir� de refer�ncia para esta.
   */
   SampleCollection(SampleCollection *matrix);

   /**
   Pega a amostra na posi��o index, desde que ela exista.
   O �ndice come�a em 0 e termina em getAmount(), isto �,
   0 <= index < getAmount()
   index - o �ndice da amostra que se deseja
   return - o valor da amostra, em double
   */
   double getSample(int index);

   /**
   Pega a transformada coseno na posi��o index, desde que ela exista.
   O �ndice come�a em 0 e termina em getAmount(), isto �,
   0 <= index < getAmount()
   index - o �ndice da DCT que se deseja
   return - o valor da amostra, em double
   */
   double getDCT(int index);

   /**
   Pega a transformada coseno inversa na posi��o index, desde que ela exista.
   O �ndice come�a em 0 e termina em getAmount(), isto �,
   0 <= index < getAmount()
   index - o �ndice da IDCT que se deseja
   return - o valor da amostra, em double
   */
   double getIDCT(int index);

   /**
   Pega a transformada coseno comprimida na posi��o index, desde que ela exista.
   O �ndice come�a em 0 e termina em getAmount(), isto �,
   0 <= index < getAmount()
   index - o �ndice da CDCT que se deseja
   return - o valor da amostra, em double
   */
   double getCDCT(int index);

   /**
   Pega a transformada coseno inversa comprimida na posi��o index, desde que ela exista.
   O �ndice come�a em 0 e termina em getAmount(), isto �,
   0 <= index < getAmount()
   index - o �ndice da CIDCT que se deseja
   return - o valor da amostra, em double
   */
   double getCIDCT(int index);

   /**
   Pega a quantidade de amostras dessa cole��o.
   return - o n�mero de amostras
   */
   int getAmount();

   /**
   Imprime no console os valores das samples contidas na classe.
   */
   void printSamples();

   /**
   Imprime no console os valores das DCTS contidas na classe.
   */
   void printDCT();

   /**
   Imprime no console os valores das IDCTS contidas na classe.
   */
   void printIDCT();

   /**
   Imprime samples, DCTs e IDCTs, junto.
   */
   void printAll();

   /**
   Pergunta se essa cole��o j� est� comprimida.
   */
   bool isCompressed();

   /**
   Chama os m�todos de compress�o do CosinTransformer,
   se essa SampleCollection ainda n�o foi comprimida.
   */
   void compressCollection();

   /**
   *Destrutor padr�o.
   */
   ~SampleCollection();


protected:

   /**
   *Bibliografia:
   *http://pessoal.utfpr.edu.br/hvieir/EL55E/dct_slides.pdf [1]
   *http://pt.wikipedia.org/wiki/Transformada_discreta_de_cosseno [2]
   */

   /**
   Classe respons�vel por fazer a transformada coseno, inversa, comprimida e comprimida inversa.
   As CDCT e CIDCT n�o s�o calculadas na cria��o da SampleCollection, porque talvez n�o sejam utilizadas.
   Mas quando solicitado, ser�o criadas e armazenadas nos respectivos vetores.
   */
   class CosinTransformer {

   private:
      double static coef(int index);
   public:
      CosinTransformer();
      /**
      Calcula a DCT. O modelo matem�tico utilizado pode ser conferido em [2].
      Ir� escrever no vetor dcts dessa SampleCollection.
      matrix - a SampleCollection que se deseja calcular a DCT.
      */
      void static calculateDCT(SampleCollection *matrix);

      /**
      Calcula a IDCT. O modelo matem�tico utilizado pode ser conferido em [2].
      Ir� escrever no vetor idcts dessa SampleCollection.
      matrix - a SampleCollection que se deseja calcular a IDCT.
      */
      void static calculateIDCT(SampleCollection *matrix);
      /**
      Calcula a CDCT. O modelo de compress�o consiste em truncar os valores que ultrapassam
      a metade do tamanho da quantidade de samples, substitu�ndo-os por zeros. 
      Ir� escrever no vetor cdcts dessa SampleCollection.
      matrix - a SampleCollection que se deseja calcular a CDCT.
      */
      void static calculateCDCT(SampleCollection *matrix);
      /**
      Calcula a CIDCT. � o mesmo c�lculo executado pela IDCT, mas ir� escrever no vetor
      cidcts dessa SampleCollection.
      matrix - a SampleCollection que se deseja calcular a CIDCT.
      */
      void static calculateCIDCT(SampleCollection *matrix);
   };
   //para possibilitar que a classe compressor utilize a calculateCDCT e calculateCIDCT.
   friend class Compressor;
};

#endif //__SAMPLE__COLLECTION__H__
