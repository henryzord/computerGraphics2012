/**
Autor: Henry Cagnini
Matrícula: 201010352
*/

/**
Define a classe FileInterpreter, que é responsável por
ler um arquivo, interpretar seus valores e criar um vetor de
SampleCollections.
Trata erros que variam desde valores incorretos até número de coleções incorreto.
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
   buffer - a string que contém as samples. Ela será quebrada e analisada por essa função.
   return - o vetor com as SampleCollections da string
   */
   std::vector<SampleCollection> *sampleCollector(std::string *buffer);

   /**
   Retorna uma string que contém os caracteres lidos no arquivo path. Será armazenado na memória principal.
   path - o caminho do arquivo a ser lido.
   return - a string contendo os caracteres lidos no arquivo. O buffer máximo é de 64KB, que é um valor muito superior
   à maior combinação possível dentro do arquivo (10 coleções * 256 amostras * double) + outros caracteres ('\0', '\n', ' ')
   */
   std::string *fileReader(char *path);

   /**
   Lê um número expresso em uma string.
   str - a substring que contém apenas o número
   return - um double com o número
   */
   double stringReader(std::string str);

public:

   /**
   Construtor padrão. Sem muita mágica.
   */
   FileInterpreter();
   /**
   Lê um arquivo no caminho especificado.
   path - o caminho do arquivo. Deve conter a terminação ".txt".
   eturn - um vetor de SampleCollection com as amostras
   */
   std::vector<SampleCollection> *readFile(char *path);

};

#endif
