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
//fenwickTree
//1-indexed, [l, r]
template <typename T>
struct fenwickTree
{
    vector<T> t;
    int n;

    fenwickTree(int size, T value = 0)
    {
        n = size;
        t.resize(n + 1, value);
    }

    fenwickTree(vector<T>& arr)
    {
        n = arr.size();
        t.resize(n + 1, 0);
        fori(n)
            update(i + 1, arr[i]);
    }

    void update(int index, T value)
    {
        for (; index <= n; index += index & -index)
            t[index] += value;
    }

    T sum(int i)
    {
        T res = 0;
        for (; i; i -= i & -i)
            res += t[i];
        return res;
    }

    T sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    T sum0(int l, int r)
    {
        return sum(r + 1) - sum(l);
    }
};

//}}}

const int p = 500;
//Mo's algorithm on subtrees
void run()
{
    ints(n, q);
    vi a(n);
    readln(a);
    vector<vector<int>> g(n);
    fori(n - 1)
    {
        ints(u, v); --u; --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<int> in(n, 0);
    vector<int> out(n, 0);
    int t = 0;
    vector<int> tree;
    function<void(int, int)> dfs = [&](int u, int p) {
        tree.pb(a[u]);
        in[u] = t++;
        for (int v: g[u])
            if (v != p)
                dfs(v, u);
        out[u] = t;
    };
    dfs(0, -1);
    
    vector<array<int, 4>> requests;
    fori(q)
    {
        ints(u, k); --u;
        requests.pb({in[u], out[u] - 1, k, i});
    }

    sort(all(requests), [&](const auto& a, const auto& b) {
        int sign = (a[0] / p) % 2 == 0 ? 1 : -1;
        return tuple(a[0] / p, a[1] * sign) < tuple(b[0] / p, b[1] * sign);
    });

    vector<int> counts(100001, 0);
    fenwickTree f(n + 1, 0);
    auto add = [&](int x) {
        if (counts[tree[x]])
            f.update(counts[tree[x]], -1);
        ++counts[tree[x]];
        f.update(counts[tree[x]], 1);
    };
    auto del = [&](int x) {
        f.update(counts[tree[x]], -1);
        --counts[tree[x]];
        if (counts[tree[x]])
            f.update(counts[tree[x]], 1);
    };
    auto addLeft = add;
    auto addRight = add;
    auto delLeft = del;
    auto delRight = del;

    int L = 0;
    int R = -1;
    vector<int> ans(q, 0);
    for (auto& [l, r, k, id]: requests) {
        while (L > l) addLeft(--L);
        while (R < r) addRight(++R);
        while (L < l) delLeft(L++);
        while (R > r) delRight(R--);
        ans[id] = k > n ? 0 : f.sum(k, n);
    }
    fori(q)
        writeln(ans[i]);
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
