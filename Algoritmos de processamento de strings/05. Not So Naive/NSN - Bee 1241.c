// Programa em C - Algoritmo Not So Naive
#include <stdio.h>
#include <string.h>

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

// O Not So Naive vai procurar de 1 em 1 caracter se as strings são iguais
// Se forem, ele vai posiciona em 2 casas, se não, ele muda 1 casa
// Isso tende a agilizar o processamento de buscar com novas casas e comparações que podem acontecer

void NSN(char *x, int m, char *y, int n) {
   int j, k, ell, verif = 0;
  
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
            x[0] == y[j]) {
            // Verificando se o padrão ocorre nos últimos dígitos do texto
            if (n == j+m) 
               printf("encaixa\n");
            else
               printf("nao encaixa\n");
            verif = 1;
         }
         j += ell;
      }
   }

   // Verificando se o padrão não ocorreu
   if (verif == 0)
      printf("nao encaixa\n");
}

int main() {
   char *y1 = "56234523485723854755454545478690";
   char *x1 = "78690";
   NSN(x1, strlen(x1), y1, strlen(y1));

   char *y2 = "5434554";
   char *x2 = "543";
   NSN(x2, strlen(x2), y2, strlen(y2));

   char *y3 = "1243";
   char *x3 = "1243";
   NSN(x3, strlen(x3), y3, strlen(y3));

   char *y4 = "54";
   char *x4 = "64545454545454545454545454545454554";
   NSN(x4, strlen(x4), y4, strlen(y4));

   return 0;
}