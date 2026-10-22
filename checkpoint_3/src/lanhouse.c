#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lanhouse.h"

/* Retorna a baia solicitada ou NULL caso o numero seja invalido. */
static Baia *buscar_baia(Sistema *sistema, int numero) {
    if (sistema == NULL || numero < 1 || numero > TOTAL_BAIAS) {
        return NULL;
    }
    return &sistema->baias[numero - 1];
}

static const Baia *buscar_baia_constante(const Sistema *sistema, int numero) {
    if (sistema == NULL || numero < 1 || numero > TOTAL_BAIAS) {
        return NULL;
    }
    return &sistema->baias[numero - 1];
}

static Produto *buscar_produto(Sistema *sistema, int id) {
    if (sistema == NULL || id < 1 || id > TOTAL_PRODUTOS) {
        return NULL;
    }
    return &sistema->produtos[id - 1];
}

/* Comparadores usados pelo qsort para cumprir o requisito de ordenacao. */
static int comparar_nome(const void *a, const void *b) {
    const Produto *produto_a = (const Produto *)a;
    const Produto *produto_b = (const Produto *)b;
    return strcmp(produto_a->nome, produto_b->nome);
}

static int comparar_preco(const void *a, const void *b) {
    const Produto *produto_a = (const Produto *)a;
    const Produto *produto_b = (const Produto *)b;
    if (produto_a->preco < produto_b->preco) return -1;
    if (produto_a->preco > produto_b->preco) return 1;
    return comparar_nome(a, b);
}

void sistema_inicializar(Sistema *sistema) {
    static const char *nomes[TOTAL_PRODUTOS] = {
        "Refrigerante", "Salgadinho", "Chocolate", "Cafe", "Agua", "Miojo"
    };
    static const double precos[TOTAL_PRODUTOS] = {
        6.00, 5.00, 4.50, 3.00, 3.50, 7.50
    };
    int i;

    memset(sistema, 0, sizeof(*sistema));
    sistema->magic = APP_MAGIC;
    sistema->versao = APP_VERSION;
    sistema->proximo_codigo = 1001;

    for (i = 0; i < TOTAL_BAIAS; i++) {
        sistema->baias[i].numero = i + 1;
    }

    for (i = 0; i < TOTAL_PRODUTOS; i++) {
        sistema->produtos[i].id = i + 1;
        snprintf(sistema->produtos[i].nome,
                 sizeof(sistema->produtos[i].nome), "%s", nomes[i]);
        sistema->produtos[i].preco = precos[i];
        sistema->produtos[i].estoque = 20;
    }
}

void listar_baias(const Sistema *sistema) {
    int i;

    puts("\n+------+----------+--------------------------------+-------------+");
    puts("| BAIA | STATUS   | CLIENTE                        | CONSUMO     |");
    puts("+------+----------+--------------------------------+-------------+");

    for (i = 0; i < TOTAL_BAIAS; i++) {
        const Baia *baia = &sistema->baias[i];
        printf("| %4d | %-8s | %-30s | R$ %8.2f |\n",
               baia->numero,
               baia->sessao.ativa ? "OCUPADA" : "LIVRE",
               baia->sessao.ativa ? baia->sessao.cliente : "-",
               total_consumo_sessao(sistema, baia->numero));
    }
    puts("+------+----------+--------------------------------+-------------+");
}

static void imprimir_produtos(const Produto produtos[]) {
    int i;
    puts("\n=== PRODUTOS ===");
    for (i = 0; i < TOTAL_PRODUTOS; i++) {
        printf("%d - %-15s | R$ %6.2f | estoque: %d\n",
               produtos[i].id, produtos[i].nome,
               produtos[i].preco, produtos[i].estoque);
    }
}

void listar_produtos(const Sistema *sistema) {
    imprimir_produtos(sistema->produtos);
}

void listar_produtos_ordenados(const Sistema *sistema, int criterio) {
    Produto copia[TOTAL_PRODUTOS];

    memcpy(copia, sistema->produtos, sizeof(copia));
    if (criterio == 1) {
        qsort(copia, TOTAL_PRODUTOS, sizeof(Produto), comparar_nome);
    } else {
        qsort(copia, TOTAL_PRODUTOS, sizeof(Produto), comparar_preco);
    }
    imprimir_produtos(copia);
}

int abrir_sessao(Sistema *sistema, int numero_baia, const char *cliente,
                 unsigned long *codigo) {
    Baia *baia = buscar_baia(sistema, numero_baia);
    size_t tamanho;

    if (baia == NULL || baia->sessao.ativa || cliente == NULL) return 0;
    tamanho = strlen(cliente);
    if (tamanho < 2 || tamanho >= MAX_NOME) return 0;

    memset(&baia->sessao, 0, sizeof(baia->sessao));
    baia->sessao.ativa = 1;
    baia->sessao.codigo = sistema->proximo_codigo++;
    snprintf(baia->sessao.cliente, sizeof(baia->sessao.cliente),
             "%s", cliente);

    if (codigo != NULL) *codigo = baia->sessao.codigo;
    return 1;
}

int adicionar_consumo(Sistema *sistema, int numero_baia, int produto_id,
                      int quantidade) {
    Baia *baia = buscar_baia(sistema, numero_baia);
    Produto *produto = buscar_produto(sistema, produto_id);
    int i;

    if (baia == NULL || !baia->sessao.ativa || produto == NULL ||
        quantidade <= 0 || produto->estoque < quantidade) {
        return 0;
    }

    /* Se o produto ja existe na conta, apenas soma a quantidade. */
    for (i = 0; i < baia->sessao.total_itens; i++) {
        if (baia->sessao.itens[i].produto_id == produto_id) {
            baia->sessao.itens[i].quantidade += quantidade;
            produto->estoque -= quantidade;
            return 1;
        }
    }

    if (baia->sessao.total_itens >= MAX_CONSUMOS) return 0;

    baia->sessao.itens[baia->sessao.total_itens].produto_id = produto_id;
    baia->sessao.itens[baia->sessao.total_itens].quantidade = quantidade;
    baia->sessao.total_itens++;
    produto->estoque -= quantidade;
    return 1;
}

int repor_estoque(Sistema *sistema, int produto_id, int quantidade) {
    Produto *produto = buscar_produto(sistema, produto_id);
    if (produto == NULL || quantidade <= 0 ||
        produto->estoque > 100000 - quantidade) {
        return 0;
    }
    produto->estoque += quantidade;
    return 1;
}

double total_consumo_sessao(const Sistema *sistema, int numero_baia) {
    const Baia *baia = buscar_baia_constante(sistema, numero_baia);
    double total = 0.0;
    int i;

    if (baia == NULL || !baia->sessao.ativa) return 0.0;

    for (i = 0; i < baia->sessao.total_itens; i++) {
        const ItemConsumo *item = &baia->sessao.itens[i];
        if (item->produto_id >= 1 && item->produto_id <= TOTAL_PRODUTOS) {
            total += sistema->produtos[item->produto_id - 1].preco *
                     item->quantidade;
        }
    }
    return total;
}

int fechar_sessao(Sistema *sistema, int numero_baia, int minutos,
                  Fechamento *fechamento) {
    Baia *baia = buscar_baia(sistema, numero_baia);

    if (baia == NULL || !baia->sessao.ativa || minutos <= 0 ||
        minutos > 1440 || fechamento == NULL) {
        return 0;
    }

    memset(fechamento, 0, sizeof(*fechamento));
    fechamento->codigo = baia->sessao.codigo;
    snprintf(fechamento->cliente, sizeof(fechamento->cliente),
             "%s", baia->sessao.cliente);
    fechamento->baia = numero_baia;
    fechamento->minutos = minutos;
    fechamento->tempo = (minutos / 60.0) * PRECO_HORA;
    fechamento->produtos = total_consumo_sessao(sistema, numero_baia);
    fechamento->total = fechamento->tempo + fechamento->produtos;

    sistema->sessoes_fechadas++;
    sistema->receita_tempo += fechamento->tempo;
    sistema->receita_produtos += fechamento->produtos;
    memset(&baia->sessao, 0, sizeof(baia->sessao));
    return 1;
}
