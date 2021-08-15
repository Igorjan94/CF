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
//dsu
struct dsu
{
    vector<int> a, size;
    set<pii> comps;
    vector<vector<int>> v;

    dsu(int n)
    {
        a.resize(n);
        size.resize(n, 1);
        v.resize(n);
        fori(n)
            v[i].pb(i),
            comps.insert({1, i});
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
        comps.erase({size[i], i});
        comps.erase({size[j], j});
        size[j] += size[i];
        for (int x: v[i])
            v[j].pb(x);
        v[i] = vector<int>();
        comps.insert({size[j], j});
    }
};

//}}}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void run()
{
    ints(n, m1, m2);
    dsu c(n);
    dsu d(n);
    fori(m1)
    {
        ints(u, v); --u; --v;
        c.uni(u, v);
    }
    fori(m2)
    {
        ints(u, v); --u; --v;
        d.uni(u, v);
    }
    vector<pii> ans;
    vector<int> p(n);
    iota(all(p), 0);
    shuffle(all(p), rng);

    while (SZ(c.comps) >= 2 && SZ(d.comps) >= 2)
    {
        auto [sz, i] = *c.comps.begin();
        for (int u: c.v[i])
            for (int j: p)
                if (c[u] != c[j] && d[u] != d[j])
                {
                    c.uni(u, j);
                    d.uni(u, j);
                    ans.pb({u + 1, j + 1});
                    goto found;
                }
        break;
found:
        42;
    }
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
