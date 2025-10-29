#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int *permutaciones;
    int cambios;
} Pivoteo;

int leer_datos(double **A, double *B, int *n) {
    char opcion;
    char nombre_archivo[100];
    FILE *archivo;
    
    printf("=== RESOLUCION DE SISTEMAS POR FACTORIZACION LU ===\n");
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
        printf("Ingrese la dimension del sistema (n): ");
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

void imprimir_matriz(double **A, int n, const char *nombre) {
    printf("\n%s:\n", nombre);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.3f ", A[i][j]);
        }
        printf("\n");
    }
}

void imprimir_vector(double *V, int n, const char *nombre) {
    printf("%s:\n", nombre);
    for (int i = 0; i < n; i++) {
        printf("%f\n", V[i]);
    }
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

int encontrar_pivote(double **A, int n, int columna, int fila_actual) {
    int fila_pivote = fila_actual;
    double max_valor = fabs(A[fila_actual][columna]);
    
    for (int i = fila_actual + 1; i < n; i++) {
        if (fabs(A[i][columna]) > max_valor) {
            max_valor = fabs(A[i][columna]);
            fila_pivote = i;
        }
    }
    
    return fila_pivote;
}

void intercambiar_filas(double **A, double *B, int n, int fila1, int fila2, Pivoteo *piv) {
    if (fila1 == fila2) return;
    
    double *temp_fila = A[fila1];
    A[fila1] = A[fila2];
    A[fila2] = temp_fila;

    if (B != NULL) {
        double temp_elem = B[fila1];
        B[fila1] = B[fila2];
        B[fila2] = temp_elem;
    }

    int temp_perm = piv->permutaciones[fila1];
    piv->permutaciones[fila1] = piv->permutaciones[fila2];
    piv->permutaciones[fila2] = temp_perm;
    
    piv->cambios++;
}

int factorizacion_lu(double **A, int n, Pivoteo *piv, double *determinante) {

    piv->permutaciones = (int*)malloc(n * sizeof(int));
    piv->cambios = 0;
    for (int i = 0; i < n; i++) {
        piv->permutaciones[i] = i;
    }
    
    *determinante = 1.0;
    
    for (int k = 0; k < n - 1; k++) {
        
        int fila_pivote = encontrar_pivote(A, n, k, k);
        
        if (fila_pivote != k) {
            intercambiar_filas(A, NULL, n, k, fila_pivote, piv);
            printf("Intercambiadas filas %d y %d\n", k + 1, fila_pivote + 1);
        }

        if (fabs(A[k][k]) < 1e-12) {
            printf("Error: Matriz singular.\n");
            *determinante = 0;
            return 0;
        }

        for (int i = k + 1; i < n; i++) {
            A[i][k] = A[i][k] / A[k][k];  
            for (int j = k + 1; j < n; j++) {
                A[i][j] = A[i][j] - A[i][k] * A[k][j];
            }
        }
        
        printf("\nPaso %d completado:\n", k + 1);
        imprimir_matriz(A, n, "Matriz despues de eliminacion");
    }

    if (fabs(A[n-1][n-1]) < 1e-12) {
        printf("Error: Matriz singular detectada.\n");
        *determinante = 0;
        return 0;
    }

    *determinante = 1.0;
    for (int i = 0; i < n; i++) {
        *determinante *= A[i][i];
    }

    if (piv->cambios % 2 != 0) {
        *determinante = -(*determinante);
    }
    
    return 1;
}

void resolver_L(double **LU, double *Pb, double *y, int n) {
    for (int i = 0; i < n; i++) {
        y[i] = Pb[i];
        for (int j = 0; j < i; j++) {
            y[i] -= LU[i][j] * y[j];
        }
    }
}

void resolver_U(double **LU, double *y, double *x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= LU[i][j] * x[j];
        }
        x[i] = x[i] / LU[i][i];
    }
}

void extraer_L(double **LU, double **L, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
                L[i][j] = LU[i][j];
            } else if (i == j) {
                L[i][j] = 1.0;
            } else {
                L[i][j] = 0.0;
            }
        }
    }
}

void extraer_U(double **LU, double **U, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                U[i][j] = LU[i][j];
            } else {
                U[i][j] = 0.0;
            }
        }
    }
}

void aplicar_permutacion(double *B, double *Pb, Pivoteo *piv, int n) {
    for (int i = 0; i < n; i++) {
        Pb[i] = B[piv->permutaciones[i]];
    }
}

int resolver_sistema_lu(double **A, double *B, int n, double *solucion, double *determinante) {
    Pivoteo piv;
    double *y, *Pb;
    double **L, **U;
    int exito;

    y = (double*)malloc(n * sizeof(double));
    Pb = (double*)malloc(n * sizeof(double));
    L = (double**)malloc(n * sizeof(double*));
    U = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        L[i] = (double*)malloc(n * sizeof(double));
        U[i] = (double*)malloc(n * sizeof(double));
    }

    double **A_copia = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A_copia[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            A_copia[i][j] = A[i][j];
        }
    }
    
    exito = factorizacion_lu(A_copia, n, &piv, determinante);
    
    if (exito) {
        printf("Factorizacion completa.\n");
        
        extraer_L(A_copia, L, n);
        extraer_U(A_copia, U, n);
        
        imprimir_matriz(L, n, "Matriz L");
        imprimir_matriz(U, n, "Matriz U");
        
        aplicar_permutacion(B, Pb, &piv, n);
        imprimir_vector(Pb, n, "Vector Pb (B permutado)");
        
        resolver_L(A_copia, Pb, y, n);
        imprimir_vector(y, n, "Vector y (de Ly = Pb)");
        resolver_U(A_copia, y, solucion, n);
        
        printf("Resolucion completa\n");
    }

    free(y);
    free(Pb);
    for (int i = 0; i < n; i++) {
        free(L[i]);
        free(U[i]);
        free(A_copia[i]);
    }
    free(L);
    free(U);
    free(A_copia);
    free(piv.permutaciones);
    
    return exito;
}

void imprimir_resultados(double *solucion, int n, double determinante, int exito) {
    printf("Resultados \n");
    
    if (exito) {
        printf("El sistema tiene solucion unica.\n");
        printf("Determinante: %f\n", determinante);
        
        printf("Solucion del sistema:\n");
        for (int i = 0; i < n; i++) {
            printf("x%d = %f\n", i + 1, solucion[i]);
        }
        
        if (fabs(determinante) < 1e-10) {
            printf("El sistema puede ser mal condicionado.\n");
        } else {
            printf("El problema esta bien determinado.\n");
        }
    } else {
        printf("El sistema no tiene solucion unica.\n");
    }
}

int main() {
    double **A = NULL;
    double *B = NULL;
    double *solucion = NULL;
    double determinante;
    int n, exito;

    if (!leer_datos(&A, &B, &n)) {
        return 1;
    }

    solucion = (double*)malloc(n * sizeof(double));
    
    // Mostrar sistema original
    printf("Sistema original");
    imprimir_sistema(A, B, n);

    exito = resolver_sistema_lu(A, B, n, solucion, &determinante);
    
    // Mostrar resultados
    imprimir_resultados(solucion, n, determinante, exito);
    
    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(B);
    free(solucion);
    
    printf("\nPrograma terminado.\n");
    return 0;
}