// Programa em C - Algoritmo Apostolico-Crochemore
#include <stdio.h>
#include <string.h>

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

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
    int verif = 0;

    // Pré-processando
    preKmp(x, m, kmpNext);

    for (ell = 1; x[ell - 1] == x[ell]; ell++);
    if (ell == m)
        ell = 0;

    // Buscando
    i = ell;
    j = k = 0;
    while (j <= n - m) {
        while (i < m && x[i] == y[i + j])
            ++i;
        
        if (i >= m) {
            while (k < ell && x[k] == y[j + k])
                ++k;
            if (k >= ell){
                // Verificando se o padrão ocorre nos últimos dígitos do texto
                if (n == j+m) 
                    printf("encaixa\n");
                else
                    printf("nao encaixa\n");
                verif = 1;
            }
        }
        j += (i - kmpNext[i]);
        if (i == ell)
            k = MAX(0, k - 1);
        else {
            if (kmpNext[i] <= ell) {
                k = MAX(0, kmpNext[i]);
                i = ell;
            } else {
                k = ell;
                i = kmpNext[i];
            }
        }
    }
    if (verif == 0)
        printf("nao encaixa\n");
}

int main() {
   char *y1 = "56234523485723854755454545478690";
   char *x1 = "78690";
   AXAMAC(x1, strlen(x1), y1, strlen(y1));

   char *y2 = "5434554";
   char *x2 = "543";
   AXAMAC(x2, strlen(x2), y2, strlen(y2));

   char *y3 = "1243";
   char *x3 = "1243";
   AXAMAC(x3, strlen(x3), y3, strlen(y3));

   char *y4 = "54";
   char *x4 = "64545454545454545454545454545454554";
   AXAMAC(x4, strlen(x4), y4, strlen(y4));

   return 0;
}