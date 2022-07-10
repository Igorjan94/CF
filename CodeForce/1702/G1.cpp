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
//lca
struct lca
{
    vector<vector<int>> g, up;
    vector<int> h;
    int n, l;

    lca(const vector<vector<int>>& g) //O(n * log(n))
    {
        this->g = g;
        n = SZ(g);
        l = 1;
        while ((1 << l) <= n) ++l;
        h.resize(n, -1);
        up.resize(l + 1, vector<int>(n));
        dfs(0, 0);
        fori(l)
            forj(n)
                up[i + 1][j] = up[i][up[i][j]];
    }
 
    int getParent(int u, int dist) { //O(log(n))
        fori(l)
            if (dist >> i & 1)
                u = up[i][u];
        return u;
    }

    void dfs(int u, int p) //O(n)
    {
        h[u] = h[p] + 1;
        up[0][u] = p;
        for (const int& v: g[u])
            if (v != p)
                dfs(v, u);
    }

    int get(int a, int b) //O(log(n))
    {
        if (h[a] < h[b]) swap(a, b);
        a = getParent(a, h[a] - h[b]);
        if (a == b) return a;
        ROF(i, l, 0)
            if (up[i][a] != up[i][b])
                a = up[i][a],
                b = up[i][b];
        return up[0][a];
    }

    int getChildWithVertex(int a, int b) //O(log(n))
    {
        if (a == b) return -1;
        return getParent(b, h[b] - h[a] - 1);
    }
};

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
    lca l(g);
    ints(q);
    forn(Q, q)
    {
        ints(k);
        map<int, vector<int>> m;
        fori(k)
        {
            ints(x); --x;
            m[-l.h[x]].pb(x);
        }
        if (k == 1)
        {
            writeln("YES");
            continue;
        }
        auto find = [&](const int& first, const int& second) {
            int cur = l.get(first, second);
            if (cur == first || cur == second)
                return -1;
            return cur;
        };
        bool ok = true;
        bool last = false;
        int first = -1;
        int second = -1;
        for (auto& [h, vs]: m)
            if (vs.size() > 2)
                ok = false;
            else
            {
                for (int u: vs)
                {
                    if (last)
                        ok = false;
                    if (first == -1)
                        first = u;
                    else
                    {
                        if (find(u, first) == -1)
                        {
                            if (second != -1 && find(u, second) == -1)
                            {
                                int fin = find(first, second);
                                if (fin != u)
                                    ok = false;
                                else
                                    last = true;
                            }
                            first = u;
                        }
                        else if (second == -1)
                            second = u;
                        else if (find(u, second) == -1)
                            second = u;
                        else
                            ok = false;
                    }
                }
            }

        writeln(ok ? "YES" : "NO");
    }
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
