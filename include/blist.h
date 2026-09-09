#ifndef NUMERICAL_LAB_BLIST_H
#define NUMERICAL_LAB_BLIST_H

#include <stdio.h>

typedef struct bListNode
{
    struct bListNode *pre;
    struct bListNode *nxt;
    int data;
} bListNode;

typedef struct
{
    bListNode *front;
    bListNode *back;
    size_t size;
} bList;

void bListInit(bList *blp);
void bListRelease(bList *blp);


void bListAppend(bList *blp, int a);

bList bListFromArray(int *a, size_t size);
bList bListFromBList(bList bl);


void bListForwardPrint(bList bl);
void bListReversePrint(bList bl);

#endif
