CC := g++

CFLAGS := -std=c++11 -Wall -Werror

main.out: number.o main.o
	$(CC) $^ -o $@

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.out
