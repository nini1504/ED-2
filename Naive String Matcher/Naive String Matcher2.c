#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char texto[] = "nicollypicole";
    char padrao[] = "*ico";

    int N = strlen(texto);
    int M = strlen(padrao);
    int i, j;

    printf("\n----- Etapa 2 (curinga) -----\n");

    for (i = 0; i <= N - M; i++)
    {
        j = 0;  

        while (j < M)
        {
            if (padrao[j] == '*') 
            {
                j++;  
            }
            else if (texto[i + j] == padrao[j]) 
            {
                j++;  
            }
            else
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
