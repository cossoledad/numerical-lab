#include "derivative.h"
#include "integration.h"
#include "matrix.h"
#include "monte_carlo.h"
#include "numeric_error.h"
#include "ode.h"
#include "optimize.h"
#include "regression.h"
#include "root.h"
#include "statistics.h"
#include "utils.h"

#include <big_number.h>
#include <blist.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

/*
 * main.c
 *
 * 这个文件负责：
 *     1. 程序菜单；
 *     2. 准备各个数值实验所需的数学函数；
 *     3. 调用不同模块；
 *     4. 展示结果。
 *
 * 每个数值算法的具体实现都放在独立 .c 文件中，
 * 从而展示真实 C 项目的模块化组织方式。
 */

static double root_function(double x)
{
    /* 示例方程：x^3 + x - 1 = 0 */
    return x * x * x + x - 1.0;
}

static double root_function_derivative(double x)
{
    return 3.0 * x * x + 1.0;
}

static double gaussian_function(double x)
{
    /*
     * e^(-x²)
     *
     * 它的原函数无法使用有限个初等函数写出，
     * 因而非常适合展示数值积分的价值。
     */
    return exp(-x * x);
}

static double square_function(double x)
{
    return x * x;
}

static double cooling_ode(double t, double temperature)
{
    /*
     * Newton 冷却定律：
     *
     *     dT/dt = -k(T - T_env)
     */
    (void)t;

    const double room_temperature = 20.0;
    const double k = 0.10;

    return -k * (temperature - room_temperature);
}

static double optimization_function(double x)
{
    /*
     * 一个简单但非纯二次的目标函数。
     */
    return (x - 2.0) * (x - 2.0) + 0.3 * sin(3.0 * x);
}

static void run_root_demo(void)
{
    RootOptions options;
    options.tolerance = 1.0e-10;
    options.max_iterations = 100;

    RootResult bisection =
        root_bisection(root_function, 0.0, 1.0, options);

    RootResult newton =
        root_newton(
            root_function,
            root_function_derivative,
            0.5,
            options);

    printf("\n=== 非线性方程求根 ===\n");
    printf("方程: x^3 + x - 1 = 0\n");

    printf("\n二分法:\n");
    printf("root       = %.12f\n", bisection.root);
    printf("residual   = %.3e\n", bisection.residual);
    printf("iterations = %d\n", bisection.iterations);
    printf("converged  = %s\n",
           bisection.converged ? "yes" : "no");

    printf("\nNewton 法:\n");
    printf("root       = %.12f\n", newton.root);
    printf("residual   = %.3e\n", newton.residual);
    printf("iterations = %d\n", newton.iterations);
    printf("converged  = %s\n",
           newton.converged ? "yes" : "no");
}

static void run_integration_demo(void)
{
    const double a = 0.0;
    const double b = 1.0;
    const int n = 100;

    double midpoint =
        integrate_midpoint(gaussian_function, a, b, n);

    double trapezoid =
        integrate_trapezoid(gaussian_function, a, b, n);

    double simpson =
        integrate_simpson(gaussian_function, a, b, n);

    printf("\n=== 数值积分 ===\n");
    printf("积分: ∫[0,1] exp(-x^2) dx\n");
    printf("Midpoint  = %.12f\n", midpoint);
    printf("Trapezoid = %.12f\n", trapezoid);
    printf("Simpson   = %.12f\n", simpson);
}

static void run_derivative_demo(void)
{
    const double x = 2.0;
    const double exact = 4.0;

    printf("\n=== 数值微分 ===\n");
    printf("函数: f(x) = x^2, 在 x=2 处导数精确值为 4\n");

    const double h_values[] =
        {
            1.0e-1,
            1.0e-3,
            1.0e-5,
            1.0e-7};

    const int count =
        (int)(sizeof(h_values) / sizeof(h_values[0]));

    for (int i = 0; i < count; ++i)
    {
        double h = h_values[i];

        double forward =
            derivative_forward(square_function, x, h);

        double central =
            derivative_central(square_function, x, h);

        printf(
            "h=%-10.1e forward=%-14.10f central=%-14.10f "
            "central_error=%.3e\n",
            h,
            forward,
            central,
            fabs(central - exact));
    }
}

static void print_ode_sample(
    const char *name,
    const ODEPoint *points,
    int count)
{
    printf("\n%s\n", name);
    printf("%10s %15s\n", "time", "temperature");

    /*
     * 避免输出过多，只打印部分点。
     */
    int stride = count / 10;

    if (stride < 1)
    {
        stride = 1;
    }

    for (int i = 0; i < count; i += stride)
    {
        printf("%10.2f %15.6f\n",
               points[i].t,
               points[i].y);
    }

    if (count > 0 && (count - 1) % stride != 0)
    {
        printf("%10.2f %15.6f\n",
               points[count - 1].t,
               points[count - 1].y);
    }
}

static void run_ode_demo(void)
{
    enum
    {
        CAPACITY = 200
    };

    ODEPoint euler_points[CAPACITY];
    ODEPoint rk4_points[CAPACITY];

    int euler_count = ode_euler(
        cooling_ode,
        0.0,
        90.0,
        30.0,
        0.5,
        euler_points,
        CAPACITY);

    int rk4_count = ode_rk4(
        cooling_ode,
        0.0,
        90.0,
        30.0,
        0.5,
        rk4_points,
        CAPACITY);

    printf("\n=== Newton 冷却定律 ===\n");
    printf("初始温度 90°C，环境温度 20°C\n");

    print_ode_sample("Euler:", euler_points, euler_count);
    print_ode_sample("RK4:", rk4_points, rk4_count);
}

static void run_matrix_demo(void)
{
    /*
     * 求解：
     *
     *  2x +  y -  z =  8
     * -3x -  y + 2z = -11
     * -2x +  y + 2z = -3
     *
     * 精确解：
     * x=2, y=3, z=-1
     */
    Matrix A = matrix_create(3, 3);

    if (A.data == 0)
    {
        printf("矩阵内存分配失败。\n");
        return;
    }

    const double values[3][3] =
        {
            {2.0, 1.0, -1.0},
            {-3.0, -1.0, 2.0},
            {-2.0, 1.0, 2.0}};

    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            matrix_set(&A, r, c, values[r][c]);
        }
    }

    double b[3] = {8.0, -11.0, -3.0};
    double x[3] = {0.0, 0.0, 0.0};

    printf("\n=== 线性方程组 ===\n");

    if (solve_linear_system(&A, b, x))
    {
        printf("x = %.6f\n", x[0]);
        printf("y = %.6f\n", x[1]);
        printf("z = %.6f\n", x[2]);
    }
    else
    {
        printf("求解失败：矩阵可能奇异。\n");
    }

    matrix_free(&A);
}

static void run_regression_demo(void)
{
    /*
     * 模拟带测量噪声的匀速运动数据。
     */
    const double x[] =
        {
            0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

    const double y[] =
        {
            0.1, 2.0, 4.1, 5.9, 8.2, 9.8};

    const int n = (int)(sizeof(x) / sizeof(x[0]));

    LinearRegressionResult result =
        linear_regression(x, y, n);

    printf("\n=== 最小二乘线性拟合 ===\n");
    printf("模型: y = a*x + b\n");
    printf("a = %.6f\n", result.slope);
    printf("b = %.6f\n", result.intercept);
    printf("R^2 = %.6f\n", result.r_squared);
}

static void run_optimize_demo(void)
{
    OptimizeResult result =
        golden_section_minimize(
            optimization_function,
            0.0,
            4.0,
            1.0e-10,
            100);

    printf("\n=== 一维函数最小化 ===\n");
    printf("f(x) = (x-2)^2 + 0.3*sin(3x)\n");
    printf("x_min = %.12f\n", result.x);
    printf("f_min = %.12f\n", result.fx);
    printf("iterations = %d\n", result.iterations);
    printf("converged = %s\n",
           result.converged ? "yes" : "no");
}

static void run_monte_carlo_demo(void)
{
    const long samples = 500000;

    double pi_estimate =
        monte_carlo_pi(samples);

    double integral_estimate =
        monte_carlo_integral(
            gaussian_function,
            0.0,
            1.0,
            samples);

    printf("\n=== Monte Carlo ===\n");
    printf("samples = %ld\n", samples);
    printf("pi estimate = %.8f\n", pi_estimate);
    printf("integral estimate = %.8f\n", integral_estimate);
}

static void run_statistics_demo(void)
{
    const double temperatures[] =
        {
            21.5, 22.1, 19.8, 20.4, 23.0, 24.2, 22.7};

    const int n =
        (int)(sizeof(temperatures) /
              sizeof(temperatures[0]));

    StatisticsResult result =
        statistics_analyze(temperatures, n);

    printf("\n=== 基础统计 ===\n");
    printf("min  = %.3f\n", result.min);
    printf("max  = %.3f\n", result.max);
    printf("mean = %.3f\n", result.mean);
    printf("variance = %.6f\n", result.variance);
    printf("stddev   = %.6f\n",
           result.standard_deviation);
}

static void run_numeric_error_demo(void)
{
    printf("\n=== 浮点数与数值误差 ===\n");
    demo_floating_point_equality();
    demo_catastrophic_cancellation();
    demo_summation_order();
}

static void print_menu(void)
{
    printf("\n");
    printf("=============================================\n");
    printf(" Numerical Lab\n");
    printf("=============================================\n");
    printf("1. 非线性方程求根\n");
    printf("2. 数值积分\n");
    printf("3. 数值微分\n");
    printf("4. 常微分方程\n");
    printf("5. 线性方程组\n");
    printf("6. 最小二乘拟合\n");
    printf("7. 函数最小化\n");
    printf("8. Monte Carlo\n");
    printf("9. 基础统计\n");
    printf("10. 浮点数与数值误差\n");
    printf("0. 退出\n");
    printf("=============================================\n");
}

int main(void)
{

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    char a100[] = "43612987461293179";
    char b100[] = "471895437891";

    bString aa100 = bStringFromCString(a100);
    bString bb100 = bStringFromCString(b100);

    bString *b = (bString *)calloc(1, sizeof(bString));
    add(&aa100, &bb100, &b);

    bStringPrint(b);
    bStringRelease(b);


    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    bList bl = bListFromArray(a, 10);
    bList nbl = bListFromBList(bl);
    bListForwardPrint(bl);
    bListReversePrint(nbl);

    /*
     * rand() 是伪随机数生成器。
     * 使用当前时间作为种子，使每次 Monte Carlo 结果略有不同。
     */
    srand((unsigned int)time(0));

    for (;;)
    {
        int choice = -1;

        print_menu();

        if (!read_int("请选择实验: ", &choice))
        {
            printf("输入无效，请输入整数。\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            run_root_demo();
            break;

        case 2:
            run_integration_demo();
            break;

        case 3:
            run_derivative_demo();
            break;

        case 4:
            run_ode_demo();
            break;

        case 5:
            run_matrix_demo();
            break;

        case 6:
            run_regression_demo();
            break;

        case 7:
            run_optimize_demo();
            break;

        case 8:
            run_monte_carlo_demo();
            break;

        case 9:
            run_statistics_demo();
            break;

        case 10:
            run_numeric_error_demo();
            break;

        case 0:
            printf("程序结束。\n");
            return 0;

        default:
            printf("未知选项。\n");
            break;
        }
    }
}
