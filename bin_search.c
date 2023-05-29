#include <stdio.h>
/*
 * Binary Search Implementation in C.
 * Time Complexity: O(logn)
 */

int binary_search(int *arr, int search, int size) {
  int first, mid, last;
  first = 0;
  last = size - 1;
  while (first <= last) {
    // to avoid integer overflow for large integers.
    mid = first + (last - first) / 2;
    if (search == arr[mid])
      return mid;
    else if (search > arr[mid])
      first = mid + 1;
    else last = mid - 1;
  }
  return -1;
}

int main() {
  int i, size, search, array[100], found;
  size = 5;
  search = 6;

  printf("{ ");
  for (i = 0; i < size; i++) {
    if (i > 0) printf(", ");
    printf("%d",array[i] = i + 1);
  }
  printf(" }\n");

  found = binary_search(array, search, size);

  if (found == -1)
    printf("%d not found in the array!", search);
  else printf("%d found in index %d.", search, found);

  return 0;
}
