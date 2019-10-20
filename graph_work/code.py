array = [1,2,3]
count = len(array)
n = 10 ** len(str(abs(max(array))))
neg = sum(x < 0 for x in array)
i = 1
while (i < n):
    sort = [[] for k in range(10)]
    for x in array:
        sort[get_digit(x, i)].append(x)
    array = [0] * count
    u = w = 0
    for k in range(10):
        for j in range(len(sort[k])):
            if (sort[k][j] < 0):
                array[w] = sort[k][j]
                w += 1
            else:
                array[u + neg] = sort[k][j]
                u += 1
    i *= 10
print(array)
