/**
Henry Cagnini
201010352
*/

/**
A classe Cylinder cria um cilindro, dado
duas faces ou uma face e uma distância a partir
dela. O número de vértices da face que será top/bottom
não é relevante, pois é utilizado GL_POLYGON para desenho.
*/

#ifndef __CYLINDER__H__
#define __CYLINDER__H__

#include "Face.h"

class Cylinder {
private:
   Face top, bottom;
   std::vector<Face> side_face;

public:
   /**
   Cria um cilindro dado uma face e uma distância
   dessa face. A distância deve ser um vetor perpendicular
   à face.
   */
   Cylinder(Face bottom, TriPoint length);
   /**
   Cria um cilindro dado uma face que é o topo e outra a 
   base do cilindro. Cria as faces laterais do cilindro.
   */
   Cylinder(Face top, Face bottom);
   void draw(void);
   
   /**
   Métodos para pegar pontos relativos do cilindro.
   */
   TriPoint getMiddle(void);
   Face getTopFace(void);
   Face getBottomFace(void);
   std::vector<Face> getSideFaces(void);
   
   /**
   Translada o cilindro howMuch posições, nos 3 eixos.
   */
   void translate(TriPoint howMuch);
   /**
   Multiplica esse cilindro por uma matriz de transformação.
   */
   Cylinder multByMatrix(float *matrix);
};

#endif //__CYLINDER__H__
