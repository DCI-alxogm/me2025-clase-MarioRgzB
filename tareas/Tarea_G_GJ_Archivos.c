#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 1e-10

void imprimir(double **mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f \n", mat[i][j]);
        }
    }
}

void intercambiar(double **mat, int f1, int f2, int m) {
    for (int j = 0; j < m; j++) {
        double temp = mat[f1][j];
        mat[f1][j] = mat[f2][j];
        mat[f2][j] = temp;
    }
}

int pivoteMaximo(double **mat, int col, int n) {
    int max_fila = col;
    for (int i = col + 1; i < n; i++) {
        if (fabs(mat[i][col]) > fabs(mat[max_fila][col])) {
            max_fila = i;
        }
    }
    return max_fila;
}

int gauss(double **mat, int n, double *sol) {
    for (int i = 0; i < n; i++) {
        int pivote = pivoteMaximo(mat, i, n);
        if (pivote != i) {
            intercambiar(mat, i, pivote, n + 1);
            printf("Intercambio fila %d con %d\n", i + 1, pivote + 1);
        }
        
        if (fabs(mat[i][i]) < EPS) {
            printf("Sistema singular!\n");
            return -1;
        }
        
        for (int k = i + 1; k < n; k++) {
            double factor = mat[k][i] / mat[i][i];
            for (int j = i; j <= n; j++) {
                mat[k][j] -= factor * mat[i][j];
            }
        }
    }
    
    for (int i = n - 1; i >= 0; i--) {
        sol[i] = mat[i][n];
        for (int j = i + 1; j < n; j++) {
            sol[i] -= mat[i][j] * sol[j];
        }
        sol[i] /= mat[i][i];
    }
    return 1;
}

int gaussJordan(double **mat, int n, double *sol) {
    for (int i = 0; i < n; i++) {
        int pivote = pivoteMaximo(mat, i, n);
        if (pivote != i) {
            intercambiar(mat, i, pivote, n + 1);
        }
        
        if (fabs(mat[i][i]) < EPS) {
            printf("Sistema singular\n");
            return -1;
        }
        
        double pivot_val = mat[i][i];
        for (int j = i; j <= n; j++) {
            mat[i][j] /= pivot_val;
        }
        
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = mat[k][i];
                for (int j = i; j <= n; j++) {
                    mat[k][j] -= factor * mat[i][j];
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        sol[i] = mat[i][n];
    }
    return 1;
}

double **leerMatriz(int n) {
    double **mat = (double **)malloc(n * sizeof(double *));
    printf("Ingrese la matriz aumentada (%d filas, %d columnas):\n", n, n + 1);
    for (int i = 0; i < n; i++) {
        mat[i] = (double *)malloc((n + 1) * sizeof(double));
        printf("Fila %d: ", i + 1);
        for (int j = 0; j <= n; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }
    return mat;
}

double **copiarMatriz(double **orig, int n) {
    double **copia = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        copia[i] = (double *)malloc((n + 1) * sizeof(double));
        for (int j = 0; j <= n; j++) {
            copia[i][j] = orig[i][j];
        }
    }
    return copia;
}

void liberarMatriz(double **mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

int main() {
    int n;
    printf("Dimension del sistema: ");
    scanf("%d", &n);
    
    double **matriz = leerMatriz(n);
    double **copia_g = copiarMatriz(matriz, n);
    double **copia_gj = copiarMatriz(matriz, n);
    
    double *sol_g = (double *)malloc(n * sizeof(double));
    double *sol_gj = (double *)malloc(n * sizeof(double));
    
    printf("Matriz original:");
    imprimir(matriz, n, n + 1);
    
    printf("Eliminacion Gauss\n");
    if (gauss(copia_g, n, sol_g) == 1) {
        printf("Solucion Gauss: ");
        for (int i = 0; i < n; i++) printf("x%d=%f ", i + 1, sol_g[i]);
        printf("\n");
    }
    
    printf("Gauss-Jordan\n");
    if (gaussJordan(copia_gj, n, sol_gj) == 1) {
        printf("Solucion Gauss-Jordan: ");
        for (int i = 0; i < n; i++) printf("x%d=%f ", i + 1, sol_gj[i]);
    }
    
    liberarMatriz(matriz, n);
    liberarMatriz(copia_g, n);
    liberarMatriz(copia_gj, n);
    free(sol_g);
    free(sol_gj);
    
    return 0;

}
