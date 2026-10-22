#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "lanhouse.h"
int main(void){Baia b[TOTAL_BAIAS];Produto p[TOTAL_PRODUTOS];double t;inicializar(b,p);assert(abrir_sessao(&b[0],"Ana"));assert(!abrir_sessao(&b[0],"Bia"));assert(adicionar_consumo(&b[0],p,1,2));assert(p[0].estoque==18);t=fechar_sessao(&b[0],p,60,12.0);assert(fabs(t-24.0)<0.001);assert(!b[0].sessao.ativa);puts("Checkpoint 2: testes unitarios OK");return 0;}
