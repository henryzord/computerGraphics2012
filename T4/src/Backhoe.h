/**
Henry Cagnini
201010352
*/

/**
A classe Backhoe define a escavadeira na sua totalidade.
Dentro desta classe, est�o definidos objetos est�ticos
[a cabine, vidro, bra�o de sustenta��o do bra�o m�vel]
e m�veis [o pist�o e o bra�o m�vel]. 
� atrav�s dela, tamb�m, que s�o chamados callbacks de 
objetos subordinados � ela.
*/

#ifndef __BACKHOE__H__
#define __BACKHOE__H__

#include "Piston.h"
#include "Arm.h"

class Backhoe {
private:
   const static int n_comp = 4; //n�mero de componentes est�ticos
   
   BiPoint prev_mouse;
   TriPoint trans_all, rotate_all;
   float matrix[Transformator::matrix_positions];
   
   Arm *arm;
   Piston *piston;
   Cylinder *components[n_comp];

   /**
   Salva a matriz de transforma��o. Isso � feito para evitar
   que a cada draw fa�a-se repetidas multiplica��es de matrizes,
   que no geral n�o difeririam muito no decorrer do tempo.
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