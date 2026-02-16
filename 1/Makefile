build:
	g++ -Wall -pedantic -fsanitize=address -g main.c -o bin/run

run: build
	exec ./bin/run

test: build
	exec ./bin/test.sh

debug: build 
	gdb bin/run 
