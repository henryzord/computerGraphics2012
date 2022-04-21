/**
Henry Cagnini
201010352
*/

#ifndef __TANK__H__
#define __TANK__H__

#include <stdlib.h>

#include "Arrow.h"

class Tank : public MobileObject {
protected:
   const static int cannon_points = 5;
   const static int wheel_length = 7;
   const static int tank_step = 6;
   const static int fire_points = 9;

   const static int a_key = 97;
   const static int d_key = 100;
   const static int w_key = 119;
   const static int s_key = 115;
   const static int space_key = 32;
   const static int maxCoolDown = 180; //180 frames, ou 3 seg a 60 frames por seg

   Arrow arrow;
   bool lockedCannon;
   int previous_angle;
   float vx[cannon_points], vy[cannon_points];
   float firex[fire_points], firey[fire_points], relfirex[fire_points], relfirey[fire_points];

   void allignCannon(scv::Point aim);
   void moveTank(scv::Point howMuch);
   
public:
   const static int tire_length = 10;

   Tank(scv::Canvas *canvas, scv::Color4f object_color, scv::Point center);
   Arrow *getArrow(void);
   void render(void);
   //callbacks
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
};

#endif //__TANK__H__