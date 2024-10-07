#include <stdio.h>
#include <stdlib.h>
#define TAM 10

int main()
{

    int vet[TAM], temp, n = 1;

    // preenchendo o vetor em ordem decrescente
    for (int i = TAM - 1; i >= 0; i--)
    {
        vet[i] = n;
        n++;
    }

    //vetor desordenado
    printf("\nVetor desordenado: ");
    for (int i = 0; i < TAM; i++)
    {
        printf("%d ", vet[i]);
    }

    // bubble
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM - 1; j++)
        {
            if (vet[j] > vet[j + 1])
            {
                temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }

    //vetor ordenado
    printf("\nVetor ordenado: ");
    for (int i = 0; i < TAM; i++)
    {
        printf("%d ", vet[i]);
    }

    printf("\n");
   return 0;
}