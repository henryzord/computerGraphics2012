/**
Henry Cagnini
201010352
*/

/**
A classe Backhoe define a escavadeira na sua totalidade.
Dentro desta classe, estão definidos objetos estáticos
[a cabine, vidro, braço de sustentação do braço móvel]
e móveis [o pistão e o braço móvel]. 
É através dela, também, que são chamados callbacks de 
objetos subordinados à ela.
*/

#ifndef __BACKHOE__H__
#define __BACKHOE__H__

#include "Piston.h"
#include "Arm.h"

class Backhoe {
private:
   const static int n_comp = 4; //número de componentes estáticos
   
   BiPoint prev_mouse;
   TriPoint trans_all, rotate_all;
   float matrix[Transformator::matrix_positions];
   
   Arm *arm;
   Piston *piston;
   Cylinder *components[n_comp];

   /**
   Salva a matriz de transformação. Isso é feito para evitar
   que a cada draw faça-se repetidas multiplicações de matrizes,
   que no geral não difeririam muito no decorrer do tempo.
   */
   void saveTransformationMatrix(void);

public:
   Backhoe();
   void draw(void);
   void translate(TriPoint howMuch);
   /**
   Callback para rotacionar a escavadeira, de acordo
   com o movimento do mouse.
   */
   void onMouseOver(int x, int y);
   /**
   Encaminha a tecla pressionada para todos os 
   objetos, para fazerem tratamento da tecla.
   */
   void onKeyPressed(int key);
   ~Backhoe(void);
};

#endif //__BACKHOE__H__