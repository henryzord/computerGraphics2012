/**
Henry Cagnini
201010352
*/

#include "Transformator.h"

std::vector<float> Transformator::createTranslationMatrix(TriPoint howMuch) {
   std::vector<float> matrix;
   float values[Transformator::matrix_positions] =  {
      /*1st*/ 1.f, 0.f, 0.f, howMuch.getX(),
      /*2nd*/ 0.f, 1.f, 0.f, howMuch.getY(), 
      /*3rd*/ 0.f, 0.f, 1.f, howMuch.getZ(), 
      /*4th*/ 0.f, 0.f, 0.f,           1.f};
      for(int n = 0; n < Transformator::matrix_positions; n++) {
         matrix.push_back(values[n]);
      }
      return matrix;
}

std::vector<float> Transformator::createScalationMatrix(float howMuch) {
   std::vector<float> matrix;
   float values[Transformator::matrix_positions] =  {
      /*1st*/ howMuch, 0.f, 0.f, 0.f,
      /*2nd*/ 0.f, howMuch, 0.f, 0.f, 
      /*3rd*/ 0.f, 0.f, howMuch, 0.f, 
      /*4th*/ 0.f, 0.f,     0.f, 1.f};
      for(int n = 0; n < Transformator::matrix_positions; n++) {
         matrix.push_back(values[n]);
      }
      return matrix;
}

std::vector<float> Transformator::createXRotationMatrix(float howMuch) {
   std::vector<float> matrix;
   float values[Transformator::matrix_positions] =  {
      /*1st*/ 1.f,          0.f,           0.f, 0.f,
      /*2nd*/ 0.f, cos(howMuch), -sin(howMuch), 0.f,
      /*3rd*/ 0.f, sin(howMuch),  cos(howMuch), 0.f,
      /*4th*/ 0.f,          0.f,           0.f, 1.f};
      for(int n = 0; n < Transformator::matrix_positions; n++) {
         matrix.push_back(values[n]);
      }
      return matrix;
}

std::vector<float> Transformator::createYRotationMatrix(float howMuch) {
   std::vector<float> matrix;
   float values[Transformator::matrix_positions] =  {
      /*1st*/  cos(howMuch), 0.f, sin(howMuch), 0.f,
      /*2nd*/           0.f, 1.f,          0.f, 0.f,
      /*3rd*/ -sin(howMuch), 0.f, cos(howMuch), 0.f,
      /*4th*/           0.f, 0.f,          0.f, 1.f};
      for(int n = 0; n < Transformator::matrix_positions; n++) {
         matrix.push_back(values[n]);
      }
      return matrix;
}

std::vector<float> Transformator::createZRotationMatrix(float howMuch) {
   std::vector<float> matrix;
   float values[Transformator::matrix_positions] =  {
      /*1st*/  cos(howMuch), -sin(howMuch), 0.f, 0.f,
      /*2nd*/  sin(howMuch),  cos(howMuch), 0.f, 0.f,
      /*3rd*/           0.f,           0.f, 1.f, 0.f,
      /*4th*/           0.f,           0.f, 0.f, 1.f};
      for(int n = 0; n < Transformator::matrix_positions; n++) {
         matrix.push_back(values[n]);
      }
      return matrix;
}

std::vector<float> Transformator::multiplyMatrix(std::vector<float> matrix1, std::vector<float> matrix2) {
   std::vector<float> result;
   int index_x = 0, index_y = 0;
   for(int n = 0; n < Transformator::matrix_positions; n++) {
      result.push_back((matrix1.at(index_x)*matrix2.at(index_y)) + (matrix1.at(index_x + 1)*matrix2.at(index_y + 4)) + (matrix1.at(index_x + 2)*matrix2.at(index_y + 8)) + (matrix1.at(index_x + 3)*matrix2.at(index_y + 12)));
      index_x = ((n+1)/4)*4;  //perdura por 4 vezes e depois passa pra próxima
      index_y = (n+1)%4;      //passa 4x pra próxima e depois volta pra primeira
   }
   return result;
}

TriPoint Transformator::multiplyMatrixByPoint(float *matrix, TriPoint point) {
   float x, y, z;
   x = (*matrix        * point.getX()) + (*(matrix + 1)  * point.getY()) + (*(matrix + 2)  * point.getZ()) + (*(matrix + 3)  * 1.f);
   y = (*(matrix + 4)  * point.getX()) + (*(matrix + 5)  * point.getY()) + (*(matrix + 6)  * point.getZ()) + (*(matrix + 7)  * 1.f);
   z = (*(matrix + 8)  * point.getX()) + (*(matrix + 9)  * point.getY()) + (*(matrix + 10) * point.getZ()) + (*(matrix + 11) * 1.f);
   return TriPoint(x, y, z);
}

TriPoint Transformator::multiplyMatrixByPoint(std::vector<float> matrix, TriPoint point) {
   float x, y, z;
   x = (matrix.at(0)  * point.getX()) + (matrix.at(1)  * point.getY()) + (matrix.at(2)  * point.getZ()) + (matrix.at(3)  * 1.f);
   y = (matrix.at(4)  * point.getX()) + (matrix.at(5)  * point.getY()) + (matrix.at(6)  * point.getZ()) + (matrix.at(7)  * 1.f);
   z = (matrix.at(8)  * point.getX()) + (matrix.at(9)  * point.getY()) + (matrix.at(10) * point.getZ()) + (matrix.at(11) * 1.f);
   return TriPoint(x, y, z);
}

std::vector<TriPoint> Transformator::multiplyMatrixByPoint(float *matrix, std::vector<TriPoint> points) {
   int size = points.size();
   float *runner = matrix;
   std::vector<TriPoint> result;
   for(int n = 0; n < size; n++) {
      result.push_back(multiplyMatrixByPoint(runner, points.at(n)));
      runner = matrix;
   }
   return result;
}

std::vector<TriPoint> Transformator::multiplyMatrixByPoint(std::vector<float> matrix, std::vector<TriPoint> points) {
   std::vector<TriPoint> result;
   for(int n = 0; n < points.size(); n++) {
      result.push_back(multiplyMatrixByPoint(matrix, points.at(n)));
   }
   return result;
}

SweepObject Transformator::modifySweepObject(SweepObject object, TriPoint new_center, float scale, int rotateX, int rotateY, int rotateZ) {
   int cur_matrix = 0, size;
   std::vector<float> matrices[max_matrices], result;

   int n_rotateX = (SweepObject::revolution+(object.getAngleX() + rotateX))%SweepObject::revolution,
      n_rotateY = (SweepObject::revolution+(object.getAngleY() + rotateY))%SweepObject::revolution, 
      n_rotateZ = (SweepObject::revolution+(object.getAngleZ() + rotateZ))%SweepObject::revolution;

   result = createTranslationMatrix(new_center);
   if(n_rotateZ != 0) {
      matrices[cur_matrix] = createZRotationMatrix(Transformator::degreeToRadian(n_rotateZ));
      cur_matrix++;
   }
   if(n_rotateY != 0) {
      matrices[cur_matrix] = createYRotationMatrix(Transformator::degreeToRadian(n_rotateY));
      cur_matrix++;  
   }
   if(n_rotateX != 0) {
      matrices[cur_matrix] = createXRotationMatrix(Transformator::degreeToRadian(n_rotateX));
      cur_matrix++;
   }
   if(scale != 1.f) {
      matrices[cur_matrix] = createScalationMatrix(scale);
      cur_matrix++;
   }
   //concatena as matrizes
   for(int n = 0; n < cur_matrix; n++) {
      result = multiplyMatrix(result, matrices[n]);
   }

   TriPoint new_relative_center = Transformator::multiplyMatrixByPoint(result, object.getOriginalCenter());
   std::vector<TriPoint> object_original = object.getOriginal(), new_relative;
   size = object_original.size();

   for(int n = 0; n < size; n++) {
      new_relative.push_back(Transformator::multiplyMatrixByPoint(result, object_original.at(n)));
   }
   return (SweepObject(object.getOriginalCenter(), new_relative_center, object_original, new_relative, object.getSteps(), TriPoint((float)n_rotateX, (float)n_rotateY, (float)n_rotateZ)));
}

float Transformator::degreeToRadian(int degree) {
   return (((float)degree)*(PI/180.f));
}

int Transformator::radianToDegree(float radian) {
   return (int)((180.f*radian)/PI);
}

int Transformator::findDegreeAngle(scv::Point p1, scv::Point p2) {
   return radianToDegree(findRadianAngle(p1, p2));
}

float Transformator::findRadianAngle(scv::Point p1, scv::Point p2) {
   if(p1 == p2) {
      return 0.f;
   }
   scv::Point np2(p2);
   np2 -= p1; //p1 é considerado como a origem, e p2 será movido para manter a relação
   float factorx, factory, multx, multy;

   if(np2.x < 0) {
      factorx = PI;
      multx = -1;
   } else {
      factorx = 0;
      multx = 1;
   }
   if(np2.y < 0) {
      factory = 2*PI;
      multy = -1;
   } else {
      factory = 0;
      multy = 1;
   }
   float x_projection, x_angle, hypotenuse, coef_ang = (float)np2.y/(float)np2.x;
   hypotenuse = (sqrt(1.f + (pow(coef_ang,2))));
   x_projection = 1.f/hypotenuse;
   x_angle = acos(x_projection);
   return (factory + (multy*(factorx+(multx*x_angle))));
}
