/**
Henry Cagnini
201010352
*/

/**
A classe Transformator provê um conjunto de operações que se propõem
a solucionar diversos problemas matemáticos.
*/

#ifndef __TRANSFORMATOR__H__
#define __TRANSFORMATOR__H__

#include <SCV/SCV.h>
#include <math.h>

#include "SweepObject.h"

const static float PI = 3.1415926535897932f;

class Transformator {
private:
   const static int max_matrices = 6;

public:
   const static int matrix_positions = 16;

   /**
   Criação de matrizes
   */
   static std::vector<float> createTranslationMatrix(TriPoint howMuch);
   static std::vector<float> createScalationMatrix(float howMuch);
   static std::vector<float> createXRotationMatrix(float howMuch);
   static std::vector<float> createYRotationMatrix(float howMuch);
   static std::vector<float> createZRotationMatrix(float howMuch);

   /**
   Multiplicação de matrizes por matrizes e pontos
   */
   static std::vector<float> multiplyMatrix(std::vector<float> matrix1, std::vector<float> matrix2);
   static TriPoint multiplyMatrixByPoint(float *matrix, TriPoint point);
   static TriPoint multiplyMatrixByPoint(std::vector<float> matrix, TriPoint point);
   static std::vector<TriPoint> multiplyMatrixByPoint(std::vector<float> matrix, std::vector<TriPoint> points);
   static std::vector<TriPoint> multiplyMatrixByPoint(float *matrix, std::vector<TriPoint> points);

   /**
   Dado um SweepObject, pode realizar uma operação de escala, translação, rotação em X, rotação em Y e rotação em Z, 
   apenas uma, algumas ou todas juntas.
   O argumento new_center corresponde à uma operação de translação, onde, ao invés de informar-se o quanto deseja-se
   transladar o objeto, informa-se onde deseja-se que ele esteja ao final das outras operações.
   */
   static SweepObject modifySweepObject(SweepObject object, TriPoint new_center, float scale, int rotateX, int rotateY, int rotateZ);

   /**
   Funções trigonométricas
   */
   static float degreeToRadian(int degree);
   static int radianToDegree(float radian);
   static int findDegreeAngle(scv::Point p1, scv::Point p2);
   static float findRadianAngle(scv::Point p1, scv::Point p2);

};

#endif //__TRANSFORMATOR__H__