/**
Henry Cagnini
201010352
*/

#include "TriPoint.h"

TriPoint::TriPoint(void) {
   x = y = z = 0.f;
}

TriPoint::TriPoint(float x, float y, float z) {
   this->x = x;
   this->y = y;
   this->z = z;
}
float TriPoint::getX() {
   return x;
}
float TriPoint::getY() {
   return y;
}
float TriPoint::getZ() {
   return z;
}

TriPoint TriPoint::operator+ (TriPoint p1) {
   return TriPoint(x + p1.getX(), y + p1.getY(), z + p1.getZ());
}
TriPoint TriPoint::operator- (TriPoint p1) {
   return TriPoint(x - p1.getX(), y - p1.getY(), z - p1.getZ());
}
TriPoint TriPoint::operator* (int value) {
   return TriPoint(x * value, y * value, z * value);
}
bool TriPoint::operator== (TriPoint p1) {
   return (x == p1.getX() && y == p1.getY() && z == p1.getZ());
}