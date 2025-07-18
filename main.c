#include <stdio.h>

#include "huffman.h"

int main(int argc, char* argv[]) {
   //printf("Hello, World!\n");

   char *file = argv[0];
   CountFrequency(file);
    
   return 0;
}
