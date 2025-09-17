#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include <likwid.h>

#include "utils.h"
#include "edo.h"

int main() {
    fesetround(FE_DOWNWARD);

    EDo edo;
    Tridiag *sl;
    real_t *x, normaL2, tempo;
    int it;

    LIKWID_MARKER_INIT;

    scanf("%d", &edo.n);
    scanf("%lf %lf", &edo.a, &edo.b);
    scanf("%lf %lf", &edo.ya, &edo.yb);
    scanf("%lf %lf", &edo.p, &edo.q);

    x = (real_t *) calloc(edo.n, sizeof(real_t));

    while(scanf("%lf %lf %lf %lf", &edo.r1, &edo.r2, &edo.r3, &edo.r4) == 4)
    {
        sl = genTridiag(&edo);

        LIKWID_MARKER_START("GaussSeidel");
        tempo = timestamp();
        gaussSeidel(sl, x, &it, &normaL2);
        tempo = timestamp() - tempo;
        LIKWID_MARKER_STOP("GaussSeidel");

        // --- SAÍDA FORMATADA PARA O VERIFICADOR ---
        
        // A função prnEDOsl já imprime 'n' e a matriz aumentada [A|B]
        prnEDOsl(&edo);
        
        // Imprime o vetor solução Y
        for (int i = 0; i < sl->n; ++i) {
            printf(FORMAT, x[i]);
            printf(" ");
        }
        printf("\n");

        // Imprime as estatísticas finais
        printf("%d\n", it);
        printf(FORMAT, normaL2);
        printf("\n");
        printf("%.8e\n", tempo);
        
        // Libera a memória para o próximo laço
        free(sl->D); free(sl->Di); free(sl->Ds); free(sl->B); free(sl);
    }
    
    free(x);
    LIKWID_MARKER_CLOSE;
    return 0;
}