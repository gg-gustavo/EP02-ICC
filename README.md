## EP-02: Solução de Equações Diferenciais Ordinárias

* **Aluno:** GUSTAVO GABRIEL RIPKA
* **GRR:** 20203935

## Sobre o Trabalho

Este trabalho implementa um programa em C para resolver Equações Diferenciais Ordinárias (EDOs) de segunda ordem com Problema de Valor de Contorno (PVC).

O método utilizado consiste em duas etapas principais:
1.  **Método das Diferenças Finitas:** A EDO é discretizada e transformada em um sistema de equações lineares com uma matriz de coeficientes tridiagonal.
2.  **Método de Gauss-Seidel:** O sistema linear tridiagonal resultante é resolvido de forma iterativa para encontrar a solução aproximada da EDO nos pontos da malha.

O programa também foi instrumentado com a biblioteca LIKWID para permitir a análise de performance do método de Gauss-Seidel.

## Arquivos do Projeto

* `resolveEDO.c`: Programa principal que contém a função `main`. É responsável por ler os dados de entrada, orquestrar a chamada das funções e imprimir os resultados.
* `edo.h`: Arquivo de cabeçalho que define as estruturas de dados (`EDo`, `Tridiag`) e as assinaturas das funções da biblioteca.
* `edo.c`: Biblioteca com a implementação das funções principais:
    * `genTridiag()`: Gera o sistema linear tridiagonal a partir dos parâmetros da EDO.
    * `gaussSeidel()`: Resolve o sistema linear pelo método iterativo.
    * `prnEDOsl()`: Imprime a matriz aumentada do sistema.
* `utils.h` / `utils.c`: Funções utilitárias fornecidas, como `timestamp()`.
* `Makefile`: Automatiza a compilação do projeto e a execução de testes.
* `executa_likwid.sh`: Script para executar o programa com o LIKWID e formatar a saída de performance conforme o enunciado.

## Como Compilar e Executar

### Compilação

Para compilar todo o projeto, basta executar o comando na raiz do diretório:
```bash
make
````

### Execução Padrão

O programa lê os dados da entrada padrão. Para executar com um arquivo de dados (como `teste.dat`):

```bash
cat teste.dat | ./resolveEDO
```

### Teste de Formato (Recomendado)

Para verificar se a saída do programa está no formato exato esperado pelo sistema de correção automática:

```bash
make testeFormato
```

### Execução com LIKWID

Para executar o programa e obter as métricas de performance do LIKWID, utilize o script fornecido:

```bash
./executa_likwid.sh
```
## Limitações do Programa

  * **Convergência do Método:** A convergência do método de Gauss-Seidel não é garantida para todos os tipos de sistemas lineares. A implementação atual não verifica se a matriz do sistema é de diagonal dominante, critério que garante a convergência.
  * **Formato de Entrada:** O programa espera um formato de entrada estrito, conforme definido no enunciado. Qualquer desvio neste formato pode levar a erros de leitura ou comportamento inesperado.
  * **Ambiente de Execução (LIKWID):** O script `executa_likwid.sh` foi configurado e validado para o ambiente do laboratório DINF na máquina **i40 do LAB3 (arquitetura Intel Coffee Lake)**. A execução em outras máquinas pode exigir a alteração das variáveis `CONTADOR` e `METRICA` no script para o nome correto do contador de performance da arquitetura específica.