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

// Função que executa o pré-processamento e a fase de busca
void BM(char *x, int m, char *y, int n) {
   int i, j, bmGs[m], bmBc[ASIZE], verif = 0;
 
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
         // Verificando se o padrão ocorre nos últimos dígitos do texto
         if (n == j+m) 
            printf("encaixa\n");
         else
            printf("nao encaixa\n");
         verif = 1;

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

   // Verificando se o padrão não ocorreu
   if (verif == 0)
      printf("nao encaixa\n");
}

int main() {
   char *y1 = "56234523485723854755454545478690";
   char *x1 = "78690";
   BM(x1, strlen(x1), y1, strlen(y1));

   char *y2 = "5434554";
   char *x2 = "543";
   BM(x2, strlen(x2), y2, strlen(y2));

   char *y3 = "1243";
   char *x3 = "1243";
   BM(x3, strlen(x3), y3, strlen(y3));

   char *y4 = "54";
   char *x4 = "64545454545454545454545454545454554";
   BM(x4, strlen(x4), y4, strlen(y4));

   return 0;
}