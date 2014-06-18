#include <bits/stdc++.h>
#include <ctime>

using namespace std;
using namespace std::placeholders;

static const double eps = 0.01;
static const double delta = 0.001;
static const double l = -10., r = 10.;
static const double q11 = 3., q12 = -3., q22 = 4., r1 = -2., r2 = 1.;

double f(double x1, double x2)
{
    return q11 * x1 * x1 + q12 * x1 * x2 + q22 * x2 * x2 + r1 * x1 + r2 * x2;
    /* _                 _
      |  / 6 -3 \ * /f1\  | x /f1\  = 6*f1*f1-3*f2*f1-3*f1*f2+8*f2*f2
      |_ \ -3 8 /   \f2/ _|   \f2/
    */

    /*
        H = / 6 -3 \ ;   -1 = 1  / 8 3 \
            \-3  8 /    H     39 \ 3 6 /
    */
}

double ftemp(std::function<double(double)> f)
{
    auto ff = [f](double x){ return (f(x + delta) - f(x)) / delta;};
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

double fx1(double x1, double x2)
{
    return (f(x1 + delta, x2) - f(x1, x2)) / delta;
}

double fx2(double x1, double x2)
{
    return (f(x1, x2 + delta) - f(x1, x2)) / delta;
}

bool check(double x1, double x2)
{
    return (fabs(fx1(x1, x2)) <= eps && fabs(fx2(x1, x2)) <= eps);
}

pair<double, double> coordinateDown()
{
    double x1 = 0., x2 = 0.;
    int countOfOperations = 0;
    double start = clock();
    double x, temp, mn, val;
    while (!check(x1, x2))
    {
        countOfOperations++;
        x1 = ftemp(bind(f, _1, x2));
        x2 = ftemp(bind(f, x1, _1));
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

pair<double, double> gradientDownFragmentation()
{
    double x1 = 0., x2 = 0.;
    int countOfOperations = 0;
    double start = clock();
    double alpha = 1, x11, x21, t;
    while (!check(x1, x2))
    {
        countOfOperations++;
        t = f(x1, x2);
        while (true)
        {
            x11 = x1 - alpha * fx1(x1, x2);
            x21 = x2 - alpha * fx2(x1, x2);
            if (f(x11, x21) > t)
                alpha /= 2;
            else
                break;
        }
        x1 = x11;
        x2 = x21;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

pair<double, double> gradientDownConst()
{
    double x1 = 0., x2 = 0.;
    int countOfOperations = 0;
    double start = clock();
    double alpha = 0.1;
    while (!check(x1, x2))
    {
        countOfOperations++;
        x1 = x1 - alpha * fx1(x1, x2);
        x2 = x2 - alpha * fx2(x1, x2);
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

pair<double, double> fastestGradientDown()
{
    double x1 = 0., x2 = 0.;
    int countOfOperations = 0;
    double start = clock();
    double alpha = 1, x11, x21, f1, f2;
    auto fun = [&x1, &x2](double lambda){return f(x1 - lambda * fx1(x1, x2), x2 - lambda * fx2(x1, x2));};
    while (!check(x1, x2))
    {
        countOfOperations++;
        f1 = fx1(x1, x2);
        f2 = fx2(x1, x2);
        alpha = ftemp(bind(fun, _1));
        x1 = x1 - alpha * f1;
        x2 = x2 - alpha * f2;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

pair<double, double> soprDirection()
{
    double x1 = 0., x2 = 0.;
    int countOfOperations = 1;
    double start = clock();
    double alpha = 1, beta = 0;
    double f1, f2, p1, p2, f1p, f2p;
    p1 = f1 = fx1(x1, x2);
    p2 = f2 = fx2(x1, x2);
    auto fun = [&x1, &x2, &p1, &p2](double lambda){return f(x1 - lambda * p1, x2 - lambda * p2);};
    alpha = ftemp(bind(fun, _1));
    x1 = x1 - alpha * p1;
    x2 = x2 - alpha * p2;
    while (!check(x1, x2))
    {
        countOfOperations++;
        f1p = f1;
        f2p = f2;
        f1 = fx1(x1, x2);
        f2 = fx2(x1, x2);
        beta = (f1 * f1 + f2 * f2) / (f1p * f1p + f2p * f2p);
        p1 = f1 + beta * p1;
        p2 = f2 + beta * p2;
        alpha = ftemp(bind(fun, _1));
        if (f(x1, x2) <= f(x1 - alpha * p1, x2 - alpha * p2))
        {
            p1 = f1;
            p2 = f2;
            alpha = ftemp(bind(fun, _1));
        }
        x2 = x2 - alpha * p2;
        x1 = x1 - alpha * p1;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

pair<double, double> Gradppor()
{
    double x1 = 0., x2 = 0.;
    int countOfOperations = 1;
    double start = clock();
    double alpha = 1, beta = 0;
    double f1, f2, p1, p2, f1p, f2p, a = 1., b = 0., c = 0., d = 1., q, w, e, r, t, y, u, s, v, h, g, y1, y2;
    auto fun = [&x1, &x2, &p1, &p2](double lambda){return f(x1 - lambda * p1, x2 - lambda * p2);};
    while (!check(x1, x2))
    {
        countOfOperations++;
        f1 = fx1(x1, x2);
        f2 = fx2(x1, x2);
        p1 = a * f1 + b * f2;
        p2 = c * f1 + d * f2;
        alpha = ftemp(bind(fun, _1));
        x1 = x1 - alpha * p1;
        x2 = x2 - alpha * p2;
        y1 = fx1(x1, x2) - f1;
        y2 = fx2(x1, x2) - f2;
        q = a * y1 + b * y2;
        w = c * y1 + d * y2;
        u = q * y1 + w * y2;
        e = (q * y1 * a + q * y2 * c) / u;
        r = (q * y1 * b + q * y2 * d) / u;
        t = (w * y1 * a + w * y2 * c) / u;
        y = (w * y1 * b + w * y2 * d) / u;
        u = (p1 * y1 + p2 * y2) /  alpha;
        s = (p1 * p1 * a + p1 * p2 * b) / u;
        v = (p1 * p1 * c + p1 * p2 * d) / u;
        h = (p1 * p2 * a + p2 * p2 * b) / u;
        g = (p1 * p2 * c + p2 * p2 * d) / u;
        a = a - e + s;
        b = b - r + v;
        c = c - t + h;
        d = d - y + g;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

pair<double, double> newton()
{
    double x1 = 0., x2 = 0.;
    int countOfOperations = 0;
    double start = clock(), f1, f2, x11, x21;
    while (!check(x1, x2))
    {
        countOfOperations++;
        f1 = fx1(x1, x2);
        f2 = fx2(x1, x2);
        x1 = x1 - (f1 * 2 * q22 - f2 * q12) / (4 * q11 * q22 - q12 * q12);
        x2 = x2 - (-f1 * q12 + f2 * 2 * q11) / (4 * q11 * q22 - q12 * q12);
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

int main()
{
    pair<double, double> temp;
    cout.precision(3);
    cout << "coordinate down:\n" << (temp = coordinateDown()).first << " " << temp.second << endl << endl;
    cout << "gradient down with const:\n" << (temp = gradientDownConst()).first << " " << temp.second << endl << endl;
    cout << "gradient down with fragmentation:\n" << (temp = gradientDownFragmentation()).first << " " << temp.second << endl << endl;
    cout << "fastest gradient down:\n" << (temp = fastestGradientDown()).first << " " << temp.second << endl << endl;
    cout << "sopr direction(Fletchera-Rivsa):\n" << (temp = soprDirection()).first << " " << temp.second << endl << endl;
    cout << "newton:\n" << (temp = newton()).first << " " << temp.second << endl << endl;
    cout << "gradient p poryadka:\n" << (temp = Gradppor()).first << " " << temp.second << endl << endl;
    return 0;
}
