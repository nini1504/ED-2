#include <stdlib.h>
#include <stdio.h>
#define TAM 100

void main()
{
    int vet[TAM], num, inicio = 0, fim = TAM - 1, meio = 0, temp, v = 0, achou = 0, cont = 0, i, p;

    // populaçao do vetor com numeros aleatorios
    for (int i = 0; i < TAM; i++)
    {
        vet[i] = rand() % 100;
    }

    // ordenaçao - bubble sort
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

    // printando o vetor ordenado
    for (int x = 0; x < TAM; x++)
    {
        printf("\nvet[%d]: %d", x, vet[x]);
    }

    printf("\n\nQual o valor a ser buscado? ");
    scanf("%d", &num);

    printf("\n----------Tarefa 02----------\n");
    printf("\nO numero %d aparece nas seguintes posicoes: ", num);

    // busca binaria
    while (inicio <= fim)
    {
        v++;
        meio = (inicio + fim) / 2;
        if (num == vet[meio])
        {
            cont++;
            achou = 1;
            printf("\nPosicao: %d", meio);

            // verificar a esquerda
            i = meio - 1;
            while (i >= 0 && vet[i] == num)
            {
                cont++;
                printf("\nPosicao: %d", i);
                i--;
            }

            // verificar a direita
            p = meio + 1;
            while (p < TAM && vet[p] == num)
            {
                cont++;
                printf("\nPosicao: %d", p);
                p++;
            }
            break; // Encontrou o número, pode sair do loop
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

    if (achou == 1)
    {
        printf("\n\nForam realizadas %d verificações.", v);
        printf("\nO numero %d repete %d vezes", num, cont);
    }
    else
    {
        printf("\nO numero %d nao foi encontrado no vetor apos %d verificacoes.\n", num, v);
    }
}
