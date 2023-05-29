#include <stdio.h>

int main() {
  int i, first, last, mid, n, search, array[100];

  // Take the input array.
  printf("Enter the size of array: ");
  scanf("%d", &n);
  puts("Enter the elements:");
  for (i = 0; i < n; i++) {
    printf("Enter element %d: ", i + 1);
    scanf("%d", (array + i));
  }
  printf("Enter the value to search: ");
  scanf("%d", &search);

  // implement binary search
  first = 0;
  last = n - 1;
  while (first <= last) {
    mid = (first + last) / 2;
    if (array[mid] < search)
      first = mid + 1;
    else if (array[mid] == search) {
      printf("%d was found at index %d.\n", search, mid);
      break;
    } else last = mid - 1;

  }
  if (first > last) {
    puts("Not found!");
  }
  return 0;
}
