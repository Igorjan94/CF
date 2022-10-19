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

static const int TREES = 40;
static const int N = 3 * 100000 + 10;
static const int Q = 3 * 100000 + 10;

//Igorjan
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//fenwickTree
//1-indexed, [l, r]
template <typename T>
struct fenwickTree
{
    int t[N];
    int n;

    fenwickTree()
    {
        n = N;
        fori(n) t[i] = 0;
    }

    fenwickTree(vector<T>& arr)
    {
        n = arr.size();
        fori(n)
            update(i + 1, arr[i]);
    }

    inline void update(int index, T value)
    {
        for (; index <= n; index += index & -index)
            t[index] += value;
    }

    inline T sum(int i)
    {
        T res = 0;
        for (; i; i -= i & -i)
            res += t[i];
        return res;
    }

    inline T sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    T sum0(int l, int r)
    {
        return sum(r + 1) - sum(l);
    }
};

//}}}

fenwickTree<int> trees[TREES];
bitset<N + Q> used[TREES];

struct query {
    int type;
    int l, r, k;
    query() {}
};

istream& operator>>(istream& is, query& q) {
    is >> q.type;
    if (q.type == 1)
        is >> q.l >> q.k;
    else
        is >> q.l >> q.r >> q.k;
    return is;
}
vector<query> queries;

void run()
{
    ints(n, q);
    vi a(n);
    vector<query> queries(q);
    readln(a, queries);
    vector<array<int, 3>> coords;
    fori(n)
        coords.pb({a[i], 1, i});
    fori(q)
        if (queries[i].type == 1)
            coords.pb({queries[i].k, 0, i});
    sort(all(coords));

    int counter = 0;
    for (int i = 0; i < SZ(coords); )
    {
        int j = i;
        while (j < SZ(coords) && coords[j][0] == coords[i][0])
            ++j;
        FOR(k, i, j)
            if (coords[k][1] == 0)
                queries[coords[k][2]].k = counter;
            else
                a[coords[k][2]] = counter;

        ++counter;
        i = j;
    }

    fori(TREES)
        forj(N + Q)
            used[i][j] = (rng() & 1) != 0;

    fori(TREES)
        forj(n)
            if (used[i][a[j]])
                trees[i].update(j + 1, 1);

    for (auto& [t, l, r, k]: queries)
    {
        if (t == 2)
        {
            bool ok = (r - l + 1) % k == 0;
            for (int i = 0; i < TREES && ok; ++i)
                ok &= trees[i].sum(l, r) % k == 0;
            writeln(ok ? "YES" : "NO");
        }
        else
        {
            fori(TREES)
            {
                if (used[i][a[l - 1]])
                    trees[i].update(l, -1);
                if (used[i][k])
                    trees[i].update(l, 1);
            }
            a[l - 1] = k;
        }
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
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
