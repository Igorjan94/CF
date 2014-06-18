#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#define enter printf("\n");
#define ull unsigned long long
#define ll long long
#define sort(a) sort(a.begin(), a.end())

using namespace std;
int INF = 1000000007;
vector<int> a;
int n, x, y;
int co[6][7] = {{1, 2, 0, 0, 0, 0, 0}, {1, 3, 4, 0, 0, 0, 0}, {1, 4, 7, 8, 0, 0, 0}, {1, 5, 11, 15, 16, 0, 0}, {1, 6, 16, 26, 31, 32, 0}, {1, 7, 22, 42, 57, 63, 64}};
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
    int x;
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

double test()
{
    readln(n, x, y);
    x = abs(x);
    int i = 0;
    while (n > a[i])
        i++;
    int count = a[i] - n;
    if (count == 0)
        return (int) (x + y <= 2 * i);
    if (x + y < 2 * i)
        return 1;
    if (x + y > 2 * i)
        return 0;
    if (y == 2 * i)
        return 0;
    count = n - a[i - 1];
    if (count - 2 * i > y)
        return 1;
    if (count < y)
        return 0;
    bool f = false;
    if (count > 2 * i)
    {
        count -= 2 * i;
        y = 2 * i - y;
        f = true;
    }
    //writeln(n, x, y, count);
    double h = co[count - 1][y];
    for (int j = 0; j < count; j++, h /= 2);
    return !f ? 1.0 - h : h;
}

int main()
{
    freopen("input1.txt", "r", stdin);
    freopen("output.txt", "w+", stdout);
    a.resize(1);
    a[0] = 1;
    for (int i = 1; a[i - 1] < 1000000;i++)
        a.push_back((2 * i + 1) * (i + 1));
    int T;
    readln(T);
    for (int tttt = 0; tttt < T; tttt++)
    {
        printf("Case #%d: ", tttt + 1);
        printf("%.8f\n", test());
    }
    return 0;
}
