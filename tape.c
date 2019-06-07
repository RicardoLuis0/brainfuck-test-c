#include "tape.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPE_LENGTH 1024

struct _tape{
    struct _tape * next;
    uint8_t data[TAPE_LENGTH];
};

struct _tape_root{
    struct _tape * positive;
    struct _tape * negative;
};

static struct _tape * _make_tape(){
    struct _tape * temp=malloc(sizeof(struct _tape));
    if(!temp){
        printf("Failed to allocate struct 'tape'\n");
        return NULL;
    }
    temp->next=NULL;
    memset(temp->data,0,TAPE_LENGTH*sizeof(uint8_t));
    return temp;
}

tape_root * make_tape(){
    tape_root * temp=malloc(sizeof(tape_root));
    if(!temp){
        printf("Failed to allocate struct 'tape_root'\n");
        return NULL;
    }
    temp->positive=NULL;
    temp->negative=NULL;
    return temp;
}

static void _free_tape(struct _tape * sroot){
    struct _tape * temp;
    while(sroot!=NULL){
        temp=sroot;
        sroot=sroot->next;
        free(temp);
    }
}

void free_tape(tape_root * root){
    _free_tape(root->positive);
    _free_tape(root->negative);
    free(root);
}

static uint8_t * _get_tape_data(struct _tape * sroot,uint32_t address,uint32_t index){
    if((index+TAPE_LENGTH)>address){
        return &sroot->data[address-index];
    }else{
        if(!sroot->next){
            sroot->next=_make_tape();
            if(!sroot->next)return NULL;//allocation failed
        }
        return _get_tape_data(sroot->next,address,index+TAPE_LENGTH);
    }
}

uint8_t * get_tape_data(tape_root * root,uint32_t address,bool negative){
    if(negative){
        if(!root->negative){
            root->negative=_make_tape();
            if(!root->negative)return NULL;
        }
        return _get_tape_data(root->negative,-address,1);
    }else{
        if(!root->positive){
            root->positive=_make_tape();
            if(!root->positive)return NULL;
        }
        return _get_tape_data(root->positive,address,0);
    }
}
