#include <stdio.h>

int power(int base, int a) {
    if (a != 0)
        return (base * power(base, a - 1));
    else
        return 1;
}

int fibbonacci(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return (fibbonacci(n - 1) + fibbonacci(n - 2));
  }
}

int fact(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return n * fact(n - 1);
  }
}

int main() {
  int n, f;
  printf("Enter the number whose factorial you want to calculate?");
  scanf("%d", &n);
  f = fact(n);
  printf("factorial = %d", f);
}
