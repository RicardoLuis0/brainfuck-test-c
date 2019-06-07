#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STACK_SIZE 1024

struct _uint32_t_stack{
    uint32_t sp;
    uint32_t data[STACK_SIZE];
};

uint32_t_stack * make_stack(){
    uint32_t_stack * temp=malloc(sizeof(uint32_t_stack));
    temp->sp=0;
    memset(temp->data,0,sizeof(uint32_t)*STACK_SIZE);
    return temp;
}

void free_stack(uint32_t_stack * st){
    free(st);
}

bool pop(uint32_t_stack * st){
    if(st->sp>0){
        st->sp--;
        return true;
    }
    printf("Stack Underflow\n");
    return false;
}

bool push(uint32_t_stack * st,uint32_t val){
    if(st->sp<STACK_SIZE){
        st->data[st->sp++]=val;
        return true;
    }
    printf("Stack Overflow\n");
    return false;
}

uint32_t peek(uint32_t_stack * st){
    if(st->sp>0)return st->data[st->sp-1];
    printf("Peek at Empty Stack\n");
    return 0;
}
