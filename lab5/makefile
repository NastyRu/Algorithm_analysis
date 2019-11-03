CC := g++

CFLAGS := -std=c++11 -Wall -Werror

main.out: number.o main.o
	g++ -std=c++11 $^ -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $<

number.o: number.cpp number.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.out
