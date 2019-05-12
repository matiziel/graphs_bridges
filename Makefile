CC=g++
CFLAGS=-Wall -g -std=c++11

all:
	$(CC) $(CFLAGS) mosty.cpp -o run
clean:
	rm -f run
