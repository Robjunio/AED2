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
 
/* Verificando se as sílabas se repetem */
int search_gago(char pat[], char txt[], int N) {
    int M = strlen(pat);
    int TF[M+1][NO_OF_CHARS];
    int gago = 0;

    computeTF(pat, M, TF);

    // Processando o texto no AFD
    int i, state = 0;

    for (i = 0; i < N; i++) {   
        state = TF[state][txt[i]]; 
        if (state == M)
            gago++;
    }

    return gago;
}

/* Separando as palavras da frase e removendo as sílabas repetidas */
void search(char *pat, char *txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    int TF[M+1][NO_OF_CHARS];

    char palavra[N], padrao[3];
    char resp[N];

    computeTF(pat, M, TF);

    // Processando o texto no AFD
    int i, j = 0, k, tam_p = 0, tam_r = 0, state = 0;

    for (i = 0; i < N; i++) {   
        state = TF[state][txt[i]];
        if (state == M) {
            // Separando as palavras da frase
            for (; j < i-M+1; j++) {
                palavra[tam_p] = txt[j];
                tam_p++;
            }
            j = i-M+2;

            // Verificando se a palavra tem mais de 4 letras
            if (tam_p >= 4) {
                for (k = 0; k < 2; k++)
                    padrao[k] = palavra[k];

                /* Verifica se as duas primeiras letras são repetidas e adiciona
                o texto correto a resp */
                if (search_gago(padrao, palavra, tam_p) > 1) {
                    for (k = 2; k < tam_p; k++) {
                        resp[tam_r] = palavra[k];
                        tam_r++;
                    }
                } else {
                    for (k = 0; k < tam_p; k++) {
                        resp[tam_r] = palavra[k];
                        tam_r++;
                    }
                }
            } else {
                for (k = 0; k < tam_p; k++) {
                    resp[tam_r] = palavra[k];
                    tam_r++;
                }
            }
            resp[tam_r] = ' ';
            tam_r++;
            tam_p = 0;
        }
        // Adicionando a última palavra depois do último espaço
        if (i == N-1) {
            for (; j < N; j++) {
                resp[tam_r] = txt[j];
                tam_r++;
            }
        }
    }

    printf("%s\n", resp);
}

int main() {
    char *txt = "Juca comprou fafarinha na memercearia e papagou 4 reais o quilo. A mamae de Juca pediu para ele comprar mamais 2 quilos.";
    char *pat = " ";
    search(pat, txt);
    return 0;
}