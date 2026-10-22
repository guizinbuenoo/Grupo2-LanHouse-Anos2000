#ifndef LANHOUSE_H
#define LANHOUSE_H
#define TOTAL_BAIAS 10
#define TOTAL_PRODUTOS 5
#define MAX_NOME 50
#define MAX_CONSUMOS 20

typedef struct { int id; char nome[30]; double preco; int estoque; } Produto;
typedef struct { int produto_id; int quantidade; } ItemConsumo;
typedef struct {
    int ativa;
    char cliente[MAX_NOME];
    ItemConsumo itens[MAX_CONSUMOS];
    int total_itens;
} Sessao;
typedef struct { int numero; Sessao sessao; } Baia;

void inicializar(Baia baias[], Produto produtos[]);
void listar_baias(const Baia baias[]);
void listar_produtos(const Produto produtos[]);
int abrir_sessao(Baia *baia, const char *cliente);
int adicionar_consumo(Baia *baia, Produto produtos[], int produto_id, int quantidade);
double fechar_sessao(Baia *baia, const Produto produtos[], int minutos, double preco_hora);
#endif
