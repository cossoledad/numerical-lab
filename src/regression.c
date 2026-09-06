#include "regression.h"

#include <math.h>

LinearRegressionResult linear_regression(
    const double *x,
    const double *y,
    int n
)
{
    LinearRegressionResult result = {0.0, 0.0, 0.0};

    if (x == 0 || y == 0 || n < 2)
    {
        return result;
    }

    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xx = 0.0;
    double sum_xy = 0.0;

    for (int i = 0; i < n; ++i)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_xx += x[i] * x[i];
        sum_xy += x[i] * y[i];
    }

    double denominator =
        n * sum_xx - sum_x * sum_x;

    if (fabs(denominator) < 1.0e-14)
    {
        return result;
    }

    result.slope =
        (n * sum_xy - sum_x * sum_y) / denominator;

    result.intercept =
        (sum_y - result.slope * sum_x) / n;

    /*
     * R² = 1 - SSE/SST
     *
     * 越接近 1，说明拟合对数据变化的解释程度越高。
     */
    double mean_y = sum_y / n;
    double sse = 0.0;
    double sst = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double predicted =
            result.slope * x[i] + result.intercept;

        double residual = y[i] - predicted;
        double centered = y[i] - mean_y;

        sse += residual * residual;
        sst += centered * centered;
    }

    result.r_squared =
        (sst > 1.0e-14) ? 1.0 - sse / sst : 1.0;

    return result;
}
