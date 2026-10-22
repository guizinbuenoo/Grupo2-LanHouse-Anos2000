CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Wpedantic -Werror -Iinclude
SRC=src/main.c src/lanhouse.c src/storage.c
all: lanhouse
lanhouse: $(SRC) include/models.h include/lanhouse.h include/storage.h
	$(CC) $(CFLAGS) $(SRC) -o $@
test_unit: tests/test_core.c src/lanhouse.c src/storage.c
	$(CC) $(CFLAGS) tests/test_core.c src/lanhouse.c src/storage.c -lm -o test_final
	./test_final
test_integration: lanhouse
	sh tests/teste_integracao.sh
test: test_unit test_integration
clean:
	rm -f lanhouse test_final data/*.dat data/*.csv data/comprovante_*.txt data/saida_integracao.txt
.PHONY: all test test_unit test_integration clean
