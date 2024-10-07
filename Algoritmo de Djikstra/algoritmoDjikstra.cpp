#include <iostream>
#include <climits> //p definir o "infinito"
using namespace std;

#define V 12

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
            if (!visitado[v] && grafo[m][v] != -1 && distancia[m] != INT_MAX && distancia[m] + grafo[m][v] < distancia[v])
            {
                distancia[v] = distancia[m] + grafo[m][v]; // atualiza a menor distancia
                anterior[v] = m;
            }
        }
    }

    cout << "Vertice\tDistancia da origem (a)\tVertice anterior" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << vertices[i] << "\t\t" << distancia[i] << "\t\t" << vertices[anterior[i]] << endl;
    }

    cout << "\nDistancia de (a) ate (m): " << distancia[11] << "\n";
    mostrarCaminho(anterior, 11, vertices);
    cout << endl;
}

int main()
{
    char vertices[V] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'l', 'm'};

    int grafo[12][12] = {
    //   a,  b,  c,  d,  e,  f,  g,  h,  i,  j,  l,  m
  /*a*/ {-1, 61, 50, 42, -1, -1, -1, -1, -1, -1, -1, -1}, 
  /*b*/ {61, -1, -1, 32, -1, 29, -1, -1, -1, 17, -1, -1}, 
  /*c*/ {50, -1, -1, 56, 67, -1, -1, -1, -1, -1, -1, -1}, 
  /*d*/ {42, 32, 56, -1, 45, 62, 85, -1, -1, -1, -1, -1}, 
  /*e*/ {-1, -1, 67, 45, -1, -1, 72, -1, 73, -1, -1, -1}, 
  /*f*/ {-1, 29, -1, 62, -1, -1, 20, 35, -1, 30, 45, -1}, 
  /*g*/ {-1, -1, -1, 85, 72, 20, -1, 40, 60, -1, -1, 32}, 
  /*h*/ {-1, -1, -1, -1, -1, 35, 40, -1, -1, -1, 50, 21}, 
  /*i*/ {-1, -1, -1, -1, 73, -1, 60, -1, -1, -1, -1, 50}, 
  /*j*/ {-1, 17, -1, -1, -1, 30, -1, -1, -1, -1, 30, -1}, 
  /*l*/ {-1, -1, -1, -1, -1, 45, -1, 50, -1, 30, -1, -1}, 
  /*m*/ {-1, -1, -1, -1, -1, -1, 32, 21, 50, -1, -1, -1}, 
    };

    dijkstra(grafo, 0, vertices); // inicia na origem 0 = vertice a
    return 0;
}
