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
string FILENAME = "start";
string FILEINPUT = FILENAME;
int mx = 0;
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);mx=max(mx,x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

int n, k;
vector< vector<pair<int, int> > > edges;
vector<bool> used;
vi a;
int dfs(int u)
{
    used[u] = true;
    int mx = 0;
    forn(i, edges[u].size())
        if (!used[edges[u][i].first])
        {
            int t = dfs(edges[u][i].first);
            if (edges[u][i].second && !t)
            {
                mx++;
                a.pb(edges[u][i].first + 1);
            }
            else
                mx += t;
        }
    return mx;
}

void run()
{
    readln(n);
    edges.resize(n + 1);
    used.resize(n + 1, false);
    int x, y, t;
    forn(i, n - 1)
    {
        readln(x, y, t);
        edges[x - 1].pb({y - 1, t - 1});
        edges[y - 1].pb({x - 1, t - 1});
    }
    cout << dfs(0) << endl;
    writeln(a);
}

int main()
{
    //freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}

