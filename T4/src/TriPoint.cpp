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

void TriPoint::setValues(float x, float y, float z) {
   this->x = x;
   this->y = y;
   this->z = z;
}

void TriPoint::setX(float x) {
   this->x = x;
}

void TriPoint::setY(float y) {
   this->y = y;
}

void TriPoint::setZ(float z) {
   this->z = z;
}

TriPoint TriPoint::mean(TriPoint p1) {
   return TriPoint((x+p1.getX())/2.f, (y+p1.getY())/2.f, (z+p1.getZ())/2.f);
}

TriPoint TriPoint::operator+ (TriPoint p1) {
   return TriPoint(x + p1.getX(), y + p1.getY(), z + p1.getZ());
}
TriPoint TriPoint::operator- (TriPoint p1) {
   return TriPoint(x - p1.getX(), y - p1.getY(), z - p1.getZ());
}
TriPoint TriPoint::operator* (float value) {
   return TriPoint(x * value, y * value, z * value);
}

TriPoint TriPoint::operator/ (float value) {
   return TriPoint(x/value, y/value, z/value);
}

bool TriPoint::operator== (TriPoint p1) {
   return (x == p1.getX() && y == p1.getY() && z == p1.getZ());
}

void TriPoint::operator-= (TriPoint p1) {
   x -= p1.getX();
   y -= p1.getY();
   z -= p1.getZ();
}