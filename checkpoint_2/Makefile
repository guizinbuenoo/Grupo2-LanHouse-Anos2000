CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Wpedantic -Werror -Iinclude
all: lanhouse_cp2
lanhouse_cp2: src/main.c src/lanhouse.c include/lanhouse.h
	$(CC) $(CFLAGS) src/main.c src/lanhouse.c -o $@
test: tests/test_core.c src/lanhouse.c
	$(CC) $(CFLAGS) tests/test_core.c src/lanhouse.c -lm -o test_cp2
	./test_cp2
clean:
	rm -f lanhouse_cp2 test_cp2
.PHONY: all test clean
