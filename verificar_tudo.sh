#!/bin/sh
set -eu
RAIZ=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

executar() {
    nome=$1
    pasta=$2
    echo "=== $nome ==="
    cd "$RAIZ/$pasta"
    make clean
    make
    make test
}

executar "CHECKPOINT 1" checkpoint_1
executar "CHECKPOINT 2" checkpoint_2
executar "CHECKPOINT 3" checkpoint_3
executar "ENTREGA FINAL" entrega_final

echo "=== TODOS OS PACOTES FORAM APROVADOS ==="
