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
   int d, hx, hy, i, j, verif = 0;

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
      	// Verificando se o padrão ocorre nos últimos dígitos do texto
         if (n == j+m) 
            printf("encaixa\n");
         else
            printf("nao encaixa\n");
         verif = 1;
      }
   	hy = REHASH(y[j], y[j + m], hy);
   	++j;
	}

  	// Verificando se o padrão não ocorreu
   if (verif == 0)
      printf("nao encaixa\n");
}

int main() {
	char *y1 = "56234523485723854755454545478690";
   char *x1 = "78690";
   KR(x1, strlen(x1), y1, strlen(y1));

   char *y2 = "5434554";
   char *x2 = "543";
   KR(x2, strlen(x2), y2, strlen(y2));

   char *y3 = "1243";
   char *x3 = "1243";
   KR(x3, strlen(x3), y3, strlen(y3));

   char *y4 = "54";
   char *x4 = "64545454545454545454545454545454554";
   KR(x4, strlen(x4), y4, strlen(y4));

	return 0;
}