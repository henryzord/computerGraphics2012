/**
Autor: Henry Cagnini
Matr�cula: 201010352
*/

/**
Define a classe FileInterpreter, que � respons�vel por
ler um arquivo, interpretar seus valores e criar um vetor de
SampleCollections.
Trata erros que variam desde valores incorretos at� n�mero de cole��es incorreto.
*/

#ifndef __FILE__INTERPRETER__H__
#define __FILE__INTERPRETER__H__

#include <fstream>
#include <vector>

#include "SampleCollection.h"

class FileInterpreter {

public:
   const static int max_collections = 10;

private:

   const static int max_buffer = 64000;
   std::ifstream in;

   /**
   Coleta as samples contidas na string buffer.
   buffer - a string que cont�m as samples. Ela ser� quebrada e analisada por essa fun��o.
   return - o vetor com as SampleCollections da string
   */
   std::vector<SampleCollection> *sampleCollector(std::string *buffer);

   /**
   Retorna uma string que cont�m os caracteres lidos no arquivo path. Ser� armazenado na mem�ria principal.
   path - o caminho do arquivo a ser lido.
   return - a string contendo os caracteres lidos no arquivo. O buffer m�ximo � de 64KB, que � um valor muito superior
   � maior combina��o poss�vel dentro do arquivo (10 cole��es * 256 amostras * double) + outros caracteres ('\0', '\n', ' ')
   */
   std::string *fileReader(char *path);

   /**
   L� um n�mero expresso em uma string.
   str - a substring que cont�m apenas o n�mero
   return - um double com o n�mero
   */
   double stringReader(std::string str);

public:

   /**
   Construtor padr�o. Sem muita m�gica.
   */
   FileInterpreter();
   /**
   L� um arquivo no caminho especificado.
   path - o caminho do arquivo. Deve conter a termina��o ".txt".
   eturn - um vetor de SampleCollection com as amostras
   */
   std::vector<SampleCollection> *readFile(char *path);

};

#endif
