/**
Henry Cagnini
201010352
*/

/**
A classe TriPoint representa um ponto em um espa?o R?. Ela 
prov? um conjunto de m?todos que facilitam a manipula??o destes
pontos.
*/

#ifndef __TRI__POINT__H__
#define __TRI__POINT__H__

class TriPoint {
private:
   float x, y, z;

public:
   TriPoint();
   TriPoint(float x, float y, float z);
   float getX();
   float getY();
   float getZ();

   TriPoint operator+ (TriPoint p1);
   TriPoint operator- (TriPoint p1);
   TriPoint operator* (int value);
   bool operator== (TriPoint p1);
};

#endif //__TRI__POINT__H__