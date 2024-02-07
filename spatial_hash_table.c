#include <stdio.h>
#include <stdlib.h>
#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300
#define NO_OBJECTS 10
#define CELL_SIZE 100
#define WINDOW_ROWS (WINDOW_WIDTH / CELL_SIZE)
#define WINDOW_COLS (WINDOW_HEIGHT / CELL_SIZE)
#define SIZE (WINDOW_ROWS * WINDOW_COLS)
const int vicinity = 100;

double clamp(double a, double min, double max) {
  if (a <= min)
    return min;
  if (a >= max)
    return max;
  return a;
}

typedef struct {
  double x;
  double y;
  int id;
} GameObject;

GameObject objects[NO_OBJECTS];

void initialize_objects() {
  for (int i = 0; i < NO_OBJECTS; i++) {
    GameObject object;
    object.x = random() % WINDOW_WIDTH;
    object.y = random() % WINDOW_HEIGHT;
    object.id = i;

    objects[i] = object;
  }
}

typedef struct Entry {
  int key;
  int value;
  struct Entry *next;
} Entry;

typedef struct {
  Entry **cells;
  int size;
} SpatialHashTable;

// returns the key for the cell corresponding the
// object position
int hash(double b_x, double b_y) {
  int x = b_x / CELL_SIZE;
  int y = b_y / CELL_SIZE;
  return x + y * WINDOW_COLS;
}

SpatialHashTable *create_hash_table() {
  int size = SIZE;
  SpatialHashTable *h = malloc(sizeof(SpatialHashTable));
  if (h != NULL) {
    h->size = size;
    h->cells = calloc(size, sizeof(Entry *));
  } else {
    printf("Error! Failed to Allocate HashTable");
  }
  return h;
}

void add_to_hash_table(SpatialHashTable *h, int key, int value) {
  // Always adds to the head of the hash table
  Entry *cell = h->cells[key];
  Entry *new = malloc(sizeof(Entry));
  new->key = key;
  new->value = value;
  h->cells[key] = new;
  if (cell != NULL) {
    new->next = cell;
  }
}

void fill_hash_table(SpatialHashTable *h) {
  for (int i = 0; i < NO_OBJECTS; i++) {
    int key = hash(objects[i].x, objects[i].y);
    int value = objects[i].id;
    add_to_hash_table(h, key, value);
  }
}

void remove_from_cell(SpatialHashTable *h, int key, int value) {
  Entry *cell = h->cells[key];
  while (cell != NULL) {
    // if the value is in the head
    if (cell->value == value) {
      h->cells[key] = cell->next;
      free(cell);
      return;
    }
    // if the value is in the middle or the end
    if (cell->next != NULL && cell->next->value == value) {
      Entry *matching_node = cell->next;
      cell->next = matching_node->next;
      free(matching_node);
      return;
    }
    cell = cell->next;
  }
}

void update_hash_table(SpatialHashTable *h, int value, int prev_key,
                       int new_key) {
  // remove the value from previous cell
  remove_from_cell(h, prev_key, value);
  // add the value into the new key
  add_to_hash_table(h, new_key, value);
}

void free_hash_table(SpatialHashTable *h) {
  for (int key = 0; key < h->size; key++) {
    Entry *cell = h->cells[key];
    while (cell != NULL) {
      Entry *next = cell->next;
      free(cell);
      cell = next;
    }
  }
  free(h->cells);
  free(h);
}

void print_hash_table(SpatialHashTable *h) {
  for (int key = 0; key < h->size; key++) {
    Entry *cell = h->cells[key];
    printf("cell %d: ", key);
    while (cell != NULL) {
      printf("(%d, %d) -> ", cell->key, cell->value);
      cell = cell->next;
    }
    printf("NULL\n");
  }
}

int get_neighboring_objects(SpatialHashTable *h, GameObject object,
                            int *neighbors) {
  double b_x = object.x;
  double b_y = object.y;

  int neighbor_count = 0;

  int minx = (int)clamp(b_x - vicinity / 2.0, 0, WINDOW_WIDTH - 1) / CELL_SIZE;
  int miny = (int)clamp(b_y - vicinity / 2.0, 0, WINDOW_HEIGHT - 1) / CELL_SIZE;
  int maxx = (int)clamp(b_x + vicinity / 2.0, 0, WINDOW_WIDTH - 1) / CELL_SIZE;
  int maxy = (int)clamp(b_y + vicinity / 2.0, 0, WINDOW_HEIGHT - 1) / CELL_SIZE;

  for (int x = minx; x <= maxx; x++) {
    for (int y = miny; y <= maxy; y++) {
      int key = x + y * WINDOW_COLS;
      Entry *cell = h->cells[key];
      while (cell != NULL) {
        neighbors[neighbor_count++] = cell->value;
        cell = cell->next;
      }
    }
  }

  return neighbor_count;
}

int main(void) {
  SpatialHashTable *hash_table = create_hash_table();

  initialize_objects();
  fill_hash_table(hash_table);
  print_hash_table(hash_table);
  update_hash_table(hash_table, 0, 0, 1);
  putchar('\n');
  print_hash_table(hash_table);
  update_hash_table(hash_table, 0, 1, 0);
  putchar('\n');
  print_hash_table(hash_table);

  int neighbors[NO_OBJECTS];
  int neighbor_count = get_neighboring_objects(hash_table, objects[0], neighbors);
  printf("neighbors of %d are\n", 0);
  for (int i = 0; i < neighbor_count; i++) {
    printf("%d ", neighbors[i]);
  }

  free_hash_table(hash_table);

  return 0;
}
