#include "derivative.h"

double derivative_forward(MathFunction f, double x, double h)
{
    if (f == 0 || h == 0.0)
    {
        return 0.0;
    }

    return (f(x + h) - f(x)) / h;
}

double derivative_central(MathFunction f, double x, double h)
{
    if (f == 0 || h == 0.0)
    {
        return 0.0;
    }

    return (f(x + h) - f(x - h)) / (2.0 * h);
}
