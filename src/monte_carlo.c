#include "monte_carlo.h"

#include <stdlib.h>

static double random_01(void)
{
    /*
     * rand() 返回 [0, RAND_MAX] 的整数，
     * 除以 RAND_MAX 后映射到 [0,1]。
     */
    return (double)rand() / (double)RAND_MAX;
}

double monte_carlo_pi(long samples)
{
    if (samples <= 0)
    {
        return 0.0;
    }

    long inside = 0;

    for (long i = 0; i < samples; ++i)
    {
        double x = 2.0 * random_01() - 1.0;
        double y = 2.0 * random_01() - 1.0;

        if (x * x + y * y <= 1.0)
        {
            ++inside;
        }
    }

    return 4.0 * (double)inside / (double)samples;
}

double monte_carlo_integral(
    MathFunction f,
    double a,
    double b,
    long samples
)
{
    if (f == 0 || samples <= 0)
    {
        return 0.0;
    }

    double sum = 0.0;

    for (long i = 0; i < samples; ++i)
    {
        double x = a + (b - a) * random_01();
        sum += f(x);
    }

    return (b - a) * sum / (double)samples;
}
