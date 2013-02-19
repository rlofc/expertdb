build: clean deps
	@mkdir bin
	@gcc -g -Wall -std=c99 src/*.c test/*.c test/c89spec/*.c -o bin/test
	@bin/test

clean:
	@rm -Rf bin 

deps:
	@git submodule update --init --recursive
