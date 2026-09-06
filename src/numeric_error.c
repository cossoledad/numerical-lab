#include "numeric_error.h"

#include <math.h>
#include <stdio.h>

void demo_floating_point_equality(void)
{
    double x = 0.1 + 0.2;
    double expected = 0.3;

    printf("\n[浮点相等比较]\n");
    printf("0.1 + 0.2 = %.17f\n", x);
    printf("0.3       = %.17f\n", expected);
    printf("直接比较 x == 0.3 : %s\n",
           x == expected ? "true" : "false");

    printf("误差比较 |x-0.3| < 1e-12 : %s\n",
           fabs(x - expected) < 1.0e-12 ? "true" : "false");
}

void demo_catastrophic_cancellation(void)
{
    const double x = 1.0e16;

    /*
     * 数学上：
     *
     * sqrt(x²+1)-x
     *
     * 与
     *
     * 1 / (sqrt(x²+1)+x)
     *
     * 完全等价。
     *
     * 但第一种写法会发生两个非常接近的大数相减，
     * 从而损失有效数字。
     */
    double unstable = sqrt(x * x + 1.0) - x;
    double stable = 1.0 / (sqrt(x * x + 1.0) + x);

    printf("\n[消去误差]\n");
    printf("x = %.0f\n", x);
    printf("直接公式 : %.17g\n", unstable);
    printf("等价变形 : %.17g\n", stable);
}

void demo_summation_order(void)
{
    /*
     * 浮点加法不满足严格意义上的结合律。
     *
     * (a+b)+c 与 a+(b+c) 在机器上可能不同。
     */
    double a = 1.0e16;
    double b = -1.0e16;
    double c = 1.0;

    double first = (a + b) + c;
    double second = a + (b + c);

    printf("\n[求和顺序]\n");
    printf("(a+b)+c = %.17g\n", first);
    printf("a+(b+c) = %.17g\n", second);
}
