// Programa em C - Algoritmo Apostolico-Crochemore
#include <stdio.h>
#include <string.h>

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

// Nesse pré-processamento é feita a lista preKmp que auxilia para saber o que já foi comparado na string original
void preKmp(char *x, int m, int kmpNext[]) {
    int i, j;

    i = 0;
    j = kmpNext[0] = -1;
    while (i < m) {
        while (j > -1 && x[i] != x[j])
            j = kmpNext[j];
        i++;
        j++;
        if (x[i] == x[j])
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}

// Função calcula o maior entre dois números
int MAX(int num1, int num2) {
    return (num1 > num2 ) ? num1 : num2;
}

void AXAMAC(char *x, int m, char *y, int n) {
    int a, i, j, k, ell, kmpNext[m];

    // Pré-processando

    // Insere as informações na lista kmpNext
    preKmp(x, m, kmpNext);

    for (ell = 1; x[ell - 1] == x[ell]; ell++);
    if (ell == m)
        ell = 0;

    // Buscando
    i = ell;
    j = k = 0;
    while (j <= n - m) { // Enquanto j for menor que o tamanho da string menos o padrão
        while (i < m && x[i] == y[i + j])
            ++i;
        
        if (i >= m) {
            while (k < ell && x[k] == y[j + k])
                ++k;
            if (k >= ell) // Se caso k >= ell quer dizer que uma palavra foi encontrada 
                printf("Pattern found at index %d\n", j);
        }
        j += (i - kmpNext[i]);
        if (i == ell)
            k = MAX(0, k - 1);
        else {
            if (kmpNext[i] <= ell) {
                k = MAX(0, kmpNext[i]); // Pega o maior entre os dois
                i = ell;
            } else {
                k = ell;
                i = kmpNext[i];
            }
        }
    }
}

int main() {
    char *y = "GCATCGCAGAGAGTATACAGTACG";
    char *x = "GCAGAGAG";
    AXAMAC(x, strlen(x), y, strlen(y));
    return 0;
}