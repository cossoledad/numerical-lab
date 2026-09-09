#include <blist.h>

#include <stdlib.h>

void bListInit(bList *blp)
{
    blp->size = 0;
    blp->front = (bListNode *)calloc(1, sizeof(bListNode));
    blp->back = (bListNode *)calloc(1, sizeof(bListNode));

    blp->front->pre = 0;
    blp->front->nxt = blp->back;

    blp->back->pre = blp->front;
    blp->back->nxt = 0;
}

void bListRelease(bList *blp)
{
    bListNode *itp = blp->front->nxt;
    while (itp != blp->back)
    {
        bListNode *relItp = itp;
        itp = itp->nxt;
        free(relItp);
    }
    free(blp->front);
    free(blp->front);
    blp->size = -1;
}

void bListAppend(bList *blp, int a)
{
    bListNode *endprep = blp->back->pre;

    bListNode *ap = (bListNode *)calloc(1, sizeof(bListNode));
    ap->data = a;

    endprep->nxt = ap;
    ap->pre = endprep;

    blp->back->pre = ap;
    ap->nxt = blp->back;
}

bList bListFromArray(int *a, size_t size)
{
    bList bl;
    bListInit(&bl);
    for (size_t i = 0; i < size; i++)
    {
        bListAppend(&bl, a[i]);
    }
    return bl;
}

bList bListFromBList(bList bl)
{
    bList nbl;
    bListInit(&nbl);

    bListNode *itp = bl.front->nxt;
    while (itp != bl.back)
    {
        bListAppend(&nbl, itp->data);
        itp = itp->nxt;
    }
    return nbl;
}

void bListForwardPrint(bList bl)
{
    bListNode *itp = bl.front->nxt;
    while (itp != bl.back)
    {
        printf("%d ", itp->data);
        itp = itp->nxt;
    }
    printf("\n");
}

void bListReversePrint(bList bl)
{
    bListNode *itp = bl.back->pre;
    while (itp != bl.front)
    {
        printf("%d ", itp->data);
        itp = itp->pre;
    }
    printf("\n");
}
