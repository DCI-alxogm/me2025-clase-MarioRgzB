#include <stdio.h>
#include <math.h>

#define MAX_DIM 10
#define TOL 1e-6
#define MAX_ITER 1000

double funcion(double x[], int dim) {
    if (dim == 2) {
        return -(x[0]-2.0)*(x[0]-2.0) - (x[1]-3.0)*(x[1]-3.0);
    }

    double suma = 0.0;
    for (int i = 0; i < dim; i++) {
        double d = x[i] - (i + 1.0);
        suma -= d * d;
    }
    return suma;
}

void calcular_gradiente(double x[], double grad[], int dim) {
    double h = 1e-6;
    double t;
    
    for (int i = 0; i < dim; i++) {
        t = x[i];
        
        x[i] = t + h;
        double f1 = funcion(x, dim);
        
        x[i] = t - h;
        double f2 = funcion(x, dim);
        
        grad[i] = (f1 - f2) / (2.0 * h);
        x[i] = t;  
    }
}

double buscar_paso_optimo(double x[], double dir[], int dim) {
    double alpha = 1.0;
    double factor = 0.5;
    double f_act = funcion(x, dim);
    
    for (int i = 0; i < 10; i++) {
        double x_t[MAX_DIM];
        for (int j = 0; j < dim; j++) {
            x_t[j] = x[j] + alpha * dir[j];
        }
        
        double f_n = funcion(x_t, dim);
        
        if (f_n > f_act) {
            return alpha;  
        }
        
        alpha *= factor;  
    }
    
    return 0.1;  
}

void gradiente(double x0[], int dim) {
    double x[MAX_DIM], grad[MAX_DIM];
    double alpha, norma_grad;
    int iter;

    for (int i = 0; i < dim; i++) {
        x[i] = x0[i];
    }

    printf("Punto inicial: (");
    for (int i = 0; i < dim; i++) {
        printf("%f%s", x[i], (i < dim-1) ? ", " : "");
    }
    
    for (iter = 0; iter < MAX_ITER; iter++) {

        calcular_gradiente(x, grad, dim);

        norma_grad = 0.0;
        for (int i = 0; i < dim; i++) {
            norma_grad += grad[i] * grad[i];
        }
        norma_grad = sqrt(norma_grad);

        if (norma_grad < TOL) {
            printf("Convergencia alcanzada\n");
            break;
        }

        alpha = buscar_paso_optimo(x, grad, dim);

        for (int i = 0; i < dim; i++) {
            x[i] += alpha * grad[i];
        }

        if (iter % 50 == 0) {
            printf("Iter %d: f = %f, |grad f| = %f\n", 
                   iter, funcion(x, dim), norma_grad);
        }
    }
  
    printf("Resultados:\n");
    printf("Iteraciones: %d\n", iter);
    printf("Punto óptimo: (");
    for (int i = 0; i < dim; i++) {
        printf("%f%s", x[i], (i < dim-1) ? ", " : "");
    }
    printf("Valor función: %f\n", funcion(x, dim));
    printf("Norma gradiente: %f\n", norma_grad);
}

int main() {
    int dimension;
    double punto_inicial[MAX_DIM];

    
    printf("Ingrese dimension (2-%d): ", MAX_DIM);
    scanf("%d", &dimension);
    
    if (dimension < 2 || dimension > MAX_DIM) {
        printf("Dimension no valida\n");
        return 1;
    }
    
    printf("Ingrese punto inicial:\n");
    for (int i = 0; i < dimension; i++) {
        printf("Coordenada %d: ", i + 1);
        scanf("%lf", &punto_inicial[i]);
    }

    gradiente(punto_inicial, dimension);
    
    return 0;
}