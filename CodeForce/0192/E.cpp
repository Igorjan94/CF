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
//segmentTree
//0-indexed, [l..r]
template<typename T>
struct segmentTree
{
    int n;
    vector<T> t;
    vector<T> add;
    //vector<T> pos;
    function<T(const T&, const T&)> f = [](const T& a, const T& b) { return min(a, b); };
    T NEITRAL_ELEMENT = numeric_limits<T>::max();
 
    void push(int v, int tl, int tr)
    {
        if (add[v] == 0) return;

        t[v] += add[v];
        if (tl != tr)
            add[v * 2] += add[v],
            add[v * 2 + 1] += add[v];
        add[v] = 0;
    }

    void build(const vector<T>& a, int v, int l, int r)
    {
        if (l == r)
        {
            t[v] = a[l];
            //pos[v] = l;
        }
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            T left = t[v * 2];
            T right = t[v * 2 + 1];

            //if (left > right)
                //pos[v] = pos[v * 2];
            //else
                //pos[v] = pos[v * 2 + 1];
            t[v] = f(left, right);
        }
    };
 
    segmentTree(const vector<T>& a)
    {
        n = a.size();
        t.resize(n * 4 + 10);
        add.resize(n * 4 + 10, 0);
        //pos.resize(n * 4 + 10, 0);
        build(a, 1, 0, n - 1);
    }
 
    void update(int l, int r, T value)
    {
        update(1, 0, n - 1, l, r, value);
    }
 
    void update(int v, int tl, int tr, int l, int r, T value) 
    {
        push(v, tl, tr);
        if (l > r)
            return;
        if (tl == l && tr == r)
        {
            t[v] += value;
            if (tl != tr)
                add[v * 2] += value,
                add[v * 2 + 1] += value;
        }
        else 
        {
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), value);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, value);
            T left = t[v * 2];
            T right = t[v * 2 + 1];

            //if (left > right)
                //pos[v] = pos[v * 2];
            //else
                //pos[v] = pos[v * 2 + 1];
            t[v] = f(left, right);
        }
    }

    T get(int l, int r)
    {
        return get(1, 0, n - 1, l, r);
    }

    T get(int v, int tl, int tr, int l, int r) 
    {
        push(v, tl, tr);
        if (l > r) return NEITRAL_ELEMENT;

        if (tl == l && tr == r)
            return t[v];
        else 
        {
            int tm = (tl + tr) / 2;
            T left = get(v * 2, tl, tm, l, min(r, tm));
            T right = get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
            return f(left, right);
        }
    }

};

//heavyLight
template<typename T>
struct heavyLight 
{
    vector<T> a;
    segmentTree<T> tree;

    int n;
    int paths = 0;
    vector<int> sizes;  //Size of subtree
    vector<int> depth;  //Depth of vertex
    vector<int> parent; //Parent vertex
    vector<int> path;   //Path to which vertex belongs (like disjoint set union)
    vector<int> heavy;  //Heavy child if exists else -1
    vector<int> index;  //Index of vertex in segment tree
    vector<int> first;  //Highest vertex of path

    heavyLight(const vector<vector<int>>& g, const vector<T>& a) : tree(a) 
    {
        this->a = a;
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

    void upd(int u, int v, int one = 1)
    {
        if (u > v)
            swap(u, v);
        if (one == -1)
        {
            int x = min(u, v) + 1;
            int y = max(u, v);
            u = x;
            v = y;
        }
        tree.update(u, v, 1);
    }

    void update(int u, int v) 
    {
        int l = path[u];
        int r = path[v];
        if (l == r)
            return upd(index[u], index[v], -1);
        if (depth[first[u]] < depth[first[v]])
            swap(u, v);
        upd(index[u], index[first[u]]);
        update(parent[first[u]], v);
    }
};

//}}}

void run()
{
    ints(n);
    vector<vector<int>> g(n);
    vector<array<int, 3>> edges;
    vector<int> ans(n - 1);
    fori(n - 1)
    {
        ints(u, v); --u; --v;
        g[u].pb(v);
        g[v].pb(u);
        edges.pb({u, v, i});
    }
    heavyLight hld(g, vector(n, 0));
    ints(q);
    fori(q)
    {
        ints(u, v); --u; --v;
        hld.update(u, v);
    }
    for (auto& [u, v, i]: edges)
    {
        int x = hld.depth[u] < hld.depth[v] ? v : u;
        x = hld.index[x];
        ans[i] = hld.tree.get(x, x);
    }
    writeln(ans);
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
