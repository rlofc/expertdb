build:
	@rm -f test/test
	@gcc -Wall -std=gnu89 -pedantic test/*.c test/c89spec/*.c -o test/test
	@test/test
