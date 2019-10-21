#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
#include <math.h>
using namespace std;
using namespace std::chrono;

std::ostream& operator<< (std::ostream &out, vector< vector<int> > matrix);
std::ostream& operator<< (std::ostream &out, vector< vector<int> > matrix)
{
    for(int i = 0; i < matrix.size(); i++) {
      for(int j = 0; j < matrix[i].size(); j++) {
          cout << matrix[i][j] << ' ';
      }
      cout << endl;
    }

    return out;
}

vector< vector<int> > rand_vector(int m, int n, int begin, int end)
{
  vector< vector<int> > matrix(m, vector<int> (n, 0));

  for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) {
        matrix[i][j] = begin + rand() % abs(end - begin + 1);
    }
  }
  return matrix;
}

void cycle(vector< vector<int> > m1, vector< vector<int> > m2, vector< vector<int> > &m3, vector<int> row, vector<int> col, int m_begin, int m_end) {
  int n = m1[0].size();
  int q = m2[0].size();
  for (int i = m_begin; i < m_end; i++) {
    for (int j = 0; j < q; j++){
      m3[i][j] = row[i] + col[j];
      for (int k = 1; k < n; k += 2) {
        m3[i][j] += (m1[i][k - 1] + m2[k][j]) * (m1[i][k] + m2[k - 1][j]);
      }
      if (1 == n % 2)
          m3[i][j] += m1[i][n - 1] * m2[n - 1][j];
    }
  }
}

int vinograd_optimizate_multiplication_matrix(vector< vector<int> > m1, vector< vector<int> > m2, int count) {
  if (m2.size() != m1[0].size()) {
    cout << "Матрицы не могут быть перемножены";
    return -1;
  } else {
    int m = m1.size();
    int n = m1[0].size();
    int q = m2[0].size();
    vector< vector<int> > m3(m, vector<int> (q, 0));

    vector<int> row(m, 0);
    for (int i = 0; i < m; i++) {
      for (int j = 1; j < n; j += 2){
        row[i] -= m1[i][j] * m1[i][j - 1];
      }
    }

    vector<int> col(q, 0);
    for (int j = 0; j < q; j++) {
      for (int i = 1; i < n; i += 2){
        col[j] -= m2[i][j] * m2[i - 1][j];
      }
    }

    high_resolution_clock::time_point t1, t2;
    int d = m / count;
    vector<thread> func_thread;
    for (int i = 0; i < count; i++) {
      if (i == count - 1) {
        func_thread.push_back(thread(cycle, m1, m2, ref(m3), row, col, i * d, (1 + i) * d + m % count));
      } else {
        func_thread.push_back(thread(cycle, m1, m2, ref(m3), row, col, i * d, (1 + i) * d));
      }
    }

    t1 = high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
      func_thread[i].join();
    }
    t2 = high_resolution_clock::now();
    //cout << m3;
    return duration_cast<microseconds>(t2 - t1).count();
  }

  return 0;
}

int main(int argc, char* argv[]) {
  int buf;
  cout << "1 - графики, 2 - подсчет произведения?" << endl;
  cin >> buf;
  if (2 == buf) {
    int m, n, k, q;
    cout << "Введите размерность матрицы 1 ";
    cin >> m >> n;
    cout << "Введите размерность матрицы 2 ";
    cin >> k >> q;

    vector< vector<int> > matrix1 = rand_vector(m, n, -10, 10);
    cout << matrix1;

    vector< vector<int> > matrix2 = rand_vector(k, q, -10, 10);
    cout << matrix2;

    vinograd_optimizate_multiplication_matrix(matrix1, matrix2, 1);
  } else if (1 == buf) {
    for (int m = 100; m <= 1500; m += 100) {
      vector<int> time(15, 0);
      for (int k = 0; k < 5; k++) {
        vector< vector<int> > matrix1 = rand_vector(m, m, -10, 10);
        vector< vector<int> > matrix2 = rand_vector(m, m, -10, 10);

        for (int i = 0; i <= 5; i++) {
          time[i] += vinograd_optimizate_multiplication_matrix(matrix1, matrix2, pow(2, i));
        }
      }
      for (int k = 0; k < 6; k++) {
        cout << time[k] / 5 << ' ';
      }
      cout << endl;
      cout << m << endl;
    }
  } else {
    cout << "Некорректно!";
  }
}
