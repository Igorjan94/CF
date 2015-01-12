#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");
#define vi vector<int>

using namespace std;
int INF = 1000000007;
vector<int> a, b, c, d;
int n, m;
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

void readln(vector<int> &f, int n)
{
    int x;
    for (int i = 1; i <= n; i++)
    {
        read(x);
        f.push_back(x);
    }
}

void writeln(vector<int> &f)
{
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

int counter = 0;
bool tr(vector<int> a, vi b, vi c, vi d, int t, int s)
{
    /*writeln(d);
    writeln(a);
    writeln(b);
    writeln(c);
    enter;*/
    if (s > n)
        return false;
    bool f = false;
    for (int i = t; i <= 3 * n; i++)
    {
        if (d[i])
            continue;
        b[s] = i;
        c[s] = a[s] + b[s];
        if (c[s] <= 3 * n && d[c[s]])
            continue;
        if (c[s] > 3 * n)
            return false;
        d[b[s]]++;
        d[c[s]]++;
        if (s == n && a[s] + b[s] == c[s] && c[s] <= 3 * n && d[c[s]] == 1)
        {
            writeln(a);
            writeln(b);
            writeln(c);
            return true;
        }
        f |= tr(a, b, c, d, t, s + 1);
        if (f)
            return true;
        d[b[s]] = max(0, d[b[s]] - 1);
        d[c[s]] = max(0, d[c[s]] - 1);
    }
    return f;
}

int main()
{
    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w+", stdout);
    readln(n);
    n = 20;
    for (n = 1; n <= 23; n++)
    {
        writeln(n);
        if (n % 4 >= 2)
            continue;
        d.resize(3 * n + 1, 0);
        a.resize(n + 1);
        for (int i = 1; i <= n; i++)
            a[i] = i,
            d[i] = 1;
        b.resize(n + 1);
        c.resize(n + 1);
        tr(a, b, c, d, n, 1);
    }
    return 0;
}
