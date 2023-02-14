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
    vector<vector<int>> g(n);
    fori(n - 1)
    {
        ints(u, v); --u; --v;
        g[u].pb(v);
        g[v].pb(u);
    }

    vector<int> bad;

    bool ok = true;
    vector<map<int, int>> children(n);
    auto dfs = [&](auto dfs, int u, int p) -> int {
        for (int v: g[u])
            if (v != p)
                ++children[u][dfs(dfs, v, u)];

        if (children[u].empty())
            return 0;
        auto it = children[u].find(-1);
        int badChilds = it == children[u].end() ? 0 : it->second;

        int goodChilds = SZ(children[u]) - (badChilds != 0);
        bool isGood = goodChilds <= 1;

        if (badChilds >= 2 || (badChilds == 1 && !isGood))
            ok = false;

        if (!isGood)
            bad.pb(u);

        bool isBad = badChilds || !isGood;
        if (isBad)
            return -1;
        auto child = children[u].begin()->first;
        return child + 1;
    };

    int l = dfs(dfs, 0, -1);
    if (bad.size())
    {
        int u = bad[0];
        bad.clear();
        children.clear();
        children.resize(n);
        l = dfs(dfs, u, -1);
    }
    if (!ok || bad.size() >= 2)
        return writeln(-1);
    if (bad.size())
    {
        int u = bad[0];
        if (SZ(children[u]) > 2)
            return writeln(-1);
        l = children[u].begin()->first + children[u].rbegin()->first + 2;
    }

    while (l % 2 == 0) l /= 2;
    writeln(l);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
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
