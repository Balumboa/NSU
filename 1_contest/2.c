#include <stdio.h>

int main() {
  int N;
  int M, P, K, L;
  scanf("%d", &N);
  scanf("%d %d %d %d", &M, &P, &K, &L);

  int x = (M - 1) / ((P - 1) * L + (K - 1)); // количество квартир на этаже
  int answerp = (N - 1) / (L * x) + 1;
  int answerk = (N - 1 - (answerp - 1) * L * x) / x + 1;
  printf("%d %d", answerp, answerk);
}