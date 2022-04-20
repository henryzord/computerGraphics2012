/**
Autor: Henry Cagnini
Matrícula: 201010352
*/

/**
Define e implementa as classes de exceções.
*/

#ifndef __EXCEPTIONS__H__
#define __EXCEPTIONS__H__

#include <iostream>

using namespace std;

#ifndef __READING__FILE__EXCEPTION__H__
#define __READING__FILE__EXCEPTION__H__

class ReadingFileException: public exception {
   virtual const char* what() const throw() {
      return "O arquivo nao pode ser aberto com exito.";
   }
};

#endif //__READING__FILE__EXCEPTION__H__

#ifndef __SYNTAX_EXCEPTION__H__
#define __SYNTAX_EXCEPTION__H__

class SyntaxException: public exception {
   virtual const char* what() const throw() {
      return "A sintaxe esta incorreta.";
   }
};

#endif //__SYNTAX_EXCEPTION__H__

#ifndef __VALUE_EXCEPTION__H__
#define __VALUE_EXCEPTION__H__

class ValueException: public exception {
   virtual const char* what() const throw() {
      return "Valor esta fora do intervalo de 2 <= valor <= 256.";
   }
};

#endif //__VALUE_EXCEPTION__H__

#ifndef __OUT_OF_RANGE_EXCEPTION__H__
#define __OUT_OF_RANGE_EXCEPTION__H__

class OutOfRangeException : public exception {

   virtual const char* what() const throw() {
      return "Indice invalido.";
   }
};

#endif //__OUT_OF_RANGE_EXCEPTION__H__

#endif //__EXCEPTIONS__H__
