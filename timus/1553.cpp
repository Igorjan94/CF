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
//downTree
//0-indexed, [l..r)
template<typename T, typename F>
struct downTree {
    F f;
    vector<T> t;
    int n;

    downTree(int sz, const F &g, T defaultValue = T()) : f(g)
    {
        n = 1;
        while (n <= sz) n <<= 1;
        t.resize(n * 2, defaultValue);
    }

    downTree(const vector<T> &a, const F &g, T defaultValue = T()) : downTree(a.size(), g, defaultValue)
    {
        for (int i = 0; i < SZ(a); ++i)
            t[i + n] = a[i];
        for (int i = n - 1; i >= 1; --i)
            t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    void update(int i, const T& x)
    {
        i += n;
        t[i] = f(t[i], x);
        for (i >>= 1; i > 1; i >>= 1)
            t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    T get(int l, int r) 
    {
        if (l > r)
            swap(l, r);
        return getRaw(l, r + 1);
    }

    T getRaw(int l, int r)
    {
        T resL = t[0];
        T resR = t[0];
        l += n;
        r += n;
        while (l < r)
        {
            if (l & 1)
                resL = f(resL, t[l++]);
            if (r & 1)
                resR = f(t[--r], resR);
            l >>= 1;
            r >>= 1;
        }
        return f(resL, resR);
    }
};


//}}}
int f(const int& a, const int& b)
{
    return max(a, b);
}

//IgorjanheavyLight
template<typename T, typename F>
struct heavyLight 
{
    F f;
    vector<T> a;
    downTree<T, F> tree;

    int n;
    int paths = 0;
    vector<int> sizes;  //Size of subtree
    vector<int> depth;  //Depth of vertex
    vector<int> parent; //Parent vertex
    vector<int> path;   //Path to which vertex belongs (like dsu)
    vector<int> heavy;  //Heavy child if exists else -1
    vector<int> index;  //Index of vertex in segment tree
    vector<int> first;  //Highest vertex of path

    heavyLight(const vector<vector<int>>& g, const vector<T>& a, const F& f, const T& defaultValue) : tree(a, f, defaultValue) 
    {
        this->a = a;
        this->f = f;
        n = g.size();
        sizes.resize(n, 1);
        depth.resize(n, 0);
        parent.resize(n, -1);
        path.resize(n, -1);
        heavy.resize(n, -1);
        index.resize(n, -1);
        first.resize(n, -1);

        auto dfs = [&](auto dfs, int u, int p) -> void
        {
            for (const int& v: g[u]) if (v != p)
            {
                depth[v] = depth[u] + 1;
                parent[v] = u;
                dfs(dfs, v, u);
                sizes[u] += sizes[v];
            }
            for (const int& v: g[u]) if (v != p)
                if (sizes[v] * 2 >= sizes[u])
                    heavy[u] = v;
        };
        dfs(dfs, 0, -1);

        int cur = -1;
        fori(n)
            if (heavy[i] == -1)
            {
                int u = i;
                vector<int> currentPath;
                while (true)
                {
                    currentPath.pb(u);
                    path[u] = paths;
                    int nu = parent[u];
                    if (nu == -1 || heavy[nu] != u)
                        break;
                    u = nu;
                }

                reverse(all(currentPath));
                for (int v: currentPath)
                    first[v] = u,
                    index[v] = ++cur;
                ++paths;
            }
    }

    T get(int u, int v) 
    {
        int l = path[u];
        int r = path[v];
        if (l == r)
            return tree.get(index[u], index[v]);
        if (depth[first[u]] < depth[first[v]])
            swap(u, v);
        int left = tree.get(index[u], index[first[u]]);
        return f(left, get(parent[first[u]], v));
    }
};

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

    heavyLight hld(g, vector(n, 0), &f, 0);

    ints(q);
    forn(Q, q)
    {
        char c;
        int u, v;
        readln(c, u, v); --u;
        if (c == 'I') //Change
        {
            hld.a[u] += v;
            hld.tree.update(hld.index[u], hld.a[u]);
        }
        else //Query
            writeln(hld.get(u, --v));
    }

}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    run();
    //cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
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
