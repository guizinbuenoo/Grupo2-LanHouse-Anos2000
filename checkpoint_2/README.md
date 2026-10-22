# Checkpoint 2 - Modularizacao

Evolucao com arquivos `.h`/`.c`, estruturas, catalogo de produtos, estoque, itens consumidos e cobranca proporcional do tempo.

Regra: valor do tempo = minutos / 60 x R$ 12,00. O total soma tempo e produtos consumidos.

Comandos: `make`, `make test` e `make clean`.

As operacoes de abertura de sessao, inclusao de consumo e fechamento funcionam como modulos de cadastro. As funcoes `listar_baias` e `listar_produtos` ficam separadas das regras de negocio em `src/lanhouse.c`.

No Dev-C++, abra `LanHouse_CP2.dev` e pressione F11.
