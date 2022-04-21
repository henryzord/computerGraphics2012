/**
Henry Cagnini
201010352
*/

/**
A classe Cylinder cria um cilindro, dado
duas faces ou uma face e uma dist�ncia a partir
dela. O n�mero de v�rtices da face que ser� top/bottom
n�o � relevante, pois � utilizado GL_POLYGON para desenho.
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
   Cria um cilindro dado uma face e uma dist�ncia
   dessa face. A dist�ncia deve ser um vetor perpendicular
   � face.
   */
   Cylinder(Face bottom, TriPoint length);
   /**
   Cria um cilindro dado uma face que � o topo e outra a 
   base do cilindro. Cria as faces laterais do cilindro.
   */
   Cylinder(Face top, Face bottom);
   void draw(void);
   
   /**
   M�todos para pegar pontos relativos do cilindro.
   */
   TriPoint getMiddle(void);
   Face getTopFace(void);
   Face getBottomFace(void);
   std::vector<Face> getSideFaces(void);
   
   /**
   Translada o cilindro howMuch posi��es, nos 3 eixos.
   */
   void translate(TriPoint howMuch);
   /**
   Multiplica esse cilindro por uma matriz de transforma��o.
   */
   Cylinder multByMatrix(float *matrix);
};

#endif //__CYLINDER__H__
