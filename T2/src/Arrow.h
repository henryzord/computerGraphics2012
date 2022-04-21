/**
Henry Cagnini
201010352
*/

#ifndef __ARROW__H__
#define __ARROW__H__

#include "MobileObject.h"

class Arrow : public MobileObject {
private:
   const static int arrow_step = 3;
   const static int arrow_points = 4;

   bool toRight;
   int time, dif;
   float af, bf, factor, vx[arrow_points], vy[arrow_points];
   scv::Point launchPosition, target, previous;

   void rotateArrow(void);
   void createFunction(void);
   int findY(int x);
   int findX(int y);

public:
   scv::Point pos;

   void updateData(scv::Canvas *canvas, scv::Point launchPosition, scv::Point target);
   Arrow(void);
   Arrow(scv::Canvas *canvas, scv::Point launchPosition, scv::Point target);
   void update(void);
   void render(void);
};

#endif //__ARROW__H__