#include <stdio.h>

int main() {
  int n = 8;
  int arr[8] = {25, 57, 48, 37, 12, 92, 86, 33};


  // Bubble Sort
  for (int i = 0; i < n - 1; i++) {
    int swapped = 0;
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j+1]) {
        int tmp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = tmp;
        swapped = 1;
      }
    }
    if (!swapped) {
      break;
    }
  }

  // Selection Sort
/*
  for (int i = 0 ; i < n - 1; i++) {
    int min_index = i;
    for (int j = i+1; j < n; j++) {
      // looking for new mininum
      if (arr[j] < arr[min_index]) min_index = j;
    }
    // swapping garne aba
    if (min_index != i) { // naya mininmum bhetayo vane
      int tmp = arr[min_index];
      arr[min_index] = arr[i];
      arr[i] = tmp;
    }
  } */

  // Insertion Sort 1
/*
  for (int i = 1; i <= n - 1; i++) {
    int j = i;
    // elements to the left are of i are considered sorted
    while (j > 0 && arr[j] < arr[j-1]) {
      int tmp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = tmp;
      j = j - 1;
    }
  }
 */

  // Insertion Sort 2

  /* for (int i = 1; i < n; i++) {
    int j = i - 1;
    int tmp = arr[i];
    // find the position for tmp in sorted subarray
    while (j >= 0 && arr[j] > tmp) {
      // shift elements of sorted arry to the right
      arr[j+1] = arr[j];
      j = j - 1;
    }
    // insert ith element into correct position in sorted array
    arr[j + 1] = tmp;
  } */

  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  return 0;
}
