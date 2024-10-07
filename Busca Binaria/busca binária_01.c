#include <stdlib.h>
#include <stdio.h>
#define TAM 100

void main()
{
    int vet[TAM], num, inicio = 0, fim = TAM - 1, meio = 0, temp, v = 0, achou=0, p=-1, cont=0;

    //populaçao do vetor com numeros aleatorios
    for (int i = 0; i < TAM; i++)
    {
        vet[i] = rand() % 100;
    }

    //ordenaçao - bubble sort
    for (int i = 0; i < TAM - 1; i++)
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

    //printando o vetor ordenado
    for (int x = 0; x < TAM; x++)
    {
        printf("\nvet[%d]: %d", x, vet[x]);
    }

    printf("\n\nQual o valor a ser buscado? ");
    scanf("%d", &num);

    printf("\n----------Tarefa 01----------\n");

    //busca binaria
    while (inicio <= fim)
    {
        v++;
        meio = ((inicio + fim) / 2);
        if (num == vet[meio])
        {
            achou = 1;
            p = meio;
            printf("\nA posicao eh: %d", meio);
            break;
        }
        else if (num > vet[meio])
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }
    printf("\nO numero de verficacoes eh igual a: %d\n", v);

    if (achou == 0)
    {
        printf("\nO numero nao esta no vetor.\n");
    }
}
