#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "edo.h"

// Gera o sistema linear tridiagonal a partir dos parâmetros da EDO.
Tridiag *genTridiag (EDo *edo)
{
  Tridiag *sl;
  real_t x, rx;
  int n = edo->n;
  
  sl = (Tridiag *) malloc (sizeof(Tridiag));
  sl->n = edo->n;

  sl->D = (real_t *) calloc(n, sizeof(real_t));
  sl->Di = (real_t *) calloc(n, sizeof(real_t));
  sl->Ds = (real_t *) calloc(n, sizeof(real_t));
  sl->B = (real_t *) calloc(n, sizeof(real_t));

  real_t h = (edo->b - edo->a)/(n+1);

  for (int i=0; i < n; ++i) {
    x = edo->a + (i+1)*h;
    rx = edo->r1*x + edo->r2*x*x + edo->r3*cos(x) + edo->r4*exp(x);
    
    sl->B[i] = h*h * rx;
    sl->Di[i] = 1.0 - (h * edo->p / 2.0);
    sl->D[i] = -2.0 + (h*h * edo->q);
    sl->Ds[i] = 1.0 + (h * edo->p / 2.0);
  }

  sl->B[0] -= edo->ya * (1.0 - h*edo->p/2.0);
  sl->B[n-1] -= edo->yb * (1.0 + h*edo->p/2.0);
  
  return sl;
}

// Exibe SL na saída padrão 
void prnEDOsl (EDo *edoeq)
{
  int n = edoeq->n, i, j;
  real_t x, b, d, di, ds,rx;
  real_t h = (edoeq->b - edoeq->a)/(n+1);

  printf ("%d\n", n);

  for (i=0; i < n; ++i) {
    x = edoeq->a + (i+1)*h;
    rx = edoeq->r1*x + edoeq->r2*x*x + edoeq->r3*cos(x) + edoeq->r4*exp(x);
    
    b = h*h * rx; 
    di = 1 - h * edoeq->p/2.0;
    d = -2 + h*h * edoeq->q;
    ds = 1 + h * edoeq->p/2.0;
      
    for (j=0; j < n; ++j) {
      if (i == j)
	      printf (FORMAT,d);
      else if (j == i-1)
	      printf (FORMAT,di);
      else if (j == i+1)
	      printf (FORMAT,ds);
      else
	      printf(FORMAT, 0.0);
      printf(" ");
    }
      
    if (i == 0)
      b -= edoeq->ya * (1 - h*edoeq->p/2.0);
    else if (i == n-1)
      b -= edoeq->yb * (1 + h*edoeq->p/2.0);

    printf (FORMAT, b);
    printf ("\n");
  }
}

// *** IMPLEMENTAÇÃO DE GAUSS-SEIDEL ***
void gaussSeidel (Tridiag *sl, real_t *x, int *it, real_t *normaL2)
{
    const int max_iter = 100;
    const real_t tol = 1.0e-5;
    int n = sl->n;
    real_t *residuo = (real_t *) calloc(n, sizeof(real_t));

    // Inicializa o vetor solução x com zeros
    for(int i = 0; i < n; ++i) {
        x[i] = 0.0;
    }

    // Laço principal das iterações
    for (*it = 1; *it <= max_iter; ++(*it)) {
        // Calcula a nova solução x^(k+1) usando x^(k) e os valores já atualizados
        if (n > 0) {
            // Primeira linha do sistema
            x[0] = (sl->B[0] - sl->Ds[0] * x[1]) / sl->D[0];

            // Linhas intermediárias
            for (int i = 1; i < n - 1; ++i) {
                x[i] = (sl->B[i] - sl->Di[i] * x[i-1] - sl->Ds[i] * x[i+1]) / sl->D[i];
            }

            // Última linha do sistema
            if (n > 1) {
                x[n-1] = (sl->B[n-1] - sl->Di[n-1] * x[n-2]) / sl->D[n-1];
            }
        }
        
        // --- Cálculo do Critério de Parada (Norma L2 do Resíduo) ---
        *normaL2 = 0.0;
        // Calcula o resíduo: r = B - Ax
        for (int i = 0; i < n; ++i) {
            real_t ax = sl->D[i] * x[i];
            if (i > 0) ax += sl->Di[i] * x[i-1];
            if (i < n - 1) ax += sl->Ds[i] * x[i+1];
            residuo[i] = sl->B[i] - ax;
            *normaL2 += residuo[i] * residuo[i];
        }
        *normaL2 = sqrt(*normaL2);

        // Se o resíduo for pequeno o suficiente, para o método
        if (*normaL2 <= tol) {
            break;
        }
    }
    free(residuo);
}