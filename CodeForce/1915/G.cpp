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
//dijkstra
template<typename T>
vector<T> dijkstra(const vector<vector<pair<int, T>>> g, const int start, ll weight)
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
            if (T temp = d[u] + w * weight; d[v] > temp)
                d[v] = temp,
                q.push({-d[v], v});
    }
    return d;
}

//}}}

void run()
{
    ints(n, m);
    vector<vector<pair<int, ll>>> g(n);
    fori(m)
    {
        ints(u, v, w); --u; --v;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    vector<ll> s(n);
    readln(s);
    vector<vector<ll>> d;
    fori(n)
        d.pb(dijkstra(g, i, s[i]));
    vector<pair<ll, int>> b;
    fori(n)
        b.pb({s[i], i});
    sort(all(b));
    reverse(all(b));
    auto ans = d[0];
    for (auto& [x, index]: b)
        if (x < s[0])
        {
            auto nxt(ans);
            fori(n)
                nxt[i] = min(ans[i], ans[index] + d[index][i]);
            ans = nxt;
        }
    writeln(ans.back());
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
