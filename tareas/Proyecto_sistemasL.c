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
