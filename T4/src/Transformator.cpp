/**
Henry Cagnini
201010352
*/

#include "Transformator.h"

float *Transformator::createTranslationMatrix1(TriPoint howMuch) {
   float *matrix = new float [Transformator::matrix_positions],
      values[Transformator::matrix_positions] =  {
         /*1st*/ 1.f, 0.f, 0.f, howMuch.getX(),
         /*2nd*/ 0.f, 1.f, 0.f, howMuch.getY(), 
         /*3rd*/ 0.f, 0.f, 1.f, howMuch.getZ(), 
         /*4th*/ 0.f, 0.f, 0.f,           1.f};
         for(int n = 0; n < Transformator::matrix_positions; n++) {
            matrix[n] = values[n];
         }
         return matrix;
}

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

float Transformator::degreeToRadian(int degree) {
   return (((float)degree)*(PI/180.f));
}

int Transformator::radianToDegree(float radian) {
   return (int)((180.f*radian)/PI);
}

int Transformator::degreeBiAngle(BiPoint p1, BiPoint p2) {
   return radianToDegree(radianBiAngle(p1, p2));
}

float Transformator::radianBiAngle(BiPoint p1, BiPoint p2) {
   if(p1 == p2) {
      return 0.f;
   }
   BiPoint np2(p2);
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

TriPoint Transformator::radianTriAngle(TriPoint p1, TriPoint p2) {
   BiPoint p1_1(p1.getX(), p1.getY()), p2_1(p2.getX(), p2.getY()),
      p1_2(p1.getZ(), p1.getY()), p2_2(p2.getZ(), p2.getY()),
      p1_3(p1.getX(), p1.getZ()), p2_3(p2.getX(), p2.getZ());
   float anglex = Transformator::radianBiAngle(p1_2, p2_2),
      angley = Transformator::radianBiAngle(p1_3, p2_3),
      anglez = Transformator::radianBiAngle(p1_1, p2_1);
   return TriPoint(anglex, angley, anglez);
}

TriPoint Transformator::degreeTriAngle(TriPoint p1, TriPoint p2) {
   TriPoint result = Transformator::radianTriAngle(p1, p2);
   return TriPoint((float)Transformator::radianToDegree(result.getX()), (float)Transformator::radianToDegree(result.getY()), (float)Transformator::radianToDegree(result.getZ()));
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

TriPoint Transformator::multiplyMatrixByPoint(std::vector<float> matrix, TriPoint point) {
   float x, y, z;
   x = (matrix.at(0)  * point.getX()) + (matrix.at(1)  * point.getY()) + (matrix.at(2)  * point.getZ()) + (matrix.at(3)  * 1.f);
   y = (matrix.at(4)  * point.getX()) + (matrix.at(5)  * point.getY()) + (matrix.at(6)  * point.getZ()) + (matrix.at(7)  * 1.f);
   z = (matrix.at(8)  * point.getX()) + (matrix.at(9)  * point.getY()) + (matrix.at(10) * point.getZ()) + (matrix.at(11) * 1.f);
   return TriPoint(x, y, z);
}

TriPoint Transformator::multiplyMatrixByPoint(float *matrix, TriPoint point) {
   float x, y, z;
   x = (*matrix        * point.getX()) + (*(matrix + 1)  * point.getY()) + (*(matrix + 2)  * point.getZ()) + (*(matrix + 3)  * 1.f);
   y = (*(matrix + 4)  * point.getX()) + (*(matrix + 5)  * point.getY()) + (*(matrix + 6)  * point.getZ()) + (*(matrix + 7)  * 1.f);
   z = (*(matrix + 8)  * point.getX()) + (*(matrix + 9)  * point.getY()) + (*(matrix + 10) * point.getZ()) + (*(matrix + 11) * 1.f);
   return TriPoint(x, y, z);
}

float Transformator::scalarProduct(TriPoint p1, TriPoint p2) {
   return ((p1.getX() * p2.getX()) + (p1.getY() * p2.getY()) + (p1.getZ() * p2.getZ()));
}