// Programa em C - Algoritmo Reverse Colussi
#include <stdio.h>
#include <string.h>

#define ASIZE 256 // quantidade possível de diferentes caracteres no texto
// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

/* A função preRc é para o pré-processamento dos componentes,
computando na tabela que vai ser fatorado em sufixo e começa 
a agilizar a organização para a procura */
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

// Verificando se as sílabas se repetem
int RC_gago(char *x, int m, char *y, int n) {
   int i, j, s, rcBc[ASIZE][m], rcGs[m], h[m], gago = 0;
 
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
      if (i >= m)
         gago++;
      s = rcGs[i];
      j += s;
   }

   return gago;
}

/* A função principal da RC funciona agiliazando o passo na procura
de strings dos quais os sufixos vão esta organizados nas tabelas */
// Separando as palavras da frase e removendo as sílabas repetidas
void RC(char *x, int m, char *y, int n) {
   int i, j, s, rcBc[ASIZE][m], rcGs[m], h[m], k = 0, l, tam_p = 0, tam_r = 0;
   char palavra[n], padrao[3];
   char resp[n];

 
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
         for (; k < j; k++) {
            palavra[tam_p] = y[k];
            tam_p++;
         }
         k = j+1;
         
         // Verificando se a palavra tem mais de 4 letras
         if (tam_p >= 4) {
            for (l = 0; l < 2; l++)
               padrao[l] = palavra[l];

            /* Verifica se as duas primeiras letras são repetidas e adiciona
            o texto correto a resp */
            if (RC_gago(padrao, strlen(padrao), palavra, tam_p) > 1) {
               for (l = 2; l < tam_p; l++) {
                  resp[tam_r] = palavra[l];
                  tam_r++;
               }
            } else {
               for (l = 0; l < tam_p; l++) {
                  resp[tam_r] = palavra[l];
                  tam_r++;
               }
            }
         } else {
            for (l = 0; l < tam_p; l++) {
               resp[tam_r] = palavra[l];
               tam_r++;
            }
         }

         resp[tam_r] = ' ';
         tam_r++;
         tam_p = 0;
      }
      s = rcGs[i];
      j += s;
   }

   for (; k < n; k++) {
      resp[tam_r] = y[k];
      tam_r++;
   }
   printf("%s\n", resp);
}

int main() {
   char *y = "Juca comprou fafarinha na memercearia e papagou 4 reais o quilo. A mamae de Juca pediu para ele comprar mamais 2 quilos.";
   char *x = " ";
   RC(x, strlen(x), y, strlen(y));
   return 0;
}