#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define tam 20

int buscaBinariaRecursiva(int vet[], int key, int inicio, int fim)
{
    int meio, achou = 0;

    // busca binaria
    while (inicio <= fim)
    {
        meio = ((inicio + fim) / 2);
        if (key == vet[meio])
        {
            achou = 1;
            return meio;
        }
        else if (key > vet[meio])
        {
            inicio = meio + 1; 
            buscaBinariaRecursiva(vet, key, inicio, fim);
        }
        else
        {
            fim = meio - 1;
            buscaBinariaRecursiva(vet, key, inicio, fim);
        }
    }

    if (achou == 0)
        return -1;    
}

int main()
{

    int vet[tam], valor, inicio=0, fim=tam;

    // preenchendo aleatoriamente
    for (int i = 0; i < tam; i++)
    {
        vet[i] = rand() % 100;
    }

    // ordenando
    sort(vet, vet + tam);

    cout << "Qual valor deseja buscar no vetor? ";
    cin >> valor;

    if(buscaBinariaRecursiva(vet, valor, inicio, fim) != -1)
        cout << "\nO numero "<< valor << " se encontra na posicao " << buscaBinariaRecursiva(vet, valor, inicio, fim) << " do vetor.\n";
    else
        cout << "\nO numero nao esta no vetor\n";

    return 0;
}
