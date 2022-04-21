/**
Henry Cagnini
201010352
*/

#include "HumanTank.h"

HumanTank::HumanTank(scv::Canvas *canvas, scv::Color4f tank_color, scv::Point center) : Tank(canvas, tank_color, center) {
}

void HumanTank::update(void) {
   arrow.update();
   if(active) {
      if(arrow.active) {
         allignCannon(arrow.pos);
      } else {
         if(!lockedCannon && canvas->isHolded()) {
            holder += 10;
            if(holder > canvas->getWidth()) {
               holder = canvas->getWidth(); 
            }
         }
      }
   }
}

void HumanTank::onMouseOver(const scv::MouseEvent &evt) {
   if(active && !lockedCannon) {
      allignCannon(evt.getPosition());
   }
}

void HumanTank::onMouseClick(const scv::MouseEvent &evt) {
   if(active && !lockedCannon) {
      target = evt.getPosition();
      holder = 0;
   }
}
void HumanTank::onMouseUp(const scv::MouseEvent &evt) {
   if(active && !lockedCannon) {
      lockedCannon = true;
      if(target.x < relative->at(0).x) {
         holder *= -1;
      }
      arrow.updateData(canvas, relative->at(0), scv::Point(relative->at(0).x + holder, target.y));
      holder = 0;
   }
}
void HumanTank::onKeyPressed(const scv::KeyEvent &evt) {
   if(active && !evt.special) {
      switch(evt.keycode) {
         case a_key:
            moveTank(scv::Point(-1*tank_step, 0));
         break;
         case d_key:
            moveTank(scv::Point(tank_step, 0));
         break;
      }
   }
}
