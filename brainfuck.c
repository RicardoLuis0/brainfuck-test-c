#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bool.h"
#include "parser.h"
#include "tape.h"
#include "stack.h"

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
    uint32_t_stack * stack=make_stack();
    if(!stack){
        return 1;
    }
    tape_root * tape=make_tape();
    if(!tape){
        return 1;
    }
    bool skip=false;
    uint32_t skip_depth=0;
    uint32_t address=0;
    bool negative=false;
    uint32_t pc=0;
    for(;pc<len;pc++){
        if(skip){
            if(program[pc]==OPERATOR_LBRACKET){
                skip_depth++;
            }else if(program[pc]==OPERATOR_RBRACKET){
                if(skip_depth>0){
                    skip_depth--;
                }else{
                    skip=false;
                }
            }
            continue;
        }
        switch(program[pc]){
        case OPERATOR_MVRIGHT://move address pointer to the right
            if(negative){
                if(address>0){
                    address--;
                }else{
                    negative=false;
                }
            }else{
                address++;
            }
            break;
        case OPERATOR_MVLEFT://move address pointer to the left
            if(negative){
                address++;
            }else{
                if(address>0){
                    address--;
                }else{
                    negative=true;
                }
            }
            break;
        case OPERATOR_INCREMENT://increment value by one
            (*get_tape_data(tape,address,negative))++;
            break;
        case OPERATOR_DECREMENT://decrement value by one
            (*get_tape_data(tape,address,negative))--;
            break;
        case OPERATOR_PRINT://print character at pointer
            printf("%c",(*get_tape_data(tape,address,negative)));
            break;
        case OPERATOR_READ://read input and store it in address
            (*get_tape_data(tape,address,negative))=getchar();
            break;
        case OPERATOR_LBRACKET:
            if((*get_tape_data(tape,address,negative))==0){
                skip=true;
                skip_depth=0;
            }else{
                push(stack,pc);
            }
            break;
        case OPERATOR_RBRACKET:
            if((*get_tape_data(tape,address,negative))==0){
                pop(stack);
            }else{
                pc=peek(stack);
            }
            break;
        }
    }
    free_tape(tape);
    free_stack(stack);
    free(program);
    return 0;
}
