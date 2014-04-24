#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>
#include <queue>
#include <map>

#define enter printf("\n");
#define pb push_back
#define ll unsigned long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define vi vector<int>

using namespace std;
int INF = 1000000007;
string FILENAME = "start";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

int d1 = 0, d2 = 0;
ll s1 = 0, s2 = 0, mx, sum1 = 0, sum2 = 0;
vector< vi > a;
vector<ll> r;
int fl = 0;

void writeln(vector<int> &f)
{
    for (int i = 0; i < f.size(); i++)
        cout << (f[i] != 0 ? f[i] : (mx - r[i])) << (i == f.size() - 1 ? '\n' : ' ');
}

void readln(vector<int> &f, int n, int z)
{
    int x;
    forn(i, n)
    {
        read(x);
        f.push_back(x);
        r[i] += x;
        if (i == z)
            s1 += x;
        if (i == n - z - 1)
            s2 += x;
        if (x == 0)
        {
            if (i == z)
                d1++;
            if (i == n - z - 1)
                d2++;
        }
    }
    if (z == n - z - 1)
        fl = 1;
}

void run()
{
    int n;
    readln(n);
    a.resize(n);
    r.resize(n, 0);
    forn(i, n)
        readln(a[i], n, i);
    mx = *max_element(r.begin(), r.end());
    ll ss1 = 0, ss2 = 0;
    forn(i, n)
    {
        if (a[i][i] == 0)
            ss1 += mx - r[i];
        if (a[i][n - i - 1] == 0)
            ss2 += mx - r[n - i - 1];
    }
    mx = max(s1 + ss1, max(mx, s2 + ss2));
    if (d1 == 0)
        mx = s1;
    else
        if (d2 == 0)
            mx = s2;
        else
            mx++;
    forn(i, n)
        writeln(a[i]);
}

int main()
{
    freopen("e.in", "r", stdin);
    freopen("e.out", "w", stdout);
    run();
    return 0;
}
