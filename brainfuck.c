#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bool.h"

#define STACK_SIZE 64

#include "parser.h"

int main(int argc,char ** argv){
    if(argc<2){
        printf("Missing File Argument, usage: program \"file\"\n");
        return 1;
    }
    uint32_t len;
    uint8_t * program=parse(argv[1],&len);
    if(!program){
        return 1;
    }
    uint32_t sp=0;//stack pointer
    uint32_t * stack=calloc(STACK_SIZE,sizeof(uint32_t));
    if(!stack){
        free(program);
        printf("Failed to allocate memory for stack\n");
        return 1;
    }
    uint32_t pc=0;
    for(;pc<len;pc++){
        
    }
    free(stack);
    free(program);
    return 0;
}
