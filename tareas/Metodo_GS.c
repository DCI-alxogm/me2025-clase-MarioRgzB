#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 1000
#define TOLERANCIA 1e-6

int leer_datos(double **A, double *B, int *n) {
    char opcion;
    char nombre_archivo[100];
    FILE *archivo;
    
    printf("Gauss-Seidel\n");
    printf("¿Desea ingresar los datos por (T)erminal o (A)rchivo? ");
    scanf(" %c", &opcion);
    
    if (opcion == 'A' || opcion == 'a') {
        printf("Ingrese el nombre del archivo: ");
        scanf("%s", nombre_archivo);
        
        archivo = fopen(nombre_archivo, "r");
        if (archivo == NULL) {
            printf("Error: No se pudo abrir el archivo.\n");
            return 0;
        }
        
        fscanf(archivo, "%d", n);
        
        *A = (double**)malloc(*n * sizeof(double*));
        for (int i = 0; i < *n; i++) {
            (*A)[i] = (double*)malloc(*n * sizeof(double));
        }
        *B = (double*)malloc(*n * sizeof(double));
        
        for (int i = 0; i < *n; i++) {
            for (int j = 0; j < *n; j++) {
                fscanf(archivo, "%lf", &(*A)[i][j]);
            }
        }
        
        for (int i = 0; i < *n; i++) {
            fscanf(archivo, "%lf", &(*B)[i]);
        }
        
        fclose(archivo);
        printf("Datos cargados correctamente desde el archivo.\n");
        
    } else {
        printf("Ingrese la dimension del sistema: ");
        scanf("%d", n);
        
        *A = (double**)malloc(*n * sizeof(double*));
        for (int i = 0; i < *n; i++) {
            (*A)[i] = (double*)malloc(*n * sizeof(double));
        }
        *B = (double*)malloc(*n * sizeof(double));
        
        printf("Ingrese los elementos de la matriz A (%dx%d):\n", *n, *n);
        for (int i = 0; i < *n; i++) {
            printf("Fila %d: ", i + 1);
            for (int j = 0; j < *n; j++) {
                scanf("%lf", &(*A)[i][j]);
            }
        }
        
        printf("Ingrese los elementos del vector B:\n");
        for (int i = 0; i < *n; i++) {
            printf("B[%d] = ", i + 1);
            scanf("%lf", &(*B)[i]);
        }
    }
    
    return 1;
}

void imprimir_sistema(double **A, double *B, int n) {
    printf("Sistema de ecuaciones:\n");
    for (int i = 0; i < n; i++) {
        printf("| ");
        for (int j = 0; j < n; j++) {
            printf("%f ", A[i][j]);
        }
        printf(" | %f |\n", B[i]);
    }
}

int es_diagonal_dominante(double **A, int n) {
    int dominante = 1;
    
    for (int i = 0; i < n; i++) {
        double suma = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                suma += fabs(A[i][j]);
            }
        }
        
        if (fabs(A[i][i]) > suma) {
            printf("Fila %d: |%f| > %f (dominante)\n", i+1, A[i][i], suma);
        } else {
            printf("Fila %d: |%f| <= %f (no dominante)\n", i+1, A[i][i], suma);
            dominante = 0;
        }
    }
    
    return dominante;
}

double calcular_determinante(double **A, int n) {
    double **temp = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        temp[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            temp[i][j] = A[i][j];
        }
    }
    
    double det = 1.0;
    int cambios = 0;
    
    for (int i = 0; i < n; i++) {
        int max_fila = i;
        double max_val = fabs(temp[i][i]);
        
        for (int k = i + 1; k < n; k++) {
            if (fabs(temp[k][i]) > max_val) {
                max_val = fabs(temp[k][i]);
                max_fila = k;
            }
        }
        
        if (max_fila != i) {
            double *fila_temp = temp[i];
            temp[i] = temp[max_fila];
            temp[max_fila] = fila_temp;
            cambios++;
        }
        
        if (fabs(temp[i][i]) < 1e-12) {
            det = 0.0;
            break;
        }
        
        det *= temp[i][i];

        for (int k = i + 1; k < n; k++) {
            double factor = temp[k][i] / temp[i][i];
            for (int j = i + 1; j < n; j++) {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }
    
    if (cambios % 2 == 1) {
        det = -det;
    }
    
    for (int i = 0; i < n; i++) {
        free(temp[i]);
    }
    free(temp);
    
    return det;
}

int gauss_seidel(double **A, double *B, int n, double *X, double *error_final, int *iteraciones) {
    double *X_anterior = (double*)malloc(n * sizeof(double));
    if (X_anterior == NULL) {
        printf("No se pudo asignar memoria.\n");
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        X[i] = 0.0;
    }
    
    int iter;
    for (iter = 0; iter < MAX_ITER; iter++) {
        for (int i = 0; i < n; i++) {
            X_anterior[i] = X[i];
        }

        for (int i = 0; i < n; i++) {
            double suma = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    suma += A[i][j] * X[j];
                }
            }
            X[i] = (B[i] - suma) / A[i][i];
        }

        double error_max = 0.0;
        for (int i = 0; i < n; i++) {
            double error = fabs(X[i] - X_anterior[i]);
            if (error > error_max) {
                error_max = error;
            }
        }
        
        if (iter < 10 || (iter + 1) % 50 == 0 || error_max < TOLERANCIA) {
            printf("%d  %e", iter + 1, error_max);
            if (error_max < TOLERANCIA) printf("Convergido");
        }

        if (error_max < TOLERANCIA) {
            break;
        }
    }
    
    *error_final = 0.0;
    for (int i = 0; i < n; i++) {
        double error = fabs(X[i] - X_anterior[i]);
        if (error > *error_final) {
            *error_final = error;
        }
    }
    
    *iteraciones = iter + 1;
    free(X_anterior);
    
    return 1;
}

void verificar_solucion(double **A, double *B, double *X, int n) {
    printf("Verificando la solución:\n");
    double error_max = 0.0;
    
    for (int i = 0; i < n; i++) {
        double suma = 0.0;
        for (int j = 0; j < n; j++) {
            suma += A[i][j] * X[j];
        }
        double residuo = fabs(suma - B[i]);
        printf("Ecuacion %d: %f (residuo: %e)\n", i+1, suma, residuo);
        
        if (residuo > error_max) {
            error_max = residuo;
        }
    }
    printf("Error maximo en verificacion: %e\n", error_max);
}

void imprimir_resultados(double *X, int n, double determinante, int iteraciones, 
                        double error_final, int convergio, int dominante) {
    printf("resultados\n");
    
    printf("Determinante: %f\n", determinante);
    
    if (fabs(determinante) < 1e-12) {
        printf("El sistema puede ser singular o mal condicionado.\n");
    } else {
        printf("El sistema esta bien determinado.\n");
    }
    
    if (dominante) {
        printf("La matriz es diagonalmente dominante.\n");
    } else {
        printf("La matriz no es diagonalmente dominante.\n");
    }
    
    if (convergio) {
        printf("Convergencia alcanzada en %d iteraciones.\n", iteraciones);
        printf("Error final: %e\n", error_final);
    } else {
        printf("No se alcanzo convergencia.\n", iteraciones);
        printf("Error final: %e\n", error_final);
    }
    
    printf("Solucion del sistema:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %f\n", i + 1, X[i]);
    }
}

int main() {
    double **A = NULL;
    double *B = NULL;
    double *X = NULL;
    double determinante, error_final;
    int n, iteraciones, dominante;
    
    if (!leer_datos(&A, &B, &n)) {
        return 1;
    }
    
    X = (double*)malloc(n * sizeof(double));
    if (X == NULL) {
        printf("No se pudo asignar memoria para la solución.\n");
        for (int i = 0; i < n; i++) free(A[i]);
        free(A);
        free(B);
        return 1;
    }

    printf("Sistema Original");
    imprimir_sistema(A, B, n);

    dominante = es_diagonal_dominante(A, n);

    determinante = calcular_determinante(A, n);

    int exito = gauss_seidel(A, B, n, X, &error_final, &iteraciones);
    
    if (exito) {

        verificar_solucion(A, B, X, n);

        int convergio = (error_final < TOLERANCIA);
        imprimir_resultados(X, n, determinante, iteraciones, error_final, convergio, dominante);
    }

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(B);
    free(X);
    
    printf("\nPrograma terminado.\n");
    return 0;
}