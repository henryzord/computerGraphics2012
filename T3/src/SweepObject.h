/**
Henry Cagnini
201010352
*/

/**
A class SweepObject constr�i um objeto tridimensional em um espa�o R�
baseado na no��o de s�lido de rota��o. 
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
   Constr�i um s�lido de rota��o baseado em um plano, que foi anteriormente desenhado no Canvas.
   */
   SweepObject(std::vector<scv::Point> bidimensional, int steps, int distanceFromCenter);
   /**
   Constr�i um s�lido de rota��o baseado nas informa��es de outro s�lido de rota��o. A necessidade
   deste construtor deve-se para criar v�rias vers�es do mesmo objeto sendo rotacionadas n graus
   nos 3 eixos.
   */
   SweepObject(TriPoint originalCenter, TriPoint relativeCenter, std::vector<TriPoint> original, std::vector<TriPoint> relative, int steps, TriPoint angles);
   /**
   O centro relativo do objeto (onde ele realmente est� em R�).
   */
   TriPoint getRelativeCenter();
   /**
   O centro original do objeto (geralmente centralizado na origem).
   */
   TriPoint getOriginalCenter();
   /**
   Pega os pontos de controle do objeto em R�.
   */
   std::vector<TriPoint> getRelative();
   /**
   Pega os pontos de controle do objeto que est�o baseados em um centro
   posicionado na origem. Prov� facilidade de manipula��o do s�lido.
   */
   std::vector<TriPoint> getOriginal();
   /**
   Em quantos passos esse s�lido foi feito.
   Ex: 4 passos significa que ele ter� pontos em 0�, 90�, 180� e 270�.
   */
   int getSteps();
   /**
   �ngulo que o eixo principal faz com o eixo X.
   */
   int getAngleX();
   /**
   �ngulo que o eixo principal faz com o eixo Y.
   */
   int getAngleY();
   /**
   �ngulo que o eixo principal faz com o eixo Z.
   */
   int getAngleZ();
};

#endif //__SWEEP__OBJECT__H__