#ifndef NUMERICAL_LAB_OPTIMIZE_H
#define NUMERICAL_LAB_OPTIMIZE_H

#include "common.h"

/*
 * 一维函数最小化。
 *
 * 黄金分割搜索要求目标函数在给定区间内近似单峰。
 */
typedef struct
{
    double x;
    double fx;
    int iterations;
    int converged;
} OptimizeResult;

OptimizeResult golden_section_minimize(
    MathFunction f,
    double left,
    double right,
    double tolerance,
    int max_iterations
);

#endif
