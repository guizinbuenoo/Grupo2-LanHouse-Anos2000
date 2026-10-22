#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "lanhouse.h"
#include "storage.h"
int main(void){Sistema s,l;Fechamento f;unsigned long c;const char*arq="data/teste_estado.dat";remove(arq);sistema_inicializar(&s);assert(s.magic==APP_MAGIC);assert(abrir_sessao(&s,1,"Carlos Silva",&c));assert(c==1001);assert(!abrir_sessao(&s,1,"Outro",NULL));assert(adicionar_consumo(&s,1,1,2));assert(adicionar_consumo(&s,1,1,1));assert(s.produtos[0].estoque==17);assert(fabs(total_consumo_sessao(&s,1)-18.0)<0.001);assert(!adicionar_consumo(&s,2,1,1));assert(fechar_sessao(&s,1,90,&f));assert(fabs(f.tempo-18.0)<0.001);assert(fabs(f.produtos-18.0)<0.001);assert(fabs(f.total-36.0)<0.001);assert(!s.baias[0].sessao.ativa);assert(s.sessoes_fechadas==1);assert(salvar_sistema(arq,&s));memset(&l,0,sizeof l);assert(carregar_sistema(arq,&l));assert(l.sessoes_fechadas==1);assert(l.produtos[0].estoque==17);assert(repor_estoque(&l,1,3));assert(l.produtos[0].estoque==20);remove(arq);puts("Checkpoint final: testes unitarios e persistencia OK");return 0;}
