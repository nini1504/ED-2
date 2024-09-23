#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <cstdio> // Para usar sprintf

using namespace std;
#define q 271

int main()
{
    char cidade[256], temp1[10], temp2[10];
    int somaTotal, cont = 0;
    vector<list<string>> lista(q); // Vetor de lista dinâmico

    FILE *arquivo;
    arquivo = fopen("cidades.txt", "r");
    if (arquivo == NULL){
    
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    // onde será armazenado, numero de caracteres, ponteiro para o arquivo
    while (fgets(cidade, sizeof(cidade), arquivo)) 
    {
        cidade[strcspn(cidade, "\n")] = '\0'; 
        int tam = (strlen(cidade) + 1) / 2;   
        vector<int> vet(tam); 
        somaTotal = 0;
        int j = 0; 
        
        for (int i = 0; i < strlen(cidade); i += 2)
        {
            if (i + 1 < strlen(cidade)) // Verifica se tem um proximo caractere
            {
                sprintf(temp1, "%d", (int)cidade[i]);     // Converte o primeiro caractere para string
                sprintf(temp2, "%d", (int)cidade[i + 1]); // Converte o segundo caractere para string
                strcat(temp1, temp2);                      // Concatena os dois
                vet[j] = atoi(temp1);                      // Converte para número e armazena no vetor
                j++;
            }
            else // Caso o carcatere seja o ultimo
            {
                sprintf(temp1, "%d", (int)cidade[i]); // Converte apenas um caractere
                vet[j] = atoi(temp1);                  // Converte para número
                j++;
            }
        }
        for (int l = 0; l < tam; l++)
        {
            somaTotal += vet[l];
        }

        int hash = somaTotal % q;     
        lista[hash].push_back(cidade); 
    }


    fclose(arquivo);

   int enderecos[11] = {0}; 

    for (int i = 0; i < q; i++)
    {
        int size = lista[i].size();
        if (size == 0)
            enderecos[0]++; // Contar endereços vazios
        else if (size >= 10)
            enderecos[10]++; // Contar endereços com 10 ou mais cidades
        else
            enderecos[size]++; // Contar endereços com 1 a 9 cidades

        if (!lista[i].empty())
        {
            cout << "Hash " << i;
            cout << " - Quantidade de colisoes: " << lista[i].size() << " -> ";
            for (const auto &cidade : lista[i])
            {
                cout << "[" << cidade << "]-> ";
            }
            cout << "NULL \n\n";
            if (lista[i].size() > 1)
            {
                cont += lista[i].size() - 1;
            }
        }
    }

    cout << "Quantidade total de colisoes: " << cont << "\n\n";

    for (int i = 0; i <= 9; i++)
    {
        cout << "Enderecos com " << i << " cidade(s): " << enderecos[i] << endl;
    }
    cout << "Enderecos com 10 ou mais cidades: " << enderecos[10] << endl;

    return 0;
}  