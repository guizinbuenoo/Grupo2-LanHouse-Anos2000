#ifndef LANHOUSE_H
#define LANHOUSE_H

#include "models.h"

void sistema_inicializar(Sistema *sistema);
void listar_baias(const Sistema *sistema);
void listar_produtos(const Sistema *sistema);
void listar_produtos_ordenados(const Sistema *sistema, int criterio);
int abrir_sessao(Sistema *sistema, int numero_baia, const char *cliente,
                 unsigned long *codigo);
int adicionar_consumo(Sistema *sistema, int numero_baia, int produto_id,
                      int quantidade);
int repor_estoque(Sistema *sistema, int produto_id, int quantidade);
int fechar_sessao(Sistema *sistema, int numero_baia, int minutos,
                  Fechamento *fechamento);
double total_consumo_sessao(const Sistema *sistema, int numero_baia);

#endif
