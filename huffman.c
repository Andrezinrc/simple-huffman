#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Lê um arquivo e conta a frequência de cada byte
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

    for (int i = 0; i < 256; i++)
        if (frequency[i] > 0)
            printf("Byte %3d => %d\n", i, frequency[i]);

    fclose(file); file = NULL;

    return frequency;
}