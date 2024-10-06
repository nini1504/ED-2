#include <iostream>
using namespace std;

#define v 12

void DFS(int i, int grafo[v][v], int visitado[v])
{
    cout << i + 1 << " - "; //printa o vertice visitado, i+1 pq minha matriz começa de zero
    visitado[i] = 1; //marca o vertice inicial como visitado

    // procura todos os vértices adjacentes ao v atual (o for percorre a linha da matriz de adjacência)
    for (int j = 0; j < v; j++) 
    {
        //se existe uma aresta entre o vértice atual e o vértice i e
        if (grafo[i][j] == 1 && visitado[j] == 0) //se meu adjacente ainda nao foi visitado, chamo a funçao pra ele e ai entra a recursao
        {
            DFS(j, grafo, visitado);
        }
    }
}

int main()
{
    int visitado[v] = {0};
    int grafo[v][v] = {
        {0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0}};

    DFS(0, grafo, visitado);
    return 0;
}
