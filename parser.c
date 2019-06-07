#include "parser.h"
#include <stdio.h>

static struct{char c;uint8_t op;} pt[OP_COUNT]={
    {'>',OPERATOR_MVRIGHT},
    {'<',OPERATOR_MVLEFT},
    {'+',OPERATOR_INCREMENT},
    {'-',OPERATOR_DECREMENT},
    {'.',OPERATOR_PRINT},
    {',',OPERATOR_READ},
    {'[',OPERATOR_LBRACKET},
    {']',OPERATOR_RBRACKET},
};


static uint8_t get_operator(char c){
    for(uint8_t i=0;i<OP_COUNT;i++){
        if(c==pt[i].c)return pt[i].op;
    }
    return OPERATOR_INVALID;
}

uint8_t * parse(const char * filename,uint32_t * length){
    FILE * f=fopen(filename,"r");//open file
    if(f){//if file opened successfully
        uint8_t * array=NULL;//operator array
        (*length)=0;
        char c;//character
        while((c=fgetc(f))!=EOF){//count length of operator array
            if(get_operator(c)!=OPERATOR_INVALID)(*length)++;
        }
        array=(uint8_t*)calloc(*length,sizeof(uint8_t));//allocate operator array
        if(!array){
            printf("Failed to allocate memory for program data\n");
            return NULL;
        }
        fseek(f,0,SEEK_SET);//rewind file
        for(uint32_t i=0;(c=fgetc(f))!=EOF;){//fill operator array
            if((c=get_operator(c))!=OPERATOR_INVALID)array[i++]=c;
        }
        fclose(f);//close file
        return array;
    }else{
        printf("could not open file '%s'",filename);
        return NULL;
    }
}
