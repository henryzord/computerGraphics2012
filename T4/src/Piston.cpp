/**
Henry Cagnini
201010352
*/

#include "Piston.h"

Piston::Piston(Arm *arm, TriPoint connection, int key_up, int key_down, int rotateIn, int translateIn) {
   //cria a base do extensor_matrix e do tubo do pist�o
   TriPoint tube_basis[face_vertex] = {
      TriPoint(0,  6, -6),
      TriPoint(0,  6,  6),
      TriPoint(0, -6,  6),
      TriPoint(0, -6, -6)
   }, extensor_basis[face_vertex] = { 
      TriPoint(0,  3, -3),
      TriPoint(0,  3,  3),
      TriPoint(0, -3,  3),
      TriPoint(0, -3, -3)
   };

   //cores
   TriPoint tube_color(1, 0.8f, 0.05f), extensor_color(0.75f, 0.75f, 0.75f);

   //transforma��es
   trans_extensor.setValues(0, 0, 0);
   rotate_all.setValues(0, 0, 0);

   Face tube_bottom(&tube_basis[0], 4, tube_color), tube_top = (tube_bottom + TriPoint((float)large_width, 0, 0)),
      extensor_bottom(&extensor_basis[0], 4, extensor_color), extensor_top = (extensor_bottom + TriPoint((float)large_width+5, 0, 0));

   //o tubo e o extensor_matrix
   tube_cyl = new Cylinder(tube_top, tube_bottom);
   extensor_cyl = new Cylinder(extensor_top, extensor_bottom);

   //conecta o bra�o ao pist�o e define
   //a press�o atual
   pressure = 0;
   this->arm = arm;
   this->connection = connection;

   //para prop�sitos de callback
   this->key_up = key_up;
   this->key_down = key_down;
   this->rotateIn = rotateIn;
   this->translateIn = translateIn;

   saveTransformationMatrixes();
}

void Piston::saveTransformationMatrixes(void) {
   glLoadIdentity();
   glRotatef(rotate_all.getX(), -1, 0, 0);
   glRotatef(rotate_all.getY(), 0, -1, 0);
   glRotatef(rotate_all.getZ(), 0, 0, -1);
   glTranslatef(trans_all.getX(), trans_all.getY(), trans_all.getZ());
   glGetFloatv(GL_MODELVIEW_MATRIX, &all_matrix[0]);

   glLoadIdentity();
   glTranslatef(trans_extensor.getX(), trans_extensor.getY(), trans_extensor.getZ());
   glGetFloatv(GL_MODELVIEW_MATRIX, &extensor_matrix[0]);

   glPopMatrix();
}

void Piston::draw(void) {
   //todos os componentes
   glMultMatrixf(all_matrix);
   tube_cyl->draw();

   //apenas o extensor
   glMultMatrixf(extensor_matrix);
   extensor_cyl->draw();

   glPopMatrix(); 
}

void Piston::putForce(int key) {
   TriPoint angle0(0,0,0); //quanto graus deseja-se que o bra�o gire, nos eixos x, y e z
   boolean shouldRotate = false; //se a tecla � uma das definidas para este pist�o, torna-se true

   if(key == key_down) {
      if(pressure > min_piston) { //se a press�o aplicada � maior que o m�nimo poss�vel
         shouldRotate = true;
         angle0.setZ(-1); //sentido anti-hor�rio
         pressure -= 1;
      }
   }
   else {
      if(key == key_up) { 
         if(pressure < max_piston) { //se a press�o aplicada � menor que o m�ximo poss�vel
            shouldRotate = true;
            angle0.setZ(1); //sentido hor�rio
            pressure += 1;
         }
      }  
   }

   if(shouldRotate) {
      //bottomarm � o novo ponto de conex�o
      TriPoint bottomarm = arm->putForce(angle0), angle1, angledif, transdif;

      //cria um vetor que vai do eixo de rota��o do tubo [a sua base] at� o novo ponto de conex�o
      angle0 = Transformator::degreeTriAngle(tube_cyl->getBottomFace().getMiddle(), bottomarm);
      //cria um vetor que vai do eixo de rota��o do tubo [a sua base] at� o ponto de conex�o original
      angle1 = Transformator::degreeTriAngle(tube_cyl->getBottomFace().getMiddle(), connection);

      angledif = angle1 - angle0; //calcula o �ngulo entre os dois vetores
      transdif = bottomarm - connection; //cria um vetor que vai de connection at� bottomarm

      //de posse do �ngulo que os dois vetores fazem entre si,
      //do m�dulo do vetor que vai de connection at� bottomarm,
      //e do eixo que o pist�o deve girar e em qual dire��o ele deve ser extendido,
      //rotaciona o pist�o e o extende para alcan�ar o novo ponto de conex�o
      if(rotateIn == x_axis) {
         rotate_all.setX(angledif.getX());
      } else {
         if(rotateIn == y_axis) {
            rotate_all.setY(angledif.getY());
         } else {
            rotate_all.setZ(angledif.getZ());
         }
      }
      if(translateIn == x_axis) {
         trans_extensor.setX(transdif.getX());
      } else {
         if(translateIn == y_axis) {
            trans_extensor.setY(transdif.getY());
         } else {
            trans_extensor.setZ(transdif.getZ());
         }
      }
      //registra as modifica��es
      saveTransformationMatrixes();
   }
}


void Piston::onKeyPressed(int key) {
   putForce(key);
}

void Piston::translate(TriPoint howMuch) {
   trans_all = trans_all + howMuch;

   saveTransformationMatrixes();
}

TriPoint Piston::getProperTubeBottom(void) {
   return Transformator::multiplyMatrixByPoint(&all_matrix[0], tube_cyl->getBottomFace().getMiddle());
}

TriPoint Piston::getProperTubeTop(void) {
   return Transformator::multiplyMatrixByPoint(&all_matrix[0], tube_cyl->getTopFace().getMiddle());
}

TriPoint Piston::getProperExtensorBottom(void) {
   return Transformator::multiplyMatrixByPoint(&all_matrix[0], extensor_cyl->getBottomFace().getMiddle());
}

TriPoint Piston::getProperExtensorTop(void) {
   return Transformator::multiplyMatrixByPoint(&all_matrix[0], extensor_cyl->getTopFace().getMiddle());
}

TriPoint Piston::getRelativeMiddleTube(void) {
   return getProperTubeBottom().mean(getProperTubeTop());
}

TriPoint Piston::getRelativeMiddleExtensor(void) {
   return getProperExtensorBottom().mean(getProperExtensorTop());
}

TriPoint Piston::getOriginalMiddleExtensor(void) {
   return extensor_cyl->getBottomFace().getMiddle().mean(extensor_cyl->getTopFace().getMiddle());
}

Piston::~Piston(void) {
   delete tube_cyl;
   delete extensor_cyl;
}
