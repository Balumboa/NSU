#include <math.h>
#include <stdio.h>

int main() {
  int k;
  scanf("%d", &k);
  int sqrtD = sqrt(8 * k - 7);
  if (8 * k - 7 == sqrtD * sqrtD && sqrtD % 2 == 1) {
    printf("1");
  } else {
    printf("0");
  }
}