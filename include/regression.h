#ifndef NUMERICAL_LAB_REGRESSION_H
#define NUMERICAL_LAB_REGRESSION_H

/*
 * 一元线性最小二乘拟合：
 *
 *     y ≈ slope * x + intercept
 */

typedef struct
{
    double slope;
    double intercept;
    double r_squared;
} LinearRegressionResult;

LinearRegressionResult linear_regression(
    const double *x,
    const double *y,
    int n
);

#endif
