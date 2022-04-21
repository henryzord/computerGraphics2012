/**
Henry Cagnini
201010352
*/

#ifndef __HUMAN__TANK__H__
#define __HUMAN__TANK__H__

#include "Tank.h"

class HumanTank : public Tank {

protected:
   scv::Point target;
public:
   int holder;

   HumanTank(scv::Canvas *canvas, scv::Color4f tank_color, scv::Point center);
   void update(void);
   //callbacks
   void onMouseOver(const scv::MouseEvent &evt);
   void onMouseClick(const scv::MouseEvent &evt);
   void onMouseUp(const scv::MouseEvent &evt);
   void onKeyPressed(const scv::KeyEvent &evt);
};

#endif //__HUMAN__TANK__H__