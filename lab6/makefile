CC := g++

CFLAGS := -std=c++17

main.out: dot.o ant_algorithm.o enumeration.o main.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $<

dot.o: dot.cpp dot.h
	$(CC) $(CFLAGS) -c $<

ant_algorithm.o: ant_algorithm.cpp ant_algorithm.h
	$(CC) $(CFLAGS) -c $<

enumeration.o: enumeration.cpp enumeration.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.out
