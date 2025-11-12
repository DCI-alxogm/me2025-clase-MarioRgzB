#include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 // definicion del tamaño de la matriz o sistema lineal
 #define ORDEN_MATRIZ 5
 // declaración de las funciones que se emplearan
 void mostrarMatriz(double matriz[][ORDEN_MATRIZ], int orden);
 void mostrarVector(double vect[], int orden);
 int factLU(double A[][ORDEN_MATRIZ], double L[][ORDEN_MATRIZ], double U[][ORDEN_MATRIZ], int orden);
 void solucionSistemaLU(double L[][ORDEN_MATRIZ], double U[][ORDEN_MATRIZ], double b[], double x[], int orden);
 void iteracionGS(double A[][ORDEN_MATRIZ], double b[], double x[], int orden, int maxIt, double tl);
 void eliminacionGJ(double A[][ORDEN_MATRIZ], double b[], double x[], int orden);
// Función principal int main
 int main() {
     // Matriz A de coeficientes 
     double matrizA[ORDEN_MATRIZ][ORDEN_MATRIZ] = {
         {-150, 244.5, 0, 0, 0},
         {100, -344.5, 325.5, 0, 0},
         {0, 100, -525.5, 405, 0},
         {0, 0, 200, -605, 499.5},
         {0, 0, 0, 200, -549.5}
     };
     //Vector de términos independientes b
     double vectorB[ORDEN_MATRIZ] = {0, 0, -30, 0, 0};
     // Vectores que contienen las soluciones obtenidas por los 3 métodos
     double solucionLU[ORDEN_MATRIZ], solucionGaussSeidel[ORDEN_MATRIZ], solucionGaussJordan[ORDEN_MATRIZ];
     // solución por factorización LU
     double matrizL[ORDEN_MATRIZ][ORDEN_MATRIZ], matrizU[ORDEN_MATRIZ][ORDEN_MATRIZ];
