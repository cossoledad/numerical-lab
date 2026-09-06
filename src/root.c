#include "root.h"

#include <math.h>

RootResult root_bisection(
    MathFunction f,
    double left,
    double right,
    RootOptions options
)
{
    RootResult result = {0.0, 0.0, 0, 0};

    if (f == 0 || options.tolerance <= 0.0 || options.max_iterations <= 0)
    {
        return result;
    }

    double f_left = f(left);
    double f_right = f(right);

    /*
     * 二分法要求区间两端函数值异号，
     * 从连续函数介值定理可以知道区间内部至少存在一个根。
     */
    if (f_left * f_right > 0.0)
    {
        return result;
    }

    for (int i = 1; i <= options.max_iterations; ++i)
    {
        double mid = 0.5 * (left + right);
        double f_mid = f(mid);

        result.root = mid;
        result.residual = fabs(f_mid);
        result.iterations = i;

        if (fabs(f_mid) < options.tolerance ||
            fabs(right - left) < options.tolerance)
        {
            result.converged = 1;
            return result;
        }

        if (f_left * f_mid <= 0.0)
        {
            right = mid;
            f_right = f_mid;
        }
        else
        {
            left = mid;
            f_left = f_mid;
        }
    }

    (void)f_right;
    return result;
}

RootResult root_newton(
    MathFunction f,
    MathFunction derivative,
    double initial_guess,
    RootOptions options
)
{
    RootResult result = {initial_guess, 0.0, 0, 0};

    if (f == 0 || derivative == 0 ||
        options.tolerance <= 0.0 || options.max_iterations <= 0)
    {
        return result;
    }

    double x = initial_guess;

    for (int i = 1; i <= options.max_iterations; ++i)
    {
        double fx = f(x);
        double dfx = derivative(x);

        /*
         * Newton 法需要除以导数。
         * 如果导数接近 0，更新步会非常不稳定。
         */
        if (fabs(dfx) < 1.0e-14)
        {
            result.root = x;
            result.residual = fabs(fx);
            result.iterations = i;
            return result;
        }

        double next = x - fx / dfx;

        result.root = next;
        result.residual = fabs(f(next));
        result.iterations = i;

        if (fabs(next - x) < options.tolerance ||
            result.residual < options.tolerance)
        {
            result.converged = 1;
            return result;
        }

        x = next;
    }

    return result;
}
