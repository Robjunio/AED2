// Programa em C - Algoritmo Karp-Rabin
#include <stdio.h>
#include <string.h>

// Função hash
#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b))

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

// Verificando se as sílabas se repetem
int KR_gago(char *x, int m, char *y, int n) {
   int d, hx, hy, i, j, gago = 0;

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
         gago++;
      hy = REHASH(y[j], y[j + m], hy);
      ++j;
   }

   return gago;
}

/* O algoritmo KR necessita ver a referência do comprimento das strings
para fazer a comparação do valor do hash com o elas. Assim, ele determina 
onde aquele comprimento se encaixa no texto e se é igual ao padrão */
// Separando as palavras da frase e removendo as sílabas repetidas
void KR(char *x, int m, char *y, int n) {
   int d, hx, hy, i, j, k = 0, l, tam_p = 0, tam_r = 0;
   char palavra[n], padrao[3];
   char resp[n];

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
      if (hx == hy && memcmp(x, y + j, m) == 0) {
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
            if (KR_gago(padrao, strlen(padrao), palavra, tam_p) > 1) {
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
      hy = REHASH(y[j], y[j + m], hy);
      ++j;
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
   KR(x, strlen(x), y, strlen(y));
   return 0;
}