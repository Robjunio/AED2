#include<stdio.h>
#include<stdlib.h>
#include <time.h> // Função clock

#define max 100000
#define RUN 16

// Retorna o menor valor
int min(long int a, long int b)
{
    if(a<b){ return a; }
    return b;
}
/* Essa função ordena o array do index esquerdo para o index direito que tem o 
tamanho maximo igual a RUN */
void insertionSort(long int arr[], long int left, long int right)
{
    for (long int i = left + 1; i <= right; i++)
    {
        long int temp = arr[i];
        long int j = i - 1;
        while (j >= left && arr[j] > temp)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}
 
// a função mescla as arrays ordenadas
void merge(long int arr[], long int l, long int m, long int r)
{
    // o vetor original é dividido em 2 partes, direita e esquerda
    long int len1 = m - l + 1, len2 = r - m;
    long int left[len1], right[len2];
    
    for (long int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (long int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];
 
    long int i = 0;
    long int j = 0;
    long int k = l;
 
    // Deposis de comparar juntamos os 2 vetores em um subvetor maior.
    while (i < len1 && j < len2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
 
    // se sobrar, Copia os elementos do vetor esquerdo
    while (i < len1)
    {
        arr[k] = left[i];
        k++;
        i++;
    }
 
    // se sobrar, Copia os elementos do vetor direito
    while (j < len2)
    {
        arr[k] = right[j];
        k++;
        j++;
    }
}
 
// Função iterativa Timsort para ordenar o array[0...n-1] 
void timSort(long int arr[], long int n)
{
     
    // ordena os subvetores de tamanho até RUN
    for (long int i = 0; i < n; i+=RUN)
        insertionSort(arr, i, min((i+RUN-1),
                                    (n-1)));
 
    // começa a mesclar pelo tamanho de RUN e vai sendo multiplicado por 2.
    for (long int size = RUN; size < n;
                             size = 2*size)
    {
         
        /* escolha o ponto de partida de submatriz esquerda. Nós vamos fundir o 
        vetor[esquerda..esquerda+tamanho-1] e o 
        vetor[esquerda+tamanho, esquerda+2*tamanho-1]. Após cada mesclagem, nós 
        aumentamos a esquerda em 2*tamanho */
        for (long int left = 0; left < n;
                             left += 2*size)
        {
            /* Encontra o ponto final da submatriz esquerda mid+1 é o ponto de 
            partida do sub array direito */
            long int mid = left + size - 1;
            long int right = min((left + 2*size - 1),
                                            (n-1));
 
            /* mescla o subvetor vet[esquerda.....meio] & arr[meio+1....direita] */
              if(mid < right)
                merge(arr, left, mid, right);
        }
    }
}

int main()
{
  long int a[max], a1[max],i, aux;
  long int n = max;
  clock_t tempo;

  for (i = 0; i < n; i++){
      a[i] = rand() % 100000;
  }

  tempo = clock();
  timSort(a, n);
  tempo = clock() - tempo;

  printf("T1: %f\n", (double)tempo/CLOCKS_PER_SEC);

  tempo = clock();
  timSort(a, n);
  tempo = clock() - tempo;

  printf("T2: %f\n", (double)tempo/CLOCKS_PER_SEC);

  // Invertendo um vetor ordenado
  for(i = 0; i < max; i++)
      a1[i] = a[(max - 1) - i];

  tempo = clock();
  timSort(a1, n);
  tempo = clock() - tempo;

  printf("T3: %f\n", (double)tempo/CLOCKS_PER_SEC);

  aux = 0;

  for (i = 0; i < 100000; i++) {
      if (i < 50000) {
          a1[i] = a[i];
      } else {
          a1[i] = a[(max - 1) - aux];
          aux++;
      }
  }
  
  tempo = clock();
  timSort(a1, n);
  tempo = clock() - tempo;

  printf("T4: %f\n", (double)tempo/CLOCKS_PER_SEC);

  aux = 0;

  for (i = 0; i < 100000; i++) {
      if (i < 50000) {
          a1[i] = a[(max - 50001) - aux];
          aux++;
      } else {
          a1[i] = a[i];
      }
  }

  tempo = clock();
  timSort(a1, n);
  tempo = clock() - tempo;

  printf("T5: %f\n", (double)tempo/CLOCKS_PER_SEC);
  
  return 0;
}
