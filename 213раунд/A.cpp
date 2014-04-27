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
#define ll long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define vi vector<int>

using namespace std;
int INF = 1000000007;
string FILENAME = "drying";
string FILEINPUT = FILENAME;
int mx = 0;
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);mx=max(mx,x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

int n, k;

void run()
{
    char c;
    readln(k);
    vi a;
    vi sums;
    sums.pb(0);
    int i = 0;
    while (true)
    {
        scanf("%c", &c);
        if (c == '\n')
                break;
        a.pb(c - '0');
        sums.pb(sums[i] + a[i]);
        i++;
    }
    int n = a.size();
    //writeln(a);
    //multimap<int, pair<int, int> > e;
    vector<ll> e(9 * n + 1, 0ll);
    forn(i, n)
        for(int j = i + 1; j <= n; j++)
            e[sums[j] - sums[i]]++;
    //writeln(e);
//            e.insert(make_pair(sums[j] - sums[i], make_pair(i, j)));
    ll ans = 0;
    if (k == 0)
    {
        forn(i, 9 * n)
            ans += e[i] * e[0] * 2;
        ans -= e[0] * e[0];
    }
    else
        for(int i = 1; i <= min(k, 9 * n); i++)
            if (k / i < 9 * n && k % i == 0)
                ans += e[i] * e[k / i];
    cout << ans << "\n";
}

int main()
{
    //freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
