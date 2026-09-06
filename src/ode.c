#include "ode.h"

static int validate_input(
    ODEFunction f,
    double t0,
    double t1,
    double step,
    const ODEPoint *points,
    int capacity
)
{
    if (f == 0 || points == 0 || capacity <= 0 || step <= 0.0)
    {
        return 0;
    }

    if (t1 < t0)
    {
        return 0;
    }

    return 1;
}

int ode_euler(
    ODEFunction f,
    double t0,
    double y0,
    double t1,
    double step,
    ODEPoint *points,
    int capacity
)
{
    if (!validate_input(f, t0, t1, step, points, capacity))
    {
        return 0;
    }

    double t = t0;
    double y = y0;
    int count = 0;

    while (t <= t1 + 1.0e-12 && count < capacity)
    {
        points[count].t = t;
        points[count].y = y;
        ++count;

        y = y + step * f(t, y);
        t = t + step;
    }

    return count;
}

int ode_rk4(
    ODEFunction f,
    double t0,
    double y0,
    double t1,
    double step,
    ODEPoint *points,
    int capacity
)
{
    if (!validate_input(f, t0, t1, step, points, capacity))
    {
        return 0;
    }

    double t = t0;
    double y = y0;
    int count = 0;

    while (t <= t1 + 1.0e-12 && count < capacity)
    {
        points[count].t = t;
        points[count].y = y;
        ++count;

        /*
         * RK4:
         *
         * k1 = f(t, y)
         * k2 = f(t+h/2, y+h*k1/2)
         * k3 = f(t+h/2, y+h*k2/2)
         * k4 = f(t+h,   y+h*k3)
         */
        double k1 = f(t, y);
        double k2 = f(t + step / 2.0, y + step * k1 / 2.0);
        double k3 = f(t + step / 2.0, y + step * k2 / 2.0);
        double k4 = f(t + step, y + step * k3);

        y = y + step * (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
        t = t + step;
    }

    return count;
}
