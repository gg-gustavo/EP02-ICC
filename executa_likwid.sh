#!/bin/bash

# --- Variáveis de Configuração ---
PROG="resolveEDO"
METRICA="FLOPS_DP"
CPU=3
INPUT_FILE="teste.dat"
CSV_OUTPUT="likwid_results.tmp.csv"

# --- Variável para o Contador do LIKWID ---
CONTADOR="FP_ARITH_INST_RETIRED_SCALAR_DOUBLE"

# --- Compila o programa (se necessário) ---
make

echo "--------------------------------------------------"
echo "SAIDA DO PROGRAMA:"
echo "--------------------------------------------------"

# --- Execução ---
cat ${INPUT_FILE} | likwid-perfctr -C ${CPU} -g ${METRICA} -m -o ${CSV_OUTPUT} -f ./${PROG}

echo
echo "--------------------------------------------------"
echo "SAIDA LIKWID"
echo "--------------------------------------------------"

# --- Processamento CORRIGIDO ---
awk -F',' -v var="$CONTADOR" '$1 ~ var {print $1 "," $3}' ${CSV_OUTPUT}

rm -f ${CSV_OUTPUT}
echo "--------------------------------------------------"
