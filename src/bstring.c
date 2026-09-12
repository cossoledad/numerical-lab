#include <bstring.h>

#include <stdio.h>

bString bStringCreate()
{
    bString bs;
    bs.size = 0;
    bs.data = 0;
    return bs;
}

void bStringRelease(bString *bsp)
{
    if (bsp->data != 0)
    {
        free(bsp->data);
    }
    bsp->data = 0;
    bsp->size = 0;
}

void bStringResize(bString *bsp, size_t ns)
{
    if (ns < bsp->size)
    {
        bsp->size = ns;
        return;
    }
    char *buf = (char *)calloc(ns, sizeof(char));
    for (size_t i = 0; i < bsp->size; i++)
    {
        buf[i] = bsp->data[i];
    }
    bStringRelease(bsp);
    bsp->data = buf;
    bsp->size = ns;
}

size_t cStringSize(char *cs)
{
    if (!cs)
    {
        return 0;
    }
    size_t size = 0;
    char *cp = cs;
    while (*cp != '\0')
    {
        size++;
        cp++;
    }
    return size;
}

bString bStringFromCString(char *cs)
{
    bString bs = bStringCreate();
    bStringResize(&bs, cStringSize(cs));

    for (size_t i = 0; i < bs.size; i++)
    {
        bs.data[i] = cs[i];
    }
    return bs;
}

void bStringAppendChar(bString *bsp, char c)
{

    bStringResize(bsp, bsp->size + 1);
    bsp->data[bsp->size - 1] = c;
}

void bStringAppendCString(bString *bsp, char *cs)
{
    size_t csl = cStringSize(cs);
    bStringResize(bsp, bsp->size + csl);

    for (size_t i = 0; i < csl; i++)
    {
        bsp->data[bsp->size - csl + i] = cs[i];
    }
}
void bStringAppendBString(bString *bsp, bString cbsp)
{
    bStringResize(bsp, bsp->size + cbsp.size);
    for (size_t i = 0; i < cbsp.size; i++)
    {
        bsp->data[bsp->size - cbsp.size + i] = cbsp.data[i];
    }
}

void bStringPrint(bString bs)
{
    for (size_t i = 0; i < bs.size; i++)
    {
        printf("%c", bs.data[i]);
    }
    printf("\n");
}
