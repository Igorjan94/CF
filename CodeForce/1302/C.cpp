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
//segmentTree
//0-indexed, [l..r]
template<typename T>
struct segmentTree
{
    int n;
    vector<T> t;
    typedef function<T (T, T)> F;
    F f;
    T NEITRAL_ELEMENT;

    void build(const vector<T>& a, int v, int l, int r)
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

    segmentTree(const vector<T>& a, F g, T ne = 0)
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

//}}}
segmentTree<ll> s(vector<ll>(100001, 0), [](const ll &a, const ll& b) { return a + b; });

void run()
{
    int n, q;
    scanf("%d%d", &n, &q);
    fori(q)
    {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 1)
            s.update(--x, y);
        else
            printf("%lld\n", s.get(--x, --y));
    }
}

//{{{
int main()
{
    //ios_base::sync_with_stdio(false);
    ints(t); fori(t) run();
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
