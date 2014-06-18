#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");
#define ll unsigned long long

using namespace std;
int INF = 1000000007;
vector<int> a;
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

ll ss(ll n, ll R)
{
    ll temp = n * (2 * R + 2 * n - 1);
    return temp;
}

ll test()
{
    ll R, t, n, l, r, s;
    cin >> R >> t;
    l = 0;
    r = min(1000000000000000001ull / R, 2000000000ull);
    while (true)
    {
        n = (l + r) / 2;
        s = ss(n, R);
        if (s < t)
            l = n; else
        if (s > t)
            r = n; else
            return n;
        if (l + 1 >= r)
            return (ss(r, R) <= t ? r : l);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w+", stdout);
    int T;
    readln(T);
    for (int tttt = 0; tttt < T; tttt++)
    {
        printf("Case #%d: ", tttt + 1);
        cout << test() << "\n";
    }
    return 0;
}
