/**
Henry Cagnini
201010352
*/

#include "Face.h"

Face::Face() {
   color = TriPoint(1,1,1);
}

Face::Face(TriPoint *vec, int length, TriPoint color) {
   this->color = color;
   for(int n = 0; n < length; n++) {
      vertex.push_back(*vec);
      vec++;
   }
}

Face::Face(std::vector<TriPoint> vertex, TriPoint color) {
   this->color = color;
   this->vertex = vertex;
}

Face::Face(TriPoint p1, TriPoint p2, TriPoint p3, TriPoint p4, TriPoint color) {
   vertex.push_back(p1);
   vertex.push_back(p2);
   vertex.push_back(p3);
   vertex.push_back(p4);
   this->color = color;
}

int Face::getNumberVertex() {
   return vertex.size();
}
std::vector<TriPoint> *Face::getVertex() {
   return &vertex;
}

void Face::draw(void) {
   glBegin(GL_POLYGON);
   glColor3f(color.getX(), color.getY(), color.getZ());
   for(int n = 0; n < (int)vertex.size(); n++) {
      glVertex3f(vertex.at(n).getX(), vertex.at(n).getY(), vertex.at(n).getZ());
   }
   glEnd();
}

Face Face::operator+ (TriPoint p1) {
   int n_vertex = vertex.size();
   std::vector<TriPoint> new_face;
   for(int n = 0; n < n_vertex; n++) {
      new_face.push_back(vertex.at(n) + p1);
   }
   return Face(new_face, color);
}

TriPoint Face::getColor(void) {
   return color;
}

void Face::translate(TriPoint howMuch) {
   for(int n = 0; n < (int)vertex.size(); n++) {
      vertex.at(n) = vertex.at(n) + howMuch;
   }
}

TriPoint Face::getMiddle(void) {
   TriPoint sum;
   sum.setValues(0, 0, 0);
   for(int n = 0; n < (int)vertex.size(); n++) {
      sum = sum + vertex.at(n);
   }
   return TriPoint(sum.getX()/vertex.size(), sum.getY()/vertex.size(), sum.getZ()/vertex.size());
}

Face Face::multByMatrix(float *matrix) {
   float *rnr = matrix;
   std::vector<TriPoint> multiplied;
   for(int n = 0; n < (int)vertex.size(); n++) {
      multiplied.push_back(Transformator::multiplyMatrixByPoint(matrix, vertex.at(n)));
   }
   return Face(multiplied, color);
}
