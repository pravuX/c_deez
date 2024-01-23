#include <stdio.h>
#include <stdlib.h>
// An attempt at implementing slices like in Go

typedef struct {
  int *arr;
  size_t len; // used
  size_t cap;
} Slice;

size_t len(Slice *d) { return d->len; }

size_t cap(Slice *d) { return d->cap; }

Slice *make_slice(size_t cap) {
  Slice *d = malloc(sizeof(Slice));
  d->arr = malloc(cap * sizeof(int));
  // check if malloc failed
  if (d == NULL || d->arr == NULL) {
    perror("Error: Failed to allocate memory.");
    exit(EXIT_FAILURE);
  }
  d->len = 0;
  d->cap = cap;
  // zero initliaze the array
  for (size_t i = 0; i < cap; i++) {
    d->arr[i] = 0;
  }
  return d;
}

void append(Slice *d, int el) {
  if (len(d) == cap(d)) {
    d->cap = (cap(d) * 3) / 2 + 8;
    d->arr = realloc(d->arr, cap(d) * sizeof(int));
    // check if realloc failed
    if (d->arr == NULL) {
      perror("Error: Failed to reallocate memory.");
      exit(EXIT_FAILURE);
    }
  }
  d->arr[d->len++] = el;
}

void append_slice(Slice *to, Slice *from) {
  for (int i = 0; i < len(from); i++) {
    append(to, from->arr[i]);
  }
}

void append_slice_in_range(Slice *to, Slice *from, size_t low, size_t high) {
  for (int i = low; i < high; i++) {
    append(to, from->arr[i]);
  }
}

Slice *reslice(Slice *d, size_t low, size_t high) {
  // [low, high)
  size_t len = high - low;
  Slice *slice = make_slice(len);
  append_slice_in_range(slice, d, low, high);
  return slice;
}

void free_slice(Slice *d) {
  if (d->arr != NULL) {
    free(d->arr);
  }
  if (d != NULL) {
    free(d);
  }
}

void show_slice(Slice *d) {
  for (size_t i = 0; i < len(d); i++) {
    if (i == 0)
      printf("{ ");
    printf("%d ", d->arr[i]);
    if (i == len(d) - 1)
      putchar('}');
  }
  printf(" len = %zu, cap = %zu\n", len(d), cap(d));
}

void remove_from_slice(Slice *d, int index) {
  Slice *tmp = reslice(d, 0, index);
  append_slice_in_range(tmp, d, index + 1, len(d));

  d->len = len(tmp);
  d->cap = cap(tmp);

  free(d->arr);

  d->arr = tmp->arr;

  free(tmp);
}

int main(void) {
  Slice *A = make_slice(5);
  for (int i = 0; i < 15; i++) {
    append(A, i);
  }

  Slice *Rs_1 = reslice(A, 5, 10);
  for (int i = 0; i < 5; i++) {
    append(Rs_1, i);
  }

  remove_from_slice(Rs_1, 4);

  Slice *Rs_2 = reslice(Rs_1, 1, 3);

  Slice *Rs_3 = reslice(Rs_1, 3, 9);
  append_slice(Rs_3, Rs_2);

  printf("A   : ");
  show_slice(A);
  printf("Rs_1: ");
  show_slice(Rs_1);
  printf("Rs_2: ");
  show_slice(Rs_2);
  printf("Rs_3: ");
  show_slice(Rs_3);
  free_slice(A);
  free_slice(Rs_1);
  free_slice(Rs_2);
  free_slice(Rs_3);
  return 0;
}
