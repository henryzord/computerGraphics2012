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

#include <vector>
#include <math.h>

#include "BiPoint.h"
#include "TriPoint.h"


const static float PI = 3.1415926535897932f;

class Transformator {
private:
   const static int max_matrices = 6;

public:
   const static int matrix_positions = 16;

   /**
   Criação de matrizes
   */
   static float *createTranslationMatrix1(TriPoint howMuch);
   static std::vector<float> createTranslationMatrix(TriPoint howMuch);
   static std::vector<float> createScalationMatrix(float howMuch);
   static std::vector<float> createXRotationMatrix(float howMuch);
   static std::vector<float> createYRotationMatrix(float howMuch);
   static std::vector<float> createZRotationMatrix(float howMuch);

   /**
   Multiplicação de matrizes
   */
   static std::vector<float> Transformator::multiplyMatrix(std::vector<float> matrix1, std::vector<float> matrix2);
   static TriPoint multiplyMatrixByPoint(float *matrix, TriPoint point);
   static TriPoint multiplyMatrixByPoint(std::vector<float> matrix, TriPoint point);

   /**
   Funções trigonométricas
   */
   static float degreeToRadian(int degree);
   static int radianToDegree(float radian);
   static int degreeBiAngle(BiPoint p1, BiPoint p2);
   static float radianBiAngle(BiPoint p1, BiPoint p2);

   /**
   Estes métodos descobrem o ângulo que dois pontos Tridimensionais fazem
   entre si. O cálculo é parecido com a descoberta do âgulo
   em um espaço R², apenas segmenta-se o espaço R³ em 3 espaços
   R² e então faz-se o cálculo do ângulo.
   */
   static TriPoint radianTriAngle(TriPoint p1, TriPoint p2);
   static TriPoint degreeTriAngle(TriPoint p1, TriPoint p2);
   /**
   Produto escalar de dois pontos tridimensionais
   */
   static float scalarProduct(TriPoint p1, TriPoint p2);

};

#endif //__TRANSFORMATOR__H__