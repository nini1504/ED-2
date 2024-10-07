/*Maria é médica, e faz atendimento residencial para alguns pacientes com doenças graves. Maria mora na cidade esquematizada pelo grafo abaixo. 
Sabe-se que seus pacientes moram nas áreas O, E, D, X e T. Os pesos das arestas representam o tempo gasto para ir de uma área à outra.
Ajude Maria a encontrar o menor tempo para chegar à casa de cada um de seus pacientes, partindo sempre de seu consultório na área G. Mostre à Maria, 
também, qual caminho ela percorre para chegar na casa do paciente T. (Seu código deve mostrar a tabela de distâncias e a precedência final, além do caminho 
para cada cliente.)*/

#include <iostream>
#include <climits> //p definir o "infinito"
using namespace std;

#define V 11

void mostrarCaminho(int anterior[], int destino, char vertices[])
{
    if (anterior[destino] == -1)
    {
        // Caso base: quando chegamos à origem
        cout << vertices[destino];
        return;
    }

    // Chama recursivamente para o anterior do destino
    mostrarCaminho(anterior, anterior[destino], vertices);

    // Depois da recursão, imprime o vértice atual
    cout << " -> " << vertices[destino];
}

int menorDistancia(int distancia[], int visitado[]) // achar a menor distancia que ainda n foi visitada
{
    int menor = INT_MAX, indice_do_menor = -1;

    for (int v = 0; v < V; v++)
    {
        if (!visitado[v] && distancia[v] <= menor) // ainda n foi visitado e é menor que o menor = troca
        {
            menor = distancia[v];
            indice_do_menor = v;
        }
    }

    return indice_do_menor;
}

void dijkstra(int grafo[V][V], int origem, char vertices[])
{
    int distancia[V]; // vet p guardar a menor distância da origem até i
    int visitado[V];  // vet p saber se ja foi visitado ou n
    int anterior[V];  // vet p gaurdar o vertice anterior de cada vertice

    // inicializa tudo com infinito e como nao visitado
    for (int i = 0; i < V; i++)
    {
        distancia[i] = INT_MAX; // maior valor que um tipo int pode armazenar
        visitado[i] = 0;
        anterior[i] = -1;
    }

    // a distância da origem até ela mesma é 0
    distancia[origem] = 0;

    // Encontra o caminho mais curto para todos os vértices
    for (int i = 0; i < V - 1; i++)
    {
        // u vai receber o indice da menor distancia nao visitado
        int m = menorDistancia(distancia, visitado);

        // marca o vertice como visitado
        visitado[m] = 1;

        // Atualiza os valores de distancia[] dos vértices adjacentes ao vértice escolhido
        for (int v = 0; v < V; v++)
        {
            // Atualiza distancia apenas se ainda nao foi visitado, se houver uma aresta de u para v,
            // e se a nova distância calculada for menor do que a distância atual
            if (!visitado[v] && grafo[m][v] !=-1 && distancia[m] != INT_MAX && distancia[m] + grafo[m][v] < distancia[v])
            {
                distancia[v] = distancia[m] + grafo[m][v]; // atualiza a menor distancia
                anterior[v] = m;
            }
        }
    }

    cout << "Vertice\tDistancia da origem (G)\tVertice anterior" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << vertices[i] << "\t\t" << distancia[i] << "\t\t" << vertices[anterior[i]] << endl;
    }

    // dist G-O
    cout << "\nDistancia de G ate o paciente O: " << distancia[1] << "\n";
    mostrarCaminho(anterior, 1, vertices);
    cout << endl;

    // dist G-E
    cout << "\nDistancia de G ate o paciente E: " << distancia[4] << "\n";
    mostrarCaminho(anterior, 4, vertices);
    cout << endl;

    // dist G-D
    cout << "\nDistancia de G ate o paciente D: " << distancia[8] << "\n";
    mostrarCaminho(anterior, 8, vertices);
    cout << endl;

    // dist G-X
    cout << "\nDistancia de G ate o paciente X: " << distancia[10] << "\n";
    mostrarCaminho(anterior, 10, vertices);
    cout << endl;

    // dist G-T
    cout << "\nDistancia de G ate o paciente T: " << distancia[9] << "\n";
    mostrarCaminho(anterior, 9, vertices);
    cout << endl;
}

int main()
{
    char vertices[11] = {'R', 'O', 'K', 'G', 'E', 'Q', 'A', 'M', 'D', 'T', 'X'};

     int grafo[V][V] = {
        //       R   O   K   G   E   Q   A   M   D   T   X
        /*R*/ { -1,  4,  2,  0,  0, -1, -1, -1, -1, -1, -1 }, // R
        /*O*/ {  4, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1 }, // O
        /*K*/ {  2,  1, -1,  1, -1, -1, -1, -1, -1, -1, -1 }, // K
        /*G*/ {  0, -1,  1, -1,  3,  5, -1, -1, -1, -1, -1 }, // G
        /*E*/ {  0, -1, -1,  3, -1,  -1, 2, -1, -1, -1, -1 }, // E
        /*Q*/ { -1, -1, -1,  5, -1, -1,  4,  2, -1, -1, -1 }, // Q
        /*A*/ { -1, -1, -1, -1,  2,  4, -1,  2,  1,  3, -1 }, // A
        /*M*/ { -1, -1, -1, -1, -1,  2,  2, -1, -1, -1, -1 }, // M
        /*D*/ { -1, -1, -1, -1, -1, -1,  1, -1, -1,  4,  3 }, // D
        /*T*/ { -1, -1, -1, -1, -1, -1,  3, -1,  4, -1,  2 }, // T
        /*X*/ { -1, -1, -1, -1, -1, -1, -1, -1,  3,  2, -1 }  // X
    };

    dijkstra(grafo, 3, vertices); // inicia na origem 3 = vertice G

    return 0;
}
