/**
Henry Cagnini
201010352
*/

#include "Backhoe.h"

Backhoe::Backhoe() {
   //define as faces dos objetos estáticos,
   //que serão usadas para desenhar cilindros, 
   //que por sua vez serão os objetos da escavadeira.
   TriPoint b_f_b[4] = {
      TriPoint(-60,-7,-20),TriPoint(-9,-7,-20),
      TriPoint(-9,-7,20),TriPoint(-60,-7,20)}, 
         c_f_b[4] = {
      TriPoint(-55,39,-18),TriPoint(-15,39,-18),
      TriPoint(-15,39,18),TriPoint(-55,39,18)}, 
         t_f_b[4] = {
      TriPoint(-9,60,-20),TriPoint(-60,60,-20),
      TriPoint(-60,60,20),TriPoint(-9,60,20)},
         h_f_b[4] = {
      TriPoint(15,20,-4),TriPoint(-15,20,-4),
      TriPoint(-15,20,4),TriPoint(15,20,4)};

   components[0] = new Cylinder(Face(&b_f_b[0], 4, TriPoint(1, 0.8f, 0.05f)), TriPoint(0, 46, 0));
   components[1] = new Cylinder(Face(&c_f_b[0], 4, TriPoint(0.6f, 0.85f, 0.91f)), TriPoint(0, 21, 0));
   components[2] = new Cylinder(Face(&t_f_b[0], 4, TriPoint(1, 0.8f, 0.05f)), TriPoint(0, 20, 0));
   components[3] = new Cylinder(Face(&h_f_b[0], 4, TriPoint(1, 0.8f, 0.05f)), TriPoint(0, 10, 0));

   //cria um braço na origem
   TriPoint fx[4] = {
      TriPoint(-25,-3,-4), TriPoint(-25,3,-4),
      TriPoint(-25,3,4),TriPoint(-25,-3,4)};

   arm = new Arm(Face(&fx[0], 4, TriPoint(1, 0.78f, 0.05f)), TriPoint(50, 0, 0));
   arm->rotate(TriPoint(0, 0, 90));
   arm->translate(TriPoint(15, 25, 0));

   //cria um pistão na origem
   piston = new Piston(arm, arm->getProperArmBottom(), M_KEY, N_KEY, Piston::z_axis, Piston::x_axis);
   piston->translate(TriPoint(-10, 0, 0));

   rotate_all.setValues(0, 0, 0);
   saveTransformationMatrix();
}

void Backhoe::saveTransformationMatrix(void) {
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(trans_all.getX(), trans_all.getY(), trans_all.getZ());
   glRotatef(rotate_all.getX(), -1, 0, 0);
   glRotatef(rotate_all.getY(), 0, -1, 0);
   glRotatef(rotate_all.getZ(), 0, 0, -1);
   glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0]);
   glPopMatrix();
}

void Backhoe::draw(void) {
   glLoadMatrixf(&matrix[0]);
   glPushMatrix();

   //objetos estáticos
   for(int n = 0; n < n_comp; n++) {
      components[n]->draw();
   }

   //objetos dinâmicos
   piston->draw();
   arm->draw();

   glPopMatrix();
}

void Backhoe::onMouseOver(int x, int y) {
   int ny = x - (int)prev_mouse.x, nx = y - (int)prev_mouse.y;
   rotate_all.setX((float)(((int)rotate_all.getX() + nx)%360));
   rotate_all.setY((float)(((int)rotate_all.getY() + ny)%360));
   prev_mouse.x = (float)x;
   prev_mouse.y = (float)y;

   saveTransformationMatrix();
}

void Backhoe::translate(TriPoint howMuch) {
   trans_all.setX(trans_all.getX() + howMuch.getX());
   trans_all.setY(trans_all.getY() + howMuch.getY());
   trans_all.setZ(trans_all.getZ() + howMuch.getZ());
}

void Backhoe::onKeyPressed(int key) {
   piston->onKeyPressed(key);
}

Backhoe::~Backhoe(void) {
   //objetos móveis
   delete piston;
   delete arm;
   //objetos estáticos
   for(int n = 0; n < n_comp; n++) {
      delete components[n];
   }
}