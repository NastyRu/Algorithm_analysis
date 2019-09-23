import time
a = 0
b = 0

start_time = time.time()
for i in range(10000000):
    a = a + 1
print("Время выполнения а = а + 1 для 10 миллионов итераций: " + str(time.time() - start_time))

strart_time = time.time()
for i in range(10000000):
    b += 1
print("Время выполнения b += 1 для 10 миллионов итераций: " + str(time.time() - start_time))
