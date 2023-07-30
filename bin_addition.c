#include <stdio.h>

int main(void) {
  int a, b, c;
  puts("Enter two numbers");
  scanf("%d%d", &a, &b);
  while (b != 0) {
    c = (a & b) << 1; // carry
    a = a ^ b;        // sum
    b = c;
  }
  printf("sum is: %d", a);
  return 0;
}
