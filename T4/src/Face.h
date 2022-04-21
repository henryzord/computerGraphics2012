/**
Henry Cagnini
201010352
*/

/**
A classe Face define uma face, que pode conter
quantos vértices forem desejados.
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
   Constrói uma face nula [i.e, um vértice]
   */
   Face();
   /**
   Constrói uma face dado um vetor de vértices e uma cor.
   */
   Face(TriPoint *vec, int length, TriPoint color);
   /**
   Mesmo funcionamento que o construtor anterior, apenas utilizando
   um vector.
   */
   Face(std::vector<TriPoint> vertex, TriPoint color);
   /**
   Constrói uma face com 4 vértices. É majoritariamente usada para construir
   as faces laterais de um clindro.
   */
   Face(TriPoint p1, TriPoint p2, TriPoint p3, TriPoint p4, TriPoint color);

   /**
   O número de vértices dessa face.
   */
   int getNumberVertex();
   /**
   Pega os vértices da face.
   */
   std::vector<TriPoint> *getVertex();
   void draw(void);

   /**
   Cria uma nova face face p1 
   pontos de distância da face this.
   */
   Face operator+ (TriPoint p1);
   TriPoint getColor(void);
   void translate(TriPoint howMuch);
   /**
   O centro da face.
   */
   TriPoint getMiddle(void);
   /**
   Multiplica a face por uma matriz de transformação.
   */
   Face multByMatrix(float *matrix);
};

#endif //__FACE__H__