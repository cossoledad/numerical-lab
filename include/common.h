#ifndef NUMERICAL_LAB_COMMON_H
#define NUMERICAL_LAB_COMMON_H

/*
 * common.h
 *
 * 放置整个项目中多个模块都会使用的公共类型。
 *
 * MathFunction:
 *     表示一个数学函数 y = f(x)。
 *
 * ODEFunction:
 *     表示一阶常微分方程 y' = f(t, y) 的右端函数。
 */

typedef double (*MathFunction)(double x);
typedef double (*ODEFunction)(double t, double y);

#endif
