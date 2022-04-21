/*!
\file       Canvas.h
\brief      Implementation of Canvas.
\author     SCV Team
*/

#ifndef __SCV_CANVAS_H__
#define __SCV_CANVAS_H__

#include <SCV/SCV.h>

namespace scv {

class Canvas : public Component {
public:
   Canvas(const scv::Point &p1, const scv::Point &p2);

   virtual void display();

   virtual void render(void) {}
   virtual void update(void) {}

   //Adicional Rendering functions
   void pointf(float x, float y);
   void pointd(double x, double y);
   void point(const scv::Point &p);
   void linef(float x1, float y1, float x2, float y2);
   void lined(double x1, double y1, double x2, double y2);
   void line(const scv::Point &p0, const scv::Point &p1);


   //rectangles
   void rectf(float x1, float y1, float x2, float y2);
   void rectd(double x1, double y1, double x2, double y2);
   void rect(const scv::Point &p0, const scv::Point &p1);
   void rectFillf(float x1, float y1, float x2, float y2);
   void rectFilld(double x1, double y1, double x2, double y2);
   void rectFill(const scv::Point &p0, const scv::Point &p1);

   //Convex polygon. Four vertices specify a rectangle
   void polygon(float vx[], float vy[], int n_elems); 
   void polygonFill(float vx[], float vy[], int n_elems); 

   void circlef(float x, float y, float radius, int div);
   void circled(double x, double y, double radius, int div);
   void circle(const scv::Point &p, double radius, int div);
   void circleFillf(float x, float y, float radius, int div);
   void circleFilld(double x, double y, double radius, int div);
   void circleFill(const scv::Point &p, double radius, int div);

   //Colors for drawing and cleanning
   void color(float r, float g, float b);
   void clear(float r, float g, float b);

   //draw a text
   //void text(int x, int y, const char *t);
};

} // namespace scv


#endif // __SCV_CANVAS_H__
