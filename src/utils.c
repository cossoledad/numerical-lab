#include "utils.h"

#include <stdio.h>

void clear_input_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* 丢弃当前输入行剩余字符。 */
    }
}

int read_int(const char *prompt, int *value)
{
    if (value == 0)
    {
        return 0;
    }

    if (prompt != 0)
    {
        printf("%s", prompt);
    }

    if (scanf("%d", value) != 1)
    {
        clear_input_line();
        return 0;
    }

    clear_input_line();
    return 1;
}

int read_double(const char *prompt, double *value)
{
    if (value == 0)
    {
        return 0;
    }

    if (prompt != 0)
    {
        printf("%s", prompt);
    }

    if (scanf("%lf", value) != 1)
    {
        clear_input_line();
        return 0;
    }

    clear_input_line();
    return 1;
}
