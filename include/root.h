#ifndef NUMERICAL_LAB_ROOT_H
#define NUMERICAL_LAB_ROOT_H

#include "common.h"

/*
 * 非线性方程求根模块。
 *
 * 目标：
 *     求 f(x) = 0 的近似解。
 *
 * 涉及 C 知识：
 *     enum、struct、函数指针、循环、条件判断、返回值。
 */

typedef enum
{
    ROOT_METHOD_BISECTION = 1,
    ROOT_METHOD_NEWTON = 2
} RootMethod;

typedef struct
{
    double tolerance;      /* 收敛容差 */
    int max_iterations;    /* 最大迭代次数 */
} RootOptions;

typedef struct
{
    double root;           /* 求得的根 */
    double residual;       /* |f(root)| */
    int iterations;        /* 实际迭代次数 */
    int converged;         /* 1 表示收敛，0 表示失败 */
} RootResult;

RootResult root_bisection(
    MathFunction f,
    double left,
    double right,
    RootOptions options
);

RootResult root_newton(
    MathFunction f,
    MathFunction derivative,
    double initial_guess,
    RootOptions options
);

#endif
