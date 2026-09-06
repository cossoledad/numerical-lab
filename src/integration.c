#include "integration.h"

double integrate_midpoint(MathFunction f, double a, double b, int n)
{
    if (f == 0 || n <= 0)
    {
        return 0.0;
    }

    double h = (b - a) / (double)n;
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double x_mid = a + (i + 0.5) * h;
        sum += f(x_mid);
    }

    return sum * h;
}

double integrate_trapezoid(MathFunction f, double a, double b, int n)
{
    if (f == 0 || n <= 0)
    {
        return 0.0;
    }

    double h = (b - a) / (double)n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; ++i)
    {
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h;
}

double integrate_simpson(MathFunction f, double a, double b, int n)
{
    if (f == 0 || n <= 0)
    {
        return 0.0;
    }

    /*
     * Simpson 复合公式要求子区间数量为偶数。
     * 如果用户传入奇数，这里自动加 1。
     */
    if (n % 2 != 0)
    {
        ++n;
    }

    double h = (b - a) / (double)n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; ++i)
    {
        double x = a + i * h;

        if (i % 2 == 0)
        {
            sum += 2.0 * f(x);
        }
        else
        {
            sum += 4.0 * f(x);
        }
    }

    return sum * h / 3.0;
}
