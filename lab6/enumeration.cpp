#include "enumeration.h"

int mindistance = 10000;

void fill_array(int *arr, int n) {
  for (int i = 0; i < n; i++) {
      arr[i] = i;
  }
}

void distance(int **matrix, int *arr, int n) {
  int d = 0;
  for (int i = 0; i < n - 1; i++) {
    d += matrix[arr[i]][arr[i + 1]];
  }
  d += matrix[arr[n - 1]][arr[0]];

  if (d < mindistance)
    mindistance = d;
}

void swap(int *a, int *b) {
  int buf = *a;
  *a = *b;
  *b = buf;
}

void permute(int **matrix, int *arr, int first_elem, int last_elem, int n) {
  if (first_elem == last_elem) {
    distance(matrix, arr, n);
    return;
  }
  for (int i = 0; i <= last_elem; i++) {
    swap((arr + first_elem), (arr + i));
    permute(matrix, arr, first_elem + 1, last_elem, n);
    swap((arr + first_elem), (arr + i));
  }
}

int enum_algorithm(int **matrix, int n) {
  int *arr = new int[n];
  fill_array(arr, n);
  permute(matrix, arr, 0, n - 1, n);

  return mindistance;
}
