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
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

void wr(vector<ll> &a)
{
    forn(i, a.size())
        cout << a[i] << " ";
    enter;
}

void run()
{
    int n, k, x;
    vector<pair<int, int> > a;
    readln(n);
    forn(i, n)
        scanf("%d", &x),
        a.pb({x, i + 1});
    readln(k);
    sort(a.begin(), a.end());
    vector<ll> sums, all, sums2, all2;
    sums.push_back(0);
    all.push_back(0);
    sums2.push_back(0);
    all2.push_back(0);
    forn(i, n - 1)
        sums.push_back(((ll)(a[i + 1].first - a[i].first)) * (i + 1) + sums.back()),
        all.push_back(all.back() + sums.back()),
        sums2.push_back(((ll)(a[n - i - 1].first - a[n - i - 2].first)) * (i + 1) + sums2.back()),
        all2.push_back(all2.back() + sums2.back());
    reverse(sums2.begin(), sums2.end());
    reverse(all2.begin(), all2.end());
    sums2.pb(0);
    ll mn = all[k - 1], current;
    int index = k - 1;
    for (int i = k; i < n; i++)
    {
        current = (all[i] + all2[i - k + 1] + ((ll)(a[i + 1].first - a[i - k].first)) * (i - k + 1) * (n - i - 1) +
                    sums[i - k] * (n - i - 1) + sums2[i + 1] * (i - k + 1) - all2[0]);
        if (current < mn)
            mn = current,
            index = i;
    }
    for (int i = index - k + 1; i <= index; i++)
        printf("%d ", a[i].second);
}

int main()
{
    //freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
