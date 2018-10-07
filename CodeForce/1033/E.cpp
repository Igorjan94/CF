// Igorjan94, template version from 13 October 2017. C++17 version, modified 07 August 2018 (&&, whole) {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

typedef vector<long long> vll;
typedef  pair<int, int>   pii;
typedef  valarray<int>    va;
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
const ll LLMAX = numeric_limits<ll>::max();

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//}}}

map<vector<int>, int> cache;

int query(vector<int>& a)
{
    sort(whole(a));
    if (a.size() <= 1)
        return 0;
    if (cache.find(a) != cache.end())
        return cache[a];
    writeln('?', a.size());
    writeln(a);
    cout.flush();
    ints(x);
    if (x == -1)
        exit(1);
    cache[a] = x;
    return x;
}

int dist(vector<int>& a, vector<int>& b)
{
    //writeln("Finding count of edges between", a, "and", b);
    vector<int> c(b);
    for (int& x: a)
        c.pb(x);
    return query(c) - query(a) - query(b);
}

pair<int, int> getEdge(vector<int>& a, vector<int>& b)
{
    //writeln("Finding edge between sets", a, "and", b);
    int n = a.size();
    int m = b.size();
    if (n > 1)
    {
        vector<int> x1, x2;
        fori(n)
            (i % 2 == 0 ? x1 : x2).pb(a[i]);
        //writeln("Dividing a into", x1, "and", x2);
        return getEdge(dist(x1, b) ? x1 : x2, b);
    }
    if (m > 1)
    {
        vector<int> y1, y2;
        fori(m)
            (i % 2 == 0 ? y1 : y2).pb(b[i]);
        //writeln("Dividing b into", y1, "and", y2);
        return getEdge(a, dist(y1, a) ? y1 : y2);
    }
    //writeln("Found edge", a[0], "->", b[0]);
    return {a[0], b[0]};
}

pair<int, int> getEdge2(vector<int>& a)
{
    //writeln("Finding edge in", a);
    int n = a.size();
    if (n > 2)
    {
        vector<int> x1, x2;
        fori(n)
            (i % 2 == 0 ? x1 : x2).pb(a[i]);
        //writeln("Dividing a into", x1, "and", x2);
        int x1s = query(x1);
        int x2s = query(x2);
        if (x1s + x2s == 0)
            return getEdge(x1, x2);
        return getEdge2(x1s ? x1 : x2);
    }
    //writeln("Found edge", a[0], "->", a[1]);
    return {a[0], a[1]};
}

void run()
{
    ints(n);
    if (n == 1)
    {
        writeln('Y', 1);
        writeln(1);
    }
    vector<int> left(1, 1);
    vector<int> right;
    for (int i = 2; i <= n; ++i)
        right.pb(i);

    vector<vector<int>> edges(n + 1);
    while (right.size())
    {
        auto [f, t] = getEdge(left, right);
        edges[f].pb(t);
        edges[t].pb(f);
        left.pb(t);
        right.erase(lower_bound(whole(right), t));
    }
    left.clear();
    right.clear();
    function<void(int, int, int)> dfs = [&](int u, int p, int depth) {
        (depth % 2 == 0 ? left : right).pb(u);
        for (int& x : edges[u])
            if (x != p)
                dfs(x, u, depth + 1);
    };
    dfs(1, -1, 0);
    int ls = query(left);
    int rs = query(right);
    if (ls + rs == 0)
    {
        writeln('Y', left.size());
        writeln(left);
        return;
    }
    auto [f, t] = getEdge2(ls ? left : right);
    edges[f].pb(t);
    edges[t].pb(f);
    vector<int> used(n + 1, 0);
    vector<int> ans;
    int found = 0;
    function<void(int, int, int)> dfs2 = [&](int u, int p, int depth) {
        if (used[u])
            found = used[u];
        if (found)
            return;
        used[u] = depth;
        ans.pb(u);
        for (int& x : edges[u])
            if (x != p)
            {
                dfs2(x, u, depth + 1);
                if (found) return;
            }
        ans.pop_back();
    };
    dfs2(1, -1, 0);
    fori(found) ans.erase(ans.begin());
    writeln('N', ans.size());
    writeln(ans);
}

//{{{
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
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&& a){cout<<" "<<a;}
ttti void priws(T&& a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
