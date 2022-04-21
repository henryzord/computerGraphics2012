/**
Henry Cagnini
201010352
*/

#include "Arrow.h"
#include "Tank.h"

void Arrow::rotateArrow(void) {
   int angle = trans.findDegreeAngle(previous, pos);
   *relative = trans.modifyObject(pos, scv::Point(1,1), scv::Point(angle, angle), *original);
   regularizeFloatVector(relative, &vx[0], &vy[0], 0, relative->size());
}

void Arrow::createFunction(void) {
   //descobre o ymax adequado à função
   float x1, x2, ymax;
   x1 = (float)dif;
   x2 = (float)x1/2.f;
   ymax = dif*factor;

   af = ymax/(pow(x2,2.f) - (x1*x2));
   bf = -1.f * af * x1;
}
   
//ok
int Arrow::findY(int x) {
   float y = (af * pow((float)x, 2.f)) + (bf*((float)x));
   return (int)y;
}

int Arrow::findX(int y) {
   float delta = pow(bf, 2.f) - 4.f * af * (float)(-y), x1, x2;
   x1 = (-bf * -(sqrt(delta)))/(2.f*af); //caso negativo
   x2 = (-bf * (sqrt(delta)))/(2.f*af);  //caso positivo
   return ((x1 > x2)*(int)x1) + ((x1 < x2)*(int)x2);
}

void Arrow::updateData(scv::Canvas *canvas, scv::Point launchPosition, scv::Point target) {
   if(!active) {
      this->canvas = canvas;
      this->launchPosition = launchPosition;
      this->target = target;

      factor = (float)(launchPosition.y - Tank::tire_length)/(float)(canvas->getWidth() - Tank::tire_length);
      toRight = (target.x > launchPosition.x);
      dif = (toRight)*(target.x - launchPosition.x) + (!toRight)*(launchPosition.x - target.x);
      createFunction();

      //como update é chamada antes de render, deve iniciar um antes para o x inicial ser zero OU o x da outra raiz
      time = (toRight)*(-1*(int)(arrow_step/factor)) + (!toRight)*(dif + (int)(arrow_step/factor));

      pos = target;
      previous = launchPosition;
      collisionRadix = 5;
      object_color = scv::Color4f(0,0,0);

      original->clear();
      relative->clear();
      scv::Point v1[arrow_points] = {scv::Point(0,0), scv::Point(-5, 5), scv::Point(5, 0), scv::Point(-5,-5)};
      for(int n = 0; n < arrow_points;n++) {
         original->push_back(v1[n]);
         relative->push_back(v1[n] + launchPosition);
      }
      regularizeFloatVector(relative, &vx[0], &vy[0], 0, relative->size());

      active = true;  
   }
}

Arrow::Arrow(void) : MobileObject(NULL, scv::Color4f(0,0,0)) {
   active = false;
}

Arrow::Arrow(scv::Canvas *canvas, scv::Point launchPosition, scv::Point target) : MobileObject(canvas, scv::Color4f(0,0,0)) {
   active = false;
   updateData(canvas, launchPosition, target);
}
   
void Arrow::update(void) {
   if(active) {
      int step = (int)(arrow_step/factor);
      time += (toRight)*(step) + (!toRight)*(-step);
   }
}
void Arrow::render(void) {
   if(active) {
      int xf, yf = findY(time);
      if(yf < -1*canvas->getHeight()) { //permite que a altura vá de -getHeight() < h < getHeight()
         active = false;
      }
      yf = canvas->getHeight() - (yf + (canvas->getHeight() - launchPosition.y));
      xf = time + (toRight)*(launchPosition.x) + (!toRight)*(target.x);
         
      previous = pos;
      pos.x = xf;
      pos.y = yf;
      rotateArrow();

      canvas->color(object_color[0],object_color[1],object_color[2]);
      canvas->polygonFill(vx, vy, arrow_points);
   }
}
