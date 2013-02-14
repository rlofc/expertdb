build:
	@rm -f test/test
	@gcc -Wall test/*.c test/c89spec/*.c -o test/test
	@test/test
