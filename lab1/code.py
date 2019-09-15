import random
import string
import pylab
import time

def min(firstnum, *numbers):
    minimum = firstnum
    for num in numbers:
        if (num < minimum):
            minimum = num
    return minimum

def levinstein(s1, s2):
    n_matrix = len(s1) + 1
    m_matrix = len(s2) + 1
    matrix = [[0] * m_matrix for i in range(n_matrix)]

    for i in range(n_matrix):
        matrix[i][0] = i
    for j in range(m_matrix):
        matrix[0][j] = j

    for i in range(1, n_matrix):
        for j in range(1, m_matrix):
            matrix[i][j] = min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1,
            matrix[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]))

    #for i in range(n_matrix):
    #    for j in range(m_matrix):
    #        print(matrix[i][j], end = ' ')
    #    print()
    return matrix[n_matrix - 1][m_matrix - 1]

def damerau_levinstein_matrix(s1, s2):
    n_matrix = len(s1) + 1
    m_matrix = len(s2) + 1
    matrix = [[0] * m_matrix for i in range(n_matrix)]

    for i in range(n_matrix):
        matrix[i][0] = i
    for j in range(m_matrix):
        matrix[0][j] = j

    for i in range(1, n_matrix):
        for j in range(1, m_matrix):
            if (i > 1 and s1[i - 1] == s2[j - 2] and s1[i - 2] == s2[j - 1]):
                matrix[i][j] = min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1,
                matrix[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]), matrix[i - 2][j - 2] + 1)
            else:
                matrix[i][j] = min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1,
                matrix[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]))

    #for i in range(n_matrix):
    #    for j in range(m_matrix):
    #        print(matrix[i][j], end = ' ')
    #    print()
    return matrix[n_matrix - 1][m_matrix - 1]

def damerau_levinstein_recursive(s1, s2):
    n = len(s1)
    m = len(s2)
    if (0 == n):
        return m
    if (0 == m):
        return n

    delete = damerau_levinstein_recursive(s1[:-1], s2) + 1
    insert = damerau_levinstein_recursive(s1, s2[:-1]) + 1
    replace = damerau_levinstein_recursive(s1[:-1], s2[:-1]) + (s1[-1] != s2[-1])
    transposition = 1000
    if (n > 1 and m > 1 and s1[-1] == s2[-2] and s1[-2] == s2[-1]):
        transposition = damerau_levinstein_recursive(s1[:-2], s2[:-2]) + 1

    return min(delete, insert, replace, transposition)

def main():
    print("Тесты - 1, графики - 2, ввод строки - 3? ")
    c = input()
    if ('1' == c):
        list1 = ["dessert", "cook", "mother", "woman", "program", "house", "probelm", "head", "bring",
        "happy", "minute", "person", "week", "member", "death", "education", "room", "car", "air", "country"]

        list2 = ["desert", "cooker", "money", "water", "friend", "girl", "problem", "ehda", "brought",
        "happy", "moment", "eye", "weeks", "morning", "health", "question", "moor", "city", "area", "office"]

        for s1, s2 in zip(list1, list2):
            print(s1, " & " , s2, " & " , levinstein(s1, s2), " & " , damerau_levinstein_matrix(s1, s2), " & " , damerau_levinstein_recursive(s1, s2))
    elif ('2' == c):
        xlist = []
        ylist1 = []
        ylist2 = []
        ylist3 = []

        for i in range (1, 5, 1):
            s1 = ''.join(random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(i))
            s2 = ''.join(random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(i))
            xlist.append(i)

            start_time = time.time()
            levinstein(s1, s2)
            ylist1.append(time.time() - start_time)

            start_time = time.time()
            damerau_levinstein_matrix(s1, s2)
            ylist2.append(time.time() - start_time)

            start_time = time.time()
            damerau_levinstein_recursive(s1, s2)
            ylist3.append(time.time() - start_time)

            print(i)

        pylab.xlabel('Длина строки, символов')
        pylab.ylabel('Время, секунд')
        pylab.plot(xlist, ylist1, color = 'red', label = 'Расстояние Дамерау матричным способом')
        pylab.plot(xlist, ylist2, color = 'yellow', label = 'Расстояние Дамерау-Левенштейна матричным способом')
        pylab.plot(xlist, ylist3, color = 'blue', label = 'Расстояние Дамерау-Левенштейна рекурсивным способом')
        pylab.legend(loc='upper left')
        pylab.show()

    elif ('3' == c):
        print("Введите строку 1")
        s1 = input()
        print("Введите строку 2")
        s2 = input()
        print()

        print("Левинштейн ", levinstein(s1, s2))
        print()
        print("Дамерау-Левинштейн матричным способом ", damerau_levinstein_matrix(s1, s2))
        print()
        print("Дамерау-Левинштейн рекурсивным способом ", damerau_levinstein_recursive(s1, s2))
    else:
        print("Некорректно!")

if __name__ == "__main__":
    main()
