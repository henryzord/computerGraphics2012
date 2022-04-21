/**
Henry Cagnini
201010352
*/

/**
A classe Piston representa um pist�o. Cria-se um pist�o
definindo qual bra�o estar� atrelado a ele, qual teclas
controlar�o a press�o do pist�o, em que �ngulo o pist�o
deve girar e qual dire��o deve ser extendido.
*/
#ifndef __PISTON__H__
#define __PISTON__H__

#include "Arm.h"
#include "Cylinder.h"

class Piston {
private:
   const static int face_vertex = 4, all_faces = 4;
   const static int large_width = 20;
   const static int min_piston = 0;  //m�ximo que o pist�o pode ser retra�do
   const static int max_piston = 30; //m�ximo que o pist�o pode ser extendido

   Arm *arm;
   Cylinder *tube_cyl, *extensor_cyl;
   TriPoint trans_extensor, trans_all, rotate_all, connection; 
   
   int pressure, key_up, key_down, rotateIn, translateIn;
   float all_matrix[Transformator::matrix_positions], extensor_matrix[Transformator::matrix_positions];
   
   /**
   Salva as matrizes de transforma��o. Isso � feito para evitar
   que a cada draw fa�a-se repetidas multiplica��es de matrizes,
   que no geral n�o difeririam muito no decorrer do tempo.
   */
   void saveTransformationMatrixes(void);

public:
   const static int x_axis = 0;
   const static int y_axis = 1;
   const static int z_axis = 2;

   /**
   Cria um pist�o que conecta-se � um arm, em um ponto connection.
   key_up e key_down definem as teclas de controle, e rotateIn e translateIn
   determinam em que orienta��o o pist�o deve ser extendido e rotacionado, em decorr�ncia
   do movimento do bra�o.
   */
   Piston(Arm *arm, TriPoint connection, int key_up, int key_down, int rotateIn, int translateIn);
   void draw(void);
   
   /**
   M�todo para aplicar for�a [i.e, extender o pist�o] sobre o bra�o conectado
   ao pist�o. Calcula tamb�m quanto o pist�o deve ser rotacionado e extendido
   para manter o ponto de conex�o correto.
   */
   void putForce(int key);
   void translate(TriPoint howMuch);

   /**
   M�todos para pegar a posi��o real de um determinado
   componente do pist�o.
   */
   TriPoint getRelativeMiddleTube(void);
   TriPoint getRelativeMiddleExtensor(void);
   TriPoint getOriginalMiddleExtensor(void);
   TriPoint getProperExtensorBottom(void);
   TriPoint getProperExtensorTop(void);
   TriPoint getProperTubeBottom(void);
   TriPoint getProperTubeTop(void);
   
   ~Piston(void);

   //callbacks
   void onKeyPressed(int key);
};

#endif //__PISTON__H__