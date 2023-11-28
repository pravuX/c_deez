#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
Implemenation from: https://theleo.zone/posts/hashmap-in-c/
*/

// static sized Entry and HashTable
typedef struct Entry {
  char *key; // key associated with the value
  void *val; // void pointer to the value
  struct Entry *next; // pointer to the next Entry for collision
} Entry;

typedef struct HashTable {
  Entry **buckets; // array of pointer to Entries
  int nBuckets; // the number of buckets in the Hash Table
} HashTable;

// string hash function called djb2 by Daniel Bernstein
uint32_t hash(char *s) {
  uint32_t h = 5381;
  char c;
  while ((c = *s++)) {
    h = 33 * h + c;
  }
  return h;
}

// get bucket index for a given key
uint32_t get_bucket(HashTable *h, char *key) {
  return hash(key) % h->nBuckets;
}

// HashTable Constructor
HashTable *HashTable_new() {
  int nBuckets = 4;
  HashTable *h = malloc(sizeof(HashTable));
  h->nBuckets = nBuckets;
  h->buckets = calloc(nBuckets, sizeof(Entry*));
  return h;
}

void HashTable_set(HashTable *h, char *key, void *val) {
  uint32_t bucket = get_bucket(h, key);
  Entry *v = h->buckets[bucket];
  while (v != NULL) {
    if (strcmp(v->key, key) == 0) {
      v->val = val;
      return;
    }
    v = v->next;
  }
  // no entry found so create a new one
  // make it head of the linked-list
  Entry *new = malloc(sizeof(Entry));
  new->key = strdup(key);
  new->val = val;
  new->next = h->buckets[bucket];
  h->buckets[bucket] = new;
}

void* HashTable_get(HashTable *h, char *key) {
  uint32_t bucket = get_bucket(h, key);
  Entry *v = h->buckets[bucket];
  while (v != NULL) {
    if (strcmp(v->key, key) == 0) return v->val;
    v = v->next;
  }
  return NULL;
}

void HashTable_del(HashTable *h, char *key) {
  uint32_t bucket = get_bucket(h, key);
  Entry *prev = NULL;
  Entry *v = h->buckets[bucket];

  while (v != NULL) {
    if (strcmp(v->key, key) == 0) {
      // found entry to delete
      if (prev == NULL) {
        // if head then set head to next value
        h->buckets[bucket] = v->next;
      } else {
        // any other node in the linked-list
        prev->next = v->next;
      }
      // free the node
      free(v->key);
      free(v);
    }
    prev = v;
    v = v->next;
  }
}

void HashTable_free(HashTable *h) {
  // free each entry and the key in the hash table
  for (int b = 0; b < h->nBuckets; b++) {
    Entry *v = h->buckets[b];
    while (v != NULL) {
      Entry *next = v->next;
      free(v->key);
      free(v);
      v = next;
    }
  }
  // free the buckets array and the hash table
  free(h->buckets);
  free(h);
}

// display the complete HashTable
void HashTable_print(HashTable *h) {
  for (int b = 0; b < h->nBuckets; b++) {
    Entry *v = h->buckets[b];
    printf("bucket %d: ", b);
    while (v != NULL) {
      printf("(%s, %d) -> ", v->key, *(int*)v->val);
      v = v->next;
    }
    printf("NULL\n");
    }
}

int main(void) {
  HashTable *h = HashTable_new();
  int a[7] = {69, 420, 256, 45, 23, 88, 79};
  char *c[7] = {"item a", "item b", "item c", "item d", "item e", "item f", "item g"};
  for (int i = 0; i < 7; i++) {
    HashTable_set(h, c[i], &a[i]);
  }
  HashTable_print(h);
  HashTable_free(h);
  return 0;
}
