//Igorjan94, template version from 10 March 2015
#ifndef IGORJAN94
#define IGORJAN94 1

//IgorjanIncludes
#include <bits/stdc++.h>
using namespace std;

//IgorjanPDBS
#undef _GLIBCXX_HAVE_ICONV
#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds; 
typedef tree<int, int,       less<int>, rb_tree_tag, tree_order_statistics_node_update> orderedMap;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> orderedSet;

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

template<typename T,typename D>
ostream&operator<<(ostream&os,T const&a);
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
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

//IgorjanbinarySearch
//x \in [l, r]-> min, f(x) == true
template<typename T, typename F>
T binarySearch(T l, T r, F f, T eps = 1)
{
    T m;
    while (abs(r - l) > eps)
        m = l + (r - l) / 2,
        (f(m) ? r : l) = m;
    return f(l) ? l : r;
}

//IgorjanbinSearch
//x \in [l, r]-> min, f(x) == true
// l                           r
// 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1
//                 ^
template<typename T, typename F>
T binSearch(T l, T r, F f)
{
    T m;
    while (l < r)
    {
        m = (r + l + 1) / 2;
        if (f(m))
            r = m - 1;
        else
            l = m;
    }
    return l;
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
    vector<T> add;
    //vector<T> pos;
    function<T(const T&, const T&)> f = [](const T& a, const T& b) { return min(a, b); };
    T NEITRAL_ELEMENT = numeric_limits<T>::max();
 
    void push(int v, int tl, int tr)
    {
        if (add[v] == 0) return;

        t[v] += add[v];
        if (tl != tr)
            add[v * 2] += add[v],
            add[v * 2 + 1] += add[v];
        add[v] = 0;
    }

    void build(const vector<T>& a, int v, int l, int r)
    {
        if (l == r)
        {
            t[v] = a[l];
            //pos[v] = l;
        }
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            T left = t[v * 2];
            T right = t[v * 2 + 1];

            //if (left > right)
                //pos[v] = pos[v * 2];
            //else
                //pos[v] = pos[v * 2 + 1];
            t[v] = f(left, right);
        }
    };
 
    segmentTree(const vector<T>& a)
    {
        n = a.size();
        t.resize(n * 4 + 10);
        add.resize(n * 4 + 10, 0);
        //pos.resize(n * 4 + 10, 0);
        build(a, 1, 0, n - 1);
    }
 
    void update(int l, int r, T value)
    {
        update(1, 0, n - 1, l, r, value);
    }
 
    void update(int v, int tl, int tr, int l, int r, T value) 
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
            T left = t[v * 2];
            T right = t[v * 2 + 1];

            //if (left > right)
                //pos[v] = pos[v * 2];
            //else
                //pos[v] = pos[v * 2 + 1];
            t[v] = f(left, right);
        }
    }

    T get(int l, int r)
    {
        return get(1, 0, n - 1, l, r);
    }

    T get(int v, int tl, int tr, int l, int r) 
    {
        push(v, tl, tr);
        if (l > r) return NEITRAL_ELEMENT;

        if (tl == l && tr == r)
            return t[v];
        else 
        {
            int tm = (tl + tr) / 2;
            T left = get(v * 2, tl, tm, l, min(r, tm));
            T right = get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
            return f(left, right);
        }
    }

};

//IgorjandisjointSparseTable
template<typename T>
struct disjointSparseTable // [l, r), 0-indexed
{
    vector<vector<T>> dp;
    int n;
    int h;

    T NEUTRAL_ELEMENT = 0;
    //T NEUTRAL_ELEMENT = numeric_limits<T>::max();
    //T NEUTRAL_ELEMENT = numeric_limits<T>::min();
    T f(const T& a, const T& b) const
    {
        return a + b;
    };

    int highestBit(int x) const { return 31 - __builtin_clz(x); }

    disjointSparseTable(vector<T> a)
    {
        n = a.size();
        h = highestBit(n);
        dp.resize(h, vector<T>(n + 1, NEUTRAL_ELEMENT));
        forj(h)
        {
            int l = 1 << j;
            for (int c = l; c < n + l; c += l * 2)
            {
                for (int i = c + 1; i <= min(n, c + l); ++i)
                    dp[j][i] = f(dp[j][i - 1], a[i - 1]);
                for (int i = min(n, c) - 1; i >= c - l; --i)
                    dp[j][i] = f(a[i], dp[j][i + 1]);
            }
        }
    }

    T get(int l, int r) const
    {
        int hb = highestBit(l ^ r);
        return f(dp[hb][l], dp[hb][r]);
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

    int highestBit(int x) const { return 31 - __builtin_clz(x); }

    sparseTable() {}

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
        int len = highestBit(r - l);
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
    point(const point& other) : x(other.x), y(other.y) {}
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
pointtt ostream&operator<<(ostream&os,const point<T>&a){return os<<a.x<<" "<<a.y;}
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
pointtt vector<point<T>> convexHull(vector<point<T>> a) //ANDREW
{
	if (a.size() <= 1) return a;
    sort(a.begin(), a.end());
    vector<point<T>> up, dn;
    for (const auto& p: a)
    {
        while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), p) != CCW)
            up.pop_back();
        while (dn.size() > 1 && orientation(dn[dn.size() - 2], dn.back(), p) != CW)
            dn.pop_back();
        up.push_back(p);
        dn.push_back(p);
    }
    dn.pop_back();
    copy(up.rbegin(), up.rend() - 1, back_inserter(dn));
    if (dn.size() == 2 && dn[0] == dn[1]) dn.pop_back();
    return dn;
}

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
    template<typename T1> modularR& operator^=(T1 const& deg) { modularR a(*this); value = T(1); for (T1 n = deg; n > 0; n >>= 1) { if (n & 1) *this *= a; a *= a; } return *this; }
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
template<typename T = int>
vector<T> lis(const vector<T>& a)
{
    int n = a.size();
    vector<T> d(n + 1, numeric_limits<T>::max()), p(n + 1, -1), x(n + 1, -1);
    d[0] = numeric_limits<T>::min();
 
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

    vector<T> ans;
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

//IgorjanlcaST
struct lcaST
{
    vector<vector<int>> g;
    vector<int> h, tin;
    vector<pii> euler;
    int n, l;
    sparseTable<pii> st;

    lcaST(const vector<vector<int>>& g, int root = 0) //O(n * log(n))
    {
        this->g = g;
        n = SZ(g);
        h.resize(n, -1);
        tin.resize(n, -1);
        dfs(root, -1);
        st = sparseTable<pii>(euler, [](const pii& a, const pii& b) {
            if (a.first < b.first)
                return a;
            else
                return b;
        });
    }
 
    void dfs(int u, int p) //O(n)
    {
        h[u] = h[p] + 1;
        tin[u] = SZ(euler);
        euler.emplace_back(h[u], u);
        for (const int& v: g[u]) if (v != p)
            dfs(v, u),
            euler.emplace_back(h[u], u);
    }

    int get(int a, int b) //O(1)
    {
        if (tin[a] > tin[b]) swap(a, b);
        return st.get(tin[a], tin[b] + 1).second;
    }
};

//Igorjanlca
struct lca
{
    vector<vector<int>> g, up;
    vector<int> h;
    int n, l;

    lca(const vector<vector<int>>& g) //O(n * log(n))
    {
        this->g = g;
        n = SZ(g);
        l = 1;
        while ((1 << l) <= n) ++l;
        h.resize(n, -1);
        up.resize(l + 1, vector<int>(n));
        dfs(0, 0);
        fori(l)
            forj(n)
                up[i + 1][j] = up[i][up[i][j]];
    }
 
    int getParent(int u, int dist) { //O(log(n))
        fori(l)
            if (dist >> i & 1)
                u = up[i][u];
        return u;
    }

    void dfs(int u, int p) //O(n)
    {
        h[u] = h[p] + 1;
        up[0][u] = p;
        for (const int& v: g[u])
            if (v != p)
                dfs(v, u);
    }

    int get(int a, int b) //O(log(n))
    {
        if (h[a] < h[b]) swap(a, b);
        a = getParent(a, h[a] - h[b]);
        if (a == b) return a;
        ROF(i, l, 0)
            if (up[i][a] != up[i][b])
                a = up[i][a],
                b = up[i][b];
        return up[0][a];
    }

    int getChildWithVertex(int a, int b) //O(log(n))
    {
        if (a == b) return -1;
        return getParent(b, h[b] - h[a] - 1);
    }
};

//Igorjanint128
inline istream&operator>>(istream&in,__int128&a){
    a = 0;
    bool neg = false;
    char c;
    in >> noskipws >> c;
    while (c < '0' || c > '9') {
        neg = c == '-';
        in >> noskipws >> c;
    }
    while (c >= '0' && c <= '9') {
        a = a * 10 + c - '0';
        in >> noskipws >> c;
    }
    if (neg) a *= -1;
    return in;
}
inline ostream&operator<<(ostream&out,const __int128& x) {
    auto a = x;
    if (a < 0)
    {
        out << "-";
        a *= -1;
    }
    string s;
    while (a >= 10)
        s.pb((a % 10) + '0'),
        a /= 10;
    s.pb(a + '0');
    reverse(all(s));
    return out << s;
}

//IgorjanliChaoTree
template<typename T>
struct liChaoTree //Note that liChaoTree assumes that there is no point in which more than two lines intersect
{
    int n;
    vector<point<T>> line;
    T f(const point<T>& a, T x)
    {
        return a * point<T>(x, T(1));
    };

    liChaoTree(int n, T maxSecureValue = numeric_limits<T>::max()) : n(n)
    {
        line.resize(n * 4, {0, maxSecureValue});
    }

    void addLine(point<T> nw)
    {
        addLineImpl(nw, 1, 0, n);
    }

    void addLineImpl(point<T>& nw, int v, int l, int r)
    {
        int m = (l + r) / 2;
        bool lef = f(nw, l) < f(line[v], l);
        bool mid = f(nw, m) < f(line[v], m);
        if (mid)
            swap(line[v], nw);
        if (r - l == 1)
            return;

        if (lef != mid)
            addLineImpl(nw, 2 * v, l, m);
        else
            addLineImpl(nw, 2 * v + 1, m, r);
    }

    T get(const T& x)
    {
        return getImpl(x, 1, 0, n);
    }

    T getImpl(const T& x, int v, int l, int r) 
    {
        int m = (l + r) / 2;
        if (r - l == 1)
            return f(line[v], x);
        
        if (x < m)
            return min(f(line[v], x), getImpl(x, 2 * v, l, m));
        else
            return min(f(line[v], x), getImpl(x, 2 * v + 1, m, r));
    }
};

//IgorjanchtTrick
// Add kx+b lines. Return min/max in given point
// Author: Simon Lindholm
// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
template<typename T>
struct line
{
    mutable T k, b, p;
    bool operator<(const line& other) const { return k < other.k; }
    bool operator<(const T& other) const { return p < other; }
    T get(const T& x) const { return k * x + b; }
};

template<typename T>
struct chtTrick : multiset<line<T>, less<>>
{
    static const T inf = numeric_limits<T>::max();
    int sign = 1;

    chtTrick(bool mn = false) //if mn is true, than return minimum value. Else return maximum value
    {
        if (mn) sign = -1;
    }

    T div(const T& a, const T& b)
    {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool isect(typename multiset<line<T>, less<>>::iterator x, typename multiset<line<T>, less<>>::iterator y) {
        auto& [kx, bx, px] = *x;
        auto& [ky, by, py] = *y;
		if (y == this->end())
        {
            px = inf;
            return false;
        }
		if (kx == ky)
            px = bx > by ? inf : -inf;
		else
            px = div(by - bx, kx - ky);
		return px >= py;
	}

	void addLine(const T& k, const T& b) {
		auto z = this->insert({k * sign, b * sign, 0});
        auto y = z++;
        auto x = y;
		while (isect(y, z))
            z = this->erase(z);

		if (x != this->begin() && isect(--x, y))
            isect(x, y = this->erase(y));

		while ((y = x) != this->begin() && (--x)->p >= y->p)
			isect(x, this->erase(y));
	}

	T get(const T& x) {
		assert(!this->empty());
        return sign * this->lower_bound(x)->get(x);
	}
};

//Igorjanrng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//Igorjanrng64
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

//IgorjantwoSat
struct twoSat
{
    vector<vector<int>> g, gt;
    vector<bool> used;
    vector<int> order;
    vector<int> comp;
    int n;

    twoSat(int n)
    {
        n *= 2;
        this->n = n;
        g.resize(n);
        gt.resize(n);
        used.resize(n, false);
        comp.resize(n, -1);
    }

    //(af ? not a : a) || (bf ? not b : b)
    void addOr(int a, bool af, int b, bool bf) {
        a += a + (af ^ 1);
        b += b + (bf ^ 1);
        addEdge(a ^ 1, b);
        addEdge(b ^ 1, a);
    }
    
    void addXor(int a, bool af, int b, bool bf) {
        addOr(a, af, b, bf);
        addOr(a, !af, b, !bf);
    }
    
    void addImply(int a, bool af, int b, bool bf) {
        a += a + (af ^ 1);
        b += b + (bf ^ 1);
        addEdge(a, b);
    }
    
    void addEdge(int a, int b) {
        g[a].push_back(b);
        gt[b].push_back(a);
    }
    
    //returns vector of n / 2 size -- if i / 2-th variable is true or false
    optional<vector<bool>> solve()
    {
        fori(n)
            if (!used[i])
                dfs1(i);

        reverse(all(order));

        int j = 0;
        for (const int& u: order)
            if (comp[u] == -1)
                dfs2(u, j++);

        fori(n)
            if (comp[i] == comp[i ^ 1])
                return {};
        vector<bool> ans(n / 2);
        for (int i = 0; i < n; i += 2)
            ans[i / 2] = comp[i] < comp[i ^ 1];
        return ans;
    }

private:
    void dfs1(int u)
    {
        used[u] = true;
        for (const int& v: g[u])
            if (!used[v])
                dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, int c)
    {
        comp[u] = c;
        for (const int& v: gt[u])
            if (comp[v] == -1)
                dfs2(v, c);
    }

};

//Igorjanffs
template<typename T>
int ffs(T i)
{
    if (T(0) == i)
        return 0;

    int bit = 1;
    while (!(i & 1))
        ++bit,
        i >>= 1;
    return bit;
}

//IgorjanmaxClique
//0-indexed, 3 ^ (n / 3), source: https://github.com/ShahjalalShohag/code-library/blob/master/Graph%20Theory/Maximum%20Clique.cpp
//p -- price (pass vector<int>(n, 1) to count vertices)
template<typename T>
int maxClique(const vector<vector<int>>& g, const vector<T>& p)
{
    T res = 0;
    int n = g.size();
    vector<ll> edges(n);
    fori(n)
        forj(n)
            if (g[i][j])
                edges[i] |= 1ll << j;

    auto BronKerbosch = [&](auto BronKerbosch, ll R, ll P, ll X) -> void
    {
        if (!P && !X)
        {
            int t = 0;
            fori(n)
                if (R & (1ll << i))
                    t += p[i];
            res = max(res, t);
            return;
        }
        int u = ffs(P | X) - 1;

        for (int v = 0; v < n; v++)
            if (ll V = 1ll << v; (V & P) && !(V & edges[u])) 
            {
                BronKerbosch(BronKerbosch, R | V, P & edges[v], X & edges[v]);
                P -= V;
                X |= V;
            }
    };
    BronKerbosch(BronKerbosch, 0, (1ll << n) - 1, 0);
    return res;
}

//IgorjanfastSet
//Can correctly work with numbers in range [0; MAXN]. If element is not found return NOT_FOUND
//Supports all std::set operations in O(1) on random queries / dense arrays, O(log_64(N)) in worst case (sparce array).
//Count operation works in O(1) always.
//SOURCE: https://codeforces.com/contest/1793/submission/193330718
using uint = unsigned int;
using ull = unsigned long long;

template<uint MAXN, uint NOT_FOUND>           
class fastSet {
    static constexpr ull lowest_bitsll[] = {0ull, 1ull, 3ull, 7ull, 15ull, 31ull, 63ull, 127ull, 255ull, 511ull, 1023ull, 2047ull, 4095ull, 8191ull, 16383ull, 32767ull, 65535ull, 131071ull, 262143ull, 524287ull, 1048575ull, 2097151ull, 4194303ull, 8388607ull, 16777215ull, 33554431ull, 67108863ull, 134217727ull, 268435455ull, 536870911ull, 1073741823ull, 2147483647ull, 4294967295ull, 8589934591ull, 17179869183ull, 34359738367ull, 68719476735ull, 137438953471ull, 274877906943ull, 549755813887ull, 1099511627775ull, 2199023255551ull, 4398046511103ull, 8796093022207ull, 17592186044415ull, 35184372088831ull, 70368744177663ull, 140737488355327ull, 281474976710655ull, 562949953421311ull, 1125899906842623ull, 2251799813685247ull, 4503599627370495ull, 9007199254740991ull, 18014398509481983ull, 36028797018963967ull, 72057594037927935ull, 144115188075855871ull, 288230376151711743ull, 576460752303423487ull, 1152921504606846975ull, 2305843009213693951ull, 4611686018427387903ull, 9223372036854775807ull, 18446744073709551615ull};

    static const uint PREF = (MAXN <= 64 ? 0 :
                              MAXN <= 4096 ? 1 :
                              MAXN <= 262144 ? 1 + 64 :
                              MAXN <= 16777216 ? 1 + 64 + 4096 :
                              MAXN <= 1073741824 ? 1 + 64 + 4096 + 262144 : 227) + 1;
    static const uint SZ = PREF + (MAXN + 63) / 64 + 1;
    ull m[SZ] = {0};
 
    inline uint left(uint v) const {return (v - 62) * 64;}
    inline uint parent(uint v) const {return v / 64 + 62;}
    inline void setbit(uint v) {m[v >> 6] |= 1ull << (v & 63);}
    inline void resetbit(uint v) {m[v >> 6] &= ~(1ull << (v & 63));}
    inline uint getbit(uint v) const {return m[v >> 6] >> (v & 63) & 1;}
    inline ull childs_value(uint v) const {return m[left(v) >> 6];}
 
    inline uint left_go(uint x, const uint c) const {
        const ull rem = x & 63;
        uint bt = PREF * 64 + x;
        ull num = m[bt >> 6] & lowest_bitsll[rem + c];
        if (num) return (x ^ rem) | __lg(num);
        for (bt = parent(bt); bt > 62; bt = parent(bt)) {
            const ull rem = bt & 63;
            num = m[bt >> 6] & lowest_bitsll[rem];
            if (num) {bt = (bt ^ rem) | __lg(num); break;}
        }
        if (bt == 62) return NOT_FOUND;
        while (bt < PREF * 64) bt = left(bt) | __lg(m[bt - 62]);
        return bt - PREF * 64;
    }
 
    inline uint right_go(uint x, const uint c) const {
        const ull rem = x & 63;
        uint bt = PREF * 64 + x;
        ull num = m[bt >> 6] & ~lowest_bitsll[rem + c];
        if (num) return (x ^ rem) | __builtin_ctzll(num);
        for (bt = parent(bt); bt > 62; bt = parent(bt)) {
            const ull rem = bt & 63;
            num = m[bt >> 6] & ~lowest_bitsll[rem + 1];
            if (num) {bt = (bt ^ rem) | __builtin_ctzll(num); break;}
        }
        if (bt == 62) return NOT_FOUND;
        while (bt < PREF * 64) bt = left(bt) | __builtin_ctzll(m[bt - 62]);
        return bt - PREF * 64;
    }
 
public:
    fastSet() {
        assert(PREF != 228);
        setbit(62);
    }
 
    bool empty() const {return getbit(63);}
 
    void clear() {fill(m, m + SZ, 0); setbit(62);}
 
    bool count(uint x) const {return m[PREF + (x >> 6)] >> (x & 63) & 1;}
 
    void insert(uint x) {
        for (uint v = PREF * 64 + x; !getbit(v); v = parent(v)) {
            setbit(v);
        }
    }
 
    void erase(uint x) {
        if (!getbit(PREF * 64 + x)) return;
        resetbit(PREF * 64 + x);
        for (uint v = parent(PREF * 64 + x); v > 62 && !childs_value(v); v = parent(v)) {
            resetbit(v);
        }
    }
 
    uint lower_bound(uint x) const {return right_go(x, 0);}
    uint upper_bound(uint x) const {return right_go(x, 1);}
    uint inverse_lower_bound(uint x) const {return left_go(x, 1);}
    uint inverse_upper_bound(uint x) const {return left_go(x, 0);}
};

//IgorjanMoAlgorithm
inline ll hilbertOrder(int x, int y, int pow, int rotate = 0) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? (
        (y < hpow) ? 0 : 3
    ) : (
        (y < hpow) ? 1 : 2
    );
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    ll subSquareSize = 1ll << (2 * pow - 2);
    ll ans = seg * subSquareSize;
    ll add = hilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

template<typename S, typename T>
struct MO
{
    int n;
    int w;
    int q = 0;
    vector<tuple<ll, int, int, int, T>> queries;
    vector<S> answers;

    const void f(const int&);
    void (*addLeft)(const int&);
    void (*addRight)(const int&);
    void (*delLeft)(const int&);
    void (*delRight)(const int&);
    S (*getAnswer)(const int&, const int&, const T&);

    void addQuery(int l, int r, const T& t) {
        queries.push_back({hilbertOrder(l, r, w), l, r, q++, t});
    }

    MO(unsigned int maxN,
        void addLeft(const int&),
        void addRight(const int&),
        void delLeft(const int&),
        void delRight(const int&),
        S getAnswer(const int&, const int&, const T&)
    ) {
        n = maxN;
        w = bit_width(maxN);
        this->addLeft = addLeft;
        this->addRight = addRight;
        this->delLeft = delLeft;
        this->delRight = delRight;
        this->getAnswer = getAnswer;
    }

    vector<S> go(
    ) {
        answers.resize(q);
        sort(all(queries), [&](const auto& a, const auto& b) {
            return get<0>(a) < get<0>(b);
        });

        int L = 0;
        int R = -1;

        for (int i = 0; i < q; ++i)
        {
            const auto& [_, l, r, id, t] = queries[i];
            while (L > l) addLeft(--L);
            while (R < r) addRight(++R);
            while (L < l) delLeft(L++);
            while (R > r) delRight(R--);
            answers[id] = getAnswer(l, r, t);
        }
        return answers;
    }
};

//IgorjanMOWithUpdates
//Usage example: 940/F.cpp
template<typename T>
struct query
{
    int l;
    int r;
    int i;
    int updates;
    T q;

    int lb;
    int rb;

    query(int b, int l, int r, int i, int updates, const T& q) : l(l), r(r), i(i), updates(updates), q(q) 
    {
        this->lb = l / b;
        this->rb = r / b;
    }
};

template<typename S, typename T, typename U>
struct MOWithUpdates
{
    int n;
    int b = 0;
    vector<query<T>> queries;
    vector<U> updates;
    vector<S> answers;

    const void f(int);
    void (*addLeft)(int);
    void (*addRight)(int);
    void (*delLeft)(int);
    void (*delRight)(int);
    void (*update)(int, int, int, bool, const U&);
    S (*getAnswer)(int, int, const T&);

    void addQuery(int l, int r, const T& t) {
        int i = queries.size();
        queries.push_back(query(b, l, r, i, updates.size(), t));
    }

    void addUpdate(const U& u) {
        updates.push_back(u);
    }

    MOWithUpdates(
        unsigned int maxN,
        unsigned int maxQ,
        void addLeft(int),
        void addRight(int),
        void delLeft(int),
        void delRight(int),
        void update(int, int, int, bool, const U&),
        S getAnswer(int, int, const T&)
    ) {
        queries.reserve(maxQ);
        updates.reserve(maxQ);
        n = maxN;
        b = pow(n, 2. / 3);
        this->addLeft = addLeft;
        this->addRight = addRight;
        this->delLeft = delLeft;
        this->delRight = delRight;
        this->update = update;
        this->getAnswer = getAnswer;
    }

    vector<S> go(
    ) {
        answers.resize(queries.size());
        sort(all(queries), [&](const auto& a, const auto& b) {
            if (a.lb != b.lb)
                return a.lb < b.lb;
            if (a.rb != b.rb)
                return a.lb & 1 ? a.rb < b.rb : a.rb > b.rb;
            return a.lb & 1 ^ a.rb & 1 ? a.updates < b.updates : a.updates > b.updates;
        });

        int L = 0;
        int R = -1;
        int E = 0;

        for (const auto& [l, r, id, t, q, _, __]: queries) 
        {
            while (E < t) { update(E, L, R, true, updates[E]); ++E; }
            while (E > t) { --E; update(E, L, R, false, updates[E]); }
            while (L > l) addLeft(--L);
            while (R < r) addRight(++R);
            while (L < l) delLeft(L++);
            while (R > r) delRight(R--);
            answers[id] = getAnswer(l, r, q);
        }
        return answers;
    }
};

//IgorjandownTree
//0-indexed, [l..r)
template<typename T, typename F>
struct downTree {
    F f;
    vector<T> t;
    int n;

    downTree(int sz, const F &g, T defaultValue = T()) : f(g)
    {
        n = 1;
        while (n <= sz) n <<= 1;
        t.resize(n * 2, defaultValue);
    }

    downTree(vector<T> &a, const F &g, T defaultValue = T()) : downTree(a.size(), g, defaultValue)
    {
        for (int i = 0; i < SZ(a); ++i)
            t[i + n] = a[i];
        for (int i = n - 1; i >= 1; --i)
            t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    void update(int i, const T& x)
    {
        i += n;
        t[i] = f(t[i], x);
        for (i >>= 1; i > 1; i >>= 1)
            t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    T get(int l, int r)
    {
        T resL = t[0];
        T resR = t[0];
        l += n;
        r += n;
        while (l < r)
        {
            if (l & 1)
                resL = f(resL, t[l++]);
            if (r & 1)
                resR = f(t[--r], resR);
            l >>= 1;
            r >>= 1;
        }
        return f(resL, resR);
    }
};

//IgorjanheavyLight
template<typename T, typename F>
struct heavyLight 
{
    F f;
    vector<T> a;
    downTree<T, F> tree;

    int n;
    int paths = 0;
    vector<int> sizes;  //Size of subtree
    vector<int> depth;  //Depth of vertex
    vector<int> parent; //Parent vertex
    vector<int> path;   //Path to which vertex belongs (like in disjoint set union)
    vector<int> heavy;  //Heavy child if exists else -1
    vector<int> index;  //Index of vertex in segment tree
    vector<int> first;  //Highest vertex of path

    heavyLight(const vector<vector<int>>& g, const vector<T>& a, const F& f, const T& defaultValue) : tree(a, f, defaultValue) 
    {
        this->a = a;
        this->f = f;
        n = g.size();
        sizes.resize(n, 1);
        depth.resize(n, 0);
        parent.resize(n, -1);
        path.resize(n, -1);
        heavy.resize(n, -1);
        index.resize(n, -1);
        first.resize(n, -1);

        auto dfs = [&](auto dfs, int u, int p) -> void
        {
            for (const int& v: g[u]) if (v != p)
            {
                depth[v] = depth[u] + 1;
                parent[v] = u;
                dfs(dfs, v, u);
                sizes[u] += sizes[v];
            }
            for (const int& v: g[u]) if (v != p)
                if (sizes[v] * 2 >= sizes[u])
                    heavy[u] = v;
        };
        dfs(dfs, 0, -1);

        int cur = -1;
        fori(n)
            if (heavy[i] == -1)
            {
                int u = i;
                vector<int> currentPath;
                while (true)
                {
                    currentPath.pb(u);
                    path[u] = paths;
                    int nu = parent[u];
                    if (nu == -1 || heavy[nu] != u)
                        break;
                    u = nu;
                }

                reverse(all(currentPath));
                for (int v: currentPath)
                    first[v] = u,
                    index[v] = ++cur;
                ++paths;
            }
    }

    T get(int u, int v) 
    {
        int l = path[u];
        int r = path[v];
        if (l == r)
            return tree.get(index[u], index[v]);
        if (depth[first[u]] < depth[first[v]])
            swap(u, v);
        int left = tree.get(index[u], index[first[u]]);
        return f(left, get(parent[first[u]], v));
    }
};

//IgorjanEndIfIgorjan
#endif /* IGORJAN94 */
