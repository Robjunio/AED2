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
   int i, state = 0, verif = 0;

   for (i = 0; i < N; i++) {   
      state = TF[state][txt[i]];
      if (state == M) {
         // Verificando se o padrão ocorre nos últimos dígitos do texto
         if (N == i+1) 
            printf("encaixa\n");
         else
            printf("nao encaixa\n");
         verif = 1;
      }
   }

   // Verificando se o padrão não ocorreu
   if (verif == 0)
      printf("nao encaixa\n");
}

int main() {
   char *txt1 = "56234523485723854755454545478690";
   char *pat1 = "78690";
   search(pat1, txt1);

   char *txt2 = "5434554";
   char *pat2 = "543";
   search(pat2, txt2);

   char *txt3 = "1243";
   char *pat3 = "1243";
   search(pat3, txt3);

   char *txt4 = "54";
   char *pat4 = "64545454545454545454545454545454554";
   search(pat4, txt4);

   return 0;
}