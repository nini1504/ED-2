#include <iostream>
#include <queue>
using namespace std;

#define v 12

// Função de Busca em Profundidade (DFS)
void DFS(int i, int grafo[v][v], int visitado[v]) {
    cout << i + 1 << " - "; // printa o vertice visitado, i+1 pq minha matriz começa de zero
    visitado[i] = 1;        // marca o vertice inicial como visitado

    // procura todos os vértices adjacentes ao vértice atual
    for (int j = 0; j < v; j++) {
        // Se existe uma aresta entre o vértice atual e o vértice j e
        if (grafo[i][j] == 1 && visitado[j] == 0) { // se meu adjacente ainda nao foi visitado, chamo a função para ele
            DFS(j, grafo, visitado);
        }
    }
}

// Função de Busca em Largura (BFS)
void BFS(int i, int grafo[v][v], int visitado[v]) {
    queue <int> fila;

    visitado[i] = 1; // marca o vértice  inicial como visitado
    fila.push(i);    // coloca o vértice na fila

    while (!fila.empty()) {
        // printa o primeiro vértice da fila e tira ele
        int atual = fila.front();
        cout << atual + 1 << " - ";
        fila.pop();

        // procura todos os vértices adjacentes ao vértice atual
        for (int j = 0; j < v; j++) {
            // Se existe uma aresta entre o vértice atual e o vértice j
            // e o vértice j ainda não foi visitado
            if (grafo[atual][j] == 1 && visitado[j] == 0) {
                visitado[j] = 1; // marca o vértice j como visitado
                fila.push(j);    // coloca o vértice j na fila para ser processado depois
            }
        }
    }
}

int main() {
    int op;
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

    while (op != 3) {
        cout << "\nEscolha uma opcao: \n1- Busca em profundidade (DFS) \n2- Busca em largura (BFS)\n3-Sair do programa \n";
        cin >> op;

        // reinicializa o vetor de visitados para cada nova busca
        int visitado[v] = {0};

        switch (op) {
        case 1:
            cout << "\nCaminho percorrido em profundidade: \n";
            DFS(0, grafo, visitado);
            break;

        case 2:
            cout << "\nCaminho percorrido em largura: \n";
            BFS(0, grafo, visitado);
            break;

        case 3:
            cout << "\nSaindo do programa \n";
            break;

        default:
            cout << "Opcao invalida!";
        }
    }

    return 0;
}
