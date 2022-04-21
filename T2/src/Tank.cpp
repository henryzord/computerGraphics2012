/**
Henry Cagnini
201010352
*/

#include "Tank.h"

void Tank::allignCannon(scv::Point aim) {
   int current_angle = Transformator::findDegreeAngle(relative->at(0), aim);      
   if(current_angle != previous_angle) {
      int howMuch = previous_angle - (previous_angle - current_angle);
         
      *relative = trans.modifyObject(relative->at(0), scv::Point(1,1), scv::Point(howMuch, howMuch), *original);
      regularizeFloatVector(relative, &vx[0], &vy[0], 1, relative->size()); 
      previous_angle = current_angle;
   }
}

void Tank::moveTank(scv::Point howMuch) {
   int right, left, up, down;
   right = relative->at(0).x + tire_length + howMuch.x;
   left = relative->at(0).x - tire_length + howMuch.x;
   up = relative->at(0).y - tire_length + howMuch.y;
   down = relative->at(0).y + tire_length + howMuch.y;
   if(right <= canvas->getWidth() && left >= 0 && up >= 0 && down <= canvas->getHeight()) {
      *relative = trans.modifyObject(relative->at(0) + howMuch, scv::Point(1,1), scv::Point(previous_angle, previous_angle), *original);
      regularizeFloatVector(relative, &vx[0], &vy[0], 1, relative->size());
      for(int n = 0; n < fire_points; n++) {
         relfirex[n] = firex[n] + vx[0];
         relfirey[n] = firey[n] + vy[0] + Tank::tire_length;
      }
   }
}
   
Tank::Tank(scv::Canvas *canvas, scv::Color4f object_color, scv::Point center) : MobileObject(canvas, object_color) {
   scv::Point v1[cannon_points+1] = {scv::Point(0,0), scv::Point(0, 3),scv::Point(20, 3),scv::Point(20, 0), scv::Point(20, -3),scv::Point(0, -3)};
   for(int n = 0; n < cannon_points+1;n++) {
      original->push_back(v1[n]);
      relative->push_back(v1[n] + center);
   }
   regularizeFloatVector(relative, &vx[0], &vy[0], 1, relative->size());

   previous_angle = 0;
   collisionRadix = tire_length;

   arrow.active = lockedCannon = false;
   active = true;

   scv::Point fire_values[fire_points] = {scv::Point(-4, 2), scv::Point(-10, -6), scv::Point(-4, -14), scv::Point(-2, -10), scv::Point(0, -18), scv::Point(2, -10), scv::Point(4, -14), scv::Point(10, -6), scv::Point(4,2)};
   for(int n = 0; n < fire_points; n++) {
      firex[n] = (float)fire_values[n].x;
      firey[n] = (float)fire_values[n].y;
      relfirex[n] = firex[n] + vx[0];
      relfirey[n] = firey[n] + vy[0] + Tank::tire_length;
   }
}

Arrow *Tank::getArrow(void) {
   return &arrow;
}

void Tank::render(void) {
   arrow.render();
   lockedCannon = arrow.active;
   if(active) {
      //desenha canhão
      canvas->color(object_color[0], object_color[1], object_color[2]);
      canvas->polygonFill(vx, vy, cannon_points);
      canvas->color(0,0,0);
      canvas->polygon(vx, vy, cannon_points);
      //desenha o pneu
      canvas->color(0.5f, 0.5f, 0.5f);
      canvas->circleFill(relative->at(0).x, relative->at(0).y, tire_length, 100);
      canvas->color(0,0,0);
      canvas->circle(relative->at(0).x, relative->at(0).y, tire_length, 100);
      //desenha o aro da roda
      canvas->color(object_color[0], object_color[1], object_color[2]);
      canvas->circleFill(relative->at(0).x, relative->at(0).y, wheel_length, 100);
      canvas->color(0,0,0);
      canvas->circle(relative->at(0).x, relative->at(0).y, wheel_length, 100);
   } else { //morto, desenha o fogo
      canvas->color(1, 0.5f, 0.15f);
      canvas->polygonFill(relfirex, relfirey, fire_points);
      canvas->color(0,0,0);
      canvas->polygon(relfirex, relfirey, fire_points);
   }
}

void Tank::onMouseOver(const scv::MouseEvent &evt) {
}
void Tank::onMouseClick(const scv::MouseEvent &evt) {
}
void Tank::onMouseHold(const scv::MouseEvent &evt) { 
}
void Tank::onMouseUp(const scv::MouseEvent &evt) {
}
void Tank::onKeyPressed(const scv::KeyEvent &evt) {
}
void Tank::onKeyUp(const scv::KeyEvent &evt) {
}
