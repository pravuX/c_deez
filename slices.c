#include <stdio.h>
#include <stdlib.h>
// An attempt at implementing slices like in Go

typedef struct {
  int *arr;
  size_t len; // used
  size_t cap;
} Slice;

Slice *make_slice(size_t len) {
  Slice *d = malloc(sizeof(Slice));
  d->arr = malloc(len * sizeof(int));
  // check if malloc failed
  if (d == NULL || d->arr == NULL) {
    perror("Failed to allocate memory.");
    exit(EXIT_FAILURE);
  }
  d->len = 0;
  d->cap = len;
  // zero initliaze the array
  for (size_t i = 0; i < len; i++) {
    d->arr[i] = 0;
  }
  return d;
}

void append(Slice *d, int el) {
  if (d->len == d->cap) {
    d->cap = (d->cap * 3) / 2 + 8;
    d->arr = realloc(d->arr, d->cap * sizeof(int));
    // check if realloc failed
    if (d->arr == NULL) {
      perror("Failed to reallocate memory.");
      exit(EXIT_FAILURE);
    }
  }
  d->arr[d->len++] = el;
}

void copy(Slice *to, Slice *from, size_t low, size_t high) {
  for (int i = low; i < high; i++) {
    append(to, from->arr[i]);
  }
}

Slice *reslice(Slice *d, size_t low, size_t high) {
  // [low, high)
  size_t len = high - low;
  Slice *slice = make_slice(len);
  copy(slice, d, low, high);
  return slice;

}

void free_slice(Slice *d) {
  free(d->arr);
  free(d);
}

void show_slice(Slice *d) {
  for (size_t i = 0; i < d->len; i++) {
    if (i == 0)
      printf("{ ");
    printf("%d ", d->arr[i]);
    if (i == d->len - 1)
      putchar('}');
  }
  printf("len = %zu, cap = %zu\n", d->len, d->cap);
}

int main(void) {
  Slice *A = make_slice(5);
  for (int i = 0; i < 10; i++) {
    append(A, i);
  }
  Slice *Rs_1 = reslice(A, 5, A->len);
  Slice *Rs_2 = reslice(Rs_1, 1, 3);
  for (int i = 0; i < 5; i++) {
    append(Rs_1, i);
  }
  show_slice(A);
  show_slice(Rs_1);
  show_slice(Rs_2);
  free_slice(A);
  free_slice(Rs_1);
  free_slice(Rs_2);
  return 0;
}
