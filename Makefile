CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Werror
TARGET = lanhouse_cp1
all: $(TARGET)
$(TARGET): src/main.c
	$(CC) $(CFLAGS) src/main.c -o $(TARGET)
test: $(TARGET)
	sh tests/teste_integracao.sh
clean:
	rm -f $(TARGET) saida_teste.txt
.PHONY: all test clean
