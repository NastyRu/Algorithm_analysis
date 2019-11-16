import pylab

xlist = []
ylist0 = []
ylist1 = []

f = open('data.txt')
for line in f:
    arr = line.split(' ')
    xlist.append(int(arr[0]))
    ylist0.append(int(arr[1]))
    ylist1.append(int(arr[2]))
f.close()

pylab.xlabel('Количество пар чисел')
pylab.ylabel('Время, микросекунды')
pylab.plot(xlist, ylist1, 'r-.', label = 'Конвейерная обработка')
pylab.plot(xlist, ylist0, 'g--', label = 'Последовательная обработка')
pylab.legend(loc='upper left')
pylab.show()
