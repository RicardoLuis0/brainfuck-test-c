#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bool.h"
#include "parser.h"
#include "tape.h"

#define STACK_SIZE 64

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
    uint32_t * stack=calloc(STACK_SIZE,sizeof(uint32_t));
    if(!stack){
        free(program);
        printf("Failed to allocate memory for stack\n");
        return 1;
    }
    tape_root * tape=make_tape();
    if(tape==NULL){
        return 1;
    }
    uint32_t address=0;
    bool negative=false;
    uint32_t sp=0;//stack pointer
    uint32_t pc=0;
    for(;pc<len;pc++){
        switch(program[pc]){
        case OPERATOR_MVRIGHT://move address pointer to the right
            break;
        case OPERATOR_MVLEFT://move address pointer to the left
            break;
        case OPERATOR_INCREMENT://increment value by one
            break;
        case OPERATOR_DECREMENT://decrement value by one
            break;
        case OPERATOR_PRINT://print character at pointer
            break;
        case OPERATOR_READ://read input and store it in address
            break;
        case OPERATOR_LBRACKET:
            break;
        case OPERATOR_RBRACKET:
            break;
        }
    }
    free_tape(tape);
    free(stack);
    free(program);
    return 0;
}
