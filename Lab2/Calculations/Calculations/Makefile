all: createDir build test

createDir:
	mkdir -p target
build:
	gcc -o target/Calclations Calculations.c -lm
test:
	gcc -o target/test Calculations.c test.c -Dmain=_main -lm
	./target/test