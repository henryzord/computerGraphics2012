/**
Henry Cagnini
201010352
*/

#include "Camera.h"
#include "Widget.h"

Camera::Camera(SweepObject *object, int projection, scv::Point halfScreen) {
   this->object = object;
   this->projection = projection;
   this->halfScreen = halfScreen;

   if(projection == Camera::perspective) {
      projection_call = &Plan::perspectiveMatrix;
   } else {
      projection_call = &Plan::ortographicMatrix;
   }
}

void Camera::onPositionChanged(int rotateX, int rotateY, int rotateZ) {
   *object = Transformator::modifySweepObject(*object, TriPoint(0.f, 0.f, object->getRelativeCenter().getZ()), 1.f, rotateX, rotateY, rotateZ);
   displayObject();
}

void Camera::displayObject() {
   toShow.clear();
   toShow = projection_call(*object, halfScreen);
}

void Camera::setProjection(int projection) {
   this->projection = projection;
   if(projection == Camera::perspective) {
      projection_call = &Plan::perspectiveMatrix;
   } else {
      projection_call = &Plan::ortographicMatrix;
   }
   displayObject();
}

std::vector<scv::Point> *Camera::getToShow(void) {
   return &toShow;
}