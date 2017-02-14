
CC = g++ -std=c++11

all: pizza

pizza: main.o Problem.o Slice.o Solution.o HillClimbing.o
	$(CC) -o $@ $^ -O3

%.o: %.cpp
	$(CC) -c $^ -O3

clean:
	rm *.o
