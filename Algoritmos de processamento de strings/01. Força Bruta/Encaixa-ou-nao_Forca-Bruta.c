// Programa em C - Algoritmo força-bruta
#include <stdio.h>
#include <string.h>

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

void BF(char *x, int m, char *y, int n) {
   int i, j, verif = 0;

   // Procura em todas as casas da string y e compara com as casas da string x
   // Essa aplicação gera todas as possiveis soluções para formar a palavra
    for (j = 0; j <= n - m; ++j) {
        for (i = 0; i < m && x[i] == y[i + j]; ++i);
        if (i >= m){
            // Verificando se o padrão ocorre nos últimos dígitos do texto
            if (n == j+m) 
                printf("encaixa\n");
            else
                printf("nao encaixa\n");
            verif = 1;
        }
    }
    if (verif == 0)
        printf("nao encaixa\n");
}

int main() {
   char *y1 = "56234523485723854755454545478690";
   char *x1 = "78690";
   BF(x1, strlen(x1), y1, strlen(y1));

   char *y2 = "5434554";
   char *x2 = "543";
   BF(x2, strlen(x2), y2, strlen(y2));

   char *y3 = "1243";
   char *x3 = "1243";
   BF(x3, strlen(x3), y3, strlen(y3));

   char *y4 = "54";
   char *x4 = "64545454545454545454545454545454554";
   BF(x4, strlen(x4), y4, strlen(y4));

   return 0;
}