import random
import pylab
import time

def get_digit(number, n):
    return (number // n) % 10

def make_array(n):
    array = [0] * n
    for i in range(0, n):
        array[i] = random.randint(-999, 10000)
    return array

def make_array_sort(n):
    array = [0] * n
    for i in range(0, n):
        array[i] = i
    return array

def make_array_unsort(n):
    array = [0] * n
    for i in range(0, n):
        array[i] = n-i
    return array

def bitwise_sorting(array):
    if len(array) == 0:
        print(arr)
        return []
    n = len(str(abs(max(array))))
    digit = 10
    neg = sum(x < 0 for x in array)

    n = pow(digit, n)
    i = 1

    start_time = time.process_time()
    while (i < n):
        sort = [[] for k in range(digit)]

        for x in array:
            sort[get_digit(x, i)].append(x)

        count = len(array)
        array = [0] * count
        u = 0
        w = 0
        for k in range(digit):
            for j in range(len(sort[k])):
                if (sort[k][j] < 0):
                    array[w] = sort[k][j]
                    w += 1
                else:
                    array[u + neg] = sort[k][j]
                    u += 1
        i *= 10
    t = time.process_time() - start_time

    print(array)
    return t

def quick_sorting(array):
    if len(array) <= 1:
        return array
    else:
        q = random.choice(array)
        left = []
        middle = []
        right = []
        for elem in array:
            if elem < q:
                left.append(elem)
            elif elem > q:
                right.append(elem)
            else:
                middle.append(elem)
        return quick_sorting(left) + middle + quick_sorting(right)

def insertion_sorting(array):
	for i in range(1, len(array)):
		j = i - 1
		key = array[i]
		while array[j] > key and j >= 0:
			array[j + 1] = array[j]
			j -= 1
		array[j + 1] = key
	return array

def main():
    array = []
    print("1 - Вводимый массив, 2 - Графики")
    c = input()
    if ('1' == c):
        while True:
            try:
                a = int(input())
                array.append(a)
            except ValueError:
                print("Поразрядная сортировка: ")
                bitwise_sorting(array)
                print("Быстрая сортировка: ")
                print(quick_sorting(array))
                print("Сортировка вставками: ")
                print(insertion_sorting(array))
                break

    elif ('2' == c):
        xlist = []
        ylist1 = []
        ylist2 = []
        ylist3 = []

        for i in range (1, 1000, 100):
            t1 = 0
            t2 = 0
            t3 = 0
            for j in range(50):
                array = make_array(i)
                t1 += bitwise_sorting(array)
                start_time = time.process_time()
                quick_sorting(array)
                t = time.process_time() - start_time
                t2 += t
                start_time = time.process_time()
                insertion_sorting(array)
                t = time.process_time() - start_time
                t3 += t
            ylist1.append(t1 / 50)
            ylist2.append(t2 / 50)
            ylist3.append(t3 / 50)
            xlist.append(i)
            print(i)

        pylab.xlabel('Размер массива, символы')
        pylab.ylabel('Время, секунды')
        pylab.plot(xlist, ylist1, 'r--', label = 'Поразрядная')
        pylab.plot(xlist, ylist2, color = 'yellow', label = 'Быстрая')
        pylab.plot(xlist, ylist3, 'b-.', label = 'Вставками')
        pylab.legend(loc='upper left')
        pylab.show()
    else:
        print("Некорректно")
if __name__ == "__main__":
    main()
