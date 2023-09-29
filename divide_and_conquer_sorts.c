#include <stdio.h>

void merge(int *a, int *b, int *c, int m, int n) {
  int i, j, k;
  i = j = k = 0;
  while (i < m && j < n) {
    if (a[i] < b[j])
      c[k++] = a[i++];
    else
      c[k++] = b[j++];
  }
  for (; i < m; i++)
    c[k++] = a[i];
  for (; j < n; j++)
    c[k++] = b[j];
}

void merge_subarrays(int *a, int l, int m, int h) {
  int i = l;
  int j = m + 1;
  int k = 0;
  int b[6];
  while(i <= m && j <= h) {
    if (a[i] < a[j])
      b[k++] = a[i++];
    else
      b[k++] = a[j++];
  }
  for (; i <= m; i++)
    b[k++] = a[i];
  for (; j <= h; j++)
    b[k++] = a[j];

  for (int i = l; i <= h; i++) {
    a[i] = b[i];
  }
}

int partition(int *a, int l, int h) {
  int pivot = a[l];
  int i = l;
  int j = h;
  while (i < j) {
    do {
      i++;
    } while (a[i] <= pivot); // i.e. untill i such that a[i] > pivot is not found

    do {
      j--;
    } while (a[j] > pivot); // i.e. untill j such that a[j] < pivot is not found
    if (i < j) {
      // swap(a[i], a[j])
      int tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
    }
  }
  // j is the pivot at this point
  // swap (a[j], a[l] (i.e. pivot))
  int tmp = a[l];
  a[l] = a[j];
  a[j] = tmp;

  return j;
}

int main(void) {
  /* int a[3] = {1, 3, 5};
  int b[3] = {2, 4, 6};
  int c[6] = {0};
  merge(a, b, c, 3, 3); */
  int a[6] = {1, 3, 5, 2, 4, 6};
  return 0;
}
