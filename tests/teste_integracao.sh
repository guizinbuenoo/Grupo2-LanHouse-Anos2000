#!/bin/sh
set -e
./lanhouse_cp1 < tests/entrada.txt > saida_teste.txt
grep -q "Baia ocupada com sucesso" saida_teste.txt
grep -q "Consumo registrado" saida_teste.txt
grep -q "Conta de Joao: R$ 12.50" saida_teste.txt
grep -q "Baia liberada" saida_teste.txt
echo "Checkpoint 1: teste de integracao OK"
