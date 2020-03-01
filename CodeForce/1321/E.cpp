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
    vector<T> add;
 
    void build(vector<T>& a, int v, int l, int r)
    {
        if (l == r)
            t[v] = a[l];
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            t[v] = max(t[v * 2], t[v * 2 + 1]);
        }
    };
 
    segmentTree(vector<T>& a)
    {
        n = a.size();
        t.resize(n * 4 + 10);
        add.resize(n * 4 + 10, 0);
        build(a, 1, 0, n - 1);
    }
 
    void update(int l, int r, T value)
    {
        update(1, 0, n - 1, l, r, value);
    }
 
    void update(int v, int tl, int tr, int l, int r, T value) 
    {
        if (add[v] != 0)
        {
            t[v] += add[v];
            if (tl != tr)
                add[v * 2] += add[v],
                add[v * 2 + 1] += add[v];
            add[v] = 0;
        }
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
            t[v] = max(t[v * 2], t[v * 2 + 1]);
        }
    }
};
 
//}}}
 
struct enemy {
    enemy() {}
    int x, y;
    ll z;
    friend istream& operator>>(istream& is, enemy& e) {
        return is >> e.x >> e.y >> e.z;
    }
    friend ostream& operator<<(ostream& os, const enemy& e) {
        return os << e.x << " " << e.y << " " << e.z;
    }
};
 
void run()
{
    ints(n, m, p);
    vector<pii> a(n), b(m);
    vector<enemy> e(p);
    readln(a, b, e);
    sort(whole(b));
    map<int, int> collapse;
    for (auto [x, y]: b)
        if (collapse.find(x) == collapse.end())
            collapse[x] = y;
        else
            collapse[x] = min(collapse[x], y);
    map<int, int> coords;
    int q = 0;
    m = SZ(collapse);
    vector<ll> v(m);
    for (auto [x, y]: collapse)
        v[q] = -y,
        coords[x] = q++;
 
    ll ans = numeric_limits<ll>::min();
    {
        sort(whole(e), [](const enemy& x, const enemy& y) { return tuple(x.x, x.y, x.z) < tuple(y.x, y.y, y.z);} );
        sort(whole(a));
        segmentTree<ll> s(v);
        int j = 0;
 
        for (auto& [damage, cost]: a) 
        {
            while (j < p && damage > e[j].x)
            {
                int c = coords.upper_bound(e[j].y)->second;
                s.update(c, m - 1, e[j].z);
                ++j;
            }
            ans = max(ans, s.t[1] - cost);
        }
    }
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
