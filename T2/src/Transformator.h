/**
Henry Cagnini
201010352
*/

#ifndef __TRANSFORMATOR__H__
#define __TRANSFORMATOR__H__

#include <SCV\SCV.h>
#include <vector>
#include <math.h>

const static float PI = 3.1415926535897932f;

class Transformator {
private:

   const static int max_rows = 3;
   const static int max_columns = 3;

   const static int translade_op = 0;
   const static int scale_op = 1;
   const static int rotate_op = 2;

   float main_matrix[max_rows][max_columns], aux_matrix[max_rows][max_columns], support_matrix[max_rows][max_columns];

   void hashOperation(int operation, scv::Point value, float *matrix) {
      if(operation < 1) {
         createTranslationMatrix(value, matrix);
      } else {
         if(operation > 1) {
            createRotationMatrix(value, matrix);
         } else {
            createScalationMatrix(value, matrix);
         }
      }
   }

   void initMatrix(float *matrix, float *values) {
      copyMatrix(matrix, values);
   }
   //cria uma matriz de translação e armazena-a em matrix
   void createTranslationMatrix(scv::Point position, float *matrix) {
      float values[max_rows*max_columns] = {1,0,(float)position.x, 0,1,(float)position.y, 0,0,1};
      initMatrix(matrix, &values[0]);
   }
   //cria uma matriz de escala e armazena-a em matrix
   void createScalationMatrix(scv::Point proportion, float *matrix) {
      float values[max_rows*max_columns] = {(float)proportion.x,0,0, 0,(float)proportion.y,0, 0,0,1};
      initMatrix(matrix, &values[0]);
   }
   //cria uma matriz de rotação em matrix
   void createRotationMatrix(scv::Point degreeAngle, float *matrix) {
      float angle = degreeToRadian(degreeAngle.x);
      float values[max_rows*max_columns] = {cos(angle),-sin(angle),0, sin(angle),cos(angle),0, 0,0,1};
      initMatrix(matrix, &values[0]);  
   }

   void copyMatrix(float *destination, float *source) {
      for(int n = 0; n < (max_rows*max_columns); n++) {
         *destination = *source;
         destination += 1;
         source += 1;
      }
   }

   scv::Point multiplyMatrixByPoint(float *matrix, scv::Point point) {
      float dest[3], *refmatrix = matrix;
      
      for(int n = 0; n < 3; n++) {
         dest[n] = (*refmatrix * (float)point.x) + ((*(refmatrix + 1)) * (float)point.y) + ((*(refmatrix + 2)) * 1);
         refmatrix += 3;
      }
      return scv::Point((int)dest[0], (int)dest[1]);
   }

   //multiplica duas matrizes 3x3
   //faz m1 x m2
   //armazena o resultado em dest
   void multiplyMatrix(float *mat1, float *mat2, float *dest) {
      float matrice[max_rows][max_columns], *refmatrice = &matrice[0][0], *refmat1 = mat1, *refmat2 = mat2;
      for(int n = 1; n <= (max_rows*max_columns); n++) {
         *refmatrice = ((*refmat1)*(*refmat2)) + ((*(refmat1 + 1))*(*(refmat2 + max_columns))) + ((*(refmat1 + 2))*(*(refmat2 + 2*(max_columns))));
         
         refmat1 = mat1 + (3*(n/3));
         refmat2 = mat2 + (n%3);
         
         refmatrice += 1;
      }
      copyMatrix(dest, &matrice[0][0]);
   }

   std::vector<scv::Point> queueOperations(std::vector<int> operation, std::vector<scv::Point> value, std::vector<scv::Point> point) {
      hashOperation(operation.at(0),value.at(0), &main_matrix[0][0]);
      for(int n = 1; n < operation.size(); n++) {
         hashOperation(operation.at(n), value.at(n), &aux_matrix[0][0]);
         multiplyMatrix(&main_matrix[0][0], &aux_matrix[0][0], &main_matrix[0][0]);
      }
      //após isso, já terá a matriz de transformação
      std::vector<scv::Point> new_points;
      for(int n = 0; n < point.size(); n++) {
         new_points.push_back(multiplyMatrixByPoint(&main_matrix[0][0], point.at(n)));
      }
      return new_points;
   }

public:
   
   Transformator(void) {
   }

   std::vector<scv::Point> modifyObject(scv::Point translade, scv::Point scale, scv::Point rotate, std::vector<scv::Point> original) {
      std::vector<int> operation;
      std::vector<scv::Point> value;

      operation.push_back(translade_op);
      operation.push_back(scale_op);
      operation.push_back(rotate_op);
      
      value.push_back(translade);
      value.push_back(scale);
      value.push_back(rotate);

      return queueOperations(operation, value, original);
   }

   static float degreeToRadian(int degree) {
      return ((float)degree*(PI/180.f));
   }

   static int radianToDegree(float radian) {
      return (int)((180.f*radian)/PI);
   }
   /**
   Acha o ângulo do ponto em x em graus
   */
   static int findDegreeAngle(scv::Point p1, scv::Point p2) {
      return radianToDegree(findRadianAngle(p1, p2));
   }
   /**
   Acha o ângulo do ponto em x em radianos
   */
   static float findRadianAngle(scv::Point p1, scv::Point p2) {
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
};

#endif //__TRANSFORMATOR__H__