#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definición de las funciones de los modelos
double peleg(double params[], double aw) {
    return params[0] * pow(aw, params[1]) + params[2] * pow(aw, params[3]);
}

double dlp(double params[], double aw) {
    double x = log(-log(aw));
    return params[0] + params[1] * x + params[2] * pow(x, 2) + params[3] * pow(x, 3);
}

// Función Chi-Cuadrado
double chi_squared(double params[], double (*model)(double[], double), double aw_data[], double mc_data[], int n) {
    double chi2 = 0.0;
    for (int i = 0; i < n; i++) {
        double mc_predicted = model(params, aw_data[i]);
        chi2 += pow(mc_data[i] - mc_predicted, 2);
    }
    return chi2;
}

// Método de descenso de gradiente (simplificado)
void gradient_descent(double aw_data[], double mc_data[], int n, double params[], double (*model)(double[], double), double learning_rate, int iterations) {
    double grad[4];
    for (int iter = 0; iter < iterations; iter++) {
        // Calcular gradientes (aproximación numérica)
        double delta = 0.0001;
        for (int i = 0; i < 4; i++) {
            double params_plus[4], params_minus[4];
            for (int j = 0; j < 4; j++) {
                params_plus[j] = params_minus[j] = params[j];
            }
            params_plus[i] += delta;
            params_minus[i] -= delta;

            grad[i] = (chi_squared(params_plus, model, aw_data, mc_data, n) - chi_squared(params_minus, model, aw_data, mc_data, n)) / (2 * delta);
        }

        // Actualizar parámetros
        for (int i = 0; i < 4; i++) {
            params[i] -= learning_rate * grad[i];
        }
    }
}

int main() {
    // Datos de ejemplo (deberías reemplazarlos con tus datos reales)
    double aw_data[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    double mc_data[] = {2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8};
    int n = sizeof(aw_data) / sizeof(aw_data[0]);

    // Parámetros iniciales
    double initial_params_peleg[] = {1.0, 1.0, 1.0, 1.0};
    double initial_params_dlp[] = {1.0, 1.0, 1.0, 1.0};

    // Hiperparámetros para el descenso de gradiente
    double learning_rate = 0.001;
    int iterations = 1000;

    // Optimización para Peleg
    printf("Optimizando Peleg...\n");
    gradient_descent(aw_data, mc_data, n, initial_params_peleg, peleg, learning_rate, iterations);
    printf("Parámetros optimizados Peleg: %lf %lf %lf %lf\n", initial_params_peleg[0], initial_params_peleg[1], initial_params_peleg[2], initial_params_peleg[3]);

    // Optimización para DLP
    printf("Optimizando DLP...\n");
    gradient_descent(aw_data, mc_data, n, initial_params_dlp, dlp, learning_rate, iterations);
    printf("Parámetros optimizados DLP: %lf %lf %lf %lf\n", initial_params_dlp[0], initial_params_dlp[1], initial_params_dlp[2], initial_params_dlp[3]);

    return 0;
}

