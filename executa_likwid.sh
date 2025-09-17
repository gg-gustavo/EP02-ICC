#!/bin/bash

PROG="resolveEDO"
# Métrica do LIKWID a ser utilizada
METRICA="FLOPS_DP"
# Core da CPU onde o programa será executado (fixo para consistência)
CPU=3
# Arquivo de entrada que será usado
INPUT_FILE="teste.dat"

make

# --- Executa o programa e captura a saída do LIKWID ---
# O LIKWID imprime a saída do seu programa e depois a sua própria tabela.
# Vamos capturar tudo em uma variável chamada OUTPUT.
echo "Executando o programa com LIKWID..."
OUTPUT=$(cat ${INPUT_FILE} | likwid-perfctr -C ${CPU} -g ${METRICA} -m ./${PROG})

echo "--------------------------------------------------"
echo "SAÍDA DO PROGRAMA:"
echo "--------------------------------------------------"

# --- Imprime a saída normal do programa ---
# O comando 'sed' abaixo remove a tabela de resultados do LIKWID,
# exibindo apenas a saída que o seu programa gerou.
echo "${OUTPUT}" | sed '/TABLE/q' | sed '$d'


echo "--------------------------------------------------"
echo "RESULTADO DO LIKWID:"
echo "--------------------------------------------------"

# --- Extrai e imprime APENAS a métrica que o enunciado pede ---
# O comando 'grep' encontra a linha exata que contém o contador.
echo "${OUTPUT}" | grep "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE"
echo "--------------------------------------------------"