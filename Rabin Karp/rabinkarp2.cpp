#include <iostream>
#include <vector>
#include <string>
#include <chrono> // para medir o tempo com alta precisão

#define d 256 // d é o número de caracteres no alfabeto de entrada

using namespace std;

void rabinKarp(const vector<string>& padroes, const string& texto) {
    int N = texto.length();
    int q = 101; // número primo para o hash

    // Loop sobre cada padrão
    for (const string& padrao : padroes) {
        int M = padrao.length();
        int hash_p = 0; // valor hash para o padrão
        int hash_t = 0; // valor hash para o texto
        int h = 1; // valor h usado no rehash

        // Calcula o valor de 'h' (d^(M-1)) % q para o padrão atual
        for (int i = 0; i < M - 1; i++)
            h = (h * d) % q;

        // Calcula o valor hash do padrão e da primeira janela de texto
        for (int i = 0; i < M; i++) {
            hash_p = (d * hash_p + padrao[i]) % q;
            hash_t = (d * hash_t + texto[i]) % q;
        }

        // Desliza o padrão sobre o texto um por um
        for (int i = 0; i <= N - M; i++) {
            if (hash_p == hash_t) {
                // Verifica os caracteres um por um
                int j;
                for (j = 0; j < M; j++) {
                    if (texto[i + j] != padrao[j])
                        break;
                }

                // Se p == t e padrao[0...M-1] = texto[i...i+M-1]
                if (j == M)
                    cout << "Padrao '" << padrao << "' encontrado no indice " << i << endl;
            }

            // Calcula o valor hash para a próxima janela de texto
            if (i < N - M) {
                hash_t = (d * (hash_t - texto[i] * h) + texto[i + M]) % q;

                // Corrige hash_t caso ele tenha ficado negativo
                if (hash_t < 0)
                    hash_t = (hash_t + q);
            }
        }
    }
}

int main() {
    // Texto mais longo e mais difícil
    string texto = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. "
                   "Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. "
                   "Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa.";

    // Padrões mais difíceis e maiores
    vector<string> padroes = {"consectetur", "dapibus", "imperdiet", "Mauris", "Lorem ipsum", "porta"};

    // Usa chrono para capturar o tempo de execução com alta precisão
    auto start = chrono::high_resolution_clock::now();

    // Executa o algoritmo uma única vez com o texto e os padrões mais difíceis
    rabinKarp(padroes, texto);

    // Marca o tempo de fim
    auto end = chrono::high_resolution_clock::now();

    // Calcula o tempo total em microsegundos
    chrono::duration<double, micro> elapsed_time = end - start;

    printf("\n");
    // Exibe o tempo de execução em microsegundos
    cout << "Tempo de execucao: " << elapsed_time.count() << " microsegundos" << endl;

    return 0;
}
