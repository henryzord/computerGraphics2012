/**
Henry Cagnini
201010352
*/

#include "BiPoint.h"

BiPoint::BiPoint() {
   x = y = 0;
}

BiPoint::BiPoint(float x, float y) {
   this->x = x;
   this->y = y;
}

void BiPoint::operator-= (BiPoint p2) {
   x -= p2.x;
   y -= p2.y;
}

bool BiPoint::operator== (BiPoint p2) {
   return(x == p2.x && y == p2.y);
}

BiPoint BiPoint::operator+ (BiPoint p2) {
   return BiPoint(x + p2.x, y + p2.y);
}

BiPoint BiPoint::operator- (BiPoint p2) {
   return BiPoint(x - p2.x, y - p2.y);
}