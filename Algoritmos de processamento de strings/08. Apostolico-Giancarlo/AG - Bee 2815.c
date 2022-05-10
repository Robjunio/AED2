// Programa em C - Algoritmo Apostolico-Giancarlo
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
void preBmGs(char *x, int m, int bmGs[], int suff[]) {
    int i, j;
    
    suffixes(x, m, suff);
    
    // Inicializando todas as ocorrências como m
    for (i = 0; i < m; ++i)
        bmGs[i] = m;
    
    j = 0;
    for (i = m - 1; i >= 0; --i)
        if (suff[i] == i + 1)
            for (; j < m - 1 - i; ++j)
                if (bmGs[j] == m)
                bmGs[j] = m - 1 - i;
    for (i = 0; i <= m - 2; ++i)
        bmGs[m - 1 - suff[i]] = m - 1 - i;
}

// Função calcula o maior entre dois números
int MAX(int num1, int num2) {
    return (num1 > num2 ) ? num1 : num2;
}
int AG_gago(char *x, int m, char *y, int n) {
    int i, j, k, s, shift,
        bmGs[m], skip[m], suff[m], bmBc[ASIZE];
    int gago = 0;
    // Pré-processando
    preBmGs(x, m, bmGs, suff);
    preBmBc(x, m, bmBc);
    memset(skip, 0, m*sizeof(int));
    
    // Buscando
    j = 0;
    while (j <= n - m) {
        i = m - 1;
        while (i >= 0) {
            k = skip[i];
            s = suff[i];
            if (k > 0)
                if (k > s) {
                if (i + 1 == s)
                    i = (-1);
                else
                    i -= s;
                break;
                }
                else {
                i -= k;
                if (k < s)
                    break;
                }
            else {
                if (x[i] == y[i + j])
                --i;
                else
                break;
            }
        }
        if (i < 0) {
            gago++;
            skip[m - 1] = m;
            shift = bmGs[0];
        }
        else {
            skip[m - 1] = m - 1 - i;
            shift = MAX(bmGs[i], bmBc[y[i + j]] - m + 1 + i);
        }
        j += shift;
        memcpy(skip, skip + shift, (m - shift)*sizeof(int));
        memset(skip + m - shift, 0, shift*sizeof(int));
    }
    return gago;
}

// Função que executa o pré-processamento e a fase de busca
void AG(char *x, int m, char *y, int n) {
    int i, j, k, s, shift, bmGs[m], skip[m], suff[m], bmBc[ASIZE];
    int h = 0, l, tam_p = 0, tam_r = 0;
    char palavra[n], padrao[3];
    char resp[n];
    
    // Pré-processando
    preBmGs(x, m, bmGs, suff);
    preBmBc(x, m, bmBc);
    memset(skip, 0, m*sizeof(int));
    
    // Buscando
    j = 0;
    while (j <= n - m) {
        i = m - 1;
        while (i >= 0) {
            k = skip[i];
            s = suff[i];
            if (k > 0)
                if (k > s) {
                if (i + 1 == s)
                    i = (-1);
                else
                    i -= s;
                break;
                }
                else {
                i -= k;
                if (k < s)
                    break;
                }
            else {
                if (x[i] == y[i + j])
                --i;
                else
                break;
            }
        }
        /* Se o padrão tiver sido percorrido por completo,
        é registrada uma ocorrência dele no texto, se não 
        a busca continua*/
        if (i < 0) {
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
                if (AG_gago(padrao, strlen(padrao), palavra, tam_p) > 1) {
                   for (l = 2; l < tam_p; l++) {
                      resp[tam_r] = palavra[l];
                      tam_r++;
                   }
                } 
                else {
                   for (l = 0; l < tam_p; l++) {
                      resp[tam_r] = palavra[l];
                      tam_r++;
                   }
                }
            }
            else {
                for (l = 0; l < tam_p; l++) {
                   resp[tam_r] = palavra[l];
                   tam_r++;
                }
            }

            resp[tam_r] = ' ';
            tam_r++;
            tam_p = 0;
            
            skip[m - 1] = m;
            shift = bmGs[0];
        }
        else {
            skip[m - 1] = m - 1 - i;
            shift = MAX(bmGs[i], bmBc[y[i + j]] - m + 1 + i);
        }
        j += shift;
        memcpy(skip, skip + shift, (m - shift)*sizeof(int));
        memset(skip + m - shift, 0, shift*sizeof(int));
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
   AG(x, strlen(x), y, strlen(y));
   return 0;
}
