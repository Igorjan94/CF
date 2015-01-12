//template igorjan94 version from 05 June 2014
#include <bits/stdc++.h>

#define pb push_back
#define ll long long
#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define forn(i, n) for (int i = 0; i < n; ++i)
#define forn1(i, n) for (int i = 1; i < n; ++i)
#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define ROF(i, m, n) for (int i = m; i >= n; --i)
#define fori(n) for (int i = 0; i < n; ++i)
#define forj(n) for (int j = 0; j < n; ++j)
#define fori1(n) for (int i = 1; i < n; ++i)
#define forj1(n) for (int j = 1; j < n; ++j)
#define vi vector<int>
#define vvi vector<vector<int> >
#define vll vector<long long>
#define pii pair<int, int>
#define whole(a) a.begin(), a.end()

#ifndef ONLINE_JUDGE
#define lld I64d
#endif

#define FILENAME "code"
#define INF 1000000007
#define DOUBLEFORMAT "%f"

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void writeln2(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void writeln2(){printf("\n");}void readln(){}

///----------------------------------------------------------------------------------------------------------------------------

int n, m, k, x, y;
vector<vi > edges;
vll d;
vi depth;
vi maxDepth;
vi ind;
vi sndmax;
vi vertex;
vi cur;
vi sndcur;

vector<bool> used;

int bfs(int v)
{
    queue<int> q;
    q.push(v);
    depth[v] = 0;
    while (q.size())
    {
        int u = q.front();
        q.pop();
        if (used[u])
            continue;
        used[u] = true;
        fori(edges[u].size())
            if (!used[edges[u][i]])
                depth[edges[u][i]] = depth[u] + 1,
                q.push(edges[u][i]);
    }
    return 0;
}

pii dfs(int u, int p = -1)
{
    int mx = depth[u];
    cur[u] = u;
    ind[u] = -1;
    sndmax[u] = -1;
    fori(edges[u].size())
        if (edges[u][i] != p)
        {
            pii t = dfs(edges[u][i], u);
            if (t.first > mx)
                mx = t.first,
                cur[u] = t.second,
                ind[u] = i;
            if (t.first == mx)
                cur[u] = min(cur[u], t.second);
        }
    sndcur[u] = -1;
    fori(edges[u].size())
        if (edges[u][i] != p)
            if (i != ind[u])
            {
                if (maxDepth[edges[u][i]] > sndmax[u])
                    sndmax[u] = max(sndmax[u], maxDepth[edges[u][i]]),
                    sndcur[u] = cur[edges[u][i]];
                else
                    if (maxDepth[edges[u][i]] == sndmax[u])
                        sndcur[u] = min(sndcur[u], cur[edges[u][i]]);
            }
    return {maxDepth[u] = mx, cur[u]};
}

void t(int u, int value, int v, int p)
{
    d[u] = v + depth[u];
    vertex[u] = value;
    fori(edges[u].size())
        if (edges[u][i] != p)
            t(edges[u][i], value, v, u);
}


void dfs2(int u, int value, int v = 0, int p = -1)
{
    if (v > maxDepth[u] - depth[u])
        vertex[u] = value;
    else
        vertex[u] = cur[u];
    d[u] = max(maxDepth[u] - depth[u], v);
    fori(edges[u].size())
        if (edges[u][i] != p)
            if (i != ind[u])
                t(edges[u][i], vertex[u], d[u] - depth[u], u);
    if (ind[u] != -1)
        dfs2(edges[u][ind[u]], sndcur[u] == -1 ? value : sndcur[u], max(v, sndmax[u] - depth[u]) + 1, u);
}

void run()
{
    readln(n, m);
    d.resize(n, 0);
    depth.resize(n, 0);
    edges.resize(n);
    ind.resize(n, -1);
    sndmax.resize(n, -1);
    maxDepth.resize(n, 0);
    vertex.resize(n, -1);
    used.resize(n, false);
    cur.resize(n, -1);
    sndcur.resize(n, -1);

    fori(n - 1)
        readln(x, y),
        edges[--x].pb(--y),
        edges[y].pb(x);
    bfs(0);
    dfs(0);
    dfs2(0, 0);
    int v;
    ll k;
    fori(m)
    {
        ll ans = 0;
        readln(v, k);
        --v;
        int u = vertex[v];
        int t = vertex[u];
        if (t == v)
        {
            ans = (k / 2) * (d[u] + d[v]);
            if (k % 2)
                ans += d[v];
        }
        else
        {
            k--;
            ans = d[v] + (k / 2) * (d[u] + d[t]);
            if (k % 2)
                ans += d[u];
        }
        writeln(ans);
    }
}

int main()
{
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
    return 0;
}

























void print(double a){printf(" " DOUBLEFORMAT,a);}
void print(int a){printf(" %d",a);}
void print(string a){printf(" %s",a.c_str());}
void print(long long a){printf(" %lld",a);}
void print(unsigned long a){printf(" %ld",a);}
void print(unsigned int a){printf(" %d",a);}
void print(char a){printf(" %c",a);}
void print_no_space(double a){printf(DOUBLEFORMAT, a);}
void print_no_space(int a){printf("%d", a);}
void print_no_space(string a){printf("%s", a.c_str());}
void print_no_space(long long a){printf("%lld", a);}
void print_no_space(unsigned long a){printf("%ld", a);}
void print_no_space(unsigned int a){printf("%d", a);}
void print_no_space(char a){printf("%c", a);}

template<class Type>
void print_no_space(vector<Type>& a);
template<class Type>
void print(vector<Type>& a){for(int i=0;i<a.size();++i)print(a[i]);}
template<class Type>
void print(vector<vector<Type> >& a){if(a.size())(a.size()==1)?print(a[0]):writeln2(a[0]);for(int i=1;i<a.size()-1;++i)writeln2(a[i]);if(a.size()>=2)print_no_space(a.back());}
template<class Type1, class Type2>
void print(pair<Type1, Type2>& a){print(a.first);print(a.second);}

template<class Type>
void print_no_space(vector<Type>& a){if(a.size())print_no_space(a[0]);for(int i=1;i<a.size();++i)print(a[i]);}
template<class Type>
void print_no_space(vector<vector<Type> >&a){for(int i=0;i<a.size()-1;++i)writeln(a[i]);if(a.size())print_no_space(a.back());}
template<class Type1, class Type2>
void print_no_space(pair<Type1, Type2>&a){print_no_space(a.first);print(a.second);}
template <class Head, class... Tail>
void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
template <class Head, class... Tail>
void writeln(Head head, Tail... tail){print_no_space(head);writeln2(tail...);}

void read(double &a){scanf("%lf",&a);}
void read(int &a){scanf("%d",&a);}
void read(string &a){cin>>a;}
void read(long long &a){scanf("%lld",&a);}
void read(char &a){scanf("%c",&a);}
template<class Type1, class Type2>
void read(pair<Type1, Type2>&a){readln(a.first, a.second);}
template<class Type>
void read(vector<Type> &a){if(a.size()==0){int n;read(n);a.resize(n);}for(int i=0;i<a.size();++i)readln(a[i]);}
template <class Head,class... Tail>
void readln(Head& head,Tail&... tail){read(head);readln(tail...);}
