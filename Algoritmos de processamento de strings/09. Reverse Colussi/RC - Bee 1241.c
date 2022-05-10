// Programa em C - Algoritmo Reverse Colussi
#include <stdio.h>
#include <string.h>

#define ASIZE 256 // quantidade possível de diferentes caracteres no texto
// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

void preRc(char *x, int m, int h[],
           int rcBc[ASIZE][m], int rcGs[]) {
   int a, i, j, k, q, r, s,
       hmin[m], kmin[m], link[m],
       locc[ASIZE], rmin[m];
 
   // Computação de link e locc
   for (a = 0; a < ASIZE; ++a)
      locc[a] = -1;
   link[0] = -1;
   for (i = 0; i < m - 1; ++i) {
      link[i + 1] = locc[x[i]];
      locc[x[i]] = i;
   }
 
   // Computação de rcBc
   for (a = 0; a < ASIZE; ++a)
      for (s = 1; s <= m; ++s) {
         i = locc[a];
         j = link[m - s];
         while (i - j != s && j >= 0)
            if (i - j > s)
               i = link[i + 1];
            else
               j = link[j + 1];
         while (i - j > s)
            i = link[i + 1];
         rcBc[a][s] = m - i - 1;
      }
 
   // Computação de hmin
   k = 1;
   i = m - 1;
   while (k <= m) {
      while (i - k >= 0 && x[i - k] == x[i])
         --i;
      hmin[k] = i;
      q = k + 1;
      while (hmin[q - k] - (q - k) > i) {
         hmin[q] = hmin[q - k];
         ++q;
      }
      i += (q - k);
      k = q;
      if (i == m)
         i = m - 1;
   }
 
   // Computação de kmin
   memset(kmin, 0, m * sizeof(int));
   for (k = m; k > 0; --k)
      kmin[hmin[k]] = k;
 
   // Computação de rmin
   for (i = m - 1; i >= 0; --i) {
      if (hmin[i + 1] == i)
         r = i + 1;
      rmin[i] = r;
   }
 
   // Computação de rcGs
   i = 1;
   for (k = 1; k <= m; ++k)
      if (hmin[k] != m - 1 && kmin[hmin[k]] == k) {
         h[i] = hmin[k];
         rcGs[i++] = k;
      }
   i = m-1;
   for (j = m - 2; j >= 0; --j)
      if (kmin[j] == 0) {
         h[i] = j;
         rcGs[i--] = rmin[j];
      }
   rcGs[m] = rmin[0];
}
 
 
void RC(char *x, int m, char *y, int n) {
   int i, j, s, rcBc[ASIZE][m], rcGs[m], h[m], verif = 0;
 
   // Pré-processando
   preRc(x, m, h, rcBc, rcGs);
 
   // Buscando
   j = 0;
   s = m;
   while (j <= n - m) {
      while (j <= n - m && x[m - 1] != y[j + m - 1]) {
         s = rcBc[y[j + m - 1]][s];
         j += s;
      }
      for (i = 1; i < m && x[h[i]] == y[j + h[i]]; ++i);
      if (i >= m) {
         printf("Pattern found at index %d\n", j);
         // Verificando se o padrão ocorre nos últimos dígitos do texto
         if (n == j+m) 
            printf("encaixa\n");
         else
            printf("nao encaixa\n");
         verif = 1;
      }
      s = rcGs[i];
      j += s;
   }

   // Verificando se o padrão não ocorreu
   if (verif == 0)
      printf("nao encaixa\n");
}

int main() {
   char *y1 = "56234523485723854755454545478690";
   char *x1 = "78690";
   RC(x1, strlen(x1), y1, strlen(y1));

   char *y2 = "5434554";
   char *x2 = "543";
   RC(x2, strlen(x2), y2, strlen(y2));

   char *y3 = "1243";
   char *x3 = "1243";
   RC(x3, strlen(x3), y3, strlen(y3));

   char *y4 = "54";
   char *x4 = "64545454545454545454545454545454554";
   RC(x4, strlen(x4), y4, strlen(y4));

	return 0;
}