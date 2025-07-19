#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"

int main(int argc, char* argv[]) {
    //printf("Hello, World!\n");

    if (argc < 2) {
        printf("Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    char *file = argv[1];

    int* freq = CountFrequency(file);

    if (!freq) return 1;

    for (int i = 0; i < 256; i++){
        if (freq[i] > 0){
            //printf("Byte %3d => %d\n", i, freq[i]);
            Node* node = createNode((unsigned char)i, freq[i]);
            if (node) {
                printf("Nó criado: caractere '%c' (byte %d), frequência %d\n", 
                       node->character,
                       node->character, 
                       node->frequency);
                free(node);
            } else {
                printf("Erro ao criar nó para byte %d\n", i);
            }
        }
    }
    /*
    Node* nodes[3];
    nodes[0] = createNode('A', 5);
    nodes[1] = createNode('B', 2);
    nodes[2] = createNode('C', 8);

    // ordena o array com qsort usando sua função
    qsort(nodes, 3, sizeof(Node*), compareNode);
    */

    Node* nodeList[256];
    int count = generateNodeList(freq, nodeList);
    qsort(nodeList, count, sizeof(Node*), compareNode);
    
    // imprime pra verificar se ordenou corretamente
    for (int i = 0; i < count; i++) {
        printf("'%c': %d\n", nodeList[i]->character, nodeList[i]->frequency);
        free(nodeList[i]);
    }

    free(freq);
    return 0;
}
