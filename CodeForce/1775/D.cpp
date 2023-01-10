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
    vi a(n);
    readln(a);
    ints(s, t); --s; --t;
    if (s == t)
    {
        writeln(1);
        writeln(s + 1);
        return;
    }
    int N = 300001;
    vector<vector<pii>> g(N);
    fori(n)
    {
        int x = a[i];
        vector<int> p;
        for (int d = 2; d * d <= x; ++d)
            if (x % d == 0)
            {
                p.pb(d);
                while (x % d == 0)
                    x /= d;
            }
        if (x > 1)
            p.pb(x);

        for (int x: p)
            for (int y: p)
                if (x != y)
                    g[x].pb({y, i});
        if (i == s)
            for (int x: p)
                g[0].pb({x, i});
        if (i == t)
            for (int x: p)
                g[x].pb({1, i});
    }
    queue<int> q;
    q.push(0);
    vector<int> d(N, MOD);
    vector<pii> p(N, {-1, -1});
    d[0] = 0;
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (auto [v, w]: g[u])
            if (d[v] > d[u] + 1)
                q.push(v),
                p[v] = {u, w},
                d[v] = d[u] + 1;
    }
    if (d[1] == MOD)
        return writeln(-1);
    vector<int> path;
    int u = 1;
    while (p[u].first != -1)
        path.pb(p[u].second + 1),
        u = p[u].first;
    reverse(all(path));
    writeln(path.size());
    writeln(path);
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
