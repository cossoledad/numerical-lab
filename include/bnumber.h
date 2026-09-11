#ifndef NUMERICAL_LAB_BNUMBER_H
#define NUMERICAL_LAB_BNUMBER_H

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    size_t size;
    char *buffer;
} bNumber;

void bNumberInit(bNumber *a, size_t s);
void bNumberRelease(bNumber *a);
void bNumberExpansion(bNumber **a);
void bNumberSwap(bNumber **a, bNumber **b);
void bNumberPrint(bNumber *a);
bNumber bNumberFromCString(char *c);

char halfAdder(char *a, char *b, char *c);
char fullAdder(char *a, char *b, char *d, char *c);

void add(bNumber *a, bNumber *b, bNumber **out);

#endif
