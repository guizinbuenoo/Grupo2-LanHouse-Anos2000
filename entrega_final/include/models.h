#ifndef MODELS_H
#define MODELS_H
#define APP_MAGIC 0x4C483230u
#define APP_VERSION 1u
#define TOTAL_BAIAS 12
#define TOTAL_PRODUTOS 6
#define MAX_NOME 51
#define MAX_CONSUMOS 20
#define PRECO_HORA 12.0

typedef struct { int produto_id; int quantidade; } ItemConsumo;
typedef struct {
    int ativa;
    unsigned long codigo;
    char cliente[MAX_NOME];
    ItemConsumo itens[MAX_CONSUMOS];
    int total_itens;
} Sessao;
typedef struct { int numero; Sessao sessao; } Baia;
typedef struct { int id; char nome[31]; double preco; int estoque; } Produto;
typedef struct {
    unsigned int magic, versao;
    Baia baias[TOTAL_BAIAS];
    Produto produtos[TOTAL_PRODUTOS];
    unsigned long proximo_codigo;
    unsigned long sessoes_fechadas;
    double receita_tempo;
    double receita_produtos;
} Sistema;
typedef struct { unsigned long codigo; char cliente[MAX_NOME]; int baia; int minutos; double tempo; double produtos; double total; } Fechamento;
#endif
