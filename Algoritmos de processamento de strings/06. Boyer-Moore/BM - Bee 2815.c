// Programa em C - Algoritmo Boyer-Moore
#include <stdio.h>
#include <string.h>

#define ASIZE 256 // quantidade possível de diferentes caracteres no texto
// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

// Função do Caractere Ruim
void preBmBc(char *x, int m, int bmBc[]) {
   int i;
   
   // Inicializando todas as ocorrências como m
   for (i = 0; i < ASIZE; ++i)
      bmBc[i] = m;
   
   // Preechendo o valor da última ocorrência de um caractere
   for (i = 0; i < m - 1; ++i)
      bmBc[x[i]] = m - i - 1;
}

// Função calcula os sufixo para serem usadas na função do Bom Sufixo
void suffixes(char *x, int m, int *suff) {
   int f, g, i;
 
   suff[m - 1] = m;
   g = m - 1;
   for (i = m - 2; i >= 0; --i) {
      if (i > g && suff[i + m - 1 - f] < i - g)
         suff[i] = suff[i + m - 1 - f];
      else {
         if (i < g)
            g = i;
         f = i;
         while (g >= 0 && x[g] == x[g + m - 1 - f])
            --g;
         suff[i] = f - g;
      }
   }
}

// Função do Bom Sufixo
void preBmGs(char *x, int m, int bmGs[]) {
   int i, j, suff[m];
 
   suffixes(x, m, suff);
   
   // Inicializando todas as ocorrências como m
   for (i = 0; i < m; ++i)
      bmGs[i] = m;
   
   j = 0;
   for (i = m - 1; i >= 0; --i) {
      if (suff[i] == i + 1) {
         for (; j < m - 1 - i; ++j) {
            if (bmGs[j] == m)
               bmGs[j] = m - 1 - i;
         }
      }
   }
   for (i = 0; i <= m - 2; ++i)
      bmGs[m - 1 - suff[i]] = m - 1 - i;
}

// Função calcula o maior entre dois números
int MAX(int num1, int num2) {
   return (num1 > num2 ) ? num1 : num2;
}

// Verificando se as sílabas se repetem
int BM_gago(char x[], int m, char y[], int n) {
   int i, j, bmGs[m], bmBc[ASIZE], gago = 0;
 
   // Pré-processando
   preBmGs(x, m, bmGs);
   preBmBc(x, m, bmBc);
 
   // Buscando
   j = 0; // deslocamento do padrão em relação ao texto

   while (j <= n - m) {
      /* Percorrendo o padão da direita para a esquerda e
      o texto da esquerda para a direita */
      for (i = m - 1; i >= 0 && x[i] == y[i + j]; --i);

      /* Se o padrão tiver sido percorrido por completo,
      é registrada uma ocorrência dele no texto, se não 
      a busca continua*/
      if (i < 0) {
         gago++;
         /* Desolcando o padrão para que o próximo caractere no texto se
         alinhe com a última ocorrência dele no padrão */
         j += bmGs[0]; 
      } else
         /* Deslocando o padrão para que o caractere inválido no texto se
         alinhe com a última ocorrência dele no padrão (a função max é usada
         para garantir um deslocamento positivo: pode-se obter um deslocamento
         negativo se a última ocorrência de caractere ruim no padrão estiver
         no lado direito do caractere atual) */
         j += MAX(bmGs[i], bmBc[y[i + j]] - m + 1 + i);
   }

   return gago;
}

// Separando as palavras da frase e removendo as sílabas repetidas
void BM(char *x, int m, char *y, int n) {
   int i, j, bmGs[m], bmBc[ASIZE];
   int k = 0, l, tam_p = 0, tam_r = 0;
   char palavra[n], padrao[3];
   char resp[n];
 
   // Pré-processando
   preBmGs(x, m, bmGs);
   preBmBc(x, m, bmBc);
 
   // Buscando
   j = 0; // deslocamento do padrão em relação ao texto

   while (j <= n - m) {
      /* Percorrendo o padão da direita para a esquerda e
      o texto da esquerda para a direita */
      for (i = m - 1; i >= 0 && x[i] == y[i + j]; --i);

      /* Se o padrão tiver sido percorrido por completo,
      é registrada uma ocorrência dele no texto, se não 
      a busca continua*/
      if (i < 0) {
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
            if (BM_gago(padrao, strlen(padrao), palavra, tam_p) > 1) {
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

         /* Desolcando o padrão para que o próximo caractere no texto se
         alinhe com a última ocorrência dele no padrão */
         j += bmGs[0]; 
      } else
         /* Deslocando o padrão para que o caractere inválido no texto se
         alinhe com a última ocorrência dele no padrão (a função max é usada
         para garantir um deslocamento positivo: pode-se obter um deslocamento
         negativo se a última ocorrência de caractere ruim no padrão estiver
         no lado direito do caractere atual) */
         j += MAX(bmGs[i], bmBc[y[i + j]] - m + 1 + i);
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
   BM(x, strlen(x), y, strlen(y));
   return 0;
}