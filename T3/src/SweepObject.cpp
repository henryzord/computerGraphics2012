/**
Henry Cagnini
201010352
*/

#include "SweepObject.h"
#include "Transformator.h"

SweepObject::SweepObject(std::vector<scv::Point> bidimensional, int steps, int distanceFromCenter) {
   this->steps = steps;
   scv::Point bi_center = bidimensional.at(0) + bidimensional.at(1);
   original_center = TriPoint(0.f, 0.f, 0.f);
   relative_center = TriPoint((float)bi_center.x, (float)bi_center.y, (float)distanceFromCenter); 

   TriPoint current;
   float radius, x, z, radiusAngle;
   int step = revolution/steps, size = bidimensional.size();
   /*
   Vai girar os pontos dados pelo canvas em torno do eixo principal.
   O y será mantido, e o x e o z serão calculados. O cálculo é tomado
   como se o objeto estivesse sendo visualizado de topo: x continua sendo
   x, e tratamos z como sendo o eixo y. Com isso, realiza-se uma rotação.
   */
   for(int n = 0; n < size; n++) {
      radius = (float)(bi_center.x - bidimensional.at(n).x); //o raio do ponto até o centro 
      for(int m = 0; m < revolution; m += step) {
         radiusAngle = Transformator::degreeToRadian(m);
         x = radius * cos(radiusAngle);
         z = (float)distanceFromCenter + (radius * sin(radiusAngle)); //adiciona-se a distância do centro
         current = TriPoint(x, (float)bidimensional.at(n).y, z); //y é preservado
         relative.push_back(current);
         original.push_back(current - relative_center);
      }
   }
   //define os ângulos
   angleX = initialX;
   angleY = initialY;
   angleZ = initialZ;
}

SweepObject::SweepObject(TriPoint originalCenter, TriPoint relativeCenter, std::vector<TriPoint> original, std::vector<TriPoint> relative, int steps, TriPoint angles) {
   this->original_center = originalCenter;
   this->relative_center = relativeCenter;
   this->original = original;
   this->relative = relative;
   this->steps = steps;

   angleX = (int)angles.getX();
   angleY = (int)angles.getY();
   angleZ = (int)angles.getZ();
}

TriPoint SweepObject::getRelativeCenter() {
   return relative_center;
}

TriPoint SweepObject::getOriginalCenter() {
   return original_center;
}

std::vector<TriPoint> SweepObject::getRelative() {
   return relative;
}

std::vector<TriPoint> SweepObject::getOriginal() {
   return original;
}

int SweepObject::getSteps() {
   return steps;
}

int SweepObject::getAngleX() {
   return angleX;
}

int SweepObject::getAngleY() {
   return angleY;
}

int SweepObject::getAngleZ() {
   return angleZ;
}
