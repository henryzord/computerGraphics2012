/**
Henry Cagnini
201010352
*/

#include "Plan.h"
#include "Transformator.h"


std::vector<scv::Point> Plan::perspectiveMatrix(SweepObject object, scv::Point pushTo) {
   std::vector<TriPoint> control_point = object.getRelative();
   float x, y, planZ = object.getRelativeCenter().getZ()/2.f;
   int size = control_point.size();
   std::vector<scv::Point> transformed;
   for(int n = 0; n < size; n++) {
      x = (control_point.at(n).getX()*planZ)/control_point.at(n).getZ();
      y = (control_point.at(n).getY()*planZ)/control_point.at(n).getZ();
      transformed.push_back(scv::Point((int)x, (int)y) + pushTo);
   }
   return transformed;
}

std::vector<scv::Point> Plan::ortographicMatrix(SweepObject object, scv::Point pushTo) {
   int size = object.getOriginal().size();
   float orto_val[Transformator::matrix_positions] = {
      1.f, 0.f, 0.f, 0.f,
      0.f, 1.f, 0.f, 0.f,
      0.f, 0.f, 0.f, 0.f,
      0.f, 0.f, 0.f, 1.f};

      std::vector<TriPoint> points = object.getRelative();
      std::vector<scv::Point> result;
      TriPoint current;
      for(int n = 0; n < size; n++) {
         current = Transformator::multiplyMatrixByPoint(&orto_val[0], points.at(n));
         result.push_back(scv::Point((int)current.getX(), (int)current.getY()) + pushTo);
      }
      return result;
}