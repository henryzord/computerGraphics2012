/**
Henry Cagnini
201010352
*/

#include "Arm.h"

Arm::Arm(Face bottom, TriPoint length) {
   original_arm = new Cylinder(bottom, length);
   relative_arm = new Cylinder(bottom, length);

   TriPoint middle = original_arm->getMiddle(), b_cntr = original_arm->getBottomFace().getMiddle();

   TriPoint p0_f_b[6] = {
      TriPoint(middle.getX()-6,middle.getY(),middle.getZ()+5), TriPoint(middle.getX()-3,middle.getY()+4,middle.getZ()+5), TriPoint(middle.getX()+3,middle.getY()+4,middle.getZ()+5), 
      TriPoint(middle.getX()+6,middle.getY(),middle.getZ()+5), TriPoint(middle.getX()+3,middle.getY()-4,middle.getZ()+5), TriPoint(middle.getX()-3,middle.getY()-4,middle.getZ()+5)},
      p1_f_b[6] = {
      TriPoint(b_cntr.getX()-6,b_cntr.getY(),b_cntr.getZ()+5), TriPoint(b_cntr.getX()-3,b_cntr.getY()+4,b_cntr.getZ()+5), TriPoint(b_cntr.getX()+3,b_cntr.getY()+4,b_cntr.getZ()+5), 
      TriPoint(b_cntr.getX()+6,b_cntr.getY(),b_cntr.getZ()+5), TriPoint(b_cntr.getX()+3,b_cntr.getY()-4,b_cntr.getZ()+5), TriPoint(b_cntr.getX()-3,b_cntr.getY()-4,b_cntr.getZ()+5)};   

   original_pin[0] = new Cylinder(Face(&p0_f_b[0], 6, TriPoint(0.8f, 0.8f, 0.8f)), TriPoint(0, 0, 2*(middle.getZ()-5))); 
   original_pin[1] = new Cylinder(Face(&p1_f_b[0], 6, TriPoint(0.8f, 0.8f, 0.8f)), TriPoint(0, 0, 2*(b_cntr.getZ()-5))); 

   relative_pin[0] = new Cylinder(Face(&p0_f_b[0], 6, TriPoint(0.8f, 0.8f, 0.8f)), TriPoint(0, 0, 2*(middle.getZ()-5))); 
   relative_pin[1] = new Cylinder(Face(&p1_f_b[0], 6, TriPoint(0.8f, 0.8f, 0.8f)), TriPoint(0, 0, 2*(b_cntr.getZ()-5))); 

   rotate_all.setValues(0, 0, 0);
   trans_all.setValues(0, 0, 0);

   saveTransformationMatrix();
}

void Arm::saveTransformationMatrix(void) {
   //constrói uma matriz que modifica os pontos do braço
   float all_matrix0[Transformator::matrix_positions];

   glLoadIdentity();
   glRotatef(rotate_all.getX(), -1, 0, 0);
   glRotatef(rotate_all.getY(), 0, -1, 0);
   glRotatef(rotate_all.getZ(), 0, 0, -1);
   glGetFloatv(GL_MODELVIEW_MATRIX, &all_matrix0[0]);

   glLoadIdentity();
   glTranslatef(trans_all.getX(), trans_all.getY(), trans_all.getZ());
   glGetFloatv(GL_MODELVIEW_MATRIX, &all_matrix[0]); 

   *relative_arm = original_arm->multByMatrix(&all_matrix0[0]);
   *relative_pin[0] = original_pin[0]->multByMatrix(&all_matrix0[0]);
   *relative_pin[1] = original_pin[1]->multByMatrix(&all_matrix0[0]);

   glPopMatrix();
}

/**
Dado um certo número de graus para o braço girar, 
rotaciona-o e devolve o novo ponto de conexão
*/
TriPoint Arm::putForce(TriPoint addAngle) {
   rotate(addAngle);
   return getProperArmBottom();
}

void Arm::draw(void) {
   glMultMatrixf(&all_matrix[0]);

   relative_arm->draw();
   relative_pin[0]->draw();
   relative_pin[1]->draw();
}

Cylinder *Arm::getCylinder() {
   return original_arm;
}

void Arm::translate(TriPoint howMuch) {
   trans_all = trans_all + howMuch;

   saveTransformationMatrix();
}

void Arm::rotate(TriPoint howMuch) {
   rotate_all.setX((float)((int)(rotate_all.getX() + howMuch.getX())%360));
   rotate_all.setY((float)((int)(rotate_all.getY() + howMuch.getY())%360));
   rotate_all.setZ((float)((int)(rotate_all.getZ() + howMuch.getZ())%360));

   saveTransformationMatrix();
}

std::vector<float> Arm::createModificationMatrix(void) {
   std::vector<float> x_mat, y_mat, z_mat, trans_mat, result;
   x_mat = Transformator::createXRotationMatrix(Transformator::degreeToRadian((int)rotate_all.getX()));
   y_mat = Transformator::createYRotationMatrix(Transformator::degreeToRadian((int)rotate_all.getY()));
   z_mat = Transformator::createZRotationMatrix(Transformator::degreeToRadian((int)rotate_all.getZ()));
   trans_mat = Transformator::createTranslationMatrix(trans_all);

   result = Transformator::multiplyMatrix(trans_mat, z_mat);
   result = Transformator::multiplyMatrix(result, y_mat);
   result = Transformator::multiplyMatrix(result, x_mat);

   return result;
}

TriPoint Arm::getProperArmBottom(void) {
   std::vector<float> result = createModificationMatrix();
   return Transformator::multiplyMatrixByPoint(result, original_arm->getBottomFace().getMiddle());
}

TriPoint Arm::getProperArmTop(void) {
   std::vector<float> result = createModificationMatrix();
   return Transformator::multiplyMatrixByPoint(result, original_arm->getTopFace().getMiddle());
}

Arm::~Arm(void) {
   delete original_arm;
   delete relative_arm;
   for(int n = 0; n < n_pins; n++) {
      delete original_pin[n];
      delete relative_pin[n];
   }
}
