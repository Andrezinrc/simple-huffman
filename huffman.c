#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "huffman.h"

int* CountFrequency(const char fileName[]){
    int *frequency = calloc(256, sizeof(int));

    if (!frequency) {
        printf("Erro ao alocar memória para frequências.\n");
        return NULL;
    }

    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo");
        free(frequency);
        return NULL;
    }

    unsigned char byte;
    // le o arquivo byte a byte
    while (fread(&byte, 1, 1, file) == 1) {
        frequency[byte]++;
    }

    fclose(file); file = NULL;

    return frequency;
}

Node* createNode(unsigned char character, int frequency){
    Node *node = (Node*)malloc(sizeof(Node));
    if(!node) return NULL;

    // inicializa os campos do nó
    node->frequency = frequency;
    node->character = character;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int compareNode(const void* a, const void* b){
    Node *nodeA = *(Node**)a; // converte o ponteiro genérico para ponteiro de Node
    Node *nodeB = *(Node**)b; // idem

    return nodeA->frequency - nodeB->frequency; // // ordena pela frequência
}

int generateNodeList(int* frequency, Node* nodeList[]){
    int count = 0;

    for(int i = 0; i < 256; i++){
        if(frequency[i] > 0){
            // cria um nó com o caractere e sua frequência
            nodeList[count++] = createNode((unsigned char)i, frequency[i]);
        }
    }

    return count;
}

Node* buildHuffmanTree(Node* nodes[], int count){
    // ordena a lista de nós por frequência
    while(count > 1){
        // pega os dois nós de menor frequência
        Node *left = nodes[0];
        Node *right = nodes[1];

        // cria um novo nó combinando os dois
        Node *newNode = createNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        // move todos os nós restantes 2 posiçoes para tras
        for(int i = 2; i < count; i++){
            nodes[i-2] = nodes[i];
        }

        // adiciona o novo nó no fim da lista
        nodes[count-2] = newNode;
        count--;
    }

    // quando restar só um nó, é a raiz da árvore
    return nodes[0];
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void generateCodes(Node* root, char* path, int depth, char* codes[256]){
    if(!root) return;

    // se for folha, salva o codigo
    if(!root->left && !root->right){
        if(depth == 0) {
            // arvore com só um nó, código "0"
            path[depth] = '0';
            path[depth + 1] = '\0';
        } else {
            path[depth] = '\0';
        }
        codes[root->character] = strdup(path); // salva copia do codigo
        return;
    }

    // esquerda = 0
    path[depth] = '0';
    generateCodes(root->left, path, depth + 1, codes);

    // direita = 1
    path[depth] = '1';
    generateCodes(root->right, path, depth + 1, codes);
}
