#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 256 //numero total de caracteres ASCII possiveis

// Estrutura do no da arvore de Huffman
typedef struct No {
    char caractere;  // Caractere armazenado no no (folha)
    int frequencia;  // Frequencia de ocorrencia do caractere
    struct No *esquerda, *direita;
} No;

// Estrutura para a fila de prioridade
typedef struct FilaPrioridade {
    int tamanho;
    int capacidade;
    No **vet;
} FilaPrioridade;

// Funcao para criar um novo no de Huffman com o caractere, a frequência e os nós esquerdo e direito (se houver).
No *novoNo(char caractere, int frequencia, No *esquerda, No *direita) {
    No *no = (No *)malloc(sizeof(No));
    no->caractere = caractere;
    no->frequencia = frequencia;
    no->esquerda = esquerda;
    no->direita = direita;
    return no;
}

// Funcao para criar uma fila de prioridade com uma capacidade dada
FilaPrioridade *criarFilaPrioridade(int capacidade) {
    FilaPrioridade *fila = (FilaPrioridade *)malloc(sizeof(FilaPrioridade));
    fila->tamanho = 0;
    fila->capacidade = capacidade;
    fila->vet = (No **)malloc(fila->capacidade * sizeof(No *));
    return fila;
}

// Funcao para trocar dois ponteiros de nós da fila de prioridade
void trocarNos(No **a, No **b) {
    No *temp = *a;
    *a = *b;
    *b = temp;
}

// Funcao para reorganizar a fila de prioridade
void reorganizaFila(FilaPrioridade *fila, int i) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < fila->tamanho && fila->vet[esquerda]->frequencia < fila->vet[menor]->frequencia) {
        menor = esquerda;
    }

    if (direita < fila->tamanho && fila->vet[direita]->frequencia < fila->vet[menor]->frequencia) {
        menor = direita;
    }

    if (menor != i) {
        trocarNos(&fila->vet[menor], &fila->vet[i]);
        reorganizaFila(fila, menor); //chama a funçao recursivamente ate que a ordem esteja correta
    }
}

// Funcao para remover o menor no da fila de prioridade
No *removerMin(FilaPrioridade *fila) {
    No *temp = fila->vet[0];
    fila->vet[0] = fila->vet[--fila->tamanho];
    reorganizaFila(fila, 0);
    return temp;
}

// Funcao para inserir um no na fila de prioridade
void inserirFila(FilaPrioridade *fila, No *no) {
    fila->tamanho++;
    int i = fila->tamanho - 1;
    while (i && no->frequencia < fila->vet[(i - 1) / 2]->frequencia) {
        fila->vet[i] = fila->vet[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    fila->vet[i] = no;
}

// Funcao para verificar se o no e uma folha
int ehFolha(No *no) {
    return !(no->esquerda) && !(no->direita);
}

// Funcao para construir a arvore de Huffman
No *construirArvoreHuffman(char caracteres[], int frequencias[], int tamanho) {
    FilaPrioridade *fila = criarFilaPrioridade(tamanho);

    for (int i = 0; i < tamanho; i++) {
        inserirFila(fila, novoNo(caracteres[i], frequencias[i], NULL, NULL));
    }

    while (fila->tamanho > 1) {
        No *esquerda = removerMin(fila);
        No *direita = removerMin(fila);

        No *topo = novoNo('$', esquerda->frequencia + direita->frequencia, esquerda, direita);
        inserirFila(fila, topo);
    }

    No *raiz = removerMin(fila);
    free(fila->vet);
    free(fila);
    return raiz;
}

// Funcao para gerar os codigos de Huffman a partir da arvore
void gerarTabela(No *raiz, char codigo[], int topo, char codigos[TAM][TAM]) {
    if (raiz->esquerda) {
        codigo[topo] = '0';
        gerarTabela(raiz->esquerda, codigo, topo + 1, codigos);
    }

    if (raiz->direita) {
        codigo[topo] = '1';
        gerarTabela(raiz->direita, codigo, topo + 1, codigos);
    }

    if (ehFolha(raiz)) {
        codigo[topo] = '\0';
        strcpy(codigos[raiz->caractere], codigo);
    }
}

// Funcao para gravar a arvore de Huffman no arquivo (em pre-ordem)
void gravarArvoreHuffman(No *raiz, FILE *saida) {
    if (ehFolha(raiz)) {
        fputc('1', saida);             // No folha
        fputc(raiz->caractere, saida); // Grava o caractere
    } else {
        fputc('0', saida); // No interno
    }

    if (raiz->esquerda) gravarArvoreHuffman(raiz->esquerda, saida);
    if (raiz->direita) gravarArvoreHuffman(raiz->direita, saida);
}

// Funcao para gravar o cabecalho com o delimitador
void gravarCabecalho(No *raiz, FILE *saida, int tamanhoUnicos) {
    fwrite(&tamanhoUnicos, sizeof(int), 1, saida); // Grava o numero de caracteres unicos
    gravarArvoreHuffman(raiz, saida);              // Grava a arvore
    fputc('#', saida);                             // Delimitador
}

// Funcao para codificar o arquivo
void codificarArquivo(FILE *entrada, FILE *saida, char codigos[TAM][TAM]) {
    char caractere;
    while ((caractere = fgetc(entrada)) != EOF) {
        fputs(codigos[caractere], saida);
    }
}

// Funcao para calcular a frequencia dos caracteres no arquivo
void calcularFrequencia(FILE *entrada, int frequencias[TAM]) {
    char caractere;
    while ((caractere = fgetc(entrada)) != EOF) {
        frequencias[(int)caractere]++;
    }
}

// Funcao para reconstruir a arvore de Huffman a partir do arquivo
No *lerArvoreHuffman(FILE *entrada) {
    char bit = fgetc(entrada);

    if (bit == '1') {
        // No folha: le o caractere
        char caractere = fgetc(entrada);
        return novoNo(caractere, 0, NULL, NULL);
    }

    // No interno: reconstrua recursivamente os nos da esquerda e direita
    No *esquerda = lerArvoreHuffman(entrada);
    No *direita = lerArvoreHuffman(entrada);

    return novoNo('$', 0, esquerda, direita);  // '$' e apenas um marcador de no interno
}

// Funcao para ler o cabecalho do arquivo
No *lerCabecalho(FILE *entrada) {
    int tamanhoUnicos;
    fread(&tamanhoUnicos, sizeof(int), 1, entrada); // Le o numero de caracteres unicos

    // Reconstrui a arvore de Huffman
    No *raiz = lerArvoreHuffman(entrada);

    // Le ate o delimitador '#'
    char delimitador;
    while ((delimitador = fgetc(entrada)) != '#' && delimitador != EOF);

    return raiz;
}

// Funcao para decodificar o arquivo comprimido
void decodificarArquivo(FILE *entrada, FILE *saida, No *raiz) {
    No *atual = raiz;
    char bit;

    // Percorre os bits do arquivo comprimido
    while ((bit = fgetc(entrada)) != EOF) {
        atual = (bit == '0') ? atual->esquerda : atual->direita;

        // Se chegarmos a uma folha, escrevemos o caractere correspondente
        if (ehFolha(atual)) {
            fputc(atual->caractere, saida);
            atual = raiz;  // Reinicia na raiz para o proximo caractere
        }
    }
}

// Programa principal para compressao e descompressao
int main() {
    // Abrir o arquivo de entrada para compressao
    FILE *entrada = fopen("arquivo.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Frequencia dos caracteres
    int frequencias[TAM] = {0};

    // Calcular a frequencia dos caracteres no arquivo
    calcularFrequencia(entrada, frequencias);

    // Fechar e reabrir o arquivo para codificacao
    fclose(entrada);
    entrada = fopen("arquivo.txt", "r");

    // Criar a lista de caracteres e suas frequencias
    char caracteres[TAM];
    int freqCaractere[TAM];
    int tamanho = 0;
    for (int i = 0; i < TAM; i++) {
        if (frequencias[i] > 0) {
            caracteres[tamanho] = (char)i;
            freqCaractere[tamanho] = frequencias[i];
            tamanho++;
        }
    }

    // Construir a arvore de Huffman
    No *raiz = construirArvoreHuffman(caracteres, freqCaractere, tamanho);

    // Gerar a tabela de codigos de Huffman
    char codigos[TAM][TAM] = {0};
    char codigo[TAM];
    gerarTabela(raiz, codigo, 0, codigos);

    // Codificar o arquivo e gravar o cabecalho com o delimitador
    FILE *saida = fopen("arquivo_comprimido.bin", "wb");
    gravarCabecalho(raiz, saida, tamanho);
    codificarArquivo(entrada, saida, codigos);

    // Fechar o arquivo de entrada e o arquivo comprimido
    fclose(entrada);
    fclose(saida);

    printf("Compressao concluida e arquivo comprimido gravado com sucesso.\n");

    // Iniciar o processo de descompressao
    // Abrir o arquivo comprimido para leitura
    FILE *arquivoComprimido = fopen("arquivo_comprimido.bin", "rb");
    if (arquivoComprimido == NULL) {
        printf("Erro ao abrir o arquivo comprimido.\n");
        return 1;
    }

    // Abrir o arquivo de saida para a descompressao
    FILE *saidaDescomprimida = fopen("arquivo_descomprimido.txt", "w");
    if (saidaDescomprimida == NULL) {
        printf("Erro ao criar o arquivo descomprimido.\n");
        fclose(arquivoComprimido);
        return 1;
    }

    // Reconstruir a arvore de Huffman do arquivo comprimido
    No *arvoreDecodificada = lerCabecalho(arquivoComprimido);

    // Decodificar o arquivo comprimido e gravar no arquivo de saida
    decodificarArquivo(arquivoComprimido, saidaDescomprimida, arvoreDecodificada);

    // Fechar os arquivos
    fclose(arquivoComprimido);
    fclose(saidaDescomprimida);

    printf("\nDescompressao concluida e arquivo descomprimido gravado com sucesso.\n");

    return 0;
}
