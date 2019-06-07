#ifndef TAPE_H_INCLUDED
#define TAPE_H_INCLUDED

#include <stdint.h>

#include "bool.h"

typedef struct _tape_root tape_root;

tape_root * make_tape();

void free_tape(tape_root*);

uint8_t * get_tape_data(tape_root*,uint32_t address,bool negative);


#endif // TAPE_H_INCLUDED
