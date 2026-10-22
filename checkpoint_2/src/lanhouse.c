#include <stdio.h>
#include <string.h>
#include "lanhouse.h"

void inicializar(Baia baias[], Produto produtos[]) {
    const char *nomes[TOTAL_PRODUTOS] = {"Refrigerante", "Salgadinho", "Chocolate", "Cafe", "Agua"};
    const double precos[TOTAL_PRODUTOS] = {6.0, 5.0, 4.5, 3.0, 3.5};
    int i;
    memset(baias, 0, sizeof(Baia) * TOTAL_BAIAS);
    for (i = 0; i < TOTAL_BAIAS; i++) baias[i].numero = i + 1;
    for (i = 0; i < TOTAL_PRODUTOS; i++) {
        produtos[i].id = i + 1;
        snprintf(produtos[i].nome, sizeof produtos[i].nome, "%s", nomes[i]);
        produtos[i].preco = precos[i];
        produtos[i].estoque = 20;
    }
}
void listar_baias(const Baia baias[]) {
    int i;
    puts("\n=== BAIAS ===");
    for (i = 0; i < TOTAL_BAIAS; i++)
        printf("%02d - %s%s%s\n", baias[i].numero, baias[i].sessao.ativa ? "OCUPADA (" : "LIVRE", baias[i].sessao.ativa ? baias[i].sessao.cliente : "", baias[i].sessao.ativa ? ")" : "");
}
void listar_produtos(const Produto produtos[]) {
    int i;
    puts("\n=== LANCHONETE ===");
    for (i = 0; i < TOTAL_PRODUTOS; i++)
        printf("%d - %-15s R$ %.2f | estoque: %d\n", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
}
int abrir_sessao(Baia *baia, const char *cliente) {
    if (!baia || baia->sessao.ativa || !cliente || !*cliente) return 0;
    memset(&baia->sessao, 0, sizeof baia->sessao);
    baia->sessao.ativa = 1;
    snprintf(baia->sessao.cliente, sizeof baia->sessao.cliente, "%s", cliente);
    return 1;
}
int adicionar_consumo(Baia *baia, Produto produtos[], int produto_id, int quantidade) {
    Produto *p;
    ItemConsumo *item;
    if (!baia || !baia->sessao.ativa || produto_id < 1 || produto_id > TOTAL_PRODUTOS || quantidade <= 0) return 0;
    p = &produtos[produto_id - 1];
    if (p->estoque < quantidade || baia->sessao.total_itens >= MAX_CONSUMOS) return 0;
    item = &baia->sessao.itens[baia->sessao.total_itens++];
    item->produto_id = produto_id;
    item->quantidade = quantidade;
    p->estoque -= quantidade;
    return 1;
}
double fechar_sessao(Baia *baia, const Produto produtos[], int minutos, double preco_hora) {
    double total;
    int i;
    if (!baia || !baia->sessao.ativa || minutos <= 0 || preco_hora < 0.0) return -1.0;
    total = ((double)minutos / 60.0) * preco_hora;
    for (i = 0; i < baia->sessao.total_itens; i++) {
        const ItemConsumo *item = &baia->sessao.itens[i];
        total += produtos[item->produto_id - 1].preco * item->quantidade;
    }
    memset(&baia->sessao, 0, sizeof baia->sessao);
    return total;
}
