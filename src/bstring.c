#include <bstring.h>

#include <stdio.h>

bString bStringCreate()
{
    bString bs;
    bs.size = 0;
    bs.data = 0;
}

size_t cStringSize(char *cs)
{
    if (!cs)
    {
        return 0;
    }
    size_t size = 0;
    char *cp = cs;
    while (cp != '\0')
    {
        size++;
        cp++;
    }
    return size;
}

bString bStringFromCString(char *cs)
{
    bString bs;
    bs.size = cStringSize(cs);
    bs.data = (char *)calloc(bs.size, sizeof(char));

    for (size_t i = 0; i < bs.size; i++)
    {
        bs.data[i] = cs[i];
    }
}

void bStringAppendChar(bString *bsp, char);
void bStringAppendCString(bString *bsp, char *cs);
void bStringAppendBString(bString *bsp, bString);

void bStringPrint(bString bs)
{
    for (size_t i = 0; i < bs.size; i++)
    {
        printf("%c", bs.data[i]);
    }
    printf("\n");
}
