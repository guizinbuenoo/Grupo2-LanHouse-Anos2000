#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define TOTAL_BAIAS 8
#define MAX_NOME 50

typedef struct {
    int ocupada;
    char cliente[MAX_NOME];
    double consumo;
} Baia;

static int ler_int(const char *mensagem, int minimo, int maximo) {
    char linha[128], *fim;
    long valor;
    for (;;) {
        printf("%s", mensagem);
        if (!fgets(linha, sizeof linha, stdin)) return minimo;
        errno = 0;
        valor = strtol(linha, &fim, 10);
        while (*fim == ' ' || *fim == '\t') fim++;
        if (errno == 0 && fim != linha && (*fim == '\n' || *fim == '\0') && valor >= minimo && valor <= maximo)
            return (int)valor;
        printf("Entrada invalida. Digite um valor entre %d e %d.\n", minimo, maximo);
    }
}

static double ler_double(const char *mensagem, double minimo) {
    char linha[128], *fim;
    double valor;
    for (;;) {
        printf("%s", mensagem);
        if (!fgets(linha, sizeof linha, stdin)) return minimo;
        errno = 0;
        valor = strtod(linha, &fim);
        while (*fim == ' ' || *fim == '\t') fim++;
        if (errno == 0 && fim != linha && (*fim == '\n' || *fim == '\0') && valor >= minimo) return valor;
        printf("Entrada invalida.\n");
    }
}

static void ler_texto(const char *mensagem, char *destino, size_t tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, (int)tamanho, stdin)) destino[strcspn(destino, "\r\n")] = '\0';
}

static void listar(const Baia baias[]) {
    int i;
    puts("\n=== MAPA DE BAIAS ===");
    for (i = 0; i < TOTAL_BAIAS; i++) {
        printf("Baia %d: %s", i + 1, baias[i].ocupada ? "OCUPADA" : "LIVRE");
        if (baias[i].ocupada) printf(" | Cliente: %s | Consumo: R$ %.2f", baias[i].cliente, baias[i].consumo);
        putchar('\n');
    }
}

int main(void) {
    Baia baias[TOTAL_BAIAS] = {0};
    int opcao, numero;
    double valor;
    puts("LAN HOUSE BYTE 2000 - CHECKPOINT 1");
    do {
        puts("\n1. Listar baias\n2. Ocupar baia\n3. Registrar consumo\n4. Liberar baia\n0. Sair");
        opcao = ler_int("Opcao: ", 0, 4);
        if (opcao == 1) listar(baias);
        else if (opcao == 2) {
            numero = ler_int("Numero da baia: ", 1, TOTAL_BAIAS) - 1;
            if (baias[numero].ocupada) puts("Erro: baia ja ocupada.");
            else {
                ler_texto("Nome do cliente: ", baias[numero].cliente, sizeof baias[numero].cliente);
                if (baias[numero].cliente[0] == '\0') strcpy(baias[numero].cliente, "Cliente");
                baias[numero].ocupada = 1;
                baias[numero].consumo = 0.0;
                puts("Baia ocupada com sucesso.");
            }
        } else if (opcao == 3) {
            numero = ler_int("Numero da baia: ", 1, TOTAL_BAIAS) - 1;
            if (!baias[numero].ocupada) puts("Erro: baia livre.");
            else {
                valor = ler_double("Valor do consumo (R$): ", 0.01);
                baias[numero].consumo += valor;
                puts("Consumo registrado.");
            }
        } else if (opcao == 4) {
            numero = ler_int("Numero da baia: ", 1, TOTAL_BAIAS) - 1;
            if (!baias[numero].ocupada) puts("Erro: baia livre.");
            else {
                printf("Conta de %s: R$ %.2f\n", baias[numero].cliente, baias[numero].consumo);
                memset(&baias[numero], 0, sizeof baias[numero]);
                puts("Baia liberada.");
            }
        }
    } while (opcao != 0);
    puts("Programa encerrado.");
    return 0;
}
