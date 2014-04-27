#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
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

int main()
{
//    freopen("input.txt", "r", stdin);
    int n, k;
    readln(n, k);
    int g = 1;
    int j = n - g;
    int i;
    for (i = 0; i < k; i++)
    {
        if (g >= n)
            break;
        for (int q = 1; q < n - g * 2; q++)
            printf("%d ", j);
        for (int q = n - 2 * g > 0 ? 0 : 2 * g - n + 1; q < g; q++)
            printf("%d ", j + q);
        for (int q = n - g; q < n; q++)
            printf("%d ", n);
        printf("%d\n", n);
        g *= 2;
        j = n - g;
    }
    for (int h = i; h < k; h++)
        for (int f = 0; f < n; f++)
        printf("%d%c", n, f == n - 1 ? '\n' : ' ');
    return 0;
}
