#include<stdio.h>

double f(double x, double y){
  return y - x - 2*x*x - 2*x*y - y*y;
}

int main (){
  double x_mn = -2.0, x_max = 2.0;
  double y_mn = 1.0, y_max = 3.0;
  int n = 10;

  double dx = (x_max - x_mn) / n;
  double dy = (y_max - y_mn) / n;

  double max_v = f(x_mn, y_mn);
  double m_x = x_mn;
  double m_y = y_mn;

  for(int i = 0; i <= n; i++) {
    double x = x_mn + i * dx;
    for(int j = 0; j <= n; j++){
      double y = y_mn + j * dy;
      double v = f(x, y);

      if(v > max_v){
        max_v = v;
        m_x = x;
        m_y = y;
      }
    }
  }
  printf("valor maximo x: %f, y: %f\n", m_x, m_y);
  printf("f(x,y): %f\n", max_v);

  return 0;
}