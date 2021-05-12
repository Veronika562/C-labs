all: build test

build:
	gcc -std=c89 -o main main.c person.c -lm

test:
	gcc -std=c89 -o test -Dmain=_main main.c person.c test.c -lm
	test < text_files/test_con_in.txt > text_files/test_con_out.txt