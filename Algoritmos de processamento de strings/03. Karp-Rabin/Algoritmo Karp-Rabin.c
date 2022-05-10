// Programa em C - Algoritmo Karp-Rabin
#include <stdio.h>
#include <string.h>

// Função hash
#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b))

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

/* O algoritmo KR necessita ver a referência do comprimento das strings
para fazer a comparação do valor do hash com o elas. Assim, ele determina 
onde aquele comprimento se encaixa no texto e se é igual ao padrão */
void KR(char *x, int m, char *y, int n) {
   int d, hx, hy, i, j;

   // Pré-processando
   // Calcula d = 2^(m-1) com o operados de deslocamento à esquerda
   for (d = i = 1; i < m; ++i)
      d = (d<<1);

   for (hy = hx = i = 0; i < m; ++i) {
      hx = ((hx<<1) + x[i]);
      hy = ((hy<<1) + y[i]);
   }

   // Buscando
   j = 0;
   while (j <= n-m) {
      if (hx == hy && memcmp(x, y + j, m) == 0)
         printf("Pattern found at index %d\n", j);
      hy = REHASH(y[j], y[j + m], hy);
      ++j;
   }
}

int main() {
   char *y = "ABCCDDAEFG";
   char *x = "CDD";
   KR(x, strlen(x), y, strlen(y));
   return 0;
}