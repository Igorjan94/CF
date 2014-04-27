
#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

double dist(double a, double b)
{
    return (a - b) * (a - b) + 1.0;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n, mm, r2;
    scanf("%d %d %d\n", &mm, &n, &r2);
    r2 *= r2;
    vector<double> x;
    vector<double> c;
    double f;
//    c.push_back(-1000000001.0);
    for (int i = 0; i < mm; i++)
    {
        scanf("%lf", &f);
        c.push_back(f);
    }
    c.push_back(1000000001.0);
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &f);
        x.push_back(f);
    }
    double total = 0.0;
    int j = 0, l;
    for (int i = 0; i < n; i++)
    {
        double f = x[i];
        if (dist(c[j], f) > r2)
        {
            if (c[j] > f)
            {
                int r = mm, m;
                l = 0;
                while (true)
                {
                    m = (l + r) / 2;
                    if (c[m] < f)
                        l = m; else
                        {
                            if (dist(c[m], f) >= r2)
                                r = m; else
                                    l = m;
                        }
                    if (l >= r - 1)
                    {
                        if (dist(c[l], f) > r2)
                            l++;
                        break;
                    }
                }
            }
            else
            {
                int r = mm, m;
                l = 0;
                while (true)
                {
                    m = (l + r) / 2;
                    if (c[m] > f)
                        r = m; else
                        {
                            if (dist(c[m], f) >= r2)
                                l = m; else
                                    r = m;
                        }
                    if (l >= r - 1)
                    {
                        if (dist(c[l], f) > r2)
                            l++;
                        break;
                    }
                }
            }
            //cout << f << " " << c[l] << "\n";
            total += fabs(c[j] - c[l]);
            j = l;
        }
    }
    printf("%.2f\n", total);
//    cout << total << endl;
    return 0;
}
