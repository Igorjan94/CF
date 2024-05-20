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
    ints(b, a, n, m);
    vector<pii> f(n);
    readln(f);
    for (auto& [x, y]: f) swap(x, y);
    auto xl = [](pii a, pii b) { return tuple(a.first, a.second)  < tuple(b.first, b.second);  };
    auto xr = [](pii a, pii b) { return tuple(a.first, a.second)  > tuple(b.first, b.second);  };
    auto yl = [](pii a, pii b) { return tuple(a.second, a.first) < tuple(b.second, b.first); };
    auto yr = [](pii a, pii b) { return tuple(a.second, a.first) > tuple(b.second, b.first); };
    std::set<pii, decltype(xl)> l;
    std::set<pii, decltype(xr)> r;
    std::set<pii, decltype(yl)> d;
    std::set<pii, decltype(yr)> u;
    for (auto p: f)
        l.insert(p),
        r.insert(p),
        u.insert(p),
        d.insert(p);

    int left = 0;
    int right = a + 1;
    int down = 0;
    int up = b + 1;
    int alice = 0;
    int bob = 0;
    forn(q, m)
    {
        char c;
        int k;
        readln(c, k);
        int cur = 0;
        auto erase = [&](auto p) {
            l.erase(p);
            r.erase(p);
            d.erase(p);
            u.erase(p);
        };
        if (c == 'L') {
            left += k;
            while (l.size() && l.begin()->first <= left)
                ++cur, erase(*l.begin());
        } else if (c == 'R') {
            right -= k;
            while (r.size() && r.begin()->first >= right)
                ++cur, erase(*r.begin());
        } else if (c == 'D') {
            up -= k;
            while (u.size() && u.begin()->second >= up)
                ++cur, erase(*u.begin());
        } else {
            down += k;
            while (d.size() && d.begin()->second <= down)
                ++cur, erase(*d.begin());
        }
        (q % 2 == 0 ? alice : bob) += cur;
    }
    writeln(alice, bob);
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
