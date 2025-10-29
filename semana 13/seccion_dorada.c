#include <stdio.h>
#include <math.h>

double funcion(double x){
  return (x - 2.0) * (x - 2.0);
}
double seccion_dorada(double a, double b, double tol, int max_iter){
  const double R = 0.6180033988749895;

  double x1, x2;
  double f1, f2;
  int iter = 0;

  while (fabs(b - a) > tol && iter < max_iter) {
    x1 = b - R * (b - a);
    x2 = a + R * (b - a);

    printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\n", iter, a, x1, x2, b, f1, f2);
  }
}