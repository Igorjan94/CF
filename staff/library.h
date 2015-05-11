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
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}

//Igorjanbin_search
//x -> min, f(x) == true
template<typename T, typename F>
T bin_search(T l, T r, F f, T eps)
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

    void union(int i, int j)
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
        return move(temp);
    }

    bool isPrime(int x)
    {
        return minPrime[x] == x;
    }
};

//IgorjanfenwickTree
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

//Igorjanendif
#endif /* IGORJAN94 */
