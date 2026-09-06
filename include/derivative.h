#ifndef NUMERICAL_LAB_DERIVATIVE_H
#define NUMERICAL_LAB_DERIVATIVE_H

#include "common.h"

/*
 * 数值微分模块。
 *
 * 前向差分：
 *     f'(x) ≈ [f(x+h)-f(x)] / h
 *
 * 中心差分：
 *     f'(x) ≈ [f(x+h)-f(x-h)] / (2h)
 */

double derivative_forward(MathFunction f, double x, double h);
double derivative_central(MathFunction f, double x, double h);

#endif
