#include <bits/stdc++.h>
#include <ctime>

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
    int countOfOperations = 0;
    double start = clock();
    while (x <= r)
    {
        countOfOperations++;
        temp = f(x);
        if (temp < mn)
            mn = temp,
            val = x;
        x += eps;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return val;
}

double dihotomia()
{
    double c, d, a = l, b = r;
    int countOfOperations = 0;
    double start = clock();
    do
    {
        countOfOperations++;
        c = a + (b - a) / 2 - delta / 2;
        d = a + (b - a) / 2 + delta / 2;
        if (f(c) >= f(d))
            a = c;
        else
            b = d;
    }
    while (b - a > 2 * eps);
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return a + (b - a) / 2;
}

double fi()
{
    double c, d, a = l, b = r;
    int countOfOperations = 0;
    double start = clock();
    do
    {
        countOfOperations++;
        c = a + (3 - sqrt(5)) * (b - a) / 2;
        d = b - (3 - sqrt(5)) * (b - a) / 2;
        if (f(c) >= f(d))
            a = c;
        else
            b = d;
    }
    while (b - a > 2 * eps);
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return a + (b - a) / 2;
}

double tangents()
{
    double c, d, a = l, b = r;
    int countOfOperations = 0;
    double start = clock();
    do
    {
        countOfOperations++;
        c = (f(b) - f(a) + ff(a) * a - ff(b) * b) / (ff(a) - ff(b));
        if (ff(c) >= 0)
            b = c;
        else
            a = c;
    }
    while (b - a > 2 * eps);
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return c;
}

double newton()
{
    double xk, xprev = 0;
    int countOfOperations = 0;
    double start = clock();
    do
    {
        countOfOperations++;
        xk = xprev - ff(xprev) / fff(xprev);
        xprev = xk;
    }
    while (fabs(ff(xk)) > eps);
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return xk;
}

double chord()
{
    double xk, xprev = r, xprevprev = l;
    int countOfOperations = 0;
    double start = clock();
    do
    {
        countOfOperations++;
        xk = xprev - (xprev - xprevprev) * ff(xprev) / (ff(xprev) - ff(xprevprev));
        xprevprev = xprev;
        xprev = xk;
    }
    while (fabs(ff(xk)) > eps);
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return xk;
}

int main()
{
    cout << "passiveSearch:\n" << passiveSearch() << endl << endl;
    cout << "dihotomia:\n" << dihotomia() << endl << endl;
    cout << "gold:\n" << fi() << endl << endl;
    cout << "tangents:\n" << tangents() << endl << endl;
    cout << "newton:\n" << newton() << endl << endl;
    cout << "chord:\n" << chord() << endl << endl;
    return 0;
}
