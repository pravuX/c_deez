#include <stdio.h>

int bin_addition(int a, int b) {
  int c;
  while (b != 0) {
    c = (a & b) << 1;
    a = a ^ b;
    b = c;
  }
  return a;
}

int main(void) {
  int a, b, c;
  puts("Enter two numbers");
  scanf("%d%d", &a, &b);
  // a - b = a + b'+ 1
  b = bin_addition(~b, 1);
  c = bin_addition(a, b);
  printf("difference is: %d", c);
  return 0;
}
