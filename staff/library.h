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
#define   elohw(a)   a.rbegin(), a.rend()
#define   whole(a)   a.begin(), a.end()
#define    next      next__
#define    prev      prev__
#define   union      union__

#define argmax(a)    (max_element(whole(a)) - (a).begin())
#define argmin(a)    (min_element(whole(a)) - (a).begin())
#define wr(args...)  err(split(#args,',').begin(),args)

#define FILENAME "input"
#define INF 1000000007

#define tthti  template<typename Head, typename... Tail> inline
#define ttt12i template<typename T1, typename T2> inline
#define ttti   template<typename T> inline

#define    ints(args...)     int args; readln(args)
#define     lls(args...)      ll args; readln(args)
#define   vints(args...)      vi args; readln(args)
#define strings(args...)  string args; readln(args)

//IgorjanWriteln-Readln
inline void writeln2(){cout<<"\n";}
inline void writeln() {cout<<"\n";}
inline void readln()  {}
ttti void read(T&);
ttti void priws(T);
ttti void print(T);

void err(vector<string>::iterator it){++it;}
tthti void readln (Head& head,Tail&... tail){read(head); readln  (tail...);}
tthti void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
tthti void writeln (Head head, Tail... tail){priws(head);writeln2(tail...);}
ttti  void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
tthti void err(vector<string>::iterator it,Head head,Tail...tail){writeln((*it).substr((*it)[0]==' '),"=",head);err(++it, tail...);}
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return v;}

ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}

//IgorjanbinSearch
//x -> min, f(x) == true
template<typename T, typename F>
T binSearch(T l, T r, F f, T eps)
{
    T m;
    while (fabs(r - l) > eps)
        m = (r + l) / 2,
        (f(m) ? r : l) = m;
    return f(l) ? l : r;
}

//Igorjandsu
struct dsu
{
    vector<int> a;

    dsu(int n)
    {
        a.resize(n);
        iota(a.begin(), a.end(), 0);
    }

    int get(int i)
    {
        return a[i] == i ? i : a[i] = get(a[i]);
    }

    void uni(int i, int j)
    {
        i = get(i);
        j = get(j);
        if (i != j)
            a[i] = j;
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
        t.resize(n = arr.size(), 0);
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
//zero-indexed, [l..r]
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

    void update(int position, int value)
    {
        update(1, 0, n - 1, position, value);
    }

    void update(int v, int tl, int tr, int position, int value) 
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

//sparseTable
//zero-indexes, [l, r)
template<typename T>
struct sparseTable
{
    int n;
    vector<vector<T>> st;
    vector<int> logs;
    typedef function<T (T, T)> F;
    F f;
    T NEITRAL_ELEMENT;

    sparseTable(vector<T>& a, F g, T ne = 0)
    {
        NEITRAL_ELEMENT = ne;
        n = a.size();
        f = g;

        logs.push_back(0);
        logs.push_back(0);
        FOR(i, 2, n + 1) logs.push_back(logs[i / 2] + 1);
        int L = logs.back() + 1;
        st.resize(L, vector<T>(n, ne));
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

//Igorjanbfs
template<typename S, typename T, typename F1, typename F2>
vector<T> bfs(vector<vector<S>>& a, int start, F1 get, F2 dist, T unusedParameter)
{
    int n = a.size();
    vector<T> d(n, numeric_limits<T>::max());
    vector<bool> used(n, false);
    d[start] = T(0);
    used[start] = true;
    queue<int> q;
    q.push(start);
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (S x : a[u])
        {
            int to = get(x);
            if (!used[to])
                q.push(to),
                d[to] = d[u] + dist(x),
                used[to] = true;
        }
    }
    return move(d);
}

//Igorjanbinpow
template<typename T>
T binpow(T a, ll n)
{
    if (n == 0)
        return (T) 1;
    if (n == 1)
        return a;
    T res = a;
    --n;
    while (n)
    {
        if (n & 1)
            res *= a;
        a *= a;
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
#define pointtt template<typename T>
//sorts only if z is corner point;
#define sortByPolarAngle(v, z, T) sort(v.begin(), v.end(), [&z](point<T>& a, point<T>& b) {\
    int q = orientation(z, a, b); return q == 0 ? dist(z, a) < dist(z, b) : q == -1;\
});

pointtt struct point
{
    T x, y;
    point(T _x, T _y) : x(_x), y(_y) {}
    point(){}
    point operator+(point b) { return point(x + b.x, y + b.y); }
    point operator-() { return point(-x, -y); }
    T operator*(point b) { return x * b.x + y * b.y; }
    T operator^(point b) { return x * b.y - y * b.x; }
    T operator!() { return x * x + y * y; }
    bool operator<(point b) { return x == b.x ? y < b.y : x < b.x; }
};
pointtt istream&operator>>(istream&is,point<T>&a){return is>>a.x>>a.y;}
pointtt ostream&operator<<(ostream&os,point<T>&a){return os<<a.x<<" "<<a.y;}
pointtt T dist(point<T>&a,point<T>&b){return!point<T>(a+-b);}
//dist from point C to line AB equals to answer.first / sqrt(answer.second);
pointtt pair<T,T> dist(point<T>&a,point<T>&b,point<T>&c){return{abs((a+-b)*c)+(a^b),dist(a,b)};}
pointtt int orientation(point<T>&a,point<T>&b,point<T>&c){T q=a.x*b.y-a.y*b.x-a.x*c.y+a.y*c.x+b.x*c.y-b.y*c.x;return q>0?1:q<0?-1:0;}

//IgorjanconvexHull
pointtt vector<point<T>>convexHull(vector<point<T>>a){sort(a.begin(),a.end());int n=a.size(),j=-1,k=0;ROF(i,n-2,0)a.push_back(a[i]);fori(a.size()){for(;j>k&&orientation(a[j-1],a[j],a[i])!=1;--j)
    ;a[++j]=a[i];if(!k&&i==n-1)k=j;}a.resize(j);return a;}

//IgorjanprintAns
ttti void printAnswerAndExit(T a){writeln(a);exit(0);}

//IgorjanEndIfIgorjan
#endif /* IGORJAN94 */
