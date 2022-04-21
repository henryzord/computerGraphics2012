/**
Henry Cagnini
201010352
*/

/**
Plan representa um plano posicionado sobre o eixo Z que irá se posicionar
(centro do objeto em Z)/2 unidades de distância do objeto. O centro de projeção
é sempre considerado como sendo sobre a origem.
*/

#ifndef __PLAN__H__
#define __PLAN__H__

#include <SCV\SCV.h>
#include "SweepObject.h"

class Plan {   
public:
   /**
   Representa o objeto no plano utilizando transformações de cordenadas por perspectiva.
   */
   static std::vector<scv::Point> perspectiveMatrix(SweepObject object, scv::Point pushTo);   
   /**
   Representa o objeto no plano utlizando multiplicação das coordenadas por uma matriz de 
   transformação ortográfica.
   */
   static std::vector<scv::Point> ortographicMatrix(SweepObject object, scv::Point pushTo);
};

#endif //__PLAN__H__