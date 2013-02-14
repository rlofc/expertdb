build:
	@rm -f test/test
	@gcc -Wall -std=gnu89 -pedantic src/*.c test/*.c test/c89spec/*.c -o test/test
	@test/test
