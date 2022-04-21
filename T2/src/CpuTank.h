/**
Henry Cagnini
201010352
*/

#ifndef __CPU__TANK__H__
#define __CPU__TANK__H__

#include <cstdlib>

#include "HumanTank.h"

class CpuTank : public Tank {
private:
   const static int move_skipper = 5; 
   const static int time_skipper = 60;

   bool getClose;
   int minDist, maxDist, moveCoolDown, coolDownTime;
   HumanTank *human;

   void trackHuman(void);

public:
   CpuTank(scv::Canvas *canvas, scv::Color4f tank_color, scv::Point center, HumanTank *human);
   void update(void);
};

#endif //__CPU__TANK__H__