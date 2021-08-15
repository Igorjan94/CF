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
//linearSieve
struct linearSieve
{
    vector<int> primes;
    vector<int> mobius;
    vector<int> minPrime, prev;

    linearSieve(int N)
    {
        minPrime.resize(N, 0);
        prev.resize(N, 0);
        mobius.resize(N, 0);
        mobius[1] = 1;
        for (int i = 2; i < N; i++)
        {
            if (minPrime[i] == 0)
                mobius[i] = -1,
                primes.push_back(i),
                minPrime[i] = i;
            for (int prime : primes)
            {
                int temp = prime * i;
                if (temp < N && prime <= minPrime[i])
                    minPrime[temp] = prime,
                    mobius[temp] = minPrime[i] == prime ? 0 : -mobius[i],
                    prev[temp] = i;
                else
                    break;
            }
        }
    }

    vector<pair<int, int>> foldedFactorization(int x)
    {
        vector<pair<int, int>> temp;
        int p = -1;
        int pp = -1;
        while (x > 1)
        {
            pp = p;
            p = minPrime[x];
            if (p != pp)
                temp.pb({p, 1});
            else
                temp.back().second++;
            x = prev[x];
        }
        return temp;
    }

    vector<int> divisors(int x, bool nonTrivial = true)
    {
        vector<int> ans;

        const vector<pair<int, int>>& fold = foldedFactorization(x);
        function<void(int, int)> gen = [&](int v, int j) {
            if (j == int(fold.size()))
            {
                if (!nonTrivial || (v != 1 && v != x))
                    ans.pb(v);
                return;
            }
            gen(v, j + 1);
            fori(fold[j].second)
                gen(v *= fold[j].first, j + 1);
        };
        gen(1, 0);

        return ans;
    }

    vector<int> sortedDivisors(int x, bool nonTrivial = true)
    {
        vector<int> ans = divisors(x, nonTrivial);
        sort(ans.begin(), ans.end());
        return ans;
    }

    vector<int> factorization(int x)
    {
        vector<int> temp;
        while (x > 1)
            temp.push_back(minPrime[x]),
            x = prev[x];
        return temp;
    }

    bool isPrime(int x)
    {
        return minPrime[x] == x;
    }
};

//modular
template<typename T = int, T mod = 998244353>
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
    ints(n, M);
    vector<pii> a(n);
    readln(a);
    auto get = [&](vector<pii>& a, int d) 
    {
        int m = M / d;
        vector<int> b(n);
        fori(n)
        {
            int l = (a[i].first + d - 1) / d;
            int r = a[i].second / d;
            if (l > r || l == 0) return modular(0);
            b[i] = r - l;
            m -= l;
        }
        if (m < 0) return modular(0);
        vector<modular<>> ways(m + 1);
        ways[0] = 1;

        for (int r: b)
        {
            vector<modular<>> p(m + 2);
            vector<modular<>> nw(m + 1, 0);
            partial_sum(all(ways), p.begin() + 1);
            forj(m + 1)
                nw[j] = p[j + 1] - p[max(0, j - r)];
            ways = nw;
        }

        return accumulate(all(ways), modular(0));
    };
    modular ans = 0;
    auto prime = linearSieve(M + 10);
    forj1(M + 1)
        if (prime.mobius[j] != 0)
            ans += get(a, j) * prime.mobius[j];
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
