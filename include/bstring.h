#ifndef NUMERICAL_LAB_BSTRING_H
#define NUMERICAL_LAB_BSTRING_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *data;
    size_t size;
} bString;

bString bStringCreate();
bString bStringFromCString(char *cs);

size_t cStringSize(char *cs);

void bStringAppendChar(bString *bsp, char);
void bStringAppendCString(bString *bsp, char *cs);
void bStringAppendBString(bString *bsp, bString);

void bStringPrint(bString bs);

#endif
