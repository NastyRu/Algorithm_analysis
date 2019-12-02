#include "dot.h"
#include "ant_algorithm.h"
#include "enumeration.h"
#include <fstream>

int **allocate_matrix(const char *argv, int &n)
{
    ifstream f(argv);
    if (!f)
      return nullptr;

    f >> n;

    if (n <= 0)
      return nullptr;

    cout << n << endl;

    int **matrix = new int * [n];
    for (int i = 0; i < n; i++) {
      matrix[i] = new int [n];
    }

    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        f >> matrix[i][j];
        if (matrix[i][j] < 0)
          return nullptr;
        matrix[j][i] = matrix[i][j];
      }
    }

    f.close();
    return matrix;
}

int main(int argc, char *argv[])
{
  int n;
  char filename[256];

  if (argc > 1) {
    sprintf(filename, "file%s.txt", argv[1]);
  } else {
    sprintf(filename, "file.txt");
  }

  int **matrix = allocate_matrix(filename, n);
  if (nullptr == matrix) {
    cout << "Incorrect file";
    return 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << matrix[i][j] << ' ';
    }
    cout << endl;
  }

  char graphname[256];

  if (argc > 1) {
    sprintf(graphname, "graph%s", argv[1]);
  } else {
    sprintf(graphname, "graph");
  }

  dot(graphname, matrix, n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (0 == matrix[i][j])
        matrix[i][j] = 1000;
    }
  }

  int lenant = ant_algorithm(matrix, n, 0.8, 0.2, 640, 0.4);
  cout << "Минимальная длина пути, муравьиный алгоритм: " << lenant << endl;

  int lenenum = enum_algorithm(matrix, n);
  cout << "Минимальная длина пути, полный перебор: " << lenenum << endl;
}
