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
//segmentTree
//0-indexed, [l..r]
template<typename T>
struct segmentTree
{
    int n;
    vector<T> t;

    void build(vector<T>& a, int v, int l, int r)
    {
        if (l == r)
            t[v] = a[l];
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            t[v] = (t[v * 2] + t[v * 2 + 1]);
        }
    };

    segmentTree(vector<T>& a)
    {
        n = a.size();
        t.resize(n * 4);
        build(a, 1, 0, n - 1);
    }

    T get(int l, int r)
    {
        return get(1, 0, n - 1, l, r);
    }

    T get(int v, int tl, int tr, int l, int r) 
    {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return (get(v * 2, tl, tm, l, min(r, tm)) + get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    void update(int position, T value)
    {
        update(1, 0, n - 1, position, value);
    }

    void update(int v, int tl, int tr, int position, T value) 
    {
        if (tl == tr)
            t[v] = value;
        else 
        {
            int tm = (tl + tr) / 2;
            if (position <= tm)
                update(v * 2, tl, tm, position, value);
            else
                update(v * 2 + 1, tm + 1, tr, position, value);
            t[v] = (t[v * 2] + t[v * 2 + 1]);
        }
    }
};

//}}}

void run()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ints(n);
    vector<ll> a((n + 1) / 2);
    readln(a);
    ints(x);
    fori(n / 2)
        a.pb(x);
    segmentTree f(a);
    vector<int> indices(n);
    iota(all(indices), 1);
    shuffle(all(indices), rng);
    indices.pb(n);
    FOR(i, -2, 3)
        if (n / 2 + i >= 1 && n / 2 + i <= n)
            indices.pb(n / 2 + i);
    reverse(all(indices));
    for (int k: indices)
    {
        bool ok = true;
        for (int i = 0; i < n && ok; ++i)
            if (int left = n - indices[i]; left < n - k + 1)
                ok &= f.get(left, left + k - 1) > 0;
        if (ok)
            return writeln(k);
    }
    writeln(-1);
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
