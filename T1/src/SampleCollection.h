/**
Autor: Henry Cagnini
Matrícula: 201010352
*/

/**
O SampleCollection é uma classe que pode conter de
2 à 256 amostras. A validade do valor da amostra (se é um valor
entre -128 e 127) é tratada no construtor.
A SampleCollection possui uma classe protegida chamada CosinTransformer,
que é responsável por calcular DCT, IDCT, CDCT (compressed DCT) e CIDCT (compressed IDCT -- 
recebe essa terminologia por questões práticas, pois a IDCT é calculada da mesma forma.)
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
   Constrói uma SampleCollection através de dados inseridos.
   samples - um vetor com length dados amostrados
   length - o tamanho do vetor.
   */
   SampleCollection(double samples[], int length);

   /**
   Constrói uma SampleCollection através de outra SampleCollection.
   matrix - a SampleCollection que servirá de referência para esta.
   */
   SampleCollection(SampleCollection *matrix);

   /**
   Pega a amostra na posição index, desde que ela exista.
   O índice começa em 0 e termina em getAmount(), isto é,
   0 <= index < getAmount()
   index - o índice da amostra que se deseja
   return - o valor da amostra, em double
   */
   double getSample(int index);

   /**
   Pega a transformada coseno na posição index, desde que ela exista.
   O índice começa em 0 e termina em getAmount(), isto é,
   0 <= index < getAmount()
   index - o índice da DCT que se deseja
   return - o valor da amostra, em double
   */
   double getDCT(int index);

   /**
   Pega a transformada coseno inversa na posição index, desde que ela exista.
   O índice começa em 0 e termina em getAmount(), isto é,
   0 <= index < getAmount()
   index - o índice da IDCT que se deseja
   return - o valor da amostra, em double
   */
   double getIDCT(int index);

   /**
   Pega a transformada coseno comprimida na posição index, desde que ela exista.
   O índice começa em 0 e termina em getAmount(), isto é,
   0 <= index < getAmount()
   index - o índice da CDCT que se deseja
   return - o valor da amostra, em double
   */
   double getCDCT(int index);

   /**
   Pega a transformada coseno inversa comprimida na posição index, desde que ela exista.
   O índice começa em 0 e termina em getAmount(), isto é,
   0 <= index < getAmount()
   index - o índice da CIDCT que se deseja
   return - o valor da amostra, em double
   */
   double getCIDCT(int index);

   /**
   Pega a quantidade de amostras dessa coleção.
   return - o número de amostras
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
   Pergunta se essa coleção já está comprimida.
   */
   bool isCompressed();

   /**
   Chama os métodos de compressão do CosinTransformer,
   se essa SampleCollection ainda não foi comprimida.
   */
   void compressCollection();

   /**
   *Destrutor padrão.
   */
   ~SampleCollection();


protected:

   /**
   *Bibliografia:
   *http://pessoal.utfpr.edu.br/hvieir/EL55E/dct_slides.pdf [1]
   *http://pt.wikipedia.org/wiki/Transformada_discreta_de_cosseno [2]
   */

   /**
   Classe responsável por fazer a transformada coseno, inversa, comprimida e comprimida inversa.
   As CDCT e CIDCT não são calculadas na criação da SampleCollection, porque talvez não sejam utilizadas.
   Mas quando solicitado, serão criadas e armazenadas nos respectivos vetores.
   */
   class CosinTransformer {

   private:
      double static coef(int index);
   public:
      CosinTransformer();
      /**
      Calcula a DCT. O modelo matemático utilizado pode ser conferido em [2].
      Irá escrever no vetor dcts dessa SampleCollection.
      matrix - a SampleCollection que se deseja calcular a DCT.
      */
      void static calculateDCT(SampleCollection *matrix);

      /**
      Calcula a IDCT. O modelo matemático utilizado pode ser conferido em [2].
      Irá escrever no vetor idcts dessa SampleCollection.
      matrix - a SampleCollection que se deseja calcular a IDCT.
      */
      void static calculateIDCT(SampleCollection *matrix);
      /**
      Calcula a CDCT. O modelo de compressão consiste em truncar os valores que ultrapassam
      a metade do tamanho da quantidade de samples, substituíndo-os por zeros. 
      Irá escrever no vetor cdcts dessa SampleCollection.
      matrix - a SampleCollection que se deseja calcular a CDCT.
      */
      void static calculateCDCT(SampleCollection *matrix);
      /**
      Calcula a CIDCT. É o mesmo cálculo executado pela IDCT, mas irá escrever no vetor
      cidcts dessa SampleCollection.
      matrix - a SampleCollection que se deseja calcular a CIDCT.
      */
      void static calculateCIDCT(SampleCollection *matrix);
   };
   //para possibilitar que a classe compressor utilize a calculateCDCT e calculateCIDCT.
   friend class Compressor;
};

#endif //__SAMPLE__COLLECTION__H__
