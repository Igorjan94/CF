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
#define pll pair<ll, ll>
#ifndef ONLINE_JUDGE
#define lld I64d
#endif
#define FILENAME "input"
#define INF 1000000007

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void readln(){}
struct graph{vector<vector<int>> edges;int n;graph(int);graph(int, int);graph();void createGraph(int);void add_edge(int, int);void add_or_edge(int, int);void writelnMatrix();void writeln();};

///----------------------------------------------------------------------------------------------------------------------------

int n, m, k;
vector<pii> a, ans;

void run()
{
    readln(n);
    a.resize(n);
    readln(a);
    int t;
    fori(n)
        if (a[i].first < a[i].second)
            t = a[i].first,
            a[i].first = a[i].second,
            a[i].second = t;
    sort(a.rbegin(), a.rend());
    bool tr = false;
    bool ok = true;
    ans.pb(a[0]);
    forn1(i, n)
        if (a[i] == a[i - 1])
            if (a[i].first == a[i].second)
            {
                writeln("Chaos");
                return;
            } else
            {
                if (!ok)
                {
                    writeln("Chaos");
                    return;
                }
                ok = false;
                tr = 1 - tr;
                tr ? ans.pb({a[i].second, a[i].first}) : ans.pb({a[i].first, a[i].second});
            }
        else
        {
            ok = true;
            tr ? ans.pb({a[i].second, a[i].first}) : ans.pb({a[i].first, a[i].second});
        }
    fori(n)
        printf("%d %d\n", ans[i].first, ans[i].second);
}

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    run();
    return 0;
}

























graph::graph(int n){this->n = n;edges.resize(n);int t;fori(n){edges[i].resize(n);forj(n)readln(t),edges[i][j] = t == '1';}}graph::graph(int n, int m){this->n = n;edges.resize(n);int u, v;fori(m)readln(u, v),add_edge(u - 1, v - 1);}void graph::add_edge(int u, int v){edges[u].pb(v);}void graph::add_or_edge(int u, int v){edges[u].pb(v);edges[v].pb(u);}graph::graph(){};void graph::createGraph(int n){edges.resize(n);}void graph::writeln(){fori(n)forj(edges[i].size())::writeln(i, edges[i][j]);}void graph::writelnMatrix(){::writeln(edges);}
void print(double a){printf("%f ", a);}
void print(int a){printf("%d ", a);}
void print(string a){printf("%s ", a.c_str());}
void print(long long a){printf("%lld ", a);}
void print(unsigned long a){printf("%ld ", a);}
void print(unsigned int a){printf("%d ", a);}
void print(char a){printf("%c ", a);}
template<class Type1, class Type2>
void print(pair<Type1, Type2>& a){print(a.first);print(a.second);}
template<class Type>
void print(vector<Type>& a){for(int i = 0; i < a.size(); ++i)writeln(a[i]);}
template<class Type>
void print(vector<vector<Type>>& a){for(int i = 0; i < a.size(); ++i)writeln(a[i]);}
void read(double &a){scanf("%lf", &a);}
void read(int &a){scanf("%d", &a);}
void read(string &a){cin>>a;}
void read(long long &a){scanf("%lld", &a);}
void read(char &a){scanf("%c", &a);}
template<class Type1, class Type2>
void read(pair<Type1, Type2>& a){read(a.first);read(a.second);}
template<class Type>
void read(vector<Type> &a){if (a.size() == 0){int n; read(n); a.resize(n);}for(int i = 0; i < a.size(); ++i)read(a[i]);}
template<class Type>
void read(vector<vector<Type>> &a){for(int i = 0; i < a.size(); ++i)readln(a[i]);}
template <class Head, class... Tail>
void writeln(Head head, Tail... tail){print(head);writeln(tail...);}
template <class Head, class... Tail>
void readln(Head& head, Tail&... tail){read(head);readln(tail...);}
