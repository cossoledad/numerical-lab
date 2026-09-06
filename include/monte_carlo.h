#ifndef NUMERICAL_LAB_MONTE_CARLO_H
#define NUMERICAL_LAB_MONTE_CARLO_H

#include "common.h"

/* 使用随机点估计圆周率 π。 */
double monte_carlo_pi(long samples);

/*
 * 使用简单 Monte Carlo 方法估计：
 *
 *     ∫[a,b] f(x) dx
 */
double monte_carlo_integral(
    MathFunction f,
    double a,
    double b,
    long samples
);

#endif
