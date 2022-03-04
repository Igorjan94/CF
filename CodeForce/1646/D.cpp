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

typedef pii state;

void run()
{
    ints(n);
    if (n == 2)
    {
        writeln(2, 2);
        writeln(1, 1);
        return;
    }
    vector<vector<int>> g(n);
    vector<int> w(n, 1);
    fori(n - 1)
    {
        ints(u, v); --u; --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<pair<state, state>> dp(n);
    function<void(int, int)> dfs = [&](int u, int p) {
        state used = {1, -SZ(g[u])};
        state notUsed = {0, 0};
        auto add = [&](state& s, const state& from) {
            s.first += from.first;
            s.second += from.second;
        };
        for (int v: g[u])
            if (v != p)
            {
                dfs(v, u);
                auto [l, r] = dp[v];
                add(used, r);
                add(notUsed, max(l, r));
            }
        dp[u] = {used, notUsed};
    };

    function<void(int, int, int)> dfs2 = [&](int u, int p, bool use) {
        if (use)
            w[u] = SZ(g[u]);
        for (int v: g[u])
            if (v != p)
            {
                if (use)
                    dfs2(v, u, false);
                else
                    dfs2(v, u, dp[v].first >= dp[v].second);
            }
    };
    dfs(0, -1);
    auto [l, r] = dp[0];
    dfs2(0, -1, l > r);
        
    writeln(max(l, r).first, accumulate(all(w), 0ll));
    writeln(w);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    run();
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
