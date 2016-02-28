// Igorjan94, template version from 19 March 2015 (deleted unused defines & reorganization from 05 November 2015)
#include <bits/stdc++.h>

using namespace std;

#define forit(it, r) for (auto it = r.begin(); it != r.end(); ++it)
#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn1(i, n)  for (int i = 1; i < (int) (n); ++i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     pll      pair<long long, long long>
#define   whole(a)   a.begin(), a.end()
#define    next      next__
#define    prev      prev__
#define   count      count__
#define  argmax(a)   (max_element(whole(a)) - (a).begin())
#define  argmin(a)   (min_element(whole(a)) - (a).begin())

#define  ints(a...)  int a; readln(a)
#define  lls(a...)   ll a; readln(a)
#define wr(args...)  err(split(#args,',').begin(),args)
                    
#define  FILENAME    "input"
#define     INF      1000000007
                    
#define    tthti     template<typename Head, typename... Tail> inline
#define   ttt12i     template<typename T1, typename T2> inline
#define    ttti      template<typename T> inline

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

///-------------------------------------------------------------------------------------------------------------------------------------

//segmentTree
template<typename T>
struct segmentTree
{
    int n;
    int MAX;
    vector<T> t;
    typedef function<T (T, T)> F;
    F f;
    T NEITRAL_ELEMENT;

    void build(vector<T>& a, int v, int l, int r)
    {
        if (l == r)
            t[v] = min(MAX, a[l]);
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            t[v] = f(t[v * 2], t[v * 2 + 1]);
        }
    };

    segmentTree(vector<T>& a, F g, T ne = 0, int MA = 0)
    {
        n = a.size();
        t.resize(n * 4);
        f = g;
        MAX = MA;
        NEITRAL_ELEMENT = ne;
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
            t[v] = min(value, MAX);
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
//Igorjan

void run()
{
    ints(n, k, a, b, q);
    vector<int> x(n + 2, 0);
    vector<int> y(n + 2, 0);

    segmentTree<int> A(x, [](int qwer, int asdf) { return qwer + asdf;}, 0, a);
    segmentTree<int> B(y, [](int qwer, int asdf) { return qwer + asdf;}, 0, b);
    forn(Q, q)
    {
        ints(type);
        if (type == 1)
        {
            ints(d, value);--d;
            A.update(d, A.get(d, d) + value);
            B.update(d, B.get(d, d) + value);
        }
        else
        {
            ints(p);--p;
            writeln(B.get(0, p - 1) + A.get(p + k, n));
        }
    }
}

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
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
