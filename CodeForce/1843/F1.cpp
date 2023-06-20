// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
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
typedef    long long      ll;

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
//}}}

void run()
{
    ints(n);
    vector<vector<int>> g(n + 10);
    vector p(n + 10, 0);
    vector m(n + 10, 0);
    vector value(n + 10, 0);
    value[0] = 1;
    vector<tuple<int, int, int>> requests;
    int index = 1;
    fori(n)
    {
        char c;
        readln(c);
        int u, v = index, x;
        if (c == '?')
        {
            readln(u, v, x); --u; --v;
            requests.emplace_back(u, v, x);
        }
        else
        {
            readln(u, x); --u;
            value[v] = x;
            g[u].pb(v);
            g[v].pb(u);
            ++index;
        }
    }

    auto dfs = [&](auto dfs, int u, int parent, int s, int mn, int mx) -> void {
        s += value[u];
        //writeln("GO", u + 1, s);

        mn = min(mn, s);
        mx = max(mx, s);

        p[u] = max(parent == -1 ? 0 : p[parent], s - mn);
        m[u] = min(parent == -1 ? 0 : m[parent], s - mx);
        //writeln(u + 1, p[u], m[u]);
        for (int v: g[u])
            if (v != parent)
                dfs(dfs, v, u, s, mn, mx);
    };
    dfs(dfs, 0, -1, 0, 0, 0);
    for (auto& [u, v, k]: requests)
    {
        if (k == 0)
            writeln("YES");
        else if (k > 0)
            writeln(p[v] >= k ? "YES" : "NO");
        else if (k < 0)
            writeln(m[v] <= k ? "YES" : "NO");
    }
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
