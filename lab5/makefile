CC := g++

CFLAGS := -std=c++17 -Wall -Werror

main.out: number.o main.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $<

number.o: number.cpp number.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.out
