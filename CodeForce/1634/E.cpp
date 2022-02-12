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
    vector<vector<int>> a(n);
    vector<string> ans(n);
    map<int, int> order, cnt;
    vector<map<int, vector<int>>> m(n);
    fori(n)
    {
        ints(m);
        a[i].resize(m);
        ans[i] = string(m, 'L');
        readln(a[i]);
        for (int& x: a[i])
        {
            --x;
            cnt[x]++;
            if (!order.contains(x))
            {
                auto sz = order.size();
                order[x] = sz + n;
            }
        }
    }
    for (auto& [_, c]: cnt)
        if (c % 2)
            return writeln("NO");
    int sz = n + SZ(order);
    vector<set<int>> g(sz);
    vector<int> edges;
    vector<int> deg(sz, 0);
    vector<bool> used(sz);
    forn(u, n)
        forj(a[u].size())
        {
            int x = a[u][j];
            int v = order[x];
            deg[u]++;
            deg[v]++;
            g[u].insert(edges.size());
            g[v].insert(edges.size());
            m[u][v].pb(j);
            edges.pb(u ^ v);
        }

    forn(u, n)
        if (!used[u])
        {
            vector<int> path;
            vector<int> st = {u};
            while (st.size())
            {
                int u = st.back();
                if (deg[u] == 0)
                {
                    path.pb(u);
                    used[u] = true;
                    st.pop_back();
                }
                else
                {
                    int e = *g[u].begin();
                    int v = edges[e] ^ u;
                    g[u].erase(e);
                    g[v].erase(e);
                    deg[u]--;
                    deg[v]--;
                    st.pb(v);
                }
            }
            fori1(SZ(path))
            {
                int u = path[i - 1];
                int v = path[i];
                char c = 'L';
                if (u >= n)
                    swap(u, v), c = 'R';
                ans[u][m[u][v].back()] = c;
                m[u][v].pop_back();
            }
        }
    writeln("YES");
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
