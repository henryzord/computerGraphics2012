/**
Henry Cagnini
201010352
*/

#include "Cylinder.h"

Cylinder::Cylinder(Face bottom, TriPoint length) {
   this->bottom = bottom;
   top = bottom + length;

   std::vector<TriPoint> *top_vertex = top.getVertex(), *bottom_vertex = bottom.getVertex();
   //cria as faces laterais
   int n_side_faces = top.getNumberVertex();
   for(int n = 0; n < n_side_faces; n++) { //tem o mesmo número de faces que o de vértices
      side_face.push_back(Face(top_vertex->at(n), top_vertex->at((n+1)%n_side_faces),
         bottom_vertex->at((n+1)%n_side_faces), bottom_vertex->at(n), top.getColor()));
   }
}

Cylinder::Cylinder(Face top, Face bottom) {
   this->top = top;
   this->bottom = bottom;

   std::vector<TriPoint> *top_vertex = top.getVertex(), *bottom_vertex = bottom.getVertex();
   //cria as faces laterais
   int n_side_faces = top.getNumberVertex();
   for(int n = 0; n < n_side_faces; n++) { //tem o mesmo número de faces que o de vértices
      side_face.push_back(Face(top_vertex->at(n), top_vertex->at((n+1)%n_side_faces),
         bottom_vertex->at((n+1)%n_side_faces), bottom_vertex->at(n), top.getColor()));
   }
}

void Cylinder::draw(void) {
   top.draw();
   bottom.draw();
   for(int n = 0; n < (int)side_face.size(); n++) {
      side_face.at(n).draw();
   }
}

Face Cylinder::getTopFace(void) {
   return top;
}
Face Cylinder::getBottomFace(void) {
   return bottom;
}
std::vector<Face> Cylinder::getSideFaces(void) {
   return side_face;
}

TriPoint Cylinder::getMiddle(void) {
   return getBottomFace().getMiddle().mean(getTopFace().getMiddle());
}

void Cylinder::translate(TriPoint howMuch) {
   top.translate(howMuch);
   bottom.translate(howMuch);
   for(int n = 0; n < (int)side_face.size(); n++) {
      side_face.at(n).translate(howMuch);
   }
}

Cylinder Cylinder::multByMatrix(float *matrix) {
   Face n_top = top.multByMatrix(matrix), n_bottom = bottom.multByMatrix(matrix);
   return Cylinder(n_top, n_bottom);
}

