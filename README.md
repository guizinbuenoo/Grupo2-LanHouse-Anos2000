# Checkpoint 1 — Arquitetura inicial e controle básico de baias

## Objetivo da etapa

O primeiro checkpoint estabelece a base do sistema da lan house.

Nesta etapa, o foco é representar as baias, construir o menu e implementar o fluxo inicial de atendimento. Ainda não existe um catálogo de produtos nem cobrança por tempo.

A proposta é demonstrar que o programa consegue manter informações sobre a ocupação dos computadores e executar operações básicas de maneira organizada.

## O que esta versão faz

O sistema trabalha com oito baias e oferece as seguintes operações:

1. Listar as baias.
2. Ocupar uma baia.
3. Registrar um valor de consumo.
4. Liberar uma baia.
5. Encerrar o programa.

As informações permanecem na memória durante a execução. Ao fechar o programa, os dados dessa versão são perdidos.

## Representação dos dados

Cada baia é representada pela estrutura `Baia`.

Ela possui os campos:

| Campo | Finalidade |
|---|---|
| `ocupada` | Indica se a baia está em utilização. |
| `cliente` | Armazena o nome do cliente associado à baia. |
| `consumo` | Armazena o valor acumulado de consumo. |

O programa utiliza um vetor dessas estruturas para representar as oito baias.

Essa organização permite que cada posição do vetor mantenha as informações de um computador.

## Funcionamento das operações

### Listagem das baias

A listagem percorre o vetor e apresenta a situação de cada baia.

Quando uma baia está livre, o programa informa sua disponibilidade. Quando está ocupada, também apresenta o cliente e o valor acumulado de consumo.

Essa consulta permite que o operador identifique onde pode iniciar um novo atendimento.

### Ocupação de uma baia

O operador informa o número da baia e o nome do cliente.

Antes de registrar o atendimento, o programa verifica se a baia já está ocupada.

Se estiver disponível, o cliente é associado à baia, o estado passa para ocupado e o consumo é iniciado em zero.

Se já estiver em utilização, a operação é rejeitada.

### Registro de consumo

Nesta primeira versão, o consumo é informado diretamente como um valor monetário.

O operador escolhe a baia e informa quanto deve ser acrescentado à conta.

O programa verifica se a baia está ocupada antes de registrar o consumo. Isso impede que valores sejam associados a um atendimento inexistente.

Ainda não há identificação de produto, quantidade ou movimentação de estoque.

### Liberação da baia

O operador informa a baia que deseja liberar.

O sistema apresenta o nome do cliente e o valor total de consumo. Em seguida, limpa os dados daquela baia, tornando-a disponível para outro atendimento.

Nesta etapa, o valor apresentado corresponde somente ao consumo registrado. Não existe cobrança por tempo.

## Fluxo de utilização

Um atendimento pode ocorrer da seguinte forma:

1. O operador consulta as baias.
2. Escolhe uma baia livre.
3. Registra o nome do cliente.
4. Acrescenta valores de consumo durante o atendimento.
5. Consulta novamente a situação da baia.
6. Libera a baia e visualiza o valor acumulado.

### Exemplo

Um cliente ocupa a baia 1.

Durante o atendimento, são registrados R$ 7,50 e depois R$ 5,00 de consumo.

Ao liberar a baia, o programa apresenta R$ 12,50 como valor da conta e limpa os dados para o próximo cliente.

## Organização do código

A implementação principal está em `src/main.c`.

As responsabilidades são distribuídas entre a função principal e funções auxiliares:

- `ler_int`: realiza a leitura de números inteiros dentro de uma faixa.
- `ler_double`: realiza a leitura do valor de consumo.
- `ler_texto`: recebe o nome do cliente.
- `listar`: apresenta a situação das baias.
- `main`: controla o menu e o fluxo das operações.

As funções de leitura evitam repetir o mesmo tratamento de entrada em diferentes partes do programa.

## Regras e validações

- O número da baia deve estar entre 1 e 8.
- Uma baia ocupada não pode receber outro cliente.
- O registro de consumo exige uma baia ocupada.
- A liberação exige uma baia ocupada.
- O valor de consumo deve ser de pelo menos R$ 0,01.
- As opções do menu devem respeitar a faixa apresentada.

## Conceitos aplicados

- `struct`.
- Vetor de estruturas.
- Funções.
- Entrada e saída.
- Condições.
- Repetição.
- Manipulação de strings.
- Inicialização e limpeza de dados.

## Limitações desta etapa

Esta versão ainda não possui:

- Catálogo de produtos.
- Quantidade de itens consumidos.
- Controle de estoque.
- Cobrança por tempo.
- Relatório financeiro.
- Ordenação.
- Persistência em arquivo.

Esses recursos são tratados nas etapas seguintes.

## Relação com o GitHub

O checkpoint representa a arquitetura inicial do projeto e serve como referência para acompanhar as próximas mudanças.

O repositório deve registrar essa etapa, permitindo comparar sua implementação com as versões posteriores.

## Execução

No Dev-C++, abra `LanHouse_CP1.dev` e utilize a opção de compilar e executar.

Em um ambiente com GCC e Make:

```bash
make
./lanhouse_cp1
```

## Teste disponível

O teste de integração executa um atendimento pelo menu, incluindo:

- Ocupação de uma baia.
- Registro de consumo.
- Consulta da situação.
- Fechamento e liberação.

Para executar:

```bash
make test
```

## Resultado da etapa

Ao final deste checkpoint, o sistema já representa o atendimento básico de uma lan house, mantendo a associação entre baia, cliente e consumo durante a execução.