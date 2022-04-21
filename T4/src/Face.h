/**
Henry Cagnini
201010352
*/

/**
A classe Face define uma face, que pode conter
quantos v�rtices forem desejados.
*/

#ifndef __FACE__H__
#define __FACE__H__

#include "Control.h"

#include "Transformator.h"

class Face {
private:
   TriPoint color;
   std::vector<TriPoint> vertex;

public:
   /**
   Constr�i uma face nula [i.e, um v�rtice]
   */
   Face();
   /**
   Constr�i uma face dado um vetor de v�rtices e uma cor.
   */
   Face(TriPoint *vec, int length, TriPoint color);
   /**
   Mesmo funcionamento que o construtor anterior, apenas utilizando
   um vector.
   */
   Face(std::vector<TriPoint> vertex, TriPoint color);
   /**
   Constr�i uma face com 4 v�rtices. � majoritariamente usada para construir
   as faces laterais de um clindro.
   */
   Face(TriPoint p1, TriPoint p2, TriPoint p3, TriPoint p4, TriPoint color);

   /**
   O n�mero de v�rtices dessa face.
   */
   int getNumberVertex();
   /**
   Pega os v�rtices da face.
   */
   std::vector<TriPoint> *getVertex();
   void draw(void);

   /**
   Cria uma nova face face p1 
   pontos de dist�ncia da face this.
   */
   Face operator+ (TriPoint p1);
   TriPoint getColor(void);
   void translate(TriPoint howMuch);
   /**
   O centro da face.
   */
   TriPoint getMiddle(void);
   /**
   Multiplica a face por uma matriz de transforma��o.
   */
   Face multByMatrix(float *matrix);
};

#endif //__FACE__H__