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
void mostrarMatriz(double matriz[][ORDEN_MATRIZ], int orden) {
    for (int i = 0; i < orden; i++) {
        for (int j = 0; j < orden; j++) {
            printf("%f  ", matriz[i][j]); //alineación de la salida
        }
    }
}

void mostrarVector(double vector[], int orden) {
    for (int i = 0; i < orden; i++) {
        printf("%f\n", vector[i]); // alineación de la salida
    }
}

int descomponerLU(double A[][ORDEN_MATRIZ], double L[][ORDEN_MATRIZ], double U[][ORDEN_MATRIZ], int orden) {
    //inicializar las matrices L y U (superior)
    for (int i = 0; i < orden; i++) {
        for (int j = 0; j < orden; j++) {
            L[i][j] = 0.0; //inicializar L con ceros
            U[i][j] = 0.0; //inicializar U con ceros

            if (i == j) {
                L[i][j] = 1.0; //elementos de la diagonal de L igual a 1
            }
        }
    }

    //descomposición LU
    for (int k = 0; k < orden; k++) {
        U[k][k] = A[k][k]; //el primer elemento de U es coincide con el de A

        // Verificar si el pivote es cero o muy reducido
        if (fabs(U[k][k]) < 1e-12) {
            return 1; //en caso de ser verificado
        }

        //calculo de elementos de la matriz L y U
        for (int i = k + 1; i < orden; i++) {
            L[i][k] = A[i][k] / U[k][k]; //obtención de los elementos de L
            U[k][i] = A[k][i]; //obtención de los elementos de U
        }

        // actualización de la matriz A para las siguientes iteraciones
        for (int i = k + 1; i < orden; i++) {
            for (int j = k + 1; j < orden; j++) {
                A[i][j] = A[i][j] - L[i][k] * U[k][j];
            }
        }
    }

    return 0;
}

//función que resuelve el sistema de ecuaciones lineales a través de la descomposición LU
void resolverSistemaLU(double L[][ORDEN_MATRIZ], double U[][ORDEN_MATRIZ], double b[], double x[], int orden) {
    double y[ORDEN_MATRIZ]; //vector para resolver el sistema Ly = b

    //sustitución hacia adelante
    for (int i = 0; i < orden; i++) {
        y[i] = b[i]; //inicializar y[i] con el valor correspondiente de b[i]

        //resta de términos correspondientes a las incógnitas ya resueltas
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
    }

    //realizar sustitución hacia atrás
    for (int i = orden - 1; i >= 0; i--) {
        x[i] = y[i]; //inicializacion de  x[i] con el valor correspondiente de y[i]

        //resta de términos correspondientes a las incógnitas ya resueltas
        for (int j = i + 1; j < orden; j++) {
            x[i] -= U[i][j] * x[j];
        }

        x[i] /= U[i][i]; //división por el coeficiente diagonal
    }
}

//función para realizar iteraciones de Gauss-Seidel
void iteracionGaussSeidel(double A[][ORDEN_MATRIZ], double b[], double x[], int orden, int maxIteraciones, double tolerancia) {
    double xNuevo[ORDEN_MATRIZ]; //vector que almacena los nuevos valores de x
    double error; //variable que guarda el error en cada iteración
    int iter; //contador de iteraciones

    //iterar hasta alcanzar el número máximo de iteraciones o la tolerancia deseada
    for (iter = 0; iter < maxIteraciones; iter++) {
        error = 0.0; //error inicia en cero

        //obtención de los nuevos valores de x
        for (int i = 0; i < orden; i++) {
            double suma = 0.0; //la suma comienza en cero

            //sumar los términos no diagonales
            for (int j = 0; j < orden; j++) {
                if (i != j) {
                    suma += A[i][j] * x[j];
                }
            }

            xNuevo[i] = (b[i] - suma) / A[i][i]; //obtención del nuevo valor de x[i]
            error += fabs(xNuevo[i] - x[i]);      //acumulación del error absoluto

            x[i] = xNuevo[i]; //valor de x[i] actualizado
        }

        //verificar si se alcanzó la convergencia
        if (error < tolerancia) {
            printf("Con Gauss-Seidel convergio despues de %d iteraciones\n", iter + 1);
            return;
        }
    }

    printf("Sin converger con Gauss-Seidel\n");
}

// que resuelve el sistema de ecuaciones lineales con el método de Gauss-Jordan
void eliminacionGaussJordan(double A[][ORDEN_MATRIZ], double b[], double x[], int orden) {
    //creación una matriz aumentada [A|b]
    double matrizAumentada[ORDEN_MATRIZ][ORDEN_MATRIZ + 1];

    //la matriz A y el vector b se copian en la matriz aumentada
    for (int i = 0; i < orden; i++) {
        for (int j = 0; j < orden; j++) {
            matrizAumentada[i][j] = A[i][j];
        }
        matrizAumentada[i][orden] = b[i];
    }

    // pasos de la eliminación de Gauss-Jordan
    for (int k = 0; k < orden; k++) {
        // se hacen unos en la diagonal
        double factor = matrizAumentada[k][k];
        for (int j = k; j < orden + 1; j++) {
            matrizAumentada[k][j] /= factor;
        }

        //el resto de filas se vuelven 0
        for (int i = 0; i < orden; i++) {
            if (i != k) {
                factor = matrizAumentada[i][k];
                for (int j = k; j < orden + 1; j++) {
                    matrizAumentada[i][j] -= factor * matrizAumentada[k][j];
                }
            }
        }
    }

    //solución ubicada en la última columna de la matriz aumentada
    for (int i = 0; i < orden; i++) {
        x[i] = matrizAumentada[i][orden];
    }
}
