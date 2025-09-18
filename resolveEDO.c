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
    int edo_count = 1;

    LIKWID_MARKER_INIT;

    scanf("%d", &edo.n);
    scanf("%lf %lf", &edo.a, &edo.b);
    scanf("%lf %lf", &edo.ya, &edo.yb);
    scanf("%lf %lf", &edo.p, &edo.q);

    x = (real_t *) calloc(edo.n, sizeof(real_t));

    while(scanf("%lf %lf %lf %lf", &edo.r1, &edo.r2, &edo.r3, &edo.r4) == 4)
    {
        sl = genTridiag(&edo);

        char* marker = markerName("GaussSeidel", edo_count);

        LIKWID_MARKER_START(marker); // Usa o nome unico
        tempo = timestamp();
        gaussSeidel(sl, x, &it, &normaL2);
        tempo = timestamp() - tempo;
        LIKWID_MARKER_STOP(marker);  // Usa o nome unico

        free(marker);  
        edo_count++;    

        prnEDOsl(&edo);
        for (int i = 0; i < sl->n; ++i) {
            printf(FORMAT, x[i]);
            printf(" ");
        }
        printf("\n");
        printf("%d\n", it);
        printf(FORMAT, normaL2);
        printf("\n");
        printf("%.8e\n", tempo);
        
        free(sl->D); free(sl->Di); free(sl->Ds); free(sl->B); free(sl);
    }
    
    free(x);
    LIKWID_MARKER_CLOSE;
    return 0;
}