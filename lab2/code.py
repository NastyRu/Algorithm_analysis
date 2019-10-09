import random
import pylab
import time

def print_matrix(m):
    for i in range(len(m)):
        for j in range(len(m[0])):
            print(m[i][j], end = ' ')
        print()

def make_matrix(m, n):
    matrix = [[0] * n for i in range(m)]

    for i in range(0, m):
        for j in range(0, n):
            matrix[i][j] = random.randint(-10, 10)

    return matrix

def standart_multiplication_matrix(m1, m2):
    if len(m2) != len(m1[0]):
        print("Матрицы не могут быть перемножены")
        return -1
    else:
        m = len(m1)
        n = len(m1[0])
        q = len(m2[0])
        m3 = [[0] * q for i in range(m)]

        start_time = time.process_time()
        for i in range(0, m):
            for j in range(0, q):
                for k in range(0, n):
                    m3[i][j] = m3[i][j] + m1[i][k] * m2[k][j]
        t = time.process_time() - start_time

    print_matrix(m3)
    return t

def vinograd_multiplication_matrix(m1, m2):
    if len(m2) != len(m1[0]):
        print("Матрицы не могут быть перемножены")
        return -1
    else:
        m = len(m1)
        n = len(m1[0])
        q = len(m2[0])
        m3 = [[0] * q for i in range(m)]

        row = [0] * m
        for i in range(0, m):
            for j in range(0, n // 2, 1):
                row[i] = row[i] + m1[i][2 * j] * m1[i][2 * j + 1]

        col = [0] * q
        for j in range(0, q):
            for i in range(0, n // 2, 1):
                col[j] = col[j] + m2[2 * i][j] * m2[2 * i + 1][j]

        start_time = time.process_time()
        for i in range(0, m):
            for j in range(0, q):
                m3[i][j] = -row[i] - col[j]
                for k in range(0, n // 2, 1):
                    m3[i][j] = m3[i][j] + (m1[i][2 * k + 1] + m2[2 * k][j]) * (m1[i][2 * k] + m2[2 * k + 1][j])
                if 1 == n % 2:
                    m3[i][j] = m3[i][j] + m1[i][n - 1] * m2[n - 1][j]
        t = time.process_time() - start_time

    print_matrix(m3)
    return t

def vinograd_optimizate_multiplication_matrix(m1, m2):
    if len(m2) != len(m1[0]):
        print("Матрицы не могут быть перемножены")
        return -1
    else:
        m = len(m1)
        n = len(m1[0])
        q = len(m2[0])
        m3 = [[0] * q for i in range(m)]

        row = [0] * m
        for i in range(0, m):
            for j in range(1, n, 2):
                row[i] -= m1[i][j] * m1[i][j - 1]

        col = [0] * q
        for j in range(0, q):
            for i in range(1, n, 2):
                col[j] -= m2[i][j] * m2[i - 1][j]

        start_time = time.process_time()
        for i in range(0, m):
            for j in range(0, q):
                m3[i][j] = row[i] + col[j]
                for k in range(1, n, 2):
                    m3[i][j] += (m1[i][k - 1] + m2[k][j]) * (m1[i][k] + m2[k - 1][j])
                if 1 == n % 2:
                    m3[i][j] += m1[i][n - 1] * m2[n - 1][j]
        t = time.process_time() - start_time

    print_matrix(m3)
    return t

def main():
    print("Перемножение 2 матриц - 1, графики - 2? ")
    c = input()
    if ('1' == c):
        print("Введите размерность матрицы 1 ")
        while True:
            try:
                m = int(input())
                n = int(input())
                if (m > 0) and (n > 0):
                    break
                else:
                    raise ValueError()
            except ValueError:
                print("Некорректная размерность, повторите ввод")

        print("Введите размерность матрицы 2 ")
        while True:
            try:
                k = int(input())
                q = int(input())
                if (k > 0) and (q > 0):
                    break
                else:
                    raise ValueError()

            except ValueError:
                print("Некорректная размерность, повторите ввод")

        m1 = make_matrix(m, n)
        m2 = make_matrix(k, q)

        print_matrix(m1)
        print()
        print_matrix(m2)

        print()
        standart_multiplication_matrix(m1, m2)
        print()
        vinograd_multiplication_matrix(m1, m2)
        print()
        vinograd_optimizate_multiplication_matrix(m1, m2)

    elif ('2' == c):
        xlist = []
        ylist1 = []
        ylist2 = []
        ylist3 = []

        for i in range (100, 1100, 100):
            m1 = make_matrix(i, i)
            m2 = make_matrix(i, i)
            ylist1.append(standart_multiplication_matrix(m1, m2))
            ylist2.append(vinograd_multiplication_matrix(m1, m2))
            ylist3.append(vinograd_optimizate_multiplication_matrix(m1, m2))
            xlist.append(i)
            print(i)

        pylab.xlabel('Размер матрицы, символы')
        pylab.ylabel('Время, секунды')
        pylab.plot(xlist, ylist1, 'r--', label = 'Стандартный алгоритм')
        pylab.plot(xlist, ylist2, color = 'yellow', label = 'Алгоритм Винограда')
        pylab.plot(xlist, ylist3, 'b-.', label = 'Оптимизированный алгоритм Винограда')
        pylab.legend(loc='upper left')
        pylab.show()

        xlist = []
        ylist1 = []
        ylist2 = []
        ylist3 = []

        for i in range (101, 1101, 100):
            m1 = make_matrix(i, i)
            m2 = make_matrix(i, i)
            ylist1.append(standart_multiplication_matrix(m1, m2))
            ylist2.append(vinograd_multiplication_matrix(m1, m2))
            ylist3.append(vinograd_optimizate_multiplication_matrix(m1, m2))
            xlist.append(i)
            print(i)

        pylab.xlabel('Размер матрицы, символы')
        pylab.ylabel('Время, секунды')
        pylab.plot(xlist, ylist1, 'r--', label = 'Стандартный алгоритм')
        pylab.plot(xlist, ylist2, color = 'yellow', label = 'Алгоритм Винограда')
        pylab.plot(xlist, ylist3, 'b-.', label = 'Оптимизированный алгоритм Винограда')
        pylab.legend(loc='upper left')
        pylab.show()
    else:
        print("Некорректно!")

if __name__ == "__main__":
    main()
