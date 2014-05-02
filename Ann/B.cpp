#include <bits/stdc++.h>
#include <ctime>

using namespace std;

static const double eps = 0.01;
static const double delta = 0.001;
static const double l = -10., r = 10.;

double f(double x1, double x2)
{
    return 3 * x1 * x1 - 3 * x1 * x2 + 4 * x2 * x2 - 2 * x1 + x2;
    /*
        3 -3 * f1 = 3*f1*f1-3*f2*f1
        -3 4   f2   -3*f1*f2+4*f2*f2
    */
}

double fx1(double x1, double x2)
{
    return 6 * x1 - 3 * x2 - 2;
}

double fx2(double x1, double x2)
{
    return -3 * x1 + 8 * x2 + 1;
}

bool check(double x1, double x2)
{
    return (fabs(6 * x1 - 3 * x2 - 2) <= eps && fabs(-3 * x1 + 8 * x2 + 1) <= eps);
}

pair<double, double> coordinateDown()
{
    double x1 = 10., x2 = 10.;
    int countOfOperations = 0;
    double start = clock();
    double x, temp, mn, val;
    while (!check(x1, x2))
    {
        countOfOperations++;
        x = l;
        mn = f(x, x2);
        while (x < r)
        {
            temp = f(x, x2);
            if (temp < mn)
                mn = temp,
                val = x;
            x += delta;
        }
        x1 = val;

        x = l;
        mn = f(x1, x);
        while (x < r)
        {
            temp = f(x1, x);
            if (temp < mn)
                mn = temp,
                val = x;
            x += delta;
        }
        x2 = val;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

pair<double, double> gradientDown()
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

pair<double, double> fastestDown()
{
    double x1 = 0., x2 = 0.;
    int countOfOperations = 0;
    double start = clock();
    double alpha = 1, x11, x21, f1, f2;
    while (!check(x1, x2))
    {
        countOfOperations++;
        f1 = fx1(x1, x2);
        f2 = fx2(x1, x2);
        alpha = (f1 * f1 + f2 * f2) / (3 * f1 * f1 - 3 * f2 * f1 - 3 * f1 * f2 + 4 * f2 * f2);
        x1 = x1 - alpha * f1;
        x2 = x2 - alpha * f2;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

pair<double, double> gradients()
{
    double x1 = 0., x2 = 0.;
    int countOfOperations = 1;
    double start = clock();
    double alpha = 1, x11, x21, f1, f2, p1 = fx1(x1, x2), p2 = fx2(x1, x2), beta = 0, pp1, pp2;
    double f1p = p1, f2p = p2;
        f1 = p1;
        f2 = p2;
        alpha = (f1 * p1 + f2 * p2) / (3 * p1 * p1 - 3 * p2 * p1 - 3 * p1 * p2 + 4 * p2 * p2);
        x1 = x1 - alpha * p1;
        x2 = x2 - alpha * p2;

    while (!check(x1, x2))
    {
        countOfOperations++;
        f1 = fx1(x1, x2);
        f2 = fx2(x1, x2);
        beta = (f1*f1+f2*f2) / (f1p*f1p+f2p*f2p);
        pp1 = f1 + beta * p1;
        pp2 = f2 + beta * p2;
        f1p = f1;
        f2p = f2;
        alpha = (f1 * pp1 + f2 * pp2) / (3 * p1 * p1 - 3 * p2 * p1 - 3 * p1 * p2 + 4 * p2 * p2);
        p1 = pp1;
        p2 = pp2;
        x1 = x1 - alpha * p1;
        x2 = x2 - alpha * p2;
        cout << x1 << " " << x2 << endl;
        if (countOfOperations > 10)
            break;
    }
    cout << "count of operations = " << countOfOperations << endl << "time = " << (clock() - start) / CLOCKS_PER_SEC << endl;
    return {x1, x2};
}

int main()
{
    pair<double, double> temp;
    cout.precision(3);
    cout << "coordinate down:\n" << (temp = coordinateDown()).first << " " << temp.second << endl << endl;
    cout << "gradient down:\n" << (temp = gradientDown()).first << " " << temp.second << endl << endl;
    cout << "fastest down:\n" << (temp = fastestDown()).first << " " << temp.second << endl << endl;
    cout << "gradients:\n" << (temp = gradients()).first << " " << temp.second << endl << endl;
    return 0;
}
