#include "statistics.h"

#include <math.h>

StatisticsResult statistics_analyze(
    const double *values,
    int n
)
{
    StatisticsResult result = {0.0, 0.0, 0.0, 0.0, 0.0};

    if (values == 0 || n <= 0)
    {
        return result;
    }

    result.min = values[0];
    result.max = values[0];

    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        if (values[i] < result.min)
        {
            result.min = values[i];
        }

        if (values[i] > result.max)
        {
            result.max = values[i];
        }

        sum += values[i];
    }

    result.mean = sum / n;

    double squared_sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double diff = values[i] - result.mean;
        squared_sum += diff * diff;
    }

    /*
     * 这里计算的是总体方差，分母使用 n。
     * 若把数据视为样本，可改为 n-1。
     */
    result.variance = squared_sum / n;
    result.standard_deviation = sqrt(result.variance);

    return result;
}
