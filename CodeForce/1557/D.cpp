// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
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

#define pb push_back
#define all(a) begin(a), end(a)
#define ints(a...) int a; readln(a)

[[maybe_unused]] const int MOD = 1000000007;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

#define ttt12i template<class T1, class T2> inline
#define  ttti  template<class T> inline

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

//Igorjan
//}}}

struct segment
{
    int i;
    int l;
    int type;
    segment(int i, int l, int type): i(i), l(l), type(type) {}

    bool operator<(const segment& other) const {
        return tuple(l, type, i) < tuple(other.l, other.type, other.i);
    }
};

void run()
{
    ints(n, m);
    vector<segment> a;
    forn(q, m)
    {
        ints(i, l, r);
        a.pb({i, l, -1});
        a.pb({i, r, 1});
    }
    sort(all(a));

    vector<set<int>> g(n + 2);
    auto addEdge = [&](int u, int v) {
        //writeln("ADD", u, v);
        g[u].insert(v);
    };
    fori1(n + 1)
        addEdge(0, i),
        addEdge(i, n + 1);

    map<int, int> cur;
    map<int, int> curi;
    for (auto& [i, l, type]: a)
    {
        if (type == -1) //ADD
        {
            if (++cur[i] != 1)
                continue;
            curi[-i]++;
            auto it = cur.upper_bound(i);
            if (it != cur.end())
                addEdge(i, it->first);
            auto it2 = curi.upper_bound(-i);
            if (it2 != curi.end())
                addEdge(-it2->first, i);
        }
        else
        {
            if (--cur[i] != 0)
                continue;
            cur.erase(i);
            curi.erase(-i);
            auto it = cur.upper_bound(i);
            if (it != cur.end())
            {
                auto it2 = curi.upper_bound(-i);
                if (it2 != curi.end())
                    addEdge(-it2->first, it->first);
            }
        }
    }
    
    vector<int> d(n + 2, -1);
    vector<int> p(n + 2);

    for (int u = 0; u < n + 1; ++u)
        for (int v: g[u])
            if (d[v] < d[u] + 1)
                d[v] = d[u] + 1,
                p[v] = u;

    vector<int> used(n + 2);
    int w = n + 1;
    while (w != 0)
        used[w] = true,
        w = p[w];
    used[0] = true;

    vector<int> ans;
    fori(n + 2)
        if (!used[i])
            ans.pb(i);
    writeln(ans.size());
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
