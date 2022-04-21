/**
Henry Cagnini
201010352
*/

#ifndef __MOBILE__OBJECT__H__
#define __MOBILE__OBJECT__H__

#include "Transformator.h"

class MobileObject {
protected:
   Transformator trans;
   scv::Canvas *canvas;
   scv::Color4f object_color;
   std::vector<scv::Point> *original, *relative;

   void regularizeFloatVector(std::vector<scv::Point> *vec, float *vx, float *vy, int init, int end);

public:
   bool active;
   int collisionRadix;

   MobileObject(scv::Canvas *canvas, scv::Color4f object_color);
   scv::Point getCenter(void);
   //considera os objetos a serem colididos como círculos
   //desativa os dois caso eles se colidam
   void collides(MobileObject *object);
   virtual void render(void);
   virtual void update(void);
   
   
   ~MobileObject(void);
};

#endif //__MOBILE__OBJECT__H__