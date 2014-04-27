#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
vector<long long> a, t;
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

void readln(vector<long long> &f, int n)
{
    int x;
    for (int i = 1; i <= n; i++)
    {
        read(x);
        f.push_back(x);
    }
}

void build (vector<long long> &a, int v, int tl, int tr) {
	if (tl == tr)
		t[v] = a[tl]; else
	{
		int tm = (tl + tr) / 2;
		build (a, v*2, tl, tm);
		build (a, v*2+1, tm+1, tr);
		t[v] = t[v*2] + t[v*2+1];
	}
}

long long sum (int v, int tl, int tr, int l, int r) {
	if (l > r)
		return 0;
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	return sum (v*2, tl, tm, l, min(r,tm))
		+ sum (v*2+1, tm+1, tr, max(l,tm+1), r);
}

void update (int v, int tl, int tr, int l, int r, int add) {
	if (l > r)
		return;
		t[v] += add;
	if ((l == tl && tr == r))
    return;
//	else
{
		int tm = (tl + tr) / 2;
		update (v*2, tl, tm, l, min(r,tm), add);
		update (v*2+1, tm+1, tr, max(l,tm+1), r, add);
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
   int n, m, k, l, r, d;
    readln(n, m, k);
    t.resize(n * 4, 0);
    readln(a, n);
    int f = 2;
    while (f <= n) f*=2;
    for (int i = n; i < f; i++)
        a.push_back(0);
    build(a, 1, 0, f - 1);
    for (int i = 0; i < m; i++)
    {
        readln(l, r, d);
        update(1, 0, f - 1, l - 1, r - 1, d);
    for (int i = 0; i < 10; i++)
        cout << t[i] << " ";
    cout << "\n";

    }

    for (int i = 0; i < k; i++)
    {
        readln(l, r);
        printf("%I64d ", sum(1, 0, f - 1, l - 1, r - 1));
    }
   return 0;
}
