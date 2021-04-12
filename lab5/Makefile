all: createDir build test

createDir:
	mkdir target

build:
	gcc -o target/main main.c -lm

test:
	gcc -o target/test main.c test.c -Dmain=_main -lm
	./target/test