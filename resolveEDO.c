#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h> // Para fesetround

#include "utils.h"
#include "edo.h"

int main() {
    // Define o arredondamento para baixo, conforme o enunciado
    fesetround(FE_DOWNWARD);

    EDo edo;
    Tridiag *sl;
    real_t *x, normaL2, tempo;
    int it;

    // Lê os parâmetros da EDO que são fixos para todos os casos
    scanf("%d", &edo.n);
    scanf("%lf %lf", &edo.a, &edo.b);
    scanf("%lf %lf", &edo.ya, &edo.yb);
    scanf("%lf %lf", &edo.p, &edo.q);

    // Aloca memória para o vetor solução
    x = (real_t *) calloc(edo.n, sizeof(real_t));

    // Laço para ler e resolver cada caso de função r(x)
    while(scanf("%lf %lf %lf %lf", &edo.r1, &edo.r2, &edo.r3, &edo.r4) == 4)
    {
        // 1. Gera o sistema linear tridiagonal para a EDO atual
        sl = genTridiag(&edo);

        // 2. Mede o tempo e resolve o sistema com Gauss-Seidel
        tempo = timestamp();
        gaussSeidel(sl, x, &it, &normaL2);
        tempo = timestamp() - tempo;

        // 3. Imprime os resultados no formato exigido
        prnEDOsl(&edo);
        
        for (int i = 0; i < sl->n; ++i) {
            printf(FORMAT, x[i]);
            printf(" ");
        }
        printf("\n");

        printf("%d\n", it);
        printf(FORMAT, normaL2);
        printf("\n");
        printf("%.8e\n\n", tempo);
        
        // Libera a memória do sistema linear atual antes de ler o próximo
        free(sl->D);
        free(sl->Di);
        free(sl->Ds);
        free(sl->B);
        free(sl);
    }
    
    free(x); // Libera o vetor solução no final
    return 0;
}