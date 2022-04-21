/**
Henry Cagnini
201010352
*/

/**
A classe Arm representa um braço móvel:
um cilindro com o centro de massa localizado
em seu centro. Possui dois pinos, um na
base [bottom] e outro no meio, para representar a conexão
com um pistão e um braço de apoio, respectivamente.
*/
#ifndef __ARM__H__
#define __ARM__H__

#include "Cylinder.h"

class Arm {
private:
   const static int n_pins = 2;

   Cylinder *original_arm, *original_pin[n_pins],
      *relative_arm, *relative_pin[n_pins];
   TriPoint trans_all, rotate_all;
   float all_matrix[Transformator::matrix_positions];
   
   void saveTransformationMatrix(void);
   std::vector<float> createModificationMatrix(void);

public:   
   Arm(Face bottom, TriPoint length);
   /**
   addAngle especifica quantos graus, em qual eixo de rotação,
   o braço deve girar. A partir disso, calcula as novas extremidades
   do brçao, e retorna este valor.
   */
   TriPoint putForce(TriPoint addAngle);
   Cylinder *getCylinder();
   void draw(void);
   void translate(TriPoint howMuch);
   void rotate(TriPoint howMuch);
   TriPoint getProperArmBottom(void);
   TriPoint getProperArmTop(void);

   ~Arm(void);

};

#endif //__ARM__H__