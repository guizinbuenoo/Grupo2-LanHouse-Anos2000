#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "lanhouse.h"
#define PRECO_HORA 12.0
static int ler_int(const char *m, int min, int max) { char s[100], *f; long v; for (;;) { printf("%s", m); if (!fgets(s,sizeof s,stdin)) return min; errno=0; v=strtol(s,&f,10); while(*f==' '||*f=='\t')f++; if(!errno&&f!=s&&(*f=='\n'||*f=='\0')&&v>=min&&v<=max)return(int)v; puts("Entrada invalida."); } }
static void ler_texto(const char *m, char *s, size_t n) { printf("%s",m); if(fgets(s,(int)n,stdin))s[strcspn(s,"\r\n")]=0; }
int main(void) {
    Baia baias[TOTAL_BAIAS]; Produto produtos[TOTAL_PRODUTOS]; int op, b, p, q, min; char nome[MAX_NOME]; double total;
    inicializar(baias, produtos); puts("LAN HOUSE BYTE 2000 - CHECKPOINT 2");
    do {
        puts("\n1.Listar baias 2.Abrir sessao 3.Consumir 4.Fechar conta 5.Produtos 0.Sair"); op=ler_int("Opcao: ",0,5);
        if(op==1) listar_baias(baias);
        else if(op==2){b=ler_int("Baia: ",1,TOTAL_BAIAS)-1;ler_texto("Cliente: ",nome,sizeof nome);puts(abrir_sessao(&baias[b],nome)?"Sessao aberta.":"Nao foi possivel abrir.");}
        else if(op==3){b=ler_int("Baia: ",1,TOTAL_BAIAS)-1;listar_produtos(produtos);p=ler_int("Produto: ",1,TOTAL_PRODUTOS);q=ler_int("Quantidade: ",1,99);puts(adicionar_consumo(&baias[b],produtos,p,q)?"Consumo adicionado.":"Falha: verifique sessao, estoque ou limite.");}
        else if(op==4){b=ler_int("Baia: ",1,TOTAL_BAIAS)-1;min=ler_int("Minutos usados: ",1,1440);total=fechar_sessao(&baias[b],produtos,min,PRECO_HORA);if(total<0)puts("Falha ao fechar.");else printf("TOTAL: R$ %.2f\n",total);}
        else if(op==5) listar_produtos(produtos);
    }while(op!=0); return 0;
}
