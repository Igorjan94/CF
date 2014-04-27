#include <bits/stdc++.h>

using namespace std;

static const double eps = 0.05, delta = 0.01;
static const double l = 1., r = 1.5;

double f(double x)
{
    return pow(x, 7) / 7 - pow(x, 3) + x * x / 2 - x;
}

double ff(double x)
{
    return pow(x, 6) - 3 * pow(x, 2) + x - 1;
}

double fff(double x)
{
    return 6 * pow(x, 5) - 6 * x + 1;
}

double passiveSearch()
{
    double x = l, val = l;
    double mn = f(x), temp;
    while (x <= r)
    {
        temp = f(x);
        if (temp < mn)
            mn = temp,
            val = x;
        x += eps;
    }
    return val;
}

double dihotomia()
{
    double c, d, a = l, b = r;
    do
    {
        c = a + (b - a) / 2 - delta / 2;
        d = a + (b - a) / 2 + delta / 2;
        if (f(c) >= f(d))
            a = c;
        else
            b = d;
    }
    while (b - a > 2 * eps);
    return a + (b - a) / 2;
}

double fi()
{
    double c, d, a = l, b = r;
    do
    {
        c = a + (3 - sqrt(5)) * (b - a) / 2;
        d = b - (3 - sqrt(5)) * (b - a) / 2;
        if (f(c) >= f(d))
            a = c;
        else
            b = d;
    }
    while (b - a > 2 * eps);
    return a + (b - a) / 2;
}

double tangents()
{
    double c, d, a = l, b = r;
    do
    {
        c = (f(b) - f(a) + ff(a) * a - ff(b) * b) / (ff(a) - ff(b));
        if (ff(c) >= 0)
            b = c;
        else
            a = c;
    }
    while (b - a > 2 * eps);
    return c;
}

double newton()
{
    double xk, xprev = l;
    do
    {
        xk = xprev - ff(xprev) / fff(xprev);
        xprev = xk;
    }
    while (fabs(ff(xk)) > eps);
    return xk;
}

double chord()
{
    double xk, xprev = r, xprevprev = l;
    do
    {
        xk = xprev - (xprev - xprevprev) * ff(xprev) / (ff(xprev) - ff(xprevprev));
        xprevprev = xprev;
        xprev = xk;
    }
    while (fabs(ff(xk)) > eps);
    return xk;
}

double grad_step_before()
{
    double xk, xprev = l, alpha = 0.05;
    do
    {
        xk = xprev - ff(xprev) * alpha;
        xprev = xk;
    }
    while (fabs(ff(xk)) > eps);
    return xk;
}

double grad_step_drob()
{
    double xk, xprev = l, alpha = 0.9;
    do
    {
        while (f(xk) - f(xprev) > -alpha * ff(xprev) * ff(xprev) * eps)
            xk = xprev - ff(xprev) * alpha,
            alpha *= 0.9;
        xprev = xk;
    }
    while (fabs(ff(xk)) > eps);
    return xk;
}

int main()
{
    cout << passiveSearch() << endl;
    cout << dihotomia() << endl;
    cout << fi() << endl;
    cout << tangents() << endl;
    cout << newton() << endl;
    cout << chord() << endl;
    cout << grad_step_before() << endl;
    cout << grad_step_drob() << endl;
    return 0;
}
