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

// Função que executa o pré-processamento e a fase de busca
void AG(char *x, int m, char *y, int n) {
    int i, j, k, s, shift,
        bmGs[m], skip[m], suff[m], bmBc[ASIZE];
    
    // Pré-processando
    // Pega as informações de caractere ruim, bom sufixo e os guarda em listas
    preBmGs(x, m, bmGs, suff);
    preBmBc(x, m, bmBc);
    memset(skip, 0, m*sizeof(int));
    
    // Buscando
    j = 0;
    while (j <= n - m) {  //Enquanto j for menor ou igual ao tamanho da string menos o padrão
        i = m - 1;
        while (i >= 0) {
	    //Pega as informações das tabelas
            k = skip[i]; 
            s = suff[i];
            if (k > 0)
                if (k > s) {
                if (i + 1 == s)
                    i = (-1); // Palavra foi encontrada
                else
                    i -= s;
                break;
                }
                else {
                i -= k;
                if (k < s)
                    break;
                }
	    // Se o skip for igual a 0, não há motivo para pular logo compara-se a casa e pula para a casa a esquerda
            else {
                if (x[i] == y[i + j])
                --i;
                else
                break;
            }
        }
	// Imprime o index que a palavra foi encontrada
        if (i < 0) {
            printf("Pattern found at index %d\n", j);
            skip[m - 1] = m;
            shift = bmGs[0];
        }
	// Coloca o skip em um novo valor, e calcula o novo shift
        else {
            skip[m - 1] = m - 1 - i;
            shift = MAX(bmGs[i], bmBc[y[i + j]] - m + 1 + i);
        }
        j += shift;
        memcpy(skip, skip + shift, (m - shift)*sizeof(int));
        memset(skip + m - shift, 0, shift*sizeof(int));
    }
}

int main() {
    char *y = "GCATCGCAGAGAGTATACAGTACG";
    char *x = "GCAGAGAG";
    AG(x, strlen(x), y, strlen(y));
    return 0;
}