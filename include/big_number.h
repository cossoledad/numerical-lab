#ifndef NUMERICAL_LAB_BIG_NUMBER_H
#define NUMERICAL_LAB_BIG_NUMBER_H

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    size_t size;
    char *buffer;
} bString;

void bStringInit(bString *a, size_t s);
void bStringRelease(bString *a);
void bStringExpansion(bString **a);
void bStringSwap(bString **a, bString **b);
void bStringPrint(bString *a);
bString bStringFromCString(char *c);

char halfAdder(char *a, char *b, char *c);
char fullAdder(char *a, char *b, char *d, char *c);

void add(bString *a, bString *b, bString **out);

#endif
