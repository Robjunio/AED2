// Programa em C - Algoritmo Autômato Finito Determinístico
#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256 // quantidade possível de diferentes caracteres no texto
 
int getNextState(char *pat, int M, int state, int x) {
    /* Se o caractere c for igual ao próximo caractere no padrão,
    basta incrementar o estado */
    if (state < M && x == pat[state])
        return state+1;
 
    // ns armazena o resultado que é o próximo estado
    int ns, i;
 
    /* ns final contém o prefixo mais longo,
    que também é sufixo em "pat[0..state-1]c" */
 
    /* Começa-se pelo maior valor possível e para
    quando encontrar um prefixo que também seja sufixo */
    for (ns = state; ns > 0; ns--) {
        if (pat[ns-1] == x) {
            for (i = 0; i < ns-1; i++)
                if (pat[i] != pat[state-ns+1+i])
                    break;
            if (i == ns-1)
                return ns;
        }
    }
 
    return 0;
}
 
/* Esta função constrói a tabela TF que representa m (tamanho do padrão)
Autómatos Finitos para um determinado padrão */
void computeTF(char *pat, int M, int TF[][NO_OF_CHARS]) {   
    int state, x;
    for (state = 0; state <= M; ++state)
        for (x = 0; x < NO_OF_CHARS; ++x)
            TF[state][x] = getNextState(pat, M, state, x);
}
 
/* Printando todas as ocorrências do padrão no texto */
void search(char *pat, char *txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    int TF[M+1][NO_OF_CHARS];

    computeTF(pat, M, TF);

    // Processando o texto no AFD
    int i, state = 0;

    for (i = 0; i < N; i++) {   
        state = TF[state][txt[i]];
        if (state == M)
            printf("Pattern found at index %d\n", i-M+1);
    }
}

int main() {
    char *txt = "GCATCGCAGAGAGTATACAGTACG";
    char *pat = "GCAGAGAG";
    search(pat, txt);
    return 0;
}