CC = gcc
CFLAGS = -O3 -Wall

all : main

main : main.c
	$(CC) $(CFLAGS) PortableGrayMap.c main.c -o main -lm

run : main
	./main

.PHONY : clean
clean :
	rm -f main
