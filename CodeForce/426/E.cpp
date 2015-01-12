#include <bits/stdc++.h>

#define pb push_back
#define ll long long
#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define forn1(i, n) for (int i = 1; i < n; i++)
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>
#ifndef ONLINE_JUDGE
#define lld I64D
#endif
#define FILENAME "input"
#define INF 1000000007

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void readln(){}
struct graph{vector<vector<int>> edges;int n;graph(int);graph(int, int);graph();void createGraph(int);void add_edge(int, int);void add_or_edge(int, int);void writelnMatrix();void writeln();};

///----------------------------------------------------------------------------------------------------------------------------

int n, m, k, s, e;
vi a, b, c, d;
int A[100001], B[100001];

void updateAB()
{
    fori(n)
        if (A[c[i]] == 0)
            A[c[i]] = i + 1;
        else
            c[i] = A[c[i]] - 1,
            A[c[i]] = i + 1;
    forj(m)
        jf (B[d[j]] == 0)
            B[d[j]] = j + 1;
        else
            d[j] = B[d[j]] - 1,
            B[d[j]] = j + 1;
}

int run()
{
    readln(n, m, s, e);
    a.resize(n);
    c.resize(n, 0);
    b.resize(m);
    d.resize(m, 0);
    readln(a, b);
    if (s < e)
        return -1;
    int ans = 0;
    int count = 0;
    while ()
}

int main()
{
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    writeln(run());
    return 0;
}

























graph::graph(int n){this->n = n;edges.resize(n);int t;fori(n){edges[i].resize(n);forj(n)readln(t),edges[i][j] = t == '1';}}graph::graph(int n, int m){this->n = n;edges.resize(n);int u, v;fori(m)readln(u, v),add_edge(u - 1, v - 1);}void graph::add_edge(int u, int v){edges[u].pb(v);}void graph::add_or_edge(int u, int v){edges[u].pb(v);edges[v].pb(u);}graph::graph(){};void graph::createGraph(int n){edges.resize(n);}void graph::writeln(){fori(n)forj(edges[i].size())::writeln(i, edges[i][j]);}void graph::writelnMatrix(){::writeln(edges);}
void print(double a){printf("%f ", a);}
void print(int a){printf("%d ", a);}
void print(string a){printf("%s ", a.c_str());}
void print(long long a){printf("%lld ", a);}
void print(unsigned long a){printf("%ld ", a);}
void print(char a){printf("%c ", a);}
void print(vector<int>& a){for(int i = 0; i < a.size(); ++i)printf("%d ", a[i]);}
void print(vector<vector<int>>& a){for(int i = 0; i < a.size(); ++i)writeln(a[i]);}
void read(double &a){scanf("%lf", &a);}
void read(int &a){scanf("%d", &a);}
void read(string &a){cin>>a;}
void read(long long &a){scanf("%lld", &a);}
void read(char &a){scanf("%c", &a);}
void read(vector<int> &a){for(int i = 0; i < a.size(); ++i)scanf("%d", &a[i]);}
void read(vector<vector<int>> &a){for(int i = 0; i < a.size(); ++i)readln(a[i]);}
template <class Head, class... Tail>
void writeln(Head head, Tail... tail){print(head);writeln(tail...);}
template <class Head, class... Tail>
void readln(Head& head, Tail&... tail){read(head);readln(tail...);}
