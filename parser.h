#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

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

#include <stdint.h>

uint8_t * parse(const char * filename,uint32_t * length);

#endif // PARSER_H_INCLUDED
