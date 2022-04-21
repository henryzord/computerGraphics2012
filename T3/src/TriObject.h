#ifndef __TRI__OBJECT__H__
#define __TRI__OBJECT__H__

#include "TriPoint.h"
#include "Transformator.h"

class TriObject {
private:
   const static int revolution = 360;
   const static int min_size_tridimensional = 3;
   TriPoint center;
   std::vector<TriPoint> control_points;
   int steps;
public:
   TriObject() {
   }
   
   //cria um objeto baseado em pontos setados no canvas 2D
   //considera que existe um eixo principal, que são os dois
   //primeiros pontos

   //REVISAR!
   TriObject(std::vector<scv::Point> bidimensional, int steps, int distanceFromCenter) {
      //centro do objeto
      scv::Point bi_center = bidimensional.at(0) + bidimensional.at(1);
      center = TriPoint((float)bi_center.x, (float)bi_center.y, (float)distanceFromCenter); 
      this->steps = steps;
      control_points.clear();

      if(bidimensional.size() >= min_size_tridimensional) {
         //vai girar os outros pontos em torno do eixo
         float radius, x, z, radiusAngle;
         int step = revolution/steps;
         for(int n = 2; n < bidimensional.size(); n++) {
            radius = (float)(bi_center.x - bidimensional.at(n).x); //o raio do ponto até o centro 
            for(int m = 0; m < revolution; m += step) {
               radiusAngle = Transformator::degreeToRadian(m);
               x = radius * cos(radiusAngle);
               z = (float)distanceFromCenter + (radius * sin(radiusAngle)); //TESTE
               control_points.push_back(TriPoint(x, (float)bidimensional.at(n).y, z));
            }
         }
      } else {
         for(int n = 0; n < bidimensional.size(); n++) {
            control_points.push_back(TriPoint((float)bidimensional.at(n).x, (float)bidimensional.at(n).y, (float)distanceFromCenter));
         }
      }
   }

   bool isCentralized() {
      return ((center.getX() == 0.f) && (center.getY() == 0.f) && (center.getZ() == 0.f));
   }

   std::vector<TriPoint> getControlPoints() {
      return control_points;
   }

   int getSteps() {
      return steps;
   }

   TriPoint getCenter() {
      return center;
   }
};

#endif //__3D__OBJECT__H__