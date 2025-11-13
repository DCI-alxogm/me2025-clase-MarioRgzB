#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// definicion del tamaño de la matriz o sistema lineal 
#define ORDEN_MATRIZ 5 
//funciones a utilizar
void mostrarMatriz(double matriz[][ORDEN_MATRIZ], int orden);
void mostrarVector(double vector[], int orden);
int descomponerLU(double A[][ORDEN_MATRIZ], double L[][ORDEN_MATRIZ], double U[][ORDEN_MATRIZ], int orden);
void resolverSistemaLU(double L[][ORDEN_MATRIZ], double U[][ORDEN_MATRIZ], double b[], double x[], int orden);
void iteracionGaussSeidel(double A[][ORDEN_MATRIZ], double b[], double x[], int orden, int maxIteraciones, double tolerancia);
void eliminacionGaussJordan(double A[][ORDEN_MATRIZ], double b[], double x[], int orden);

//función principal
int main() {
    //matriz de coeficientes A
    double matrizA[ORDEN_MATRIZ][ORDEN_MATRIZ] = {
        {-150, 244.5, 0, 0, 0},
        {100, -344.5, 325.5, 0, 0},
        {0, 100, -525.5, 405, 0},
        {0, 0, 200, -605, 499.5},
        {0, 0, 0, 200, -549.5}
    };

    //vector de términos independientes b
    double vectorB[ORDEN_MATRIZ] = {0, 0, -30, 0, 0};

    //registro de soluciones obtenidas por los diferentes métodos
    double solucionLU[ORDEN_MATRIZ], solucionGaussSeidel[ORDEN_MATRIZ], solucionGaussJordan[ORDEN_MATRIZ];

    //factorización LU
    double matrizL[ORDEN_MATRIZ][ORDEN_MATRIZ], matrizU[ORDEN_MATRIZ][ORDEN_MATRIZ];

    //factorizacion de la matriz A en L y U
    if (descomponerLU(matrizA, matrizL, matrizU, ORDEN_MATRIZ) == 0) {
        resolverSistemaLU(matrizL, matrizU, vectorB, solucionLU, ORDEN_MATRIZ);

        printf("Solución por Factorización LU:\n");
        mostrarVector(solucionLU, ORDEN_MATRIZ);
    } else {
        printf("Error.\n");
    }
    //solución por Gauss-Seidel
    int maxIteraciones = 1000; //limite de iteraciones
    double tolerancia = 1e-6;    //tolerancia para la convergencia del método

    //inicializacion de la solución con una aproximación inicial de ceros
    for (int i = 0; i < ORDEN_MATRIZ; i++) {
        solucionGaussSeidel[i] = 0.0;
    }

    iteracionGaussSeidel(matrizA, vectorB, solucionGaussSeidel, ORDEN_MATRIZ, maxIteraciones, tolerancia);

    printf("Solución por Gauss-Seidel:\n");
    mostrarVector(solucionGaussSeidel, ORDEN_MATRIZ);
    //solución por Gauss-Jordan
    eliminacionGaussJordan(matrizA, vectorB, solucionGaussJordan, ORDEN_MATRIZ);

    printf("Solución por Gauss-Jordan:\n");
    mostrarVector(solucionGaussJordan, ORDEN_MATRIZ);

    return 0;
}
