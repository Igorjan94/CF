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
const int N = 4096;
const int Z = 26;
const int M = N + N;
int a[M][Z];
int sum[M];
int pref[M][Z + 1];
int temp[N];

void run()
{
    ints(n, q);
    vector<vector<pii>> g(n);
    fori(n - 1)
    {
        ints(u, v); --u; --v; char c; readln(c);
        g[u].pb({v, c - 'a'});
        g[v].pb({u, c - 'a'});
    }
    fori(n)
        sort(all(g[i]), [](const pii& a, const pii& b) {
            return pair(a.second, a.first) < pair(b.second, b.first);
        });

    auto getAutomaton = [&](int S) {
        fori(M) forj(Z) a[i][j] = -1;
        fori(M) sum[i] = 0;
        fori(N) temp[i] = 0;
        int sz = 1;
        auto dfs = [&](auto dfs, int u, int root, int p) -> void {
            if (root)
                sum[root]++;
            for (auto& [v, c]: g[u])
                if (v != p)
                {
                    if (a[root][c] == -1)
                        a[root][c] = sz++;
                    dfs(dfs, v, a[root][c], u);
                }
        };
        dfs(dfs, S, 0, -1);

        auto getCount = [&](auto getCount, int root) -> int {
            pref[root][0] = sum[root];
            fori(Z)
                pref[root][i + 1] = pref[root][i] + (a[root][i] == -1 ? 0 : getCount(getCount, a[root][i]));
            return pref[root][Z];
        };
        getCount(getCount, 0);

        auto getAns = [&](auto getAns, int u, int root, int p) -> void {
            for (auto& [v, c]: g[u])
                if (v != p)
                {
                    temp[v] = temp[u] + pref[root][c];
                    getAns(getAns, v, a[root][c], u);
                }
        };
        getAns(getAns, S, 0, -1);
    };
    vector<pii> requests(q);
    readln(requests);
    vector<int> order(q);
    iota(all(order), 0);
    sort(all(order), [&](const int& a, const int& b) {
        return requests[a] < requests[b];
    });
    vector<int> ans(q);
    int prev = -1;

    for (const int& i: order)
    {
        auto& [S, F] = requests[i]; --S; --F;
        if (S != prev)
        {
            getAutomaton(S);
            prev = S;
        }
        ans[i] = temp[F];
    }
    for (int x: ans)
        writeln(x);
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
