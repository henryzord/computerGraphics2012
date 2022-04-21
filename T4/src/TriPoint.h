/**
Henry Cagnini
201010352
*/

/**
A classe TriPoint representa um ponto em um espaço R³. Ela 
provê um conjunto de métodos que facilitam a manipulação destes
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
   void setValues(float x, float y, float z);
   void setX(float x);
   void setY(float y);
   void setZ(float z);
   TriPoint mean(TriPoint p1);
   TriPoint operator+ (TriPoint p1);
   TriPoint operator- (TriPoint p1);
   TriPoint operator* (float value);
   TriPoint operator/ (float value);
   void operator-= (TriPoint p1);
   bool operator== (TriPoint p1);
};

#endif //__TRI__POINT__H__