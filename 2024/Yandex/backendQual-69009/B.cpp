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
//modular
template<typename T = int, T mod = 23>
struct modular
{
    T value;

    modular() : value(0) {}
    modular(const modular& other) : value(other.value) {}
    modular operator=(const modular& other) { value = other.value; return *this; }
    template<typename T1> modular operator=(const T1& other) { value = other % mod; if (value < 0) value += mod; return *this; }
    template<typename T1> modular(T1 const& other) { value = other % mod; if (value < 0) value += mod; }
    template<typename T1> modular(T1 const& num, T1 const& den) { *this = modular(den) ^ (mod - 2) * num; }
    template<typename T1> modular& operator^=(T1 const& deg) { modular a(*this); value = T(1); for (T1 n = deg; n > 0; n >>= 1) { if (n & 1) *this *= a; a *= a; } return *this; }
    template<typename T1> modular  operator^ (T1 const& deg) const { return modular(*this) ^= deg; }
    inline modular& operator+=(modular const& t)       { value += t.value; if (value >= mod) value -= mod; return *this; }
    inline modular& operator-=(modular const& t)       { value -= t.value; if (value < 0  ) value += mod; return *this; }
    inline modular& operator*=(modular const& t)       { value = (value * 1ll * t.value) % mod; return *this; }
    inline modular& operator/=(modular const& t)       { return *this *= ~t; }
    inline modular  operator+ (modular const& t) const { return modular(*this) += t; }
    inline modular  operator- (modular const& t) const { return modular(*this) -= t; }
    inline modular  operator* (modular const& t) const { return modular(*this) *= t; }
    inline modular  operator/ (modular const& t) const { return modular(*this) /= t; }
    inline modular  operator~ (                ) const { return modular(T(1), value); }
    inline bool     operator==(modular const& t) const { return value == t.value; }
    inline bool     operator!=(modular const& t) const { return value != t.value; }
    explicit operator T() const { return value; }

    inline friend ostream& operator<<(ostream& os, modular const& m) { return os << m.value; }
    inline friend istream& operator>>(istream& is, modular& m) { return is >> m.value; m.value %= mod; if (m.value < 0) m.value += mod; }
};

//}}}

void run()
{
    ints(n, m);
    vi x(m), B(m);
    readln(x, B);
    vector a(m, modular(0));
    vector b(m, modular(0));
    fori(m) a[i] = modular(x[i]);
    fori(m) b[i] = modular(B[i]);
    auto ans = [&](vector<modular<>> values) {
        string s;
        for (auto x: values)
            s.pb(x.value + 'a');
        fori(n - SZ(values)) s.pb('a');
        return writeln(s);
        forj(m)
        {
            auto temp = modular(0);
            fori(n)
                temp += modular(s[i] - 'a') * (a[j] ^ i);
            writeln(temp);
        }
    };
    auto solve = [&](auto b1, auto b2, auto x1, auto x2) -> pair<modular<>, modular<>> {
        auto w = (b1 - b2) / (x1 - x2);
        auto q = b1 - x1 * w;
        return {q, w};
    };
    if (m == 1) {
        return ans({b[0]});
    }
    else if (m == 2) {
        string s;
        if (b[0] == b[1])
            return ans({b[0]});
        auto [q, w] = solve(b[0], b[1], a[0], a[1]);
        return ans({q, w});
    } else if (m == 3) {
        if (b[0] == b[1] && b[1] == b[2] && a[0] == a[1] && a[1] == a[2])
            return ans({b[0]});
        if (b[0] == b[1] && a[0] == a[1]) {
            auto [q, w] = solve(b[1], b[2], a[1], a[2]);
            return ans({q, q, w});
        }
        if (b[0] == b[2] && a[0] == a[2]) {
            auto [q, w] = solve(b[0], b[1], a[0], a[1]);
            return ans({q, w, q});
        }
        if (b[1] == b[2] && a[1] == a[2]) {
            auto [q, w] = solve(b[0], b[1], a[0], a[1]);
            return ans({q, w, w});
        }
        auto c1 = a[0] * a[0];
        auto c2 = a[1] * a[1];
        auto c3 = a[2] * a[2];
        auto b2 = (b[1] - b[0]) / (x[1] - x[0]);
        auto b3 = (b[2] - b[0]) / (x[2] - x[0]);
        c2 = (c2 - c1) / (x[1] - x[0]);
        c3 = (c3 - c1) / (x[2] - x[0]);
        auto [q, w] = solve(b2, b3, c2, c3);
        auto e = b[0] - a[0] * q - c1 * w;
        return ans({e, q, w});
    }
    writeln("WTF");
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
