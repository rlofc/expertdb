build:
	@rm -f test/test
	@gcc -g -Wall -std=c99 src/*.c test/*.c test/c89spec/*.c -o test/test
	@test/test
