// Programa em C - Algoritmo Força Bruta
#include <stdio.h>
#include <string.h>

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

void BF(char *x, int m, char *y, int n) {
   int i, j;

   // Procura em todas as casas da string y e compara com as casas da string x
   // Essa aplicação gera todas as possiveis soluções para formar a palavra
    for (j = 0; j <= n - m; ++j) {
        for (i = 0; i < m && x[i] == y[i + j]; ++i);
        if (i >= m)
            printf("Pattern found at index %d\n", j);
    }
}

int main() {
    char *y = "CATAACTAAC";
    char *x = "ACT";
    BF(x, strlen(x), y, strlen(y));
    return 0;
}