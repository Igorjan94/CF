// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#include <limits>
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(size(a))

typedef  pair<int, int>   pii;
typedef   vector<int>     vi;
typedef    int      ll;
//typedef    long long      ll;

#define pb push_back
#define all(a) begin(a), end(a)
#define ints(a...) int a; readln(a)

[[maybe_unused]] const int MOD = 1000000007;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

#define ttt12i template<class T1, class T2> inline
#define  ttti  template<class T> inline

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

//Igorjan
//dijkstra
template<typename T>
vector<T> dijkstra(const vector<vector<pair<int, T>>> g, const int start)
{
    int n = SZ(g);
    vector<T> d(n, numeric_limits<T>::max());
    priority_queue<pair<T, int>> q;

    q.push({d[start] = 0, start});
    while (!q.empty())
    {
        auto [curd, u] = q.top();
        q.pop();
        if (-curd > d[u])
            continue;
        for (const auto& [v, w]: g[u])
            if (T temp = d[u] + w; d[v] > temp)
                d[v] = temp,
                q.push({-d[v], v});
    }
    return d;
}

//}}}

void run()
{
    ints(n, s, t); --s; --t;
    vector<vector<int>> a(n);
    vector<vector<int>> b(n);
    vector<pii> g, e;
    ints(m);
    fori(m)
    {
        ints(u, v); --u; --v;
        a[u].pb(v);
        a[v].pb(u);
        g.pb({min(u, v), max(u, v)});
    }
    ints(m1);
    fori(m1)
    {
        ints(u, v); --u; --v;
        b[u].pb(v);
        b[v].pb(u);
        e.pb({min(u, v), max(u, v)});
    }
    set S(all(e));
    vector<pii> same;
    vector ok(n, false);
    for (auto& q: g)
        if (S.contains(q)) {
            ok[q.first] = ok[q.second] = true;
            same.pb(q);
        }
    if (same.empty()) return writeln(-1);
    vector d1(n, -1), d2(n, -1);
    bool bi1 = true;
    bool bi2 = true;
    auto checkColor = [&](auto dfs, bool& bi, vector<int>& d, vector<vector<int>>& g, int u, int p) -> void {
        for (int v: g[u])
            if (d[v] == -1)
                d[v] = d[u] + 1,
                dfs(dfs, bi, d, g, v, u);
            else if (d[v] % 2 != (d[u] + 1) % 2)
                bi = false;
    };
    d1[s] = 0;
    d2[t] = 0;
    checkColor(checkColor, bi1, d1, a, s, -1);
    checkColor(checkColor, bi2, d2, b, t, -1);
    if (bi1 && bi2) {
        bool fail = false;
        fori(n)
            if (ok[i])
                fail |= d1[i] % 2 == d2[i] % 2;
        if (!fail)
            return writeln(-1);
    }
    auto get = [&](int u1, int u2) {
        return u1 * n + u2;
    };
    vector<vector<pair<int, ll>>> G(n * n);
    fori(n)
        forj(n)
        {
            int u = get(i, j);
            for (int v: a[i])
                for (int w: b[j])
                {
                    int f = get(v, w);
                    G[u].pb({f, abs(w - v)});
                    G[f].pb({u, abs(i - j)});
                }
        }
    int start = get(s, t);
    auto d = dijkstra(G, start);
    ll mn = numeric_limits<ll>::max();
    fori(n)
        if (ok[i])
            mn = min(mn, d[get(i, i)]);
    writeln(mn);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ints(t); fori(t) run();
    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

#define a _a
#define n _n
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
