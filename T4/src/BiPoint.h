/**
Henry Cagnini
201010352
*/

/**
A classe BiPoint representa um ponto em um espaço R².
*/
#ifndef __BI__POINT__
#define __BI__POINT__

class BiPoint {
public:
   float x, y;

   BiPoint();
   BiPoint(float x, float y);
   bool operator== (BiPoint p2);
   void operator-= (BiPoint p2);
   BiPoint operator+ (BiPoint p2);
   BiPoint operator- (BiPoint p2);
};


#endif //__BI__POINT__