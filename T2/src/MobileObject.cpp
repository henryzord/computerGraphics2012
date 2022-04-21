/**
Henry Cagnini
201010352
*/

#include "MobileObject.h"

void MobileObject::regularizeFloatVector(std::vector<scv::Point> *vec, float *vx, float *vy, int init, int end) {
   for(int n = init; n < end; n++) {
      *vx = (float)relative->at(n).x;
      *vy = (float)relative->at(n).y;
      vx++;
      vy++;
   }
}
   
MobileObject::MobileObject(scv::Canvas *canvas, scv::Color4f object_color) {
   this->canvas = canvas;
   this->object_color = object_color;

   relative = new std::vector<scv::Point>();
   original = new std::vector<scv::Point>();
   active = false;
}

scv::Point MobileObject::getCenter(void) {
   return relative->at(0);
}
//considera os objetos a serem colididos como círculos
//desativa os dois caso eles se colidam
void MobileObject::collides(MobileObject *object) {
   if(active && object->active) {
      int difx, dify;
      if(relative->at(0).x > object->getCenter().x) {
         difx = relative->at(0).x - object->getCenter().x;
      } else {
         difx = object->getCenter().x - relative->at(0).x;
      }
      if(relative->at(0).y > object->getCenter().y) {
         dify = relative->at(0).y - object->getCenter().y;
      } else {
         dify = object->getCenter().y - relative->at(0).y;
      }
         
      if(difx <= (collisionRadix + object->collisionRadix) && dify <= (collisionRadix + object->collisionRadix)) {
         active = object->active = false;
      }
   }
}

void MobileObject::render(void) {
}
void MobileObject::update(void) {
}
   
MobileObject::~MobileObject(void) {
   delete original;
   delete relative;
}
