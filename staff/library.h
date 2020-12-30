//Igorjan94, template version from 10 March 2015
#ifndef IGORJAN94
#define IGORJAN94 1

//IgorjanIncludes
#include <bits/stdc++.h>
using namespace std;

/*
#undef _GLIBCXX_HAVE_ICONV
#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds; 
*/ //typedef tree<int, int/*null_type*/, less<int>, rb_tree_tag, tree_order_statistics_node_update> orderedMap;

//IgorjanDefines
#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn1(i, n)  for (int i = 1; i < (int) (n); ++i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(size(a))

#define     fst      first
#define     snd      second
#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define      eb      emplace_back
#define      vs      vector<string>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     vvi      vector<vector<int>>
#define     pll      pair<long long, long long>
#define   rall(a)    a.rbegin(), a.rend()
#define   all(a)     a.begin(), a.end()
#define    next      next__
#define    prev      prev__
#define   union      union__

#define argmax(a)    (max_element(whole(a)) - (a).begin())
#define argmin(a)    (min_element(whole(a)) - (a).begin())

#define FILENAME "input"
#define INF 1000000007

#define    ints(args...)     int args; readln(args)
#define     lls(args...)      ll args; readln(args)
#define   vints(args...)      vi args; readln(args)
#define strings(args...)  string args; readln(args)

//IgorjanprintTuple
template<class Tuple, size_t... Is> ostream& print_tuple(ostream& os, const Tuple& t, index_sequence<Is...>) { ((os << (Is == 0 ? "" : " ") << get<Is>(t)), ...); return os; }
template<class Tuple, size_t... Is> istream& read_tuple(istream& is, Tuple& t, index_sequence<Is...>) { ((is >> get<Is>(t)), ...); return is; }
template<class... Args> inline ostream& operator<<(ostream& os, const tuple<Args...>& t) { return print_tuple(os, t, index_sequence_for<Args...>{}); }
template<class... Args> inline istream& operator>>(istream& is, tuple<Args...>& t) { return read_tuple(is, t, index_sequence_for<Args...>{}); }

//Igorjanprinter
#define ttt12i template<class T1, class T2> inline
#define  ttti  template<class T> inline
#define  ttta  template<class... Args> inline

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;}

//Igorjandebug
#ifndef ONLINE_JUDGE
#define wr(args...)  err(#args, args)
#define _GLIBCXX_DEBUG
vector<string>split(string&s,string_view d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}
#else
#define wr(args...) 42
#endif

//IgorjanbinSearch
//x \in [l, r]-> min, f(x) == true
template<typename T, typename F>
T binSearch(T l, T r, F f, T eps = 1)
{
    T m;
    while (abs(r - l) > eps)
        m = l + (r - l) / 2,
        (f(m) ? r : l) = m;
    return f(l) ? l : r;
}

//IgorjanternarySearch
//x \in [l, r]: f(x) -> min
template<typename T, typename F>
auto ternarySearch(T l, T r, F f) -> decltype(f(l))
{
    T m;
    while (r - l > 4)
    {
        m = l + (r - l) / 2;
        if (f(m) < f(m + 1))
            r = m + 1;
        else
            l = m;
    }
    auto ans = f(l);
    for (int i = l + 1; i <= r; ++i)
        ans = min(ans, f(i));
    return ans;
}

//Igorjandsu
struct dsu
{
    vector<int> a, size;

    dsu(int n)
    {
        a.resize(n);
        size.resize(n, 1);
        iota(a.begin(), a.end(), 0);
    }

    int get(int i)
    {
        return a[i] == i ? i : a[i] = get(a[i]);
    }

    int operator[](int i)
    {
        return get(i);
    }

    void uni(int i, int j)
    {
        i = get(i);
        j = get(j);
        if (i == j) return;
        if (size[i] > size[j])
            swap(i, j);
        a[i] = j;
        size[j] += size[i];
    }
};

//Igorjansieve
vector<bool> sieve(int n)
{
    vector<bool> x(n, true);
    x[0] = x[1] = false;
    for (int i = 2; i < n; i++)
        if (x[i])
            for (int j = i * 2; j < n; j += i)
                x[j] = false;
    return x;
}

//IgorjanlinearSieve
struct linearSieve
{
    vector<int> primes;
    vector<int> minPrime, prev;

    linearSieve(int N)
    {
        minPrime.resize(N, 0);
        prev.resize(N, 0);
        for (int i = 2; i < N; i++)
        {
            if (minPrime[i] == 0)
                primes.push_back(i),
                minPrime[i] = i;
            for (int prime : primes)
            {
                int temp = prime * i;
                if (temp < N && prime <= minPrime[i])
                    minPrime[temp] = prime,
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

//IgorjanfenwickTree
//1-indexed, [l, r]
template <typename T>
struct fenwickTree
{
    vector<T> t;
    int n;

    fenwickTree(int size, T value = 0)
    {
        n = size;
        t.resize(n + 1, value);
    }

    fenwickTree(vector<T>& arr)
    {
        n = arr.size();
        t.resize(n + 1, 0);
        fori(n)
            update(i + 1, arr[i]);
    }

    void update(int index, T value)
    {
        for (; index <= n; index += index & -index)
            t[index] += value;
    }

    T sum(int i)
    {
        T res = 0;
        for (; i; i -= i & -i)
            res += t[i];
        return res;
    }

    T sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    T sum0(int l, int r)
    {
        return sum(r + 1) - sum(l);
    }
};

//IgorjansegmentTree
//0-indexed, [l..r]
template<typename T>
struct segmentTree
{
    int n;
    vector<T> t;
    typedef function<T (T, T)> F;
    F f;
    T NEITRAL_ELEMENT;

    void build(vector<T>& a, int v, int l, int r)
    {
        if (l == r)
            t[v] = a[l];
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            t[v] = f(t[v * 2], t[v * 2 + 1]);
        }
    };

    segmentTree(vector<T>& a, F g, T ne = 0)
    {
        n = a.size();
        t.resize(n * 4);
        f = g;
        if (ne != 0)
            NEITRAL_ELEMENT = ne;
        else
            if (f(2, 4) == 6)
                NEITRAL_ELEMENT = 0;
            else
                if (f(-2, 10) == -2)
                    NEITRAL_ELEMENT = numeric_limits<T>::max();
        build(a, 1, 0, n - 1);
    }

    T get(int l, int r)
    {
        return get(1, 0, n - 1, l, r);
    }

    T get(int v, int tl, int tr, int l, int r) 
    {
        if (l > r)
            return NEITRAL_ELEMENT;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return f(get(v * 2, tl, tm, l, min(r, tm)), get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
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
            t[v] = f(t[v * 2], t[v * 2 + 1]);
        }
    }
};

//IgorjansparseTable
//0-indexed, [l, r)
template<typename T>
struct sparseTable
{
    int n;
    vector<vector<T>> st;
    vector<int> logs;
    typedef function<T (T, T)> F;
    F f;

    sparseTable(vector<T>& a, F g)
    {
        n = a.size();
        f = g;

        logs.push_back(0);
        logs.push_back(0);
        FOR(i, 2, n + 1) logs.push_back(logs[i / 2] + 1);
        int L = logs.back() + 1;
        st.resize(L, vector<T>(n));
        fori(n)
            st[0][i] = a[i];
        FOR(k, 1, L)
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = f(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }

    T get(int l, int r)
    {
        int len = logs[r - l];
        return f(st[len][l], st[len][r - (1 << len)]);
    }
};

//Igorjandijkstra
template<typename T>
vector<T> dijkstra(const vector<vector<pair<int, T>>> g, const int start)
{
    int n = SZ(g);
    vector<T> d(n, numeric_limits<T>::max());
    priority_queue<pair<T, int>> q;

    q.push({d[start] = 0, start});
    while (!q.empty())
    {
        auto [curd, u] = q.top();
        q.pop();
        if (-curd > d[u])
            continue;
        for (const auto& [v, w]: g[u])
            if (T temp = d[u] + w; d[v] > temp)
                d[v] = temp,
                q.push({-d[v], v});
    }
    return d;
}

//Igorjanbfs
template<typename T>
vector<T> bfs(const vector<vector<T>>& g, int start)
{
    int n = SZ(g);
    vector<T> d(n, numeric_limits<T>::max());
    vector<bool> used(n, false);
    d[start] = T(0);
    used[start] = true;
    queue<int> q;
    q.push(start);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int& v: g[u])
            if (!used[v])
                q.push(v),
                d[v] = d[u] + 1,
                used[v] = true;
    }
    return d;
}

//Igorjanbinpow
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

//Igorjanbinpowmod
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

//Igorjanfft
typedef complex<double> base;
 
void fft(vector<base>& a, bool invert)
{
    int n = a.size();
    if (n == 1)
        return;
    vector<base> a0, a1;
    fori(n)
        (i % 2 ? a1 : a0).pb(a[i]);
    fft(a0, invert);
    fft(a1, invert);
    n /= 2;

    double ang = M_PI / n * (invert ? -1 : 1);
    base w(1);
    base wn(cos(ang), sin(ang));
    fori(n)
    {
        a[i + 0] = a0[i] + w * a1[i];
        a[i + n] = a0[i] - w * a1[i];
        if (invert)
            a[i + 0] /= 2,
            a[i + n] /= 2;
        w *= wn;
    }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b)
{
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    vector<int> res;
    size_t n = 1;
    while (n < max(a.size(), b.size())) 
        n <<= 1;
    n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    fori(n)
        fa[i] *= fb[i];
    fft(fa, true);
    fori(n)
        res.pb(int(fa[i].real() + 0.5));
    return res;
}

//Igorjanpoint
#define pointtt template<typename T = int>
//sorts only if z is corner point;
#define sortByPolarAngle(v, z, T) sort(v.begin(), v.end(), [&z](point<T>& a, point<T>& b) {\
    int q = orientation(z, a, b); return q == 0 ? dist(z, a) < dist(z, b) : q == -1;\
});

pointtt struct point
{
    T x, y;
    point(){}
    point(T _x, T _y) : x(_x), y(_y) {}
    point operator=(const point& b) { x = b.x; y = b.y; return *this; }
    point operator+(const point& b) const { return point(x + b.x, y + b.y); }
    point operator-(const point& b) const { return point(x - b.x, y - b.y); }
    point operator-() const { return point(-x, -y); }
    T operator*(const point& b) const { return x * b.x + y * b.y; }
    T operator^(const point& b) const { return x * b.y - y * b.x; }
    T operator!() const { return x * x + y * y; }
    bool operator<(const point& b) const { return x == b.x ? y < b.y : x < b.x; }
};
pointtt istream&operator>>(istream&is,point<T>&a){return is>>a.x>>a.y;}
pointtt ostream&operator<<(ostream&os,point<T>&a){return os<<a.x<<" "<<a.y;}
pointtt T dist(const point<T>&a,const point<T>&b){return!point<T>(a-b);}
//dist from point C to line AB equals to answer.first / sqrt(answer.second);
pointtt pair<T,T> dist(const point<T>&a,const point<T>&b,const point<T>&c){return{abs((a-b)*c)+(a^b),dist(a,b)};}
static const int CW = 1;
static const int CCW = -1;
pointtt int orientation(const point<T>&a,const point<T>&b,const point<T>&c){T q=a.x*b.y-a.y*b.x-a.x*c.y+a.y*c.x+b.x*c.y-b.y*c.x;return q>0?CCW:q<0?CW:0;}
//reflects point C to line AB (in doubles)
pointtt point<T> reflect(const point<T>&a,const point<T>&b,const point<T>&c){
    T A = a.y - b.y;
    T B = b.x - a.x;
    T C = a ^ b;
    T D = A * A - B * B;
    T S = A * A + B * B;
    return {(-D * c.x - 2 * A * B * c.y - 2 * A * C) / S, (D * c.y - 2 * A * B * c.x - 2 * B * C) / S};
};

//IgorjanconvexHull
pointtt void convexHull(const vector<point<T>>&a){sort(whole(a));int n=SZ(a),j=-1,k=0;ROF(i,n-2,0)a.push_back(a[i]);fori(n){while(j>k&&orientation(a[j-1],a[j],a[i])!=1)--j;a[++j]=a[i];if(!k&&i==n-1)k=j;}a.resize(j);}

//IgorjanprintAns
ttta void printAnswerAndExit(Args... args){writeln(args...);exit(0);}

//Igorjanjoin
template<typename T, template<typename> typename C>
string join(C<T> const& a, string const& delim = " ")
{
    if (size(a) == 0) return "";
    stringstream ss;
    auto it = begin(a);
    for (ss << *it++; it != end(a); ++it)
        ss << delim << *it;
    return ss.str();
}

//IgorjanmodularR
template<typename T = int>
struct modularR
{
    T value;
    T mod;

    modularR() : value(0) {}
    modularR(T mod) : value(0), mod(mod) {}
    modularR(const modularR& other) : value(other.value), mod(other.mod) {}
    modularR operator=(const modularR& other) { value = other.value; mod = other.mod; return *this; }
    template<typename T1> modularR operator=(const T1& other) { assert(mod); value = other % mod; if (value < 0) value += mod; return *this; }
    template<typename T1> modularR(T1 const& other, T1 const& mod) { this->mod = mod; value = other % mod; if (value < 0) value += mod; }
    template<typename T1> modularR(T1 const& num, T1 const& den, T1 const& mod) { *this = modularR(den, mod) ^ (mod - 2) * num; }
    template<typename T1> modularR& operator^=(T1 const& deg) { modularR a(*this); for (T1 n = deg - 1; n > 0; n >>= 1) { if (n & 1) *this *= a; a *= a; } return *this; }
    template<typename T1> modularR  operator^ (T1 const& deg) const { return modularR(*this) ^= deg; }
    template<typename T1> inline modularR& operator+=(T1 const& t)       { value += t; if (value >= mod) value -= mod; return *this; }
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
    explicit operator T() const { return value; }

    inline friend ostream& operator<<(ostream& os, modularR const& m) { return os << m.value; }
    inline friend istream& operator>>(istream& is, modularR& m) { return is >> m.value >> m.mod; m.value %= m.mod; if (m.value < 0) m.value += m.mod; }
};

//Igorjanmodular
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

//Igorjanrational
template<typename T = long long>
struct rational
{
    T num, den;
    rational(T n, T d) { if (d == 0) n = 1; else if (n == 0) d = 1; else { T g = gcd(abs(d), abs(n)); d /= g; n /= g; if (d < 0) d *= -1, n *= -1; } den = d; num = n; }

    rational() : num(0), den(1) {}
    rational(const rational& other) : num(other.num), den(other.den) {}
    rational operator=(const rational& other) { num = other.num, den = other.den; return *this; }
    template<typename T1> rational operator=(const T1& other) { num = other; den = 1; return *this; }
    template<typename T1> rational(T1 const& other) { num = other; den = 1; }

    bool operator<(const rational& b) const { return num * b.den < den * b.num; }
    bool operator>(const rational& b) const { return num * b.den > den * b.num; }
    bool operator==(const rational& b) const { return num == b.num && den == b.den; }
    bool operator<=(const rational& b) const { return *this < b || *this == b; }
    bool operator>=(const rational& b) const { return *this > b || *this == b; }

    inline rational& operator+=(const rational& t)       { rational temp(num * t.den + t.num * den, den * t.den); num = temp.num; den = temp.den; return *this; }
    inline rational& operator-=(const rational& t)       { rational temp(num * t.den - t.num * den, den * t.den); num = temp.num; den = temp.den; return *this; }
    inline rational& operator*=(const rational& t)       { rational temp(num * t.num, den * t.den);               num = temp.num; den = temp.den; return *this; }
    inline rational  operator+ (const rational& t) const { return rational(*this) += t; }
    inline rational  operator- (const rational& t) const { return rational(*this) -= t; }
    inline rational  operator* (const rational& t) const { return rational(*this) *= t; }

    inline friend ostream& operator<<(ostream& os, rational const& m) { os << m.num; if (m.den != 1) os << "/" << m.den; return os; }
    inline friend istream& operator>>(istream& is, rational& m) { T d, n; is >> n >> d; m = rational(n, d); return is; }
};

//Igorjanmatrix
template<typename T>
struct matrix
{
#define vectorOrValarray template<template<typename> typename C, typename = enable_if_t<is_same<vector<T>, C<T>>::value || is_same<valarray<T>, C<T>>::value>>
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

    matrix(const vector<vector<T>>& rhs)
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

    vectorOrValarray matrix& operator=(const C<T>& rhs)
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
    vectorOrValarray C<T> operator*(const C<T>& rhs) {
        assert(m == size(rhs));
        C<T> ans(n);
        fori(n) forn(k, m) ans[i] += a[i][k] * rhs[k];
        return ans;
    }
    vectorOrValarray friend C<T> operator*(const C<T>& lhs, const matrix& rhs) {
        assert(size(lhs) == rhs.n);
        C<T> ans(rhs.m);
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
    vectorOrValarray matrix operator|=(const C<T>& rhs) { return *this |= matrix(rhs); }
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

    vectorOrValarray optional<pair<T, C<T>>> solution(const C<T>& b) {
        assert(n == m);
        matrix temp(*this);
        temp |= b;

        auto det = solve(temp);
        if (!det.has_value()) return {};

        C<T> ret(0, n);
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
        iota(all(permutation), 0);

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

//IgorjanprefixFunction
template<typename T>
vector<int> prefixFunction(T s)
{
    int n = SZ(s);
	vector<int> pi(n);
    fori1(n)
    {
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];
		if (s[i] == s[j]) ++j;
		pi[i] = j;
	}
	return pi;
}

//Igorjanumax
template<typename T1, typename T2>
T1 umax(T1& a, T2 b)
{
    return a < T2(b) ? a = b : a;
}

//Igorjanumin
template<typename T1, typename T2>
T1 umin(T1& a, T2 b)
{
    return a > T2(b) ? a = b : a;
}

//Igorjanhungarian
pair<int, vector<int>> hungarian(const vector<vector<int>>& a)
{
    int n = a.size() + 1;
    int m = a[0].size() + 1;
    vector<int> u(n), v(m), p(m), way(m);
    fori1(n)
    {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m, INF);
        vector<bool> used(m, false);
        do 
        {
            used[j0] = true;
            int i0 = p[j0];
            int delta = INF;
            int j1;
            forj1(m)
                if (!used[j]) 
                {
                    int cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur,
                        way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],
                        j1 = j;
                }
            forj(m)
                if (used[j])
                    u[p[j]] += delta,
                    v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } 
        while (p[j0] != 0);
        do 
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } 
        while (j0);
    }
    vector<int> ans(n + 1);
    forj1(m)
        ans[p[j] - 1] = j - 1;
    return {-v[0], ans};
}

//Igorjankhun
vector<pii> khun(const vector<vector<int>>& g, int n)
{
    vector<int> mt(n, -1);
    vector<int> used(n, false);
    int counter = 0;

    function<bool(int)> dfs = [&](int u) {
        used[u] = counter;
        for (const int& v: g[u])
            if (mt[v] == -1 || (used[mt[v]] != counter && dfs(mt[v])))
                return mt[v] = u, mt[u] = v, true;
        return false;
    };

    for (bool run = 1; run; )
    {
        run = 0;
        counter++;
        fori(n)
            if (mt[i] == -1 && dfs(i))
                run = 1;
    }
    vector<pii> ans;
    fori(n)
        if (mt[i] != -1)
            ans.pb({mt[i], i});
    return ans;
}

//Igorjantopsort
//Returns empty vector if cycle is found
vector<int> topsort(const vector<vector<int>>& edges, bool reversed = false)
{
    int n = edges.size();
    vector<int> ans;
    vector<int> used(n, 0);
    bool cycle = false;
    
    function<void(int)> dfs = [&](int u) {
        used[u] = 1;
        for (const int& v: edges[u])
            if (!used[v])
                dfs(v);
            else if (used[v] == 1)
                cycle = true;
        used[u] = 2;
        ans.pb(u);
    };

    fori(n)
        if (!used[i])
            dfs(i);
    if (cycle)
        return vector<int>();
    if (!reversed)
        reverse(ans.begin(), ans.end());
    return ans;
}

//Igorjanlis
vector<int> lis(const vector<int>& a)
{
    int n = a.size();
    vector<int> d(n + 1, INF), p(n + 1, -1), x(n + 1, -1);
    d[0] = -INF;
 
    fori(n)
    {
        int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[j - 1] < a[i] && a[i] < d[j])
    		d[j] = a[i],
            x[j] = i,
            p[i] = x[j - 1];
    }
    int index = 0;
    while (index <= n && d[index] < INF) ++index;
    index = x[--index];

    vector<int> ans;
    while (index != -1)
        ans.pb(a[index]),
        index = p[index];

    reverse(all(ans));
    return ans;
}

//IgorjanKTO
template<typename T, typename R = T>
T KTO(const vector<T>& a, const vector<T>& p)
{
    assert(SZ(a) == SZ(p));
    int n = SZ(a);
    vector<vector<modularR<T>>> r(n, vector<modularR<T>>(n));
    fori(n) forj(n) r[i][j] = ~modularR<T>(p[i], p[j]);
    vector<modularR<T>> x(n);
    fori(n)
        x[i] = modularR(a[i], p[i]);

    R result = 0;
    R mult = 1;
    fori(n)
    {
        forj(i)
            x[i] = (x[i] - x[j]) * r[j][i];
        result += mult * x[i];
        mult *= p[i];
    }
    return result;
}

//Igorjancached
template<class T, class... Args>
struct cached
{
    function<T(Args...)> f;
    map<tuple<Args...>, T> m;

    cached(const function<T(Args...)>& f) : f(f) { }

    T operator()(Args&&... args) {
        auto x = tuple(forward<Args>(args)...);
        if (auto it = m.find(x); it != m.end())
            return it->second;
        return m[x] = f(forward<Args>(args)...);
    }
};

//IgorjanEndIfIgorjan
#endif /* IGORJAN94 */
