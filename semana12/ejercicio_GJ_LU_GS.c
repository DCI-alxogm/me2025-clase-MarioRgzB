#include <stdio.h>
#include <math.h>

#define N 3

void g_j(double A[N][N+1]);
void lu_d(double A[N][N], double L[N][N], double U[N][N]);
void s_lu(double L[N][N], double U[N][N], double b[N], double x[N]);
void g_s(double A[N][N], double b[N], double x[N], int max_iter, double tol);
void print_m(double M[N][N+1], char* nm);
void print_v(double v[N], char* nm);

int main() {
    double A[N][N] = {
        {3.0, -0.1, -0.2},
        {0.7, 7.0, -0.3},
        {0.3, -0.2, 10.0}
    };
    
    double b[N] = {7.85, -19.3, 71.4};
    double x[N];
    
    printf("3x - 0.1y - 0.2z = 7.85\n");
    printf("0.7x + 7y - 0.3z = -19.3\n");
    printf("0.3x - 0.2y + 10z = 71.4\n");
    
    printf("Gauss Jordan\n");
    double GJ[N][N+1];
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            GJ[i][j] = A[i][j];
        }
        GJ[i][N] = b[i];
    }
    g_j(GJ);
    
    printf("Solucion:\n");
    for(int i = 0; i < N; i++) {
        printf("x%d = %f\n", i+1, GJ[i][N]);
    }
    printf("Factorizacion LU\n");
    double L[N][N], U[N][N];
    lu_d(A, L, U);
    
    printf("Matriz L:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%f ", L[i][j]);
        }
    }
    
    printf("Matriz U:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%f ", U[i][j]);
        }
    }
    
    s_lu(L, U, b, x);
    printf("Solucion LU:\n");
    for(int i = 0; i < N; i++) {
        printf("x%d = %f\n", i+1, x[i]);
    }
    
    printf("Metodo Gauss-Seidel \n");
    double x0[N] = {0.0, 0.0, 0.0};
    g_s(A, b, x0, 50, 1e-8);
    
    printf("Solucion (Gauss-Seidel):\n");
    for(int i = 0; i < N; i++) {
        printf("x%d = %f\n", i+1, x0[i]);
    }
    
    printf("Verificacion\n");
    double res[N];
    for(int i = 0; i < N; i++) {
        res[i] = 0.0;
        for(int j = 0; j < N; j++) {
            res[i] += A[i][j] * x0[j];
        }
        printf("Ecuacion %d: %f = %f (error: %e)\n", 
               i+1, res[i], b[i], fabs(res[i] - b[i]));
    }
    
    return 0;
}

void g_j(double A[N][N+1]) {
    int i, j, k;
    double factor;
    
    for(i = 0; i < N; i++) {
        int max_r = i;
        for(k = i+1; k < N; k++) {
            if(fabs(A[k][i]) > fabs(A[max_r][i])) {
                max_r = k;
            }
        }
        
        if(max_r != i) {
            for(j = 0; j <= N; j++) {
                double temp = A[i][j];
                A[i][j] = A[max_r][j];
                A[max_r][j] = temp;
            }
        }
        
        double pivot = A[i][i];
        for(j = i; j <= N; j++) {
            A[i][j] /= pivot;
        }
        
        for(k = 0; k < N; k++) {
            if(k != i) {
                factor = A[k][i];
                for(j = i; j <= N; j++) {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }
    }
}

void lu_d(double A[N][N], double L[N][N], double U[N][N]) {
    int i, j, k;

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            L[i][j] = 0.0;
            U[i][j] = 0.0;
        }
    }
    
    for(i = 0; i < N; i++) {
        for(j = i; j < N; j++) {
            U[i][j] = A[i][j];
            for(k = 0; k < i; k++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
        L[i][i] = 1.0;
        for(j = i+1; j < N; j++) {
            L[j][i] = A[j][i];
            for(k = 0; k < i; k++) {
                L[j][i] -= L[j][k] * U[k][i];
            }
            L[j][i] /= U[i][i];
        }
    }
}

void s_lu(double L[N][N], double U[N][N], double b[N], double x[N]) {
    double y[N];
    int i, j;
    
    for(i = 0; i < N; i++) {
        y[i] = b[i];
        for(j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
        y[i] /= L[i][i];
    }
    for(i = N-1; i >= 0; i--) {
        x[i] = y[i];
        for(j = i+1; j < N; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

void g_s(double A[N][N], double b[N], double x[N], int max_iter, double tol) {
    int iter, i, j;
    double error, sum, n_val;
    
    printf("Iteraciones:\n");
    for(iter = 0; iter < max_iter; iter++) {
        error = 0.0;
        
        for(i = 0; i < N; i++) {
            sum = 0.0;
            for(j = 0; j < N; j++) {
                if(j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            n_val = (b[i] - sum) / A[i][i];
            error += fabs(n_val - x[i]);
            x[i] = n_val;
        }
        
        if((iter < 5) || (iter % 5 == 0)) {
            printf("Iter %2d: x1=%f, x2=%f, x3=%f, error=%e\n", 
                   iter, x[0], x[1], x[2], error);
        }
        
        if(error < tol) {
            printf("Convergencia alcanzada en %d iteraciones\n", iter);
            break;
        }
    }
    
    if(iter == max_iter) {
        printf("Este es el maximo de iteraciones\n");
    }
}