#ifndef HUFFMAN_H
#define HUFFMAN_H

// estrutura do nó da árvore de huffman
typedef struct Node {
    unsigned char character;
    int frequency;
    struct Node *left;
    struct Node *right;
} Node;

// lê  um arquivo e conta a frequência de cada byte
int* CountFrequency(const char fileName[]);

// Cria e inicializa um novo nó da árvore de Huffman com caractere e frequência
Node* createNode(unsigned char character, int frequency);

// Função de comparção usada para ordenar os nós por frequência
int compareNode(const void* a, const void* b);

// Gera uma lista de nós a partir do array de frequências
int generateNodeList(int* frequency, Node* nodeList[]);

// Constrói a árvore de Huffman a partir de uma lista de nós com caracteres e suas frequências
Node* buildHuffmanTree(Node* nodes[], int count);

#endif
