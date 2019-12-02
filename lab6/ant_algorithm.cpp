#include "ant_algorithm.h"

#define alpha 0.5
#define beta 0.5

int ant_algorithm(int **matrix, int n) {
  srand(time(NULL));
  double **pheromone = new double * [n];
  for (int i = 0; i < n; i++) {
    pheromone[i] = new double [n];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      pheromone[j][i] = 0.1;
    }
  }
  int minlen = 1000;
  int minway[n];

  for (int time = 0; time < 10; time++) {
    int *ants = new int [n];
    for (int i = 0; i < n; i++) {
      ants[i] = i + 1;
    }

    double **delta = new double * [n];
    for (int i = 0; i < n; i++) {
      delta[i] = new double [n];
    }

    for (int k = 0; k < n; k++) {
      int count = 0;
      int cities[n];
      for (int i = 0; i < n; i++) {
        cities[i] = 0;
      }
      cities[k] = 1;
      int way[n];
      for (int i = 0; i < n; i++) {
        way[i] = 0;
      }
      way[0] = k;
      int len = 0;

      while (count + 1 < n) {
        double p[n];

        for (int j = 0; j < n; j++) {
          if (0 == cities[j]) {
            p[j] = pow(pheromone[way[count]][j], alpha) * pow(matrix[way[count]][j], beta);

            double all = 0;
            for (int q = 0; q < count; q++) {
              all += pow(pheromone[way[q]][j], alpha) * pow(matrix[way[q]][j], beta);
            }

            p[j] /= all;
          } else {
            p[j] = 0;
          }
        }
        int arr[n - count - 1];
        int cyc = 0;
        for (int i = 0; i < n; i++) {
          if (0 == cities[i]) {
            arr[cyc] = i;
            cyc++;
          }
        }
        int rdm = rand() % (n - count - 1);
        len += matrix[way[count]][arr[rdm]];
        count++;
        way[count] = arr[rdm];
        cities[arr[rdm]] = 1;
      }
      len += matrix[way[0]][way[n - 1]];

      for (int i = 0; i < n - 1 ; i++) {
        delta[way[i]][way[i + 1]] += minlen / len;
        delta[way[i + 1]][way[i]] += minlen / len;
      }
      if (len < minlen) {
        minlen = len;
        for (int i = 0; i < n; i++)
          minway[i] = way[i];
      }
    }

    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        pheromone[i][j] *= (1 - 0.2);
        pheromone[i][j] += delta[i][j];
      }
    }
  }

  cout << "Минимальный путь муравьиным алгоритмом: \n";
  for (int i = 0; i < n; i++) {
    cout << minway[i] + 1 << ' ';
  }
  cout << endl;

  return minlen;
}
