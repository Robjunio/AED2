// Programa em C - Algoritmo Apostolico-Crochemore
#include <stdio.h>
#include <string.h>

// x = padrão; y = texto; m = tamanho do padrão; n = tamanho do texto

void preKmp(char *x, int m, int kmpNext[]) {
    int i, j;

    i = 0;
    j = kmpNext[0] = -1;
    while (i < m) {
        while (j > -1 && x[i] != x[j])
            j = kmpNext[j];
        i++;
        j++;
        if (x[i] == x[j])
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}

// Função calcula o maior entre dois números
int MAX(int num1, int num2) {
    return (num1 > num2 ) ? num1 : num2;
}
int AXAMAC_gago(char *x, int m, char *y, int n) {
    int a, i, j, k, ell, kmpNext[m];
    int gago = 0;
    
    // Pré-processando
    preKmp(x, m, kmpNext);

    for (ell = 1; x[ell - 1] == x[ell]; ell++);
    if (ell == m)
        ell = 0;

    // Buscando
    i = ell;
    j = k = 0;
    while (j <= n - m) {
        while (i < m && x[i] == y[i + j])
            ++i;
        
        if (i >= m) {
            while (k < ell && x[k] == y[j + k])
                ++k;
            if (k >= ell)
                gago++;
        }
        j += (i - kmpNext[i]);
        if (i == ell)
            k = MAX(0, k - 1);
        else {
            if (kmpNext[i] <= ell) {
                k = MAX(0, kmpNext[i]);
                i = ell;
            } else {
                k = ell;
                i = kmpNext[i];
            }
        }
    }
    return gago;
}

void AXAMAC(char *x, int m, char *y, int n) {
    int a, i, j, k, ell, kmpNext[m];
    int h = 0, l, tam_p = 0, tam_r = 0;
    char palavra[n], padrao[3];
    char resp[n];
    
    // Pré-processando
    preKmp(x, m, kmpNext);

    for (ell = 1; x[ell - 1] == x[ell]; ell++);
    if (ell == m)
        ell = 0;

    // Buscando
    i = ell;
    j = k = 0;
    while (j <= n - m) {
        while (i < m && x[i] == y[i + j])
            ++i;
        
        if (i >= m) {
            while (k < ell && x[k] == y[j + k])
                ++k;
            if (k >= ell){
                for (; h < j; h++) {
                    palavra[tam_p] = y[h];
                    tam_p++;
                }
                h = j+1;
         
                // Verificando se a palavra tem mais de 4 letras
                if (tam_p >= 4) {
                    for (l = 0; l < 2; l++)
                        padrao[l] = palavra[l];

                    /* Verifica se as duas primeiras letras são repetidas e adiciona
                    o texto correto a resp */
                    if (AXAMAC_gago(padrao, strlen(padrao), palavra, tam_p) > 1) {
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
        j += (i - kmpNext[i]);
        if (i == ell)
            k = MAX(0, k - 1);
        else {
            if (kmpNext[i] <= ell) {
                k = MAX(0, kmpNext[i]);
                i = ell;
            } else {
                k = ell;
                i = kmpNext[i];
            }
        }
    }
    for (; h < n; h++) {
      resp[tam_r] = y[h];
      tam_r++;
    }
    printf("%s\n", resp);
}

int main() {
   char *y = "Juca comprou fafarinha na memercearia e papagou 4 reais o quilo. A mamae de Juca pediu para ele comprar mamais 2 quilos.";
   char *x = " ";
   AXAMAC(x, strlen(x), y, strlen(y));
   return 0;
}
