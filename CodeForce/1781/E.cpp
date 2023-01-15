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

struct rect
{
    int u, l, d, r, i;
    rect() {}
};

void run()
{
    ints(n);
    vector<rect> a(n);
    fori(n)
        readln(a[i].u, a[i].l, a[i].d, a[i].r),
        a[i].i = i;

    vector<int> u, d, b, ub, db;
    fori(n)
        if (a[i].u == a[i].d)
            (a[i].u == 1 ? u : d).pb(i);
        else
            b.pb(i);

    auto solve = [&](vector<int>& indices) {
        sort(all(indices), [&](const auto& i, const auto& j) {
            return tuple(a[i].l, a[i].r) < tuple(a[j].l, a[j].r);
        });
        int last = 0;
        int r = 0;
        for (int index: indices)
            if (a[index].l)
            {
                if (a[index].l > r)
                    r = a[index].r,
                    last = index;
                else if (a[index].r > r)
                    a[last].r = a[index].l - 1,
                    r = a[index].r,
                    last = index;
                else
                    a[index].l = 0;
            }
        for (int index: indices)
            if (a[index].l > a[index].r || a[index].l == 0)
                a[index].u = a[index].l = a[index].r = a[index].d = 0;
    };

    solve(u);
    solve(d);
    solve(b);
    fori(n)
        if (a[i].u == a[i].d)
            (a[i].u == 1 ? ub : db).pb(i);
        else
            ub.pb(i),
            db.pb(i);

    auto solve2 = [&](vector<int>& indices) {
        sort(all(indices), [&](const auto& i, const auto& j) {
            return tuple(a[i].l, a[i].r) < tuple(a[j].l, a[j].r);
        });
        int last = 0;
        int r = 0;
        for (int index: indices)
            if (a[index].l)
            {
                if (a[index].l > r)
                    r = a[index].r,
                    last = index;
                else if (a[index].r > r)
                {
                    if (a[index].d != a[index].u)
                        a[last].r = a[index].l - 1,
                        r = a[index].r,
                        last = index;
                    else
                        a[index].l = a[last].r + 1,
                        r = a[index].r,
                        last = index;

                }
                else
                {
                    if (a[index].d != a[index].u)
                        a[index].d = a[index].u = 3 - a[last].u;
                    else
                        a[index].l = 0;
                }
            }
        for (int index: indices)
            if (a[index].l > a[index].r || a[index].l == 0)
                a[index].u = a[index].l = a[index].r = a[index].d = 0;
    };
    solve2(ub);
    solve2(db);

    u.clear();
    d.clear();
    b.clear();
    fori(n)
        if (a[i].l)
        {
            if (a[i].u == a[i].d)
                (a[i].u == 1 ? u : d).pb(i);
            else
                b.pb(i);
        }
    solve(u);
    solve(d);
    solve(b);

    sort(all(a), [&](const auto& x, const auto& y) {
        return x.i < y.i;
    });
    ll s = 0;
    fori(n)
        if (a[i].d)
            s += (a[i].d - a[i].u + 1) * 1ll * (a[i].r - a[i].l + 1);
    writeln(s);
    fori(n)
        writeln(a[i].u, a[i].l, a[i].d, a[i].r);
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
