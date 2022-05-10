// Programa em C - Algoritmo Not So Naive
#include <stdio.h>
#include <string.h>

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

// O Not So Naive vai procurar de 1 em 1 caracter se as strings são iguais
// Se forem, ele vai posiciona em 2 casas, se não, ele muda 1 casa
// Isso tende a agilizar o processamento de buscar com novas casas e comparações que podem acontecer

void NSN(char *x, int m, char *y, int n) {
   int j, k, ell;
  
   // Pré-processando
   if (x[0] == x[1]) {
      k = 2;
      ell = 1;
   } else {
      k = 1;
      ell = 2;
   }
  
   // Buscando
   j = 0;
   while (j <= n - m) {
      if (x[1] != y[j + 1])
         j += k;
      else {
         if (memcmp(x + 2, y + j + 2, m - 2) == 0 &&
            x[0] == y[j])
            printf("Pattern found at index %d\n", j);
         j += ell;
      }
   }
}

int main() {
   char *y = "GCATCGCAGAGAGTATACAGTACG";
   char *x = "GCAGAGAG";
   NSN(x, strlen(x), y, strlen(y));
   return 0;
}