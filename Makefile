all: run

run: main
	./main

main: main.c
	gcc -o main main.c -lncurses
