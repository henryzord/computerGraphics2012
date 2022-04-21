/**
Henry Cagnini
201010352
*/

/**
A classe Camera representa uma C�mera, com seu centro de proje��o na origem 
de R�, olhando para um objeto que est� posicionado sobre o eixo Z. � esta classe
que possui o controle do objeto, logo, quando desejar-se transladar, rotacionar ou
escalar o objeto, as opera��es devem ser solicitadas atrav�s de seus m�todos, pois a 
Camera nunca pode deixar de olhar para o centro do objeto (posicionado sobre Z).
*/

#ifndef __CAMERA__H__
#define __CAMERA__H__

#include <SCV\SCV.h>

#include "Transformator.h"
#include "Plan.h"

class Camera {
private:
   scv::Point halfScreen;
   SweepObject *object;
   int projection;
   std::vector<scv::Point> toShow;

   std::vector<scv::Point> (*projection_call)(SweepObject, scv::Point);

public:
   const static int perspective = 0;
   const static int ortographic = 1;
   const static int defaultDistance = 1000;

   /**
   Constr�i uma camera que olha para o objeto object.
   projection refere-se ao modo de proje��o (perspectiva ou ortogr�fica), 
   e halfScreen diz o centro do plano no qual o objeto ser� projetado.
   Isto � usado para centralizar o objeto no plano.
   */
   Camera(SweepObject *object, int projection, scv::Point halfScreen);
   /**
   Mostra o objeto no plano de proje��o.
   */
   void displayObject(void);
   /**
   Modifica o objeto, rotacionando-o em um, algum ou todos os eixos.
   */
   void onPositionChanged(int rotateX, int rotateY, int rotateZ);
   /**
   Troca o modo de proje��o do plano, e altera o plano imediatamente.
   */
   void setProjection(int projection);
   /**
   Retorna os pontos (x,y) nos quais a reta do centro de proje��o at� cada
   ponto do objeto interceptou o Z do plano.
   */
   std::vector<scv::Point> *getToShow(void);
};

#endif //__CAMERA__H__