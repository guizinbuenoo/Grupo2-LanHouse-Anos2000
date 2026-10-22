#include <stdio.h>
#include <string.h>
#include <time.h>
#include "storage.h"

int salvar_sistema(const char *arquivo, const Sistema *sistema) {
    char temporario[260];
    FILE *saida;

    if (arquivo == NULL || sistema == NULL) return 0;
    if (snprintf(temporario, sizeof(temporario), "%s.tmp", arquivo) < 0)
        return 0;

    saida = fopen(temporario, "wb");
    if (saida == NULL) return 0;

    if (fwrite(sistema, sizeof(*sistema), 1, saida) != 1) {
        fclose(saida);
        remove(temporario);
        return 0;
    }
    if (fclose(saida) != 0) {
        remove(temporario);
        return 0;
    }

    /* Primeiro grava em arquivo temporario para reduzir risco de corrupcao. */
    remove(arquivo);
    if (rename(temporario, arquivo) != 0) {
        remove(temporario);
        return 0;
    }
    return 1;
}

int carregar_sistema(const char *arquivo, Sistema *sistema) {
    FILE *entrada;
    Sistema temporario;

    if (arquivo == NULL || sistema == NULL) return 0;
    entrada = fopen(arquivo, "rb");
    if (entrada == NULL) return 0;

    if (fread(&temporario, sizeof(temporario), 1, entrada) != 1) {
        fclose(entrada);
        return 0;
    }
    fclose(entrada);

    if (temporario.magic != APP_MAGIC || temporario.versao != APP_VERSION)
        return 0;

    *sistema = temporario;
    return 1;
}

int emitir_comprovante(const char *diretorio, const Fechamento *fechamento) {
    char nome_arquivo[300];
    FILE *saida;

    if (diretorio == NULL || fechamento == NULL) return 0;
    if (snprintf(nome_arquivo, sizeof(nome_arquivo),
                 "%s/comprovante_%lu.txt", diretorio,
                 fechamento->codigo) < 0) return 0;

    saida = fopen(nome_arquivo, "w");
    if (saida == NULL) return 0;

    fprintf(saida, "=====================================\n");
    fprintf(saida, "       LAN HOUSE BYTE 2000\n");
    fprintf(saida, "=====================================\n");
    fprintf(saida, "Sessao: %lu\n", fechamento->codigo);
    fprintf(saida, "Cliente: %s\n", fechamento->cliente);
    fprintf(saida, "Baia: %d\n", fechamento->baia);
    fprintf(saida, "Tempo: %d minutos ........ R$ %.2f\n",
            fechamento->minutos, fechamento->tempo);
    fprintf(saida, "Produtos .................. R$ %.2f\n",
            fechamento->produtos);
    fprintf(saida, "TOTAL ...................... R$ %.2f\n",
            fechamento->total);
    fprintf(saida, "=====================================\n");
    return fclose(saida) == 0;
}

int registrar_operacao_csv(const char *arquivo, const Fechamento *fechamento) {
    FILE *saida;

    if (arquivo == NULL || fechamento == NULL) return 0;
    saida = fopen(arquivo, "a");
    if (saida == NULL) return 0;

    if (ftell(saida) == 0) {
        fprintf(saida,
                "sessao,cliente,baia,minutos,tempo,produtos,total\n");
    }
    fprintf(saida, "%lu,\"%s\",%d,%d,%.2f,%.2f,%.2f\n",
            fechamento->codigo, fechamento->cliente,
            fechamento->baia, fechamento->minutos,
            fechamento->tempo, fechamento->produtos,
            fechamento->total);
    return fclose(saida) == 0;
}

int registrar_auditoria(const char *arquivo, const char *acao) {
    FILE *saida;
    time_t agora;
    struct tm *data_hora;
    char texto_data[32];

    if (arquivo == NULL || acao == NULL) return 0;
    saida = fopen(arquivo, "a");
    if (saida == NULL) return 0;

    agora = time(NULL);
    data_hora = localtime(&agora);
    if (data_hora != NULL) {
        strftime(texto_data, sizeof(texto_data), "%Y-%m-%d %H:%M:%S",
                 data_hora);
    } else {
        snprintf(texto_data, sizeof(texto_data), "data-indisponivel");
    }
    fprintf(saida, "[%s] %s\n", texto_data, acao);
    return fclose(saida) == 0;
}
