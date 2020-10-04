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
//dijkstra
template<typename T>
vector<T> dijkstra(const vector<vector<pair<T, int>>> g, const int start)
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
        for (const auto& [w, v]: g[u])
            if (T temp = d[u] + w; d[v] > temp)
                d[v] = temp,
                q.push({-d[v], v});
    }
    return d;
}

//}}}

void run()
{
    auto getDist = [&](const pii& a, const pii& b) {
        return abs(a.first - b.first) + abs(a.second - b.second);
    };

    ints(_, n);
    vector<array<int, 3>> a(n);
    pii s, f;
    readln(s, f);
    fori(n)
        readln(a[i][0], a[i][1]), a[i][2] = i + 1;
    int ans = getDist(s, f);
    vector<vector<pii>> g(n + 2);
    fori(n)
    {
        int d = min(abs(a[i][0] - s.first), abs(a[i][1] - s.second));
        g[0].emplace_back(d, a[i][2]);
        d = abs(a[i][0] - f.first) + abs(a[i][1] - f.second);
        g[a[i][2]].emplace_back(d, n + 1);
    }
    sort(all(a));
    fori1(n)
        g[a[i - 1][2]].emplace_back(abs(a[i][0] - a[i - 1][0]), a[i][2]),
        g[a[i][2]].emplace_back(abs(a[i][0] - a[i - 1][0]), a[i - 1][2]);
    for (auto& x: a)
        swap(x[0], x[1]);
    sort(all(a));
    fori1(n)
        g[a[i - 1][2]].emplace_back(abs(a[i][0] - a[i - 1][0]), a[i][2]),
        g[a[i][2]].emplace_back(abs(a[i][0] - a[i - 1][0]), a[i - 1][2]);
    auto x = dijkstra(g, 0);
    writeln(min(ans, x.back()));
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
