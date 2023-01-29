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

static const int FINITE = 1;
static const int INFINITE = 2;

void run()
{
    ints(n);
    vi a(n);
    readln(a);
    vector<int> used(n, 0);
    vector<int> root;

    vector<vector<int>> g(n);
    vector<int> childs(n, -1);
    fori(n)
    {
        int v = i + a[i];
        if (v >= 0 && v < n)
            g[v].pb(i);
    }

    auto dfs = [&](auto dfs, int u, int p) -> void {
        childs[u] = 1;
        for (int v: g[u])
        {
            if (v != p && childs[v] == -1)
                dfs(dfs, v, u);
            childs[u] += childs[v];
        }

    };
    fori(n)
        if (childs[i] == -1)
            dfs(dfs, i, -1);

    fori(n)
        if (!used[i])
        {
            vector<int> path;
            auto dfs = [&](auto dfs, int u, int d) -> void {
                path.pb(u);
                int v = u + a[u];
                if (v < 0 || v >= n)
                    used[u] = FINITE;
                else
                {
                    used[u] = INFINITE;
                    if (!used[v])
                        dfs(dfs, v, d + 1);
                    used[u] = used[v];
                }
            };
            dfs(dfs, i, 0);
            if (!i)
                root = path;
        }
    int finite = 0;
    fori(n) finite += used[i] == FINITE;

    int l = SZ(root);
    ll ans = (n + 1) * 1ll * l;

    if (used[0] == FINITE)
        ans += (n - l) * 1ll * (2 * n + 1);

    for (int u: root)
        if (used[0] == FINITE)
            ans += finite - childs[u];
        else
            ans += finite;
    writeln(ans);
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
