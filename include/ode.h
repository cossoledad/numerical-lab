#ifndef NUMERICAL_LAB_ODE_H
#define NUMERICAL_LAB_ODE_H

#include "common.h"

/*
 * 一阶常微分方程：
 *
 *     y' = f(t, y)
 *     y(t0) = y0
 */

typedef struct
{
    double t;
    double y;
} ODEPoint;

/*
 * 使用 Euler 法求解。
 *
 * points:
 *     调用者提供的输出数组。
 *
 * capacity:
 *     数组最多可容纳多少个 ODEPoint。
 *
 * 返回值：
 *     实际写入的点数量。
 */
int ode_euler(
    ODEFunction f,
    double t0,
    double y0,
    double t1,
    double step,
    ODEPoint *points,
    int capacity
);

/*
 * 四阶 Runge-Kutta 法（RK4）。
 * 通常比 Euler 法精度更高。
 */
int ode_rk4(
    ODEFunction f,
    double t0,
    double y0,
    double t1,
    double step,
    ODEPoint *points,
    int capacity
);

#endif
