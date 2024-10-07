#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    char texto[] = "AABAACAADAABAABA";
    char padrao[] = "AABA";

    int N = strlen(texto);
    int M = strlen(padrao);
    int i, j;

    printf("----- Etapa 1 -----");
    
    for (i = 0; i <= N - M; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (texto[i + j] != padrao[j])
            {
                break;
            }
        }
        if (j == M)
        {
            printf("\nPadrao encontrado na posicao %d\n", i);
        }
    }

    return 0;
}