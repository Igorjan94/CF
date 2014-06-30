#include <bits/stdc++.h>
#include <ctime>
#include "../write.h"

using namespace std;
using namespace std::placeholders;

static const double eps = 0.01;
static const double delta = 0.001;
static const double l = -100000., r = 500.;

long long cnk(int n, int m)
{
    return m == 0 || n == m ? 1 : cnk(n - 1, m) + cnk(n - 1, m - 1);
}

std::function<double(double)> df(std::function<double(double)> f)
{

    return [f](double x)
    {
        double ans = f(x + delta) - f(x);
        double t = ans;
        int sign = -1;
        for (int i = 1; i <= 5; i++, sign *= -1)
        {
            double tcur = 0;
            for (int j = 0, s = 1; j <= i; j++, s *= -1)
                tcur += s * cnk(i, j) * f(x + delta * (i - j + 1));
            t = tcur - t;
            ans += sign * t / (i + 1);
        }
        return ans / delta;
    };
}

double f(double x)
{
    return pow(x - 2, 4) * 8 + pow(x + 3, 2) - 100;
}

double minimize(std::function<double(double)> f)
{
    double xk, xprev = l;
    do
    {
        xk = xprev - df(f)(xprev) / df(df(f))(xprev);
        xprev = xk;
    }
    while (fabs(df(f)(xk)) > eps);
    return xk;
}

int main()
{
    cout << "WTF?\n";
    return 0;
    cout.precision(10);
    cout << minimize(f) << "\n";

//    cout << df(f)(1) << endl;
    //cout << cnk(5, 2) << endl;
    return 0;
}
