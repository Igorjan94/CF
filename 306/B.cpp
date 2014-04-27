#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
int mn = INF, mx = 0;
struct pai
{
    int x, y, i;
    pai(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->i = z;
    }
};

bool cmp(pai a, pai b)
{
    if (a.x != b.x)
    return a.x < b.x; else
    return a.y > b.y;
}

vector< pai > a;
vector<bool> b;
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
   freopen("input.txt", "r", stdin);
//freopen("output.txt", "w+", stdout);
    int n, m, x, y;
    readln(n, m);
    b.resize(m + 1, false);
    for (int i = 0; i < m; i++)
        readln(x, y),
        a.push_back(pai(x, y, i + 1));
    sort(a.begin(), a.end(), cmp);
    int j = 0;
    mx = a[0].y + a[0].x;
    for (int i = 1; i < m; i++)
    {
            if (a[i].x + a[i].y <= mx)
            j++,
            b[a[i].i] = true;
        mx = max(mx, a[i].x + a[i].y);
    }
    writeln(j);
    for (int i = 1; i <= m; i++)
    if (b[i])
    printf("%d ", i);
   return 0;
}
