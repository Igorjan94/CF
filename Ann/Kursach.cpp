#include <bits/stdc++.h>
#include <ctime>
#define MAXN 5

using namespace std;
using namespace std::placeholders;

static const double eps = 0.0001;
static const double delta = 0.00001;
static const double l = 0.;
static const double x10 = 0., x20 = 0.;

long long cnk[MAXN][MAXN];

void build_cnk()
{
    for (int i = 0; i < MAXN; i++)
        cnk[i][0] = 1ll;
    for (int i = 1; i < MAXN; i++)
        for (int j = 1; j < MAXN; j++)
            cnk[i][j] = cnk[i - 1][j] + cnk[i - 1][j - 1];
}

auto d2f(std::function<double(double, double)> f) -> decltype(f)
{
    return [f](double x, double y)
    {
        double ans = f(x + delta, y) - f(x, y);
        double t = ans;
        int sign = -1;
        for (int i = 1; i <= MAXN; i++, sign *= -1)
        {
            double tcur = 0;
            for (int j = 0, s = 1; j <= i; j++, s *= -1)
                tcur += s * cnk[i][j] * f(x + delta * (i - j + 1), y);
            t = tcur - t;
            ans += sign * t / (i + 1);
        }
        return ans / delta;
    };
}

auto df(std::function<double(double)> f) -> decltype(f)
{
    return bind(d2f([f](double x, double y){return f(x);}), _1, 0);
}

double f(double x1, double x2)
{
    return ((x2 - x1 * x1) * (x2 - x1 * x1) * 100 + (x1 - 1) * (x1 - 1) * 5) / 400;
}

double minimize(std::function<double(double)> f) //Newton method for minimization of one-dimensional function
{
    for (double x = -df(f)(0) / df(df(f))(0); ; x -= df(f)(x) / df(df(f))(x))
        if (fabs(df(f)(x)) <= eps)
            return x;
}

double fx1(double x1, double x2)
{
    return df(bind(f, _1, x2))(x1);
}

double fx2(double x1, double x2)
{
    return df(bind(f, x1, _1))(x2);
}

bool check(double x1, double x2)
{
    cout << x1 << " " << x2 << "\n";
    return (fabs(fx1(x1, x2)) <= eps && fabs(fx2(x1, x2)) <= eps);
}

pair<double, double> gradientDownFragmentation()
{
    double x1 = x10, x2 = x20;
    int countOfOperations = 0;
    double start = clock();
    double alpha = 1, x11, x21, t, f1, f2;
    while (!check(x1, x2))
    {
        countOfOperations++;
        t = f(x1, x2);
        while (true)
        {
            f1 = fx1(x1, x2);
            f2 = fx2(x1, x2);
            x11 = x1 - alpha * f1;
            x21 = x2 - alpha * f2;
            if (f(x11, x21) > t - eps * alpha * (f1 * f1 + f2 * f2))
                alpha /= 2;
            else
                break;
        }
        x1 = x11;
        x2 = x21;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl << "qwe";
    return {x1, x2};
}

pair<double, double> fastestGradientDown()
{
    double x1 = x10, x2 = x20;
    int countOfOperations = 0;
    double start = clock();
    double alpha = 1, x11, x21, f1, f2;
    auto fun = [&x1, &x2](double lambda){return f(x1 - lambda * fx1(x1, x2), x2 - lambda * fx2(x1, x2));};
    while (!check(x1, x2))
    {
        countOfOperations++;
        f1 = fx1(x1, x2);
        f2 = fx2(x1, x2);
        alpha = minimize(fun);
        x1 = x1 - alpha * f1;
        x2 = x2 - alpha * f2;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl << "qwe";
    return {x1, x2};
}

pair<double, double> soprDirection()
{
    double x1 = x10, x2 = x20;
    int countOfOperations = 0;
    double start = clock();
    double alpha = 1, beta = 0;
    double f1, f2, p1, p2, f1p, f2p;
    p1 = f1 = fx1(x1, x2);
    p2 = f2 = fx2(x1, x2);
    auto fun = [&x1, &x2, &p1, &p2](double lambda){return f(x1 - lambda * p1, x2 - lambda * p2);};
    alpha = minimize(fun);
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
        alpha = minimize(fun);
        if (f(x1, x2) <= f(x1 - alpha * p1, x2 - alpha * p2))
        {
            p1 = f1;
            p2 = f2;
            alpha = minimize(fun);
        }
        x2 = x2 - alpha * p2;
        x1 = x1 - alpha * p1;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl << "qwe";
    return {x1, x2};
}

pair<double, double> Gradppor()
{
    double x1 = x10, x2 = x20;
    int countOfOperations = 0;
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
        alpha = minimize(fun);
        if (f(x1, x2) <= f(x1 - alpha * p1, x2 - alpha * p2))
        {
            p1 = f1;
            p2 = f2;
            a=1;b=0;c=0;d=1;
            alpha = minimize(fun);
        }
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
        u = (p1 * y1 + p2 * y2);
        s = (p1 * p1 * a + p1 * p2 * b) * alpha / u;
        v = (p1 * p1 * c + p1 * p2 * d) * alpha / u;
        h = (p1 * p2 * a + p2 * p2 * b) * alpha / u;
        g = (p1 * p2 * c + p2 * p2 * d) * alpha / u;
        a = a - e + s;
        b = b - r + v;
        c = c - t + h;
        d = d - y + g;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl << "qwe";
    return {x1, x2};
}

pair<double, double> newton()
{
    double x1 = x10, x2 = x20;
    int countOfOperations = 0;
    double start = clock(), f1, f2, x11, x21;
    double q11, q12, q22;
    while (!check(x1, x2))
    {
        countOfOperations++;
        f1 = fx1(x1, x2);
        f2 = fx2(x1, x2);
        q11 = df(df(bind(f, _1, x2)))(x1);
        q12 = df(bind(d2f(f), x1, _1))(x2);
        q22 = df(df(bind(f, x1, _1)))(x2);
        x1 = x1 - (f1 * q22 - f2 * q12) / (q11 * q22 - q12 * q12);
        x2 = x2 - (-f1 * q12 + f2 * q11) / (q11 * q22 - q12 * q12);
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl << "qwe";
    return {x1, x2};
}

int main()
{
    pair<double, double> temp;
    cout.precision(10);
    build_cnk();
    freopen("output.txt", "w", stdout);
    cout << "gradient down with fragmentation:\n" << (temp = gradientDownFragmentation()).first << " ";cout << temp.second << endl << endl;
    cout << "fastest gradient down:\n" << (temp = fastestGradientDown()).first << " ";cout << temp.second << endl << endl;
    cout << "sopr direction(Fletchera-Rivsa):\n" << (temp = soprDirection()).first << " ";cout << temp.second << endl << endl;
    cout << "newton:\n" << (temp = newton()).first << " " << temp.second << endl << endl;
    cout << "gradient p poryadka:\n" << (temp = Gradppor()).first << " ";cout << temp.second << endl << endl;
    fclose(stdout);
    system("javac *.java");
    system("java MainFrame &");
    return 0;
}
