#include "optimize.h"

#include <math.h>

OptimizeResult golden_section_minimize(
    MathFunction f,
    double left,
    double right,
    double tolerance,
    int max_iterations
)
{
    OptimizeResult result = {0.0, 0.0, 0, 0};

    if (f == 0 || left >= right ||
        tolerance <= 0.0 || max_iterations <= 0)
    {
        return result;
    }

    /*
     * 黄金分割比例：
     *     φ = (sqrt(5)-1)/2 ≈ 0.618
     */
    const double ratio = (sqrt(5.0) - 1.0) / 2.0;

    double x1 = right - ratio * (right - left);
    double x2 = left + ratio * (right - left);
    double f1 = f(x1);
    double f2 = f(x2);

    for (int i = 1; i <= max_iterations; ++i)
    {
        result.iterations = i;

        if (fabs(right - left) < tolerance)
        {
            result.x = 0.5 * (left + right);
            result.fx = f(result.x);
            result.converged = 1;
            return result;
        }

        if (f1 < f2)
        {
            right = x2;
            x2 = x1;
            f2 = f1;

            x1 = right - ratio * (right - left);
            f1 = f(x1);
        }
        else
        {
            left = x1;
            x1 = x2;
            f1 = f2;

            x2 = left + ratio * (right - left);
            f2 = f(x2);
        }
    }

    result.x = 0.5 * (left + right);
    result.fx = f(result.x);

    return result;
}
