/**
Henry Cagnini
201010352
*/

/**
A classe Piston representa um pistão. Cria-se um pistão
definindo qual braço estará atrelado a ele, qual teclas
controlarão a pressão do pistão, em que ângulo o pistão
deve girar e qual direção deve ser extendido.
*/
#ifndef __PISTON__H__
#define __PISTON__H__

#include "Arm.h"
#include "Cylinder.h"

class Piston {
private:
   const static int face_vertex = 4, all_faces = 4;
   const static int large_width = 20;
   const static int min_piston = 0;  //máximo que o pistão pode ser retraído
   const static int max_piston = 30; //máximo que o pistão pode ser extendido

   Arm *arm;
   Cylinder *tube_cyl, *extensor_cyl;
   TriPoint trans_extensor, trans_all, rotate_all, connection; 
   
   int pressure, key_up, key_down, rotateIn, translateIn;
   float all_matrix[Transformator::matrix_positions], extensor_matrix[Transformator::matrix_positions];
   
   /**
   Salva as matrizes de transformação. Isso é feito para evitar
   que a cada draw faça-se repetidas multiplicações de matrizes,
   que no geral não difeririam muito no decorrer do tempo.
   */
   void saveTransformationMatrixes(void);

public:
   const static int x_axis = 0;
   const static int y_axis = 1;
   const static int z_axis = 2;

   /**
   Cria um pistão que conecta-se à um arm, em um ponto connection.
   key_up e key_down definem as teclas de controle, e rotateIn e translateIn
   determinam em que orientação o pistão deve ser extendido e rotacionado, em decorrência
   do movimento do braço.
   */
   Piston(Arm *arm, TriPoint connection, int key_up, int key_down, int rotateIn, int translateIn);
   void draw(void);
   
   /**
   Método para aplicar força [i.e, extender o pistão] sobre o braço conectado
   ao pistão. Calcula também quanto o pistão deve ser rotacionado e extendido
   para manter o ponto de conexão correto.
   */
   void putForce(int key);
   void translate(TriPoint howMuch);

   /**
   Métodos para pegar a posição real de um determinado
   componente do pistão.
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