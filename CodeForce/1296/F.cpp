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
//}}}

void run()
{
    ints(n);
    vector<vector<pii>> g(n);
    vector<int> ans(n - 1);
    vector<int> h(n);
    vector<pii> back(n);
    fori(n - 1)
    {
        ints(u, v);
        g[--u].pb({--v, i});
        g[v].pb({u, i});
    }
    function<void(int, int, int)> relabel = [&](int u, int d, int p = -1) {
        h[u] = d;
        for (auto [v, i]: g[u])
            if (v != p)
                relabel(v, d + 1, u);
            else
                back[u] = {v, i};
    };
    relabel(0, 0, -1);

    ints(q);
    vector<int> pass(q);
    function<void(int, int, int, int)> setBeauty = [&](int u, int v, int value, int p) {
        if (u == v) return;
        if (h[u] < h[v])
            swap(u, v);
        auto [to, i] = back[u];
        if (ans[i] == 0 || ans[i] == value)
            ans[i] = value,
            pass[p]++;
        setBeauty(v, to, value, p);
    };
    vector<tuple<int, int, int, int>> r;
    fori(q)
    {
        ints(u, v, w);
        --u; --v;
        r.emplace_back(-w, u, v, i);
    }
    sort(whole(r));
    for (auto [w, u, v, i]: r)
        setBeauty(u, v, -w, i);
    for (int x: pass)
        if (x == 0)
            return writeln(-1);
    for (int& x: ans) if (x == 0) ++x;
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
