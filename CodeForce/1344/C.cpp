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
//umin
template<typename T1, typename T2>
T1 umin(T1& a, T2 b)
{
    return a > T2(b) ? a = b : a;
}

//topsort
vector<int> topsort(const vector<vector<int>>& edges, bool reversed = false)
{
    int n = edges.size();
    vector<int> ans;
    vector<int> used(n, -1);
    bool cycle = false;
    int iteration = 0;
    
    function<void(int)> dfs = [&](int u) {
        used[u] = iteration;
        for (const int& v: edges[u])
            if (used[v] == iteration)
                cycle = true;
            else if (used[v] == -1)
                dfs(v);
        ans.pb(u);
    };

    fori(n)
        if (used[i] == -1)
            dfs(i), iteration++;
    if (cycle)
        return vector<int>();
    if (!reversed)
        reverse(ans.begin(), ans.end());
    return ans;
}

//}}}

void run()
{
    ints(n, m);
    vector<pii> a(m);
    readln(a);
    vector<vector<int>> g(n);
    for (auto [u, v]: a)
        g[--u].pb(--v);

    vector<int> order = topsort(g);
    if (order.empty())
        return writeln(-1);
    string ans(n, 'A');
    int cnt = n;
    vector<int> mn(n);
    iota(all(mn), 0);
    for (int i: order)
        for (int j: g[i])
            umin(mn[j], mn[i]);
    fori(n) if (mn[i] < i) ans[i] = 'E';
    reverse(all(mn));
    for (int i: order)
        for (int j: g[i])
            umin(mn[j], mn[i]);
    fori(n) if (mn[i] < i) cnt--, ans[i] = 'E';
    writeln(cnt);
    writeln(ans);
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
