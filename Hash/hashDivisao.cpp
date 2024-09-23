#include <iostream>
#include <cstring>
#include <list>
#include <vector>

using namespace std;
#define q 271
int main()
{
    char cidade[256];
    int somaTotal, cont = 0;

    vector<list<string>> lista(q); // Vetor de lista dinâmico

    FILE *arquivo;
    arquivo = fopen("cidades.txt", "r");
    if (arquivo == NULL)
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    // onde será armazenado, número de caracteres, ponteiro para o arquivo
    while (fgets(cidade, sizeof(cidade), arquivo))
    {
        cidade[strcspn(cidade, "\n")] = '\0'; // Remover a quebra de linha
        somaTotal = 0;
        for (int i = 0; i < strlen(cidade); i++)
        {   
            somaTotal += (int)cidade[i];
        }

        int hash = somaTotal % q;
        lista[hash].push_back(cidade); // inserindo a cidade na posição hash
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
