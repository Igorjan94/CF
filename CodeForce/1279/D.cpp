// Igorjan94, template version from 13 October 2017. C++17 version, modified 14 september 2019 (writeln<T>, main) {{{
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

#define    pb    push_back
#define whole(a) begin(a), end(a)
#define   next   next__
#define   prev   prev__
#define  count   count__

#define ints(a...)  int a; readln(a)
#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline

const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
vector<string>split(string&s,string d){vector<string>v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//modular
template<typename T = int, T mod = 1000000007>
struct modular
{
    T value;

    modular() : value(0) {}
    modular(const modular& other) : value(other.value) {}
    modular operator=(const modular& other) { value = other.value; return *this; }
    template<typename T1> modular operator=(const T1& other) { value = other % mod; if (value < 0) value += mod; return *this; }
    template<typename T1> modular(T1 const& other) { value = other % mod; if (value < 0) value += mod; }
    template<typename T1> modular(T1 const& num, T1 const& den) { *this = modular(den) ^ (mod - 2) * num; }
    template<typename T1> modular& operator^=(T1 const& deg) { modular a = value; for (T1 n = deg - 1; n > 0; n >>= 1) { if (n & 1) *this *= a; a *= a; } return *this; }
    template<typename T1> modular  operator^ (T1 const& deg) const { return modular(*this) ^= deg; }
    inline modular& operator+=(modular const& t)       { value += t.value; if (value > mod) value -= mod; return *this; }
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

    inline friend ostream& operator<<(ostream& os, modular const& m) { return os << m.value; }
    inline friend istream& operator>>(istream& is, modular& m) { return is >> m.value; m.value %= mod; if (m.value < 0) m.value += mod; }
};
//Igorjan
//}}}

static const int N = 1000001;
typedef modular<int, 998244353> mod;

void run()
{
    ints(n);
    vi a(N);
    vector<vector<int>> gifts(n);
    fori(n)
    {
        ints(k);
        gifts[i].resize(k);
        readln(gifts[i]);
        for (int& x: gifts[i])
            a[x]++;
    }
    mod ans;
    fori(n)
    {
        mod correct;
        for (int& x: gifts[i])
            correct += a[x];
        ans += correct / SZ(gifts[i]);
    }
    writeln(ans / n / n);
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
