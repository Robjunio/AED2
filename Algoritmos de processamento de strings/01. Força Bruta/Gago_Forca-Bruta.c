// Programa em C - Algoritmo força-bruta
#include <stdio.h>
#include <string.h>

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto
int BF_gago(char *x, int m, char *y, int n) {
    int i, j, gago = 0;

    // Procura em todas as casas da string y e compara com as casas da string x
    // Essa aplicação gera todas as possiveis soluções para formar a palavra
    for (j = 0; j <= n - m; ++j) {
        for (i = 0; i < m && x[i] == y[i + j]; ++i);
        if (i >= m)
            gago++;
    }
    return gago;
}
void BF(char *x, int m, char *y, int n) {
   int i, j, verif = 0;
   int k = 0, l, tam_p = 0, tam_r = 0;
   char palavra[n], padrao[3];
   char resp[n];

   // Procura em todas as casas da string y e compara com as casas da string x
   // Essa aplicação gera todas as possiveis soluções para formar a palavra
    for (j = 0; j <= n - m; ++j) {
        for (i = 0; i < m && x[i] == y[i + j]; ++i);
        if (i >= m){
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
                if (BF_gago(padrao, strlen(padrao), palavra, tam_p) > 1) {
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
   BF(x, strlen(x), y, strlen(y));
   return 0;
}