/**
Henry Cagnini
201010352
*/

#include "CpuTank.h"

void CpuTank::trackHuman(void) {
   //faz o cálculo de quanto menor a distância, mais rápido dispara
   //também faz o cálculo do tempo randômico pra disparar
   int dif = relative->at(0).x - human->getCenter().x, getCloseStep;
   bool inLeft = relative->at(0).x < human->getCenter().x;
   //sempre tenta se aproximar do outro tanque
   getCloseStep = (inLeft)*(tank_step) + (!inLeft)*(-tank_step);
   if(dif < 0) {
      dif *= -1;
   }
   if(getClose) {
      if(dif < minDist) {
         getClose = false;
         moveTank(scv::Point(-getCloseStep, 0));
      } else {
         moveTank(scv::Point(getCloseStep, 0));
      }
   } else {
      if(dif > maxDist) {
         getClose = true;
         moveTank(scv::Point(getCloseStep, 0));
      } else {
         moveTank(scv::Point(-getCloseStep, 0));
      }
   }
}

CpuTank::CpuTank(scv::Canvas *canvas, scv::Color4f tank_color, scv::Point center, HumanTank *human) : Tank(canvas, tank_color, center) {
   this->human = human;

   //determina a faixa de distância que esse tanque pode estar em relação ao tanque inimigo
   minDist = rand() % 200 + 100;
   maxDist = rand() % minDist + (minDist*2); 

   getClose = true;

   moveCoolDown = 0;
   coolDownTime = rand() % time_skipper + time_skipper/2;
}

void CpuTank::update(void) {
   arrow.update();
   if(active) {
      //fazer andar só uma vez a cada x frames!
      if(moveCoolDown == 0) {
         trackHuman();
         moveCoolDown = move_skipper;
      } else {
         moveCoolDown--;
      }
      if(arrow.active) {
         allignCannon(arrow.pos);
      } else {
         if(coolDownTime == 0) {
            arrow.updateData(canvas, relative->at(0), human->getCenter());
            coolDownTime = rand() % time_skipper + time_skipper/2;
         } else {
            coolDownTime--;
         }
      }
   }
}
