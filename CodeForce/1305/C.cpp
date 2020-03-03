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

//Igorjan
//modularR
template<typename T = int>
struct modularR
{
    T value;
    T mod;

    modularR() : value(0) {}
    modularR(T value, T mod) : value(value), mod(mod) {}
    modularR(const modularR& other) : value(other.value), mod(other.mod) {}
    modularR operator=(const modularR& other) { value = other.value; mod = other.mod; return *this; }
    template<typename T1> modularR operator=(const T1& other) { assert(mod); value = other % mod; if (value < 0) value += mod; return *this; }
    template<typename T1> modularR(T1 const& other, T1 const& mod) { this->mod = mod; value = other % mod; if (value < 0) value += mod; }
    template<typename T1> modularR(T1 const& num, T1 const& den, T1 const& mod) { *this = modularR(den, mod) ^ (mod - 2) * num; }
    template<typename T1> modularR& operator^=(T1 const& deg) { modularR a(*this); for (T1 n = deg - 1; n > 0; n >>= 1) { if (n & 1) *this *= a; a *= a; } return *this; }
    template<typename T1> modularR  operator^ (T1 const& deg) const { return modularR(*this) ^= deg; }
    template<typename T1> inline modularR& operator+=(T1 const& t)       { value += t; if (value > mod) value -= mod; return *this; }
    template<typename T1> inline modularR& operator-=(T1 const& t)       { value -= t; if (value < 0  ) value += mod; return *this; }
    template<typename T1> inline modularR& operator*=(T1 const& t)       { value = (value * 1ll * t) % mod; return *this; }
    template<typename T1> inline modularR& operator/=(T1 const& t)       { return *this *= ~modularR(t, mod); }
    template<typename T1> inline modularR  operator+ (T1 const& t) const { return modularR(*this) += t; }
    template<typename T1> inline modularR  operator- (T1 const& t) const { return modularR(*this) -= t; }
    template<typename T1> inline modularR  operator* (T1 const& t) const { return modularR(*this) *= t; }
    template<typename T1> inline modularR  operator/ (T1 const& t) const { return modularR(*this) /= t; }
    inline modularR  operator~ (                ) const { return modularR(T(1), value, mod); }
    inline bool     operator==(modularR const& t) const { return value == t.value; }
    inline bool     operator!=(modularR const& t) const { return value != t.value; }
    operator T() const { return value; }

    inline friend ostream& operator<<(ostream& os, modularR const& m) { return os << m.value; }
    inline friend istream& operator>>(istream& is, modularR& m) { return is >> m.value >> m.mod; m.value %= m.mod; if (m.value < 0) m.value += m.mod; }
};

//}}}

void run()
{
    ints(n, m);
    vi a(n);
    readln(a);
    sort(whole(a));
    if (n > 2000)
        return writeln(0);
    modularR<int> ans(1, m);
    fori(n)
        FOR(j, i + 1, n)
            ans *= modularR<int>(a[j] - a[i], m);
    writeln(ans);
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
