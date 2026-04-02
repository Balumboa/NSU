#include <math.h>
#include <stdio.h>

int main() {
  double x1, x2, x3;
  double y1, y2, y3;
  scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
  double dx1 = x1 - x2;
  double dy1 = y1 - y2;
  double dx2 = x3 - x2;
  double dy2 = y3 - y2;
  double dx3 = x1 - x3;
  double dy3 = y1 - y3;
  double len1 = sqrt(dx1 * dx1 + dy1 * dy1);
  double len2 = sqrt(dx2 * dx2 + dy2 * dy2);
  double len3 = sqrt(dx3 * dx3 + dy3 * dy3);
  double P = len1 + len2 + len3;
  double p = P / 2;
  double S = sqrt(p * (p - len1) * (p - len2) * (p - len3));
  printf("%.3lf\n%.3lf", P, S);
}