#ifndef STORAGE_H
#define STORAGE_H

#include "models.h"

int salvar_sistema(const char *arquivo, const Sistema *sistema);
int carregar_sistema(const char *arquivo, Sistema *sistema);
int emitir_comprovante(const char *diretorio, const Fechamento *fechamento);
int registrar_operacao_csv(const char *arquivo, const Fechamento *fechamento);
int registrar_auditoria(const char *arquivo, const char *acao);

#endif
