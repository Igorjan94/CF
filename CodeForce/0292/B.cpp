#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
int a[100002];
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

void readln(vector<int> &a, int n)
{
    int x;
    for (int i = 1; i <= n; i++)
    {
        read(x);
        a.push_back(x);
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
 //   freopen("input.txt", "r", stdin);
//freopen("output.txt", "w+", stdout);
    int n, t, c, m, x, y;
    readln(n, m);
    bool f = true;
    int pos = 0;
    for (int i = 0; i < m; i++)
    {
        readln(x, y);
        a[x]++;
        a[y]++;
        if (a[x] > 2)
            if (pos == x || pos == 0)
            pos = x; else
        {
            f = false;
            break;
        }
        if (a[y] > 2)
            if (pos == y || pos == 0)
            pos = y; else
            {
                f = false;
                break;
            }
    }
    if (!f)
    {
        printf("unknown topology\n");
        return 0;
    }
    if (pos != 0)
        if (a[pos] == n - 1)
    {
        bool d = false;
        for (int j = 1; j <= n; j++)
            if (j == pos)
            continue; else
            if (a[j] != 1)
        {
            d = true;
            break;
        }
        if (d)
        printf("unknown topology\n"); else
        printf("star topology\n");
        return 0;
    }
    int count = 0;
    int s = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] == 2)
            count++; else
            if (a[i] == 1)
                s++;
    if (count == n)
    {
        printf("ring topology\n");
        return 0;
    }
    if (count == n - 2 && s == 2)
    {
        printf("bus topology\n");
        return 0;
    }
    printf("unknown topology\n");
    return 0;
}
