#include <stdio.h>
#include <stdlib.h>
// Circular Buffer or Ring Buffer
// https://en.wikipedia.org/wiki/Circular_buffer

typedef struct {
  int *buffer;   // buffer array
  int start;     // buffer start position
  int end;       // buffer end position
  int size;      // fixed size of buffer
  int used_size; // currently used size of buffer
} CircularBuffer;

CircularBuffer create_circular_buffer(int size) {
  CircularBuffer c;
  c.buffer = (int*) malloc(size * sizeof(int));
  // buffer is empty at initialization
  c.start = 0;
  c.end = 0;
  c.used_size = 0;
  c.size = size;
  return c;
}

int write_into_buffer(CircularBuffer *c, int item) {
  if (c->used_size == c->size) {
    puts("Buffer is full!");
    return 0; // write operation was unsuccesful
  }
  // write to end
  c->buffer[c->end] = item;
  // increment to next buffer position
  c->end = (c->end + 1) % c->size;
  // increment the used_size counter
  c->used_size++;
  return 1; // write operation was succesful
}

int read_from_buffer(CircularBuffer *c, int *value) {
  if (c->used_size == 0) {
    puts("Buffer is empty!");
    return 0; // read operation was unsuccesful
  }
  // read from start
  *value = c->buffer[c->start];
  // increment to next buffer position
  c->start = (c->start + 1) % c->size;
  // decrement the used_size counter
  c->used_size--;
  return 1; // read operation was succesful
}

void free_circular_buffer(CircularBuffer *c) {
  free(c->buffer);
}

int main() {
  CircularBuffer ring_buffer = create_circular_buffer(10);

  // simple test
  int value = 60;
  while (write_into_buffer(&ring_buffer, value++));
  while (read_from_buffer(&ring_buffer, &value)) {
    printf("read: %d\n", value);
  }
  free_circular_buffer(&ring_buffer);
  return 0;
}
