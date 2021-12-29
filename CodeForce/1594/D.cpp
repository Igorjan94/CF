// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>

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
//dsu
struct dsu
{
    vector<int> a, size;

    dsu(int n)
    {
        a.resize(n);
        size.resize(n, 1);
        iota(a.begin(), a.end(), 0);
    }

    int get(int i)
    {
        return a[i] == i ? i : a[i] = get(a[i]);
    }

    int operator[](int i)
    {
        return get(i);
    }

    void uni(int i, int j)
    {
        i = get(i);
        j = get(j);
        if (i == j) return;
        if (size[i] > size[j])
            swap(i, j);
        a[i] = j;
        size[j] += size[i];
    }
};

//}}}

void run()
{
    ints(n, m);
    dsu d(n);
    vector<int> opposite(n, -1);
    vector<pii> o;

    auto add = [&](int i, int j) {
        i = d[i];
        j = d[j];
        if (opposite[i] == -1)
            opposite[i] = j;
        else
            d.uni(j, opposite[i]);
    };

    forn(q, m)
    {
        int i, j;
        string s;
        readln(i, j, s); --i; --j;
        if (s == "crewmate")
            d.uni(i, j);
        else
            o.pb({i, j});
    }
    for (auto& [i, j]: o)
        add(i, j),
        add(j, i);

    for (auto& [i, j]: o)
        if (d[i] == d[j])
            return writeln(-1);

    vector<vector<int>> g(n);
    fori(n)
        if (opposite[i] != -1)
        {
            int u = d[i];
            int v = d[opposite[i]];
            g[u].pb(v);
            g[v].pb(u);
        }
    vector<int> color(n, -1);
    bool ok = true;
    function<pii(int)> dfs = [&](int u) {
        pii p = {0, 0};
        (color[u] ? p.first : p.second) += d.size[u];
        for (int v: g[u])
            if (color[v] == -1)
            {
                color[v] = color[u] ^ 1;
                auto [f, s] = dfs(v);
                p.first += f;
                p.second += s;
            }
            else if (color[v] == color[u])
                ok = false;

        return p;
    };
    if (!ok)
        return writeln(-1);
    int ans = 0;
    fori(n)
        if (color[i] == -1 && d[i] == i)
        {
            color[i] = 0;
            auto [f, s] = dfs(i);
            ans += max(f, s);
        }
    
    writeln(ans);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
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
