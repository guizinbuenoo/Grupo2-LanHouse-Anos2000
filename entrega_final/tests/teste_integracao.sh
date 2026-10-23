#!/bin/sh
set -e
rm -f data/lanhouse.dat data/operacoes.csv data/comprovante_*.txt
./lanhouse < tests/entrada_integracao.txt > data/saida_integracao.txt
grep -q "Sessao 1001 aberta com sucesso" data/saida_integracao.txt
grep -q "Consumo adicionado" data/saida_integracao.txt
grep -q "TOTAL: R$ 24.00" data/saida_integracao.txt
grep -q "Sessoes fechadas: 1" data/saida_integracao.txt
test -f data/comprovante_1001.txt
grep -q "TOTAL ...................... R$ 24.00" data/comprovante_1001.txt
test -f data/operacoes.csv
echo "Checkpoint final: teste de integracao OK"
