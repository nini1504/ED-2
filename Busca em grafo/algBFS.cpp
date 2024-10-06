#include <iostream>
#include <queue>
using namespace std;

#define v 12

void BFS(int i, int grafo[v][v], int visitado[v])
{
    queue<int> fila;

    visitado[i] = 1; // marca o vértice  inicial como visitado
    fila.push(i);    // coloca o vértice na fila

    while (!fila.empty())
    {
        // printa o primeiro vértice da fila e tira ele
        int atual = fila.front();
        cout << atual + 1 << " - ";
        fila.pop();

        // procura todos os vértices adjacentes ao v atual (o for percorre a linha da matriz de adjacência)
        for (int i = 0; i < v; i++)
        {
            // Se existe uma aresta entre o v atual e o v i
            // e o vértice i ainda não foi visitado
            if (grafo[atual][i] == 1 && visitado[i] == 0)
            {
                visitado[i] = 1; // marca o vértice i como visitado
                fila.push(i);    // poe o vértice na fila para ser processado depois
            }
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

       BFS(0, grafo, visitado); 

    return 0;
}
