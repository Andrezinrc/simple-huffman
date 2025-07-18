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
