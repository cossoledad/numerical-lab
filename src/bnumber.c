#include <bnumber.h>
#include <stdlib.h>
#include <stdio.h>

void bNumberInit(bNumber *a, size_t s)
{
    a->size = s;
    a->buffer = (char *)calloc(a->size, sizeof(char));
}
void bNumberRelease(bNumber *a)
{
    free(a->buffer);
    a->buffer = 0;
    a->size = 0;
}
void bNumberExpansion(bNumber **a)
{
    bNumber *b = (bNumber *)calloc(1, sizeof(bNumber));
    bNumberInit(b, (*a)->size + 1);
    for (size_t i = 0; i < (*a)->size; i++)
    {
        b->buffer[i] = (*a)->buffer[i];
    }
    bNumberRelease(*a);
    *a = b;
}

void bNumberSwap(bNumber **a, bNumber **b)
{
    bNumber *aa = *a;
    *a = *b;
    *b = aa;
}

void bNumberPrint(bNumber *a)
{
    for (size_t i = a->size; i > 0; i--)
    {
        printf("%c", a->buffer[i - 1]);
    }
    printf("\n");
}

bNumber bNumberFromCString(char *c)
{
    char *i = c;
    size_t s = 0;
    while (*i != '\0')
    {
        s++;
        i++;
    }
    bNumber b;
    bNumberInit(&b, s);
    for (size_t index = 0; index < s; index++)
    {
        b.buffer[s - 1 - index] = *(c + index);
    }
    return b;
}

char halfAdder(char *a, char *b, char *c)
{

    char d = (*a + *b) - 48;
    if (d > 57)
    {
        *c = d - 10;
        return 1;
    }
    else
    {
        *c = d;
        return 0;
    }
}

char fullAdder(char *a, char *b, char *d, char *c)
{
    char ab;
    char j1 = halfAdder(a, b, &ab);
    char j2 = halfAdder(&ab, d, c);

    return (j1 || j2) + 48;
}

void add(bNumber *a, bNumber *b, bNumber **out)
{

    char d = 48;
    char d0 = 48;

    if (a->size < b->size)
    {
        bNumberSwap(&a, &b);
    }
    bNumberInit((*out), a->size);

    for (size_t i = 0; i < b->size; i++)
    {
        d = fullAdder(a->buffer + i, b->buffer + i, &d, (*out)->buffer + i);
    }
    for (size_t i = b->size; i < a->size; i++)
    {
        d = fullAdder(a->buffer + i, &d0, &d, (*out)->buffer + i);
    }
    if (d == '1')
    {
        bNumberExpansion(out);
        (*out)->buffer[(*out)->size - 1] = '1';
    }
}