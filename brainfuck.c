#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define bool uint8_t
#define true 1
#define false 0

#define OPERATOR_INVALID 0
#define OPERATOR_MVRIGHT 1
#define OPERATOR_MVLEFT 2
#define OPERATOR_INCREMENT 3
#define OPERATOR_DECREMENT 4
#define OPERATOR_PRINT 5
#define OPERATOR_READ 6
#define OPERATOR_LBRACKET 7
#define OPERATOR_RBRACKET 8

#define OP_COUNT 8

struct{char c;uint8_t op;} pt[OP_COUNT]={
    {'>',OPERATOR_MVRIGHT},
    {'<',OPERATOR_MVLEFT},
    {'+',OPERATOR_INCREMENT},
    {'-',OPERATOR_DECREMENT},
    {'.',OPERATOR_PRINT},
    {',',OPERATOR_READ},
    {'[',OPERATOR_LBRACKET},
    {']',OPERATOR_RBRACKET},
};

uint8_t get_operator(char c){
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
    
    free(program);
    return 0;
}
