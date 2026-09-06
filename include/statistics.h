#ifndef NUMERICAL_LAB_STATISTICS_H
#define NUMERICAL_LAB_STATISTICS_H

typedef struct
{
    double min;
    double max;
    double mean;
    double variance;
    double standard_deviation;
} StatisticsResult;

StatisticsResult statistics_analyze(
    const double *values,
    int n
);

#endif
