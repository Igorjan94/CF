// Igorjan94, template version from 13 October 2017. C++17 version, modified 07 August 2018 (&&, whole) {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(size(a))

typedef  pair<int, int>   pii;
typedef  valarray<int>    va;
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
const ll LLMAX = numeric_limits<ll>::max();

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string>v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}


//matrix
template<typename T>
struct matrix
{
    friend void swap(matrix& lhs, matrix& rhs)
    {
        swap(lhs.n, rhs.n);
        swap(lhs.m, rhs.m);
        swap(lhs.a, rhs.a);
    }

    matrix(int n, int m) : n(n), m(m)
    {
        a.resize(n, valarray(T(), m));
        fori(::min(n, m)) a[i][i] = T(1);
    }

    matrix(int n, int m, const T& initial) : n(n), m(m)
    {
        a.resize(n, valarray(initial, m));
    }

    matrix(const valarray<valarray<T>>& rhs)
    {
        n = size(rhs);
        m = n == 0 ? 0 : size(rhs[0]);
        a.resize(n, valarray(T(), m));
        fori(n) forj(m) a[i][j] = rhs[i][j];
    }
    
    matrix(const vector<T>& rhs)
    {
        n = size(rhs);
        m = 1;
        a.resize(n, valarray<T>(0, 1));
        fori(n) a[i] = rhs[i];
    }

    matrix(const valarray<T>& rhs)
    {
        n = size(rhs);
        m = 1;
        a.resize(n, valarray<T>(0, 1));
        fori(n) a[i] = rhs[i];
    }

    matrix(const matrix<T>& rhs) : n(rhs.n), m(rhs.m), a(rhs.a) {}

    matrix& operator=(const matrix& rhs)
    {
        if (&rhs == this)
            return *this;
        matrix temp(rhs);
        swap(*this, temp);
        return *this;
    }

    matrix& operator=(const T& rhs)
    {
        matrix temp(n, m, rhs);
        swap(*this, temp);
        return *this;
    }

    matrix& operator=(const valarray<T>& rhs)
    {
        matrix temp(size(rhs), 1, 0);
        fori(temp.n) a[i][0] = rhs[i];
        swap(*this, temp);
        return *this;
    }

    valarray<T>& operator[](int i) { return a[i]; }
    const valarray<T>& operator[](int i) const { return a[i]; }

    matrix& operator+=(const matrix& rhs) { a += rhs.a; return *this; }
    matrix& operator-=(const matrix& rhs) { a -= rhs.a; return *this; }
    matrix& operator+=(const T& rhs) { fori(n) a[i] += rhs; return *this; }
    matrix& operator-=(const T& rhs) { fori(n) a[i] -= rhs; return *this; }
    matrix& operator*=(const T& rhs) { fori(n) a[i] *= rhs; return *this; }
    matrix& operator/=(const T& rhs) { fori(n) a[i] /= rhs; return *this; }
    matrix& operator%=(const T& rhs) { fori(n) a[i] %= rhs; return *this; }
    matrix& operator*=(const matrix& rhs) {
        assert(m == rhs.n);
        matrix temp(n, rhs.m, 0);
        fori(n) forj(m) forn(k, rhs.m) temp.a[i][k] += a[i][j] * rhs[j][k];
        return *this = temp;
    }

    matrix& operator|=(const matrix& rhs) {
        assert(n == rhs.n);
        matrix temp(n, m + rhs.m, 0);
        fori(n) forj(m) temp[i][j] = a[i][j];
        fori(n) forj(rhs.m) temp[i][j + m] = rhs[i][j];
        return *this = temp;
    }

    matrix& operator^=(ll i) {
        assert(i >= 0);
        if (i == 0) return *this = matrix(n, m);
        return *this = binpow(*this, std::abs(i));
    }
    template<typename T1>
    valarray<T> operator*(const valarray<T1>& rhs) {
        assert(m == size(rhs));
        valarray<T1> ans(n);
        fori(n) forn(k, m) ans[i] += a[i][k] * rhs[k];
        return ans;
    }
    template<typename T1>
    friend valarray<T1> operator*(const valarray<T1>& lhs, const matrix& rhs) {
        assert(size(lhs) == rhs.n);
        valarray<T1> ans = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
        forj(rhs.m) forn(k, rhs.n) ans[j] += lhs[k] * rhs[k][j];
        return ans;
    }
    matrix operator-() { return *this *= -1; }

    friend matrix operator+(matrix lhs, const matrix& rhs) { lhs += rhs; return lhs; }
    friend matrix operator-(matrix lhs, const matrix& rhs) { lhs += rhs; return lhs; }
    friend matrix operator*(matrix lhs, const matrix& rhs) { lhs *= rhs; return lhs; }
    friend matrix operator|(matrix lhs, const matrix& rhs) { lhs |= rhs; return lhs; }
    friend matrix operator+(matrix lhs, const T& rhs) { lhs += rhs; return lhs; }
    friend matrix operator-(matrix lhs, const T& rhs) { lhs -= rhs; return lhs; }
    friend matrix operator*(matrix lhs, const T& rhs) { lhs *= rhs; return lhs; }
    friend matrix operator/(matrix lhs, const T& rhs) { lhs /= rhs; return lhs; }
    friend matrix operator%(matrix lhs, const T& rhs) { lhs %= rhs; return lhs; }
    friend matrix operator^(matrix lhs, const ll& rhs) { lhs ^= rhs; return lhs; }
    matrix operator|=(const valarray<T>& rhs) { return *this |= matrix(rhs); }
    T max() { return a.max(); }
    T min() { return a.min(); }
    T sum() { return a.sum(); }

    matrix transpose() {
        matrix temp(m, n, 0);
        fori(n) forj(m) temp[i][j] = a[j][i];
        return temp;
    }

    T normalize(int index) {
        T g = 1;
        bool found = false;
        for (T& x: a[index])
            if (x != 0)
            {
                if (not found) g = x, found = true;
                else g = gcd(g, x);
            }
        a[index] /= g;
        return g;
    }

    void normalize() {
        fori(n) normalize(i);
    }

    T determinant() {
        matrix temp(*this);
        T numerator = 1;
        T denumerator = 1;
        fori(n)
        {
            int nonZero = i;
            while (nonZero < n && !temp[nonZero][i]) ++nonZero;
            if (nonZero == n) return 0;

            swap(temp[i], temp[nonZero]);
            numerator *= temp[i][i];

            FOR(j, i + 1, n)
                if (temp[j][i])
                {
                    T g = gcd(temp[i][i], temp[j][i]);
                    denumerator *= temp[i][i] / g;
                    temp[j] = temp[j] * (temp[i][i] / g) - temp[i] * (temp[j][i] / g);
                }
        }
        writeln(temp); writeln();
        return numerator / denumerator;
    }

    optional<pair<T, matrix<T>>> invert() {
        assert(n == m);
        matrix temp(*this);
        temp |= matrix(n, n);

        auto det = solve(temp);
        if (!det.has_value()) return {};

        matrix ret(n, n, 0);
        auto s = slice(n, n, 1);
        fori(n) ret[i] = temp[i][s];
        return pair(det.value(), ret);
    }

    optional<pair<T, valarray<T>>> solution(const valarray<T>& b) {
        assert(n == m);
        matrix temp(*this);
        temp |= b;

        auto det = solve(temp);
        if (!det.has_value()) return {};

        valarray<T> ret(0, n);
        fori(n) ret[i] = temp[i][n];
        return pair(det.value(), ret);
    }

    friend ostream& operator<<(ostream& os, matrix rhs) {
        fori(rhs.n)
        {
            os << rhs.a[i];
            if (i != rhs.n - 1) os << "\n";
        }
        return os;
    }
    friend istream& operator>>(istream& is, matrix& rhs) {
        fori(rhs.n) is >> rhs.a[i];
        return is;
    }

private:
    valarray<valarray<T>> a;
    int n, m;

    static optional<T> solve(matrix& temp) {
        vector<int> permutation(temp.n);
        iota(whole(permutation), 0);

        auto get = [&](int i, int j) {
            return temp[permutation[i]][j];
        };
        auto findNonZero = [&](int i) {
            int nonZero = i;
            while (nonZero < temp.n && !get(nonZero, i)) ++nonZero;
            return nonZero;
        };
        fori(temp.n)
        {
            int nonZero = findNonZero(i);
            if (nonZero == temp.n) return {};
            swap(permutation[i], permutation[nonZero]);
            FOR(j, i + 1, temp.n)
                if (get(j, i))
                    temp[permutation[j]] = temp[permutation[j]] * get(i, i) - temp[permutation[i]] * get(j, i),
                    temp.normalize(permutation[j]);
        }
        ROF(i, temp.n - 1, 0)
            ROF(j, i - 1, 0)
                if (get(j, i))
                    temp[permutation[j]] = temp[permutation[j]] * get(i, i) - temp[permutation[i]] * get(j, i),
                    temp.normalize(permutation[j]);
        fori(temp.n) temp.normalize(i);
        T mx = 0;
        fori(temp.n) mx = std::max(mx, abs(get(i, i)));
        fori(temp.n) temp[permutation[i]] *= mx / get(i, i);
        matrix ret(temp.n, temp.m, 0);
        fori(temp.n) ret[i] = temp[permutation[i]];
        temp = ret;
        return mx;
    }
};

//binpowmod
template<typename T>
T binpowmod(T a, ll n, T mod)
{
    assert(n > 0);
    T res = a; --n;
    while (n > 0)
    {
        if (n & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return res;
}
//binpow

template<typename T>
T binpow(T a, ll n)
{
    assert(n > 0);
    T res = a; --n;
    while (n > 0)
    {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

//modular
template<typename T = int, T mod = 1000000007>
struct modular
{
    T value = 0;

    modular(){}
    modular(const modular& other) : value(other.value) {}
    modular operator=(const modular& other) { value = other.value; return *this; }
    template<typename T1> modular operator=(const T1& other) { value = other % mod; if (value < 0) value += mod; return *this; }
    template<typename T1> modular(T1 const& t) { value = t % mod; if (value < 0) value += mod; }
    template<typename T1> modular(T1 const& num, T1 const& den) { value = num * 1ll * binpowmod<ll>(den, mod - 2, mod) % mod; }
    template<typename T1> modular& operator^=(T1 const& deg) { value = binpowmod<ll>(value, deg, mod); return *this; }
    template<typename T1> modular  operator^ (T1 const& deg) const { return modular(*this) ^= deg; }
    inline modular& operator+=(modular const& t)       { value += t.value; if (value > mod) value -= mod; return *this; }
    inline modular& operator-=(modular const& t)       { value -= t.value; if (value < 0  ) value += mod; return *this; }
    inline modular& operator*=(modular const& t)       { value = (value * 1ll * t.value) % mod; return *this; }
    inline modular  operator+ (modular const& t) const { return modular(*this) += t; }
    inline modular  operator- (modular const& t) const { return modular(*this) -= t; }
    inline modular  operator* (modular const& t) const { return modular(*this) *= t; }

    inline friend ostream& operator<<(ostream& os, modular const& m) { return os << m.value; }
    inline friend istream& operator>>(istream& is, modular& m) { return is >> m.value; m.value %= mod; }
};

//Igorjan
//}}}

typedef modular<int, MOD - 1> modDeg;
typedef modular<int, MOD> modAns;
void run()
{
    valarray<valarray<modDeg>> coeffs = {
        {1, 0, 0, 0, 0},
        {0, 4, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1}
    };
    valarray<valarray<modDeg>> mm = {
        {1, 1, 0, 0, -6},
        {0, 1, 0, 0, 2},
        {0, 0, 0, 0, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1}
    };
    matrix<modDeg> m = mm;

    ll d;
    valarray<modAns> v(3);
    modAns c;
    readln(d, v, c);
    valarray<modDeg> x = (coeffs * (m ^ (d - 3)))[4];
    modAns ans = c ^ (x[0] + x[1]).value;
    fori(3)
        ans *= v[i] ^ x[i + 2].value;
    writeln(ans);
}

//{{{
int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
#ifndef ONLINE_JUDGE
    writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
#endif
    return 0;
}

#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>const&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>const&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>const&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
