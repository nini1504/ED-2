#include <stdio.h>
#include <string.h>
#define d 256
// d é o número de caracteres no alfabeto de entrada

void rabinKarp(char padrao[], char texto[])
{
    int M = strlen(padrao);
    int N = strlen(texto);
    int i, j, q = 101;
    int hash_p = 0; // valor hash para o padrão
    int hash_t = 0; // valor hash para o texto
    int h = 1;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calcula o valor hash do padrão e da primeira janela de texto
    for (i = 0; i < M; i++)
    {
        hash_p = (d * hash_p + padrao[i]) % q;
        hash_t = (d * hash_t + texto[i]) % q;
    }

    // Desliza o padrão sobre o texto um por um
    for (i = 0; i <= N - M; i++)
    {
        if (hash_p == hash_t)
        {
            // Verifica os caracteres um por um
            for (j = 0; j < M; j++)
            {
                if (texto[i + j] != padrao[j])
                    break;
            }

            // se p == t e padrao[0...M-1] = texto[i, i+1, ...i+M-1]
            if (j == M)
                printf("Padrao '%s' encontrado no indice %d\n", padrao, i);
        }

        // Calcula o valor hash para a próxima janela de texto: Remove
        if (i < N - M)
        {
            hash_t = (d * (hash_t - texto[i] * h) + texto[i + M]) % q;

            // Podemos obter um valor negativo de t, convertendo-o para positivo
            if (hash_t < 0)
                hash_t = (hash_t + q);
        }
    }
}

int main()
{
    char texto[] = "nicolly picole";
    char *padrao[] = {"ico", "ly"};

    // descobir o numero de padroes dividindo o tamanho do vetor pelo tamaho do elemento
    int numPadroes = sizeof(padrao) / sizeof(padrao[0]);

    // vou percorrer o texto para encontrar cada padrao
    for (int i = 0; i < numPadroes; i++)
    {
        rabinKarp(padrao[i], texto);
    }

    return 0;
}
