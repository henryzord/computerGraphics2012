/**
Henry Cagnini
201010352
*/

/**
A class SweepObject constrói um objeto tridimensional em um espaço R³
baseado na noção de sólido de rotação. 
*/

#ifndef __SWEEP__OBJECT__H__
#define __SWEEP__OBJECT__H__

#include <SCV\SCV.h>
#include "TriPoint.h"

class SweepObject {
private:
   int steps, angleX, angleY, angleZ;
   TriPoint original_center, relative_center;
   std::vector<TriPoint> original, relative;

public:
   const static int revolution = 360;
   const static int initialX = 0;
   const static int initialY = 90;
   const static int initialZ = 0;

   /**
   Constrói um sólido de rotação baseado em um plano, que foi anteriormente desenhado no Canvas.
   */
   SweepObject(std::vector<scv::Point> bidimensional, int steps, int distanceFromCenter);
   /**
   Constrói um sólido de rotação baseado nas informações de outro sólido de rotação. A necessidade
   deste construtor deve-se para criar várias versões do mesmo objeto sendo rotacionadas n graus
   nos 3 eixos.
   */
   SweepObject(TriPoint originalCenter, TriPoint relativeCenter, std::vector<TriPoint> original, std::vector<TriPoint> relative, int steps, TriPoint angles);
   /**
   O centro relativo do objeto (onde ele realmente está em R³).
   */
   TriPoint getRelativeCenter();
   /**
   O centro original do objeto (geralmente centralizado na origem).
   */
   TriPoint getOriginalCenter();
   /**
   Pega os pontos de controle do objeto em R³.
   */
   std::vector<TriPoint> getRelative();
   /**
   Pega os pontos de controle do objeto que estão baseados em um centro
   posicionado na origem. Provê facilidade de manipulação do sólido.
   */
   std::vector<TriPoint> getOriginal();
   /**
   Em quantos passos esse sólido foi feito.
   Ex: 4 passos significa que ele terá pontos em 0º, 90º, 180º e 270º.
   */
   int getSteps();
   /**
   Ângulo que o eixo principal faz com o eixo X.
   */
   int getAngleX();
   /**
   Ângulo que o eixo principal faz com o eixo Y.
   */
   int getAngleY();
   /**
   Ângulo que o eixo principal faz com o eixo Z.
   */
   int getAngleZ();
};

#endif //__SWEEP__OBJECT__H__