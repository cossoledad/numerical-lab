#ifndef NUMERICAL_LAB_INTEGRATION_H
#define NUMERICAL_LAB_INTEGRATION_H

#include "common.h"

/*
 * 数值积分模块。
 *
 * 计算定积分：
 *
 *      ∫[a,b] f(x) dx
 *
 * 当原函数无法用初等函数表达时，数值积分仍然可以得到近似值。
 */

double integrate_midpoint(MathFunction f, double a, double b, int n);
double integrate_trapezoid(MathFunction f, double a, double b, int n);
double integrate_simpson(MathFunction f, double a, double b, int n);

#endif
