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

int highestBit(int x) { return 31 - __builtin_clz(x); }

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

void solveXor(vector<int>& a) {
    int start = 0;
    for (int bit = 31; bit >= 0; --bit)
    {
        int mask = 1 << bit;
        int mn = -1;
        int index = -1;
        for (int i = start; i < SZ(a); ++i)
            if (a[i] & mask)
                if (mn < a[i])
                    mn = a[i],
                    index = i;
        if (index == -1)
            continue;
        swap(a[index], a[start]);
        fori(SZ(a))
            if (i != start)
                if (a[i] & mask)
                    a[i] ^= mn;
        ++start;
    }
    while (SZ(a) > start)
        a.pop_back();
};

struct basis
{
    vector<int> a;

    basis(int x) {
        a = {x};
    }

    basis() {}

    basis operator+(const basis& other) const {
        basis ret;
        ret.a = a;
        copy(all(other.a), back_inserter(ret.a));
        solveXor(ret.a);
        return ret;
    }

    int get() const {
        int ans = 0;
        for (int x: a)
            ans ^= x;
        return ans;
    }
};

void run()
{
    ints(n);
    vi a(n);
    readln(a);
    vector<vector<int>> g(n);
    fori(n - 1)
    {
        ints(u, v); --u; --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    lca l(g);

    vector<int> tin(n, 0);
    vector<int> tout(n, 0);
    int time = 0;
    vector<basis> basises;
    vector<basis> pref(1);
    vector<basis> suff(1);
    vector<basis> curr(n);

    auto dfs = [&](auto dfs, int u, int p) -> void {
        tin[u] = time++;
        curr[u] = basis(a[u]);
        basises.pb(basis(a[u]));

        for (int v: g[u])
            if (v != p)
            {
                dfs(dfs, v, u);
                curr[u] = curr[u] + curr[v];
            }
        tout[u] = time++;
        basises.pb(basis(a[u]));
    };
    dfs(dfs, 0, -1);
    for (basis& b: basises)
        pref.pb(pref.back() + b);
    reverse(all(basises));
    for (basis& b: basises)
        suff.pb(suff.back() + b);
    reverse(all(basises));
    reverse(all(suff));

    ints(q);
    fori(q)
    {
        ints(r, u); --r; --u;
        int z = l.get(r, u);
        if (u == r)
            writeln(suff[0].get());
        else if (z != u)
            writeln(curr[u].get());
        else
        {
            int p = l.getChildWithVertex(u, r);
            int l = max(0, tin[p] - 1);
            int r = min(SZ(basises), tout[p] + 1);
            const auto& left = pref[l];
            const auto& right = suff[r];
            const auto& up = left + right;
            writeln(up.get());
        }
    }
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
