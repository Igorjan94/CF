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

struct Update {
    int u = 0;

    Update() {}

    Update(int u) : u(u) {}

    void operator+=(const Update& b) {
        u ^= b.u;
    };

    bool empty() const {
        return u == 0;
    }

    void reset() {
        u = 0;
    }
};

struct R 
{
    int l;
    int r;
    int pl = 0;
    int pr = 0;

    R() : l(0), r(0) {}
    R(int l, int pl) : l(l), r(MOD - l), pl(pl), pr(pl) {}
    R operator+(const R& b) const {
        R ret;
        if (l >= b.l)
            ret.l = l,
            ret.pl = pl;
        else
            ret.l = b.l,
            ret.pl = b.pl;
        if (r >= b.r)
            ret.r = r,
            ret.pr = pr;
        else
            ret.r = b.r,
            ret.pr = b.pr;
        return ret;
    }

    void operator+=(const Update& update) {
        swap(l, r);
        swap(pl, pr);
    }
};

//Igorjan
//segmentTree
//0-indexed, [l..r]
template<typename V, typename T, typename U>
struct segmentTree
{
    int n;
    vector<T> t;
    vector<U> add;
 
    void push(int v, int tl, int tr)
    {
        if (add[v].empty()) return;
        
        t[v] += add[v];
        if (tl != tr)
            add[v * 2] += add[v],
            add[v * 2 + 1] += add[v];
        add[v].reset();
    }

    void build(const vector<V>& a, int v, int l, int r)
    {
        if (l == r)
            t[v] = T(a[l], l);
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            t[v] = t[v * 2] + t[v * 2 + 1];
        }
    };
 
    segmentTree(const vector<V>& a)
    {
        n = a.size();
        t.resize(n * 4 + 10);
        add.resize(n * 4 + 10);
        build(a, 1, 0, n - 1);
    }
 
    void update(int l, int r, U value)
    {
        update(1, 0, n - 1, l, r, value);
    }
 
    void update(int v, int tl, int tr, int l, int r, U value) 
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
            t[v] = t[v * 2] + t[v * 2 + 1];
        }
    }

    T get(int l, int r)
    {
        return get(1, 0, n - 1, l, r);
    }

    T get(int v, int tl, int tr, int l, int r) 
    {
        push(v, tl, tr);
        if (l > r) return T();

        if (tl == l && tr == r)
            return t[v];
        else 
        {
            int tm = (tl + tr) / 2;
            T left = get(v * 2, tl, tm, l, min(r, tm));
            T right = get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
            return left + right;
        }
    }

};

//}}}

void run()
{
    ints(n);
    vector<int> a(n);
    readln(a);
    segmentTree<int, R, Update> s(a);
    ll ans = 0;
    ints(q);
    forn(Q, q)
    {
        ints(l, r); --l; --r;
        s.update(l, r, 1);
        auto ret = s.get(0, n - 1);
        ans += ret.pl + 1;
    }
    writeln(ans);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ints(t); fori(t) cout << "Case #" << (i + 1) << ": ", run();
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
