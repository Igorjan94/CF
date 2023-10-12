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
    ints(n, m);
    vector<vector<int>> g(n);
    map<int, int> h;
    map<int, int> opp;

    auto get = [&](int x) -> int {
        auto it = h.find(x);
        if (it != h.end())
            return it->second;
        int sz = h.size();
        h[x] = sz;
        opp[sz] = x;
        return sz;
    };
    fori(n)
    {
        ints(u, k); u = get(u);
        vector<int> a(k);
        readln(a);
        for (int v: a)
            v = get(v),
            g[u].pb(v),
            g[v].pb(u);
    }
    set<int> stop;
    fori(m)
    {
        ints(k);
        vector<int> a(k);
        readln(a);
        for (int x: a)
            stop.insert(get(x));
    }
    vector<int> mx(n, 0);
    for (int x: stop)
    {
        vector<int> d(n, MOD);
        queue<int> q;
        d[x] = 1;
        q.push(x);
        while (q.size())
        {
            int u = q.front();
            q.pop();
            for (int v: g[u])
                if (d[v] == MOD)
                    d[v] = d[u] + 1,
                    q.push(v);
        }
        fori(n)
            mx[i] = max(mx[i], d[i]);
    }
    int ans = MOD;
    int index = MOD;
    fori(n)
        if (mx[i] < ans || (mx[i] == ans && opp[i] < index))
            ans = mx[i],
            index = opp[i];
    writeln(ans, index);
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
