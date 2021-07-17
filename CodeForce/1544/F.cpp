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
//modular
template<typename T = int, T mod = 31607>
struct modular
{
    T value;

    modular() : value(0) {}
    modular(const modular& other) : value(other.value) {}
    modular operator=(const modular& other) { value = other.value; return *this; }
    template<typename T1> modular operator=(const T1& other) { value = other % mod; if (value < 0) value += mod; return *this; }
    template<typename T1> modular(T1 const& other) { value = other % mod; if (value < 0) value += mod; }
    template<typename T1> modular(T1 const& num, T1 const& den) { *this = modular(den) ^ (mod - 2) * num; }
    template<typename T1> modular& operator^=(T1 const& deg) { modular a(*this); for (T1 n = deg - 1; n > 0; n >>= 1) { if (n & 1) *this *= a; a *= a; } return *this; }
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
    ints(n);
    vector<vector<modular<>>> a(n, vector<modular<>>(n));
    readln(a);
    //modular X = 1;
    fori(n)
        forj(n)
            a[i][j] /= 10000;
    //vector<modular<>> p(n + 1, 1);
    //vector<modular<>> q(n + 1, 1);
    //fori(n)
    //{
        //p[0] *= a[i][i];
        //q[0] *= a[i][n - i - 1];
        //forj(n)
            //p[i + 1] *= a[i][j],
            //q[j + 1] *= a[i][j];
    //}
    //modular fastP;
    //modular fastQ;
    //modular d1 = p[0];
    //modular d2 = q[0];
    //FOR(mask, 1, 1 << (n))
    //{
        //int bits = __builtin_popcount(mask);
        //int sign = bits % 2 == 0 ? -1 : 1;
        //modular tempP = 1;
        //modular tempQ = 1;
        //fori(n)
            //if ((1 << i) & mask)
                //tempP *= p[i + 1],
                //tempQ *= q[i + 1];
        //fastP += tempP * sign;
        //fastQ += tempQ * sign;
    //}
    //vector<modular<>> pp = {fastP, fastQ, d1, d2};
    //int m = pp.size();
    //modular fast;
    //FOR(mask, 1, 1 << m)
    //{
        //int bits = __builtin_popcount(mask);
        //int sign = bits % 2 == 0 ? -1 : 1;
        //modular temp = 1;
        //fori(m)
            //if ((1 << i) & mask)
                //temp *= pp[i];
        //fast += temp * sign;
    //}

    modular ans;
    int eee = 0;
    FOR(mask, 0, 1 << (n * n))
    {
        vector<vector<int>> b(n, vector<int>(n));
        fori(n)
            forj(n)
                if (mask & (1 << (i * n + j)))
                    b[i][j] = 1;
        bool ok = false;
        fori(n)
        {
            int cnt = 0;
            forj(n)
                cnt += b[i][j];
            ok |= cnt == n;
        }
        forj(n)
        {
            int cnt = 0;
            fori(n)
                cnt += b[i][j];
            ok |= cnt == n;
        }
        int cnt = 0;
        fori(n)
            cnt += b[i][i];
        ok |= cnt == n;
        cnt = 0;
        fori(n)
            cnt += b[i][n - i - 1];
        ok |= cnt == n;
        if (ok) {
            eee++;
            modular temp = 1;
            fori(n)
                forj(n)
                    if (b[i][j])
                        temp *= a[i][j];
                    else
                        temp *= (modular(1) - a[i][j]);
            ans += temp;
        }
    }
    writeln(ans);
    //writeln(fast, fastP, fastQ, p[0], p[1], modular(7) / 16, X, modular(1) / 16);
    //writeln(fastP + fastQ - fastP * fastQ + X * X);
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
