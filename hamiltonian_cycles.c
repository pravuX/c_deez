#include <stdio.h>
#define V 5

// i = 0  1  2  3  4
//     {0, 0, 0, 0, 0}
// The hamiltonian cycle is formed by fixing the start
// vertex at 0 then looking for possible subsequent vertices
int x[V] = {0};
int G[V][V] = {{0, 1, 1, 0, 1}, // 0
               {1, 0, 1, 1, 1}, // 1
               {1, 1, 0, 1, 0}, // 2
               {0, 1, 1, 0, 1}, // 3
               {1, 1, 0, 1, 0}};// 4
            //  0  1  2  3  4

int mod(int a, int b) {
  int res = a % b;
  if (res < 0) {
    return res + b;
  }
  return res;
}

void next_vertex(int k) {
  do {
    x[k] = mod(x[k] + 1, V);
    if (x[k] == 0) {
      return;
    }
    if (G[x[k - 1]][x[k]] == 1) {
      int j;
      for (j = 0; j < k; j++) {
        if (x[j] == x[k]) {
          break;
        }
      }
      if (j == k) {
        if (k < V - 1 || (k == V - 1 && G[x[V - 1]][x[0]] == 1)) {
          return;
        }
      }
    }
  } while (1);
}

void hamiltonian(int k) {
  do {
    next_vertex(k);
    if (x[k] == 0) {
      return;
    }
    if (k == V - 1) {
      for (int i = 0; i < V; i++) {
        printf("%d --> ", x[i]);
      }
      printf("%d\n", x[0]); // Complete the cycle
    } else {
      hamiltonian(k + 1);
    }
  } while (1);
}

int main(void) {
  hamiltonian(1);
  return 0;
}
