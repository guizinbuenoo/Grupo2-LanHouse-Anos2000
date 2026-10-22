# Casos de teste

| ID | Cenario | Resultado esperado |
|---|---|---|
| CT01 | Abrir baia livre | Sessao criada com codigo |
| CT02 | Abrir baia ocupada | Operacao rejeitada |
| CT03 | Consumir em baia livre | Operacao rejeitada |
| CT04 | Consumir sem estoque | Operacao rejeitada |
| CT05 | 90 minutos e 3 refrigerantes | Tempo R$ 18,00, produtos R$ 18,00, total R$ 36,00 |
| CT06 | Fechar sessao | Baia liberada e relatorio atualizado |
| CT07 | Salvar e carregar | Estado e estoque preservados |
| CT08 | Entrada alfabetica em campo numerico | Mensagem de erro e nova leitura |
| CT09 | Fluxo completo pelo menu | Comprovante e CSV criados |
