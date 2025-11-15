#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Número de ecuaciones 
#define N 5          
// Límite de iteraciones para métodos iterativos
#define MAX_ITER 1000 
// Tolerancia para convergencia
#define TOL 1e-6     

// Función para imprimir matrices y vectores de forma legible. Muestra el sistema Ax = b en formato matricial
void imprimir_matriz(double mat[N][N], double b[N]) {
    int i, j;
    printf("Sistema matricial A * Y = b:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            // Imprimir cada elemento de A
            printf("%f ", mat[i][j]); 
        }
        // Imprimit Y_i y b_i
        printf(" | | Y%d | = | %f |\n", i+1, b[i]); 
    }
}

//Función para imprimir el vector solución Y. Muestra las concentraciones en cada etapa

void imprimir_solucion(double y[N]) {
    int i;
    printf("Concentraciones Y_i en cada etapa:\n");
    for (i = 0; i < N; i++) {
        printf("Y%d = %f (etapa %d)\n", i+1, y[i], i+1);
    }
    printf("\n");
}

/* 
 * ========== MÉTODO GAUSS-JORDAN ==========
 * Transforma la matriz aumentada [A|b] a [I|y] mediante operaciones elementales
 * Ventaja: No requiere sustitución hacia atrás
 * Desventaja: Computacionalmente más costoso para matrices grandes
 */
void gauss_jordan(double A[N][N], double b[N], double y[N]) {
    int i, j, k;
    double factor, temp;
    //Matriz aumentada: columnas 0 a N-1 son A, columna N es b
    double Ab[N][N+1]; 
    
    printf("=== RESOLVIENDO POR ELIMINACIÓN DE GAUSS-JORDAN ===\n");
    printf("Transformando [A|b] -> [I|y] mediante operaciones elementales\n");
    
    // Paso 1: Construir matriz aumentada [A|b]
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            Ab[i][j] = A[i][j]; // Copiar matriz A
        }
        Ab[i][N] = b[i];        // Agregar vector b como última columna
    }
    
    // Paso 2: Proceso de eliminación para cada columna/pivote
    for (i = 0; i < N; i++) {
        // --- PIVOTEO PARCIAL ---
        // Buscar la fila con el mayor valor absoluto en la columna i
        int max_fila = i;
        for (k = i+1; k < N; k++) {
            if (fabs(Ab[k][i]) > fabs(Ab[max_fila][i])) {
                max_fila = k;
            }
        }
        
        // Intercambiar filas si se encontró un pivote mayor
        if (max_fila != i) {
            printf("Intercambiando fila %d con fila %d para mejor pivote\n", i+1, max_fila+1);
            for (j = 0; j <= N; j++) {
                temp = Ab[i][j];
                Ab[i][j] = Ab[max_fila][j];
                Ab[max_fila][j] = temp;
            }
        }
        
        // --- NORMALIZAR FILA PIVOTE ---
        // Hacer que el elemento diagonal sea 1 dividiendo toda la fila por Ab[i][i]
        factor = Ab[i][i];
        if (fabs(factor) < 1e-12) {
            printf("ERROR: Sistema singular detectado - pivote cercano a cero\n");
            return;
        }
        
        for (j = 0; j <= N; j++) {
            Ab[i][j] /= factor; // Dividir toda la fila por el pivote
        }
        
        // --- ELIMINACIÓN EN COLUMNA i ---
        // Hacer ceros en toda la columna i (excepto en la diagonal)
        for (k = 0; k < N; k++) {
            if (k != i) { // No modificar la fila del pivote
                factor = Ab[k][i]; // Factor para eliminar elemento (k,i)
                for (j = 0; j <= N; j++) {
                    // Restar múltiplo de la fila pivote a la fila k
                    Ab[k][j] -= factor * Ab[i][j];
                }
            }
        }
        
        printf("Pivote %d procesado - matriz diagonalizada parcialmente\n", i+1);
    }
    
    // Paso 3: Extraer solución de la última columna de la matriz aumentada
    for (i = 0; i < N; i++) {
        y[i] = Ab[i][N]; // La solución está en la última columna
    }
    
    printf("Proceso de Gauss-Jordan completado - matriz identidad alcanzada\n");
}

/* 
 * ========== FACTORIZACIÓN LU (MÉTODO DE DOOLITTLE) ==========
 * Descompone A en L (triangular inferior) y U (triangular superior)
 * L tiene 1's en la diagonal
 * Resuelve: 1) Lz = b (sustitución hacia adelante)
 *           2) Uy = z (sustitución hacia atrás)
 */
void factorizacion_lu(double A[N][N], double b[N], double y[N]) {
    double L[N][N], U[N][N]; // Matrices L y U
    double z[N];             // Vector intermedio z = Uy
    int i, j, k;
    
    printf("=== RESOLVIENDO POR FACTORIZACIÓN LU (Doolittle) ===\n");
    printf("Descomponiendo A = L * U\n");
    
    // Inicializar matrices L y U con ceros
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            L[i][j] = 0.0;
            U[i][j] = 0.0;
        }
    }
    
    // --- DESCOMPOSICIÓN LU ---
    printf("Iniciando descomposición LU...\n");
    for (i = 0; i < N; i++) {
        // Calcular elementos de la fila i de U
        for (j = i; j < N; j++) {
            U[i][j] = A[i][j]; // Empezar con el valor original de A
            // Restar producto de elementos ya calculados de L y U
            for (k = 0; k < i; k++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
        
        // Calcular elementos de la columna i de L (debajo de la diagonal)
        for (j = i; j < N; j++) {
            if (i == j) {
                L[i][i] = 1.0; // Diagonal de L siempre es 1
            } else {
                L[j][i] = A[j][i]; // Empezar con el valor original de A
                // Restar producto de elementos ya calculados de L y U
                for (k = 0; k < i; k++) {
                    L[j][i] -= L[j][k] * U[k][i];
                }
                // Dividir por el elemento diagonal de U
                if (fabs(U[i][i]) < 1e-12) {
                    printf("ERROR: División por cero en elemento U[%d][%d]\n", i, i);
                    return;
                }
                L[j][i] /= U[i][i];
            }
        }
    }
    
    printf("Descomposición LU completada\n");
    
    // --- SUSTITUCIÓN HACIA ADELANTE: Resolver Lz = b ---
    printf("Resolviendo Lz = b (sustitución hacia adelante)\n");
    for (i = 0; i < N; i++) {
        z[i] = b[i]; // Empezar con el valor de b
        // Restar contribuciones de elementos ya calculados
        for (j = 0; j < i; j++) {
            z[i] -= L[i][j] * z[j];
        }
        z[i] /= L[i][i]; // L[i][i] es siempre 1, pero por claridad
    }
    
    // --- SUSTITUCIÓN HACIA ATRÁS: Resolver Uy = z ---
    printf("Resolviendo Uy = z (sustitución hacia atrás)\n");
    for (i = N-1; i >= 0; i--) {
        y[i] = z[i]; // Empezar con el valor de z
        // Restar contribuciones de elementos ya calculados
        for (j = i+1; j < N; j++) {
            y[i] -= U[i][j] * y[j];
        }
        // Dividir por el elemento diagonal de U
        if (fabs(U[i][i]) < 1e-12) {
            printf("ERROR: Elemento diagonal U[%d][%d] es cero\n", i, i);
            return;
        }
        y[i] /= U[i][i];
    }
    
    printf("Sustituciones completadas - solución obtenida\n");
}

/* 
 * ========== MÉTODO GAUSS-SEIDEL ==========
 * Método iterativo que actualiza cada variable usando los valores más recientes
 * Converge para matrices diagonalmente dominantes (como nuestra matriz tridiagonal)
 */
int gauss_seidel(double A[N][N], double b[N], double y[N]) {
    double y_ant[N]; // Almacena la solución de la iteración anterior
    double error;    // Error máximo entre iteraciones
    int iter, i, j;
    
    printf("=== RESOLVIENDO POR MÉTODO ITERATIVO GAUSS-SEIDEL ===\n");
    printf("Iterando hasta convergencia (tolerancia: %e)\n", TOL);
    
    // Inicializar solución con valores cero
    for (i = 0; i < N; i++) {
        y[i] = 0.0;
    }
    
    // --- ITERACIONES PRINCIPALES ---
    for (iter = 0; iter < MAX_ITER; iter++) {
        // Guardar solución de la iteración anterior para calcular error
        for (i = 0; i < N; i++) {
            y_ant[i] = y[i];
        }
        
        // Actualizar cada variable Y_i usando los valores más recientes
        for (i = 0; i < N; i++) {
            double suma = 0.0;
            // Sumar contribuciones de todas las otras variables
            for (j = 0; j < N; j++) {
                if (j != i) {
                    suma += A[i][j] * y[j]; // Usa y[j] más reciente cuando j < i
                }
            }
            // Verificar que el elemento diagonal no sea cero
            if (fabs(A[i][i]) < 1e-12) {
                printf("ERROR: Elemento diagonal A[%d][%d] es cero\n", i, i);
                return 0;
            }
            // Calcular nuevo valor de Y_i
            y[i] = (b[i] - suma) / A[i][i];
        }
        
        // --- VERIFICAR CONVERGENCIA ---
        // Calcular el error máximo entre iteraciones consecutivas
        error = 0.0;
        for (i = 0; i < N; i++) {
            double diff = fabs(y[i] - y_ant[i]);
            if (diff > error) {
                error = diff;
            }
        }
        
        // Mostrar progreso cada 50 iteraciones
        if ((iter + 1) % 50 == 0) {
            printf("Iteración %d - Error: %e\n", iter+1, error);
        }
        
        // Verificar si se alcanzó la convergencia
        if (error < TOL) {
            printf("¡Convergencia alcanzada en %d iteraciones!\n", iter+1);
            printf("Error final: %e (menor que tolerancia %e)\n", error, TOL);
            return 1; // Éxito
        }
    }
    
    // Si llegamos aquí, no convergió en el número máximo de iteraciones
    printf("ADVERTENCIA: El método no convergió después de %d iteraciones\n", MAX_ITER);
    printf("Error final: %e (mayor que tolerancia %e)\n", error, TOL);
    printf("Posibles causas: matriz no diagonalmente dominante o tolerancia muy estricta\n");
    return 0; // No convergió
}

/* 
 * ========== FUNCIÓN PRINCIPAL ==========
 * Configura el problema y llama a los tres métodos de solución
 */
int main() {
    printf("Balance de masa en proceso de 5 etapas\n");
    printf("F1 = 500 kg/h, Y_ent = 0.1, F2 = 1000 kg/h, X_ent = 0, K = 4\n");
    // Matriz A del sistema (representa los coeficientes del balance de masa)
    double A[N][N] = {
        {-9.0,  8.0,  0.0,  0.0,  0.0}, // Etapa 1: Y_ent - 9Y1 + 8Y2 = 0
        { 1.0, -9.0,  8.0,  0.0,  0.0}, // Etapa 2: Y1 - 9Y2 + 8Y3 = 0
        { 0.0,  1.0, -9.0,  8.0,  0.0}, // Etapa 3: Y2 - 9Y3 + 8Y4 = 0
        { 0.0,  0.0,  1.0, -9.0,  8.0}, // Etapa 4: Y3 - 9Y4 + 8Y5 = 0
        { 0.0,  0.0,  0.0,  1.0, -9.0}  // Etapa 5: Y4 - 9Y5 = 0
    };
    
    // Vector b: términos independientes del sistema. Solo la primera ecuación tiene término no nulo por Y_ent = 0.1
    double b[N] = {-0.1, 0.0, 0.0, 0.0, 0.0};
    
    // Vectores para almacenar soluciones de cada método
    double y_gj[N]; // Solución con el método Gauss-Jordan
    double y_lu[N]; // Solución por factorización LU  
    double y_gs[N]; // Solución con el método Gauss-Seidel
    
    // Mostrar el sistema original
    printf("Sistema original:\n");
    imprimir_matriz(A, b);
    
    printf("Resolución con los 3 métodos establecidos\n");
    //Solución con el método Gauss-Jordan
    gauss_jordan(A, b, y_gj);
    imprimir_solucion(y_gj);
    
    //Solución con factorizacion Lu
    factorizacion_lu(A, b, y_lu);
    imprimir_solucion(y_lu);
    
    //Solución con el método Gauss-Seidel     gauss_seidel(A, b, y_gs);
    gauss_seidel(A, b, y_gs);
    imprimir_solucion(y_gs);
    
    //Calculo se resultados finales. X_exit se calcula como X5 = K * Y5, ya que existe un equilibrio 
    double K = 4.0;
    double X_exit_gj = K * y_gj[4];
    double X_exit_lu = K * y_lu[4];
    double X_exit_gs = K * y_gs[4];
    
    //Impresión de resultados y comparaciones de los métodos     printf("Resultados");
    printf("Variable de salida Y5 (concentración en última etapa):\n");
    printf("Gauss-Jordan:  Y5 = %f\n", y_gj[4]);
    printf("Factorización LU: Y5 = %f\n", y_lu[4]);
    printf("Gauss-Seidel:  Y5 = %f\n", y_gs[4]);
    
    printf("Variable de salida X5 (concentración en solvente):\n");
    printf("Gauss-Jordan:  X5 = K * Y5 = 4 * %f = %10.8f\n", y_gj[4], X_exit_gj);
    printf("Factorización LU: X5 = K * Y5 = 4 * %f = %10.8f\n", y_lu[4], X_exit_lu);
    printf("Gauss-Seidel:  X5 = K * Y5 = 4 * %f = %10.8f\n", y_gs[4], X_exit_gs);
    
    // verificación de consistencia entre métodos
    printf("Diferencias entre los métodos:\n");
    printf("GJ vs LU:  %e\n", fabs(y_gj[4] - y_lu[4]));
    printf("GJ vs GS:  %e\n", fabs(y_gj[4] - y_gs[4]));
    printf("LU vs GS:  %e\n", fabs(y_lu[4] - y_gs[4]));
    
    return 0;
}
