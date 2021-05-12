all: build test clean

build:
	gcc -std=c89 -o main main.c person.c -lm

test:
	gcc -ftest-coverage -fprofile-arcs -O0 -o test -Dmain=_main main.c person.c test.c -lm
	test < text_files/test_con_in.txt > text_files/test_con_out.txt
	gcov -abcfu test.c
	gcov -abcfu person.c
	gcov -abcfu main.c
clean:
	rm -rf target
