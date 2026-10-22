#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lanhouse.h"
#include "storage.h"

#define ARQUIVO_DADOS "data/lanhouse.dat"
#define ARQUIVO_CSV "data/operacoes.csv"
#define ARQUIVO_AUDITORIA "data/auditoria.log"
#define DIRETORIO_DADOS "data"

/* Le numeros com fgets + strtol para impedir letras e valores fora da faixa. */
static int ler_inteiro(const char *mensagem, int minimo, int maximo) {
    char linha[128];
    char *fim;
    long valor;

    for (;;) {
        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) == NULL) return minimo;

        errno = 0;
        valor = strtol(linha, &fim, 10);
        while (*fim == ' ' || *fim == '\t') fim++;

        if (errno == 0 && fim != linha &&
            (*fim == '\n' || *fim == '\0') &&
            valor >= minimo && valor <= maximo) {
            return (int)valor;
        }
        printf("Entrada invalida. Use um numero entre %d e %d.\n",
               minimo, maximo);
    }
}

static void ler_texto(const char *mensagem, char *destino, size_t tamanho) {
    for (;;) {
        printf("%s", mensagem);
        if (fgets(destino, (int)tamanho, stdin) == NULL) {
            destino[0] = '\0';
            return;
        }

        if (strchr(destino, '\n') != NULL) {
            destino[strcspn(destino, "\r\n")] = '\0';
            if (strlen(destino) >= 2) return;
        } else {
            int caractere;
            while ((caractere = getchar()) != '\n' && caractere != EOF) { }
        }
        puts("Texto invalido (minimo 2 e maximo 50 caracteres).");
    }
}

static void salvar(const Sistema *sistema) {
    if (!salvar_sistema(ARQUIVO_DADOS, sistema)) {
        puts("AVISO: nao foi possivel salvar os dados.");
    }
}

int main(void) {
    Sistema sistema;
    Fechamento fechamento;
    int opcao, baia, produto, quantidade, minutos, criterio;
    char cliente[MAX_NOME];
    char auditoria[160];
    unsigned long codigo;

    if (carregar_sistema(ARQUIVO_DADOS, &sistema)) {
        puts("Dados anteriores carregados.");
    } else {
        sistema_inicializar(&sistema);
        salvar(&sistema);
        puts("Novo banco de dados criado.");
    }

    registrar_auditoria(ARQUIVO_AUDITORIA, "Sistema iniciado");
    puts("\n========================================");
    puts("  LAN HOUSE BYTE 2000 - SISTEMA FINAL");
    puts("========================================");

    do {
        puts("\n1. Mapa de baias");
        puts("2. Abrir sessao");
        puts("3. Adicionar consumo");
        puts("4. Fechar conta");
        puts("5. Produtos e estoque");
        puts("6. Repor estoque");
        puts("7. Listagem ordenada de produtos");
        puts("8. Relatorio financeiro");
        puts("9. Salvar");
        puts("0. Salvar e sair");
        opcao = ler_inteiro("Opcao: ", 0, 9);

        if (opcao == 1) {
            listar_baias(&sistema);
        } else if (opcao == 2) {
            baia = ler_inteiro("Baia: ", 1, TOTAL_BAIAS);
            ler_texto("Cliente: ", cliente, sizeof(cliente));
            if (abrir_sessao(&sistema, baia, cliente, &codigo)) {
                printf("Sessao %lu aberta com sucesso.\n", codigo);
                snprintf(auditoria, sizeof(auditoria),
                         "Sessao %lu aberta na baia %d para %s",
                         codigo, baia, cliente);
                registrar_auditoria(ARQUIVO_AUDITORIA, auditoria);
                salvar(&sistema);
            } else {
                puts("Falha: baia ocupada ou dados invalidos.");
            }
        } else if (opcao == 3) {
            baia = ler_inteiro("Baia: ", 1, TOTAL_BAIAS);
            listar_produtos(&sistema);
            produto = ler_inteiro("Produto: ", 1, TOTAL_PRODUTOS);
            quantidade = ler_inteiro("Quantidade: ", 1, 100);
            if (adicionar_consumo(&sistema, baia, produto, quantidade)) {
                puts("Consumo adicionado.");
                snprintf(auditoria, sizeof(auditoria),
                         "Consumo: baia %d, produto %d, quantidade %d",
                         baia, produto, quantidade);
                registrar_auditoria(ARQUIVO_AUDITORIA, auditoria);
                salvar(&sistema);
            } else {
                puts("Falha: verifique sessao e estoque.");
            }
        } else if (opcao == 4) {
            baia = ler_inteiro("Baia: ", 1, TOTAL_BAIAS);
            minutos = ler_inteiro("Minutos utilizados: ", 1, 1440);
            if (fechar_sessao(&sistema, baia, minutos, &fechamento)) {
                printf("\nTempo: R$ %.2f\n", fechamento.tempo);
                printf("Produtos: R$ %.2f\n", fechamento.produtos);
                printf("TOTAL: R$ %.2f\n", fechamento.total);
                salvar(&sistema);
                emitir_comprovante(DIRETORIO_DADOS, &fechamento);
                registrar_operacao_csv(ARQUIVO_CSV, &fechamento);
                snprintf(auditoria, sizeof(auditoria),
                         "Sessao %lu fechada; total R$ %.2f",
                         fechamento.codigo, fechamento.total);
                registrar_auditoria(ARQUIVO_AUDITORIA, auditoria);
                printf("Comprovante %lu emitido.\n", fechamento.codigo);
            } else {
                puts("Falha: nao existe sessao ativa nessa baia.");
            }
        } else if (opcao == 5) {
            listar_produtos(&sistema);
        } else if (opcao == 6) {
            listar_produtos(&sistema);
            produto = ler_inteiro("Produto: ", 1, TOTAL_PRODUTOS);
            quantidade = ler_inteiro("Quantidade para adicionar: ", 1, 10000);
            if (repor_estoque(&sistema, produto, quantidade)) {
                puts("Estoque atualizado.");
                registrar_auditoria(ARQUIVO_AUDITORIA,
                                     "Reposicao de estoque realizada");
                salvar(&sistema);
            } else {
                puts("Falha ao repor estoque.");
            }
        } else if (opcao == 7) {
            puts("1. Ordenar por nome");
            puts("2. Ordenar por preco");
            criterio = ler_inteiro("Criterio: ", 1, 2);
            listar_produtos_ordenados(&sistema, criterio);
        } else if (opcao == 8) {
            printf("\nSessoes fechadas: %lu\n", sistema.sessoes_fechadas);
            printf("Receita de tempo: R$ %.2f\n", sistema.receita_tempo);
            printf("Receita de produtos: R$ %.2f\n",
                   sistema.receita_produtos);
            printf("RECEITA TOTAL: R$ %.2f\n",
                   sistema.receita_tempo + sistema.receita_produtos);
        } else if (opcao == 9) {
            if (salvar_sistema(ARQUIVO_DADOS, &sistema))
                puts("Dados salvos.");
            else
                puts("Falha ao salvar.");
        }
    } while (opcao != 0);

    salvar(&sistema);
    registrar_auditoria(ARQUIVO_AUDITORIA, "Sistema encerrado");
    puts("Sistema encerrado com seguranca.");
    return 0;
}
