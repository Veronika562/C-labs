all: build test

build:
	gcc -o main main.c tree.c -lm

test:
	gcc -o test main.c test.c tree.c -Dmain=_main -lm