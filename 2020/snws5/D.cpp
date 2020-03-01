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
    vector<vector<T>> t, prefix;
    vector<T> mx, pos;

    void build(vector<T>& a, int v, int l, int r)
    {
        if (l == r)
            t[v] = {a[l]},
            prefix[v].pb(a[l]);
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            merge(t[v * 2].begin(), t[v * 2].end(), t[v * 2 + 1].begin(), t[v * 2 + 1].end(), back_inserter(t[v]));
            for (T& x: t[v]) prefix[v].pb(prefix[v].back() + x);
        }
    };

    segmentTree(vector<T>& a)
    {
        n = a.size();
        t.resize(n * 4);
        prefix.resize(n * 4, vector<T>(1, 0));
        mx.resize(n * 4);
        pos.resize(n * 4);
        build(a, 1, 0, n - 1);
    }

    T get(int l, int r, T x)
    {
        return get(1, 0, n - 1, l, r, 0, x);
    }

    T get(int v, int tl, int tr, int l, int r, int curmx, T x) {
        curmx += mx[v];
        if (l > r)
            return 0;
        if (l == tl && tr == r) {
            int new_pos = upper_bound(t[v].begin() + pos[v], t[v].end(), x - curmx) - t[v].begin();
            T s = (SZ(t[v]) - new_pos) * x;
            T p = prefix[v][new_pos] - prefix[v][pos[v]];
            p += curmx * (new_pos - pos[v]);
            s += pos[v] * min(x, curmx);
            pos[v] = new_pos;
            mx[v] -= x;
            wr(l, r, p, s, curmx, x);
            writeln();
            return s + p;
        }
        int tm = (tl + tr) / 2;
        return get(v * 2, tl, tm, l, min(r, tm), curmx, x) + get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, curmx, x);
    }

    void update(int l, int r, T value)
    {
        update(1, 0, n - 1, l, r, value);
    }

    void update(int v, int tl, int tr, int l, int r, T add) {
        if (l > r)
            return;
        if (l == tl && tr == r)
            mx[v] += add;
        else {
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), add);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, add);
        }
    }
};

//}}}

void run()
{
    ints(n);
    vi a(n);
    readln(a);
    segmentTree<int> s(a);

    writeln();
    fori1(n * 2)
        writeln(i, s.t[i]);

    ints(q);
    forn(_, q)
    {
        ints(t, i, j, k);
        --i;
        --j;
        if (t == 1)
        {
            s.update(i, j, k);
            FOR(w, i, j + 1)
                a[w] += k;
        }
        else
        {
            int sum = 0;
            FOR(w, i, j + 1)
            {
                sum += min(a[w], k);
                a[w] = max(0, a[w] - k);
            }
            wr(sum);
            writeln(s.get(i, j, k));
        }
        writeln(a);
    }
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
