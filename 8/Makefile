build:
	g++ -Wall -pedantic -fsanitize=address -Wno-long-long -g main.c -o bin/run

run: build
	exec ./bin/run

test: build
	exec ./bin/test.sh

debug: build 
	gdb bin/run 

spec: build
	exec ./bin/test_spec.sh $1
