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
void bStringRelease(bString *);
void bStringResize(bString *, size_t);

bString bStringFromCString(char *cs);

size_t cStringSize(char *cs);

void bStringAppendChar(bString *bsp, char);
void bStringAppendCString(bString *bsp, char *cs);
void bStringAppendBString(bString *bsp, bString);

char bStringAt(bString, size_t);

// 左闭右开
bString bStringSlice(bString, size_t, size_t);

void bStringPrint(bString bs);

#endif
