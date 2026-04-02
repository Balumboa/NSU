#include <math.h>
#include <stdio.h>

int main() {
  double a, b, c;
  scanf("%lf %lf %lf", &a, &b, &c);
  if (a == 0 && b == 0) { // c = 0
    if (c == 0) {
      printf("MANY");
    } else {
      printf("ERROR");
    }
  } else if (a == 0) { // bx + c = 0
    double x = (-c) / b;
    printf("1\n%.5lf", x);
  } else {
    double D = b * b - 4 * a * c;
    if (D < 0) { // ax^2 + bx + c = 0
      printf("NO");
    } else if (D == 0) {
      printf("1\n%.5lf", (-b) / (2 * a));
    } else {
      double x1 = (-b - sqrt(D)) / (2 * a);
      double x2 = (-b + sqrt(D)) / (2 * a);
      printf("2\n");
      if (x1 < x2) {
        printf("%.5lf %.5lf", x1, x2);
      } else {
        printf("%.5lf %.5lf", x2, x1);
      }
    }
  }
}