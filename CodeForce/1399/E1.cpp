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

void run()
{
    int n;
    ll s;
    readln(n, s);
    vector<vector<tuple<int, int, int>>> edges(n);
    vector<int> leaves(n, 0);
    fori(n - 1)
    {
        ints(u, v, w); --u; --v; int p = 0;
        edges[u].emplace_back(v, w, p);
        edges[v].emplace_back(u, w, p);
    }
    vector<vector<ll>> c(2);
    ll sum = 0;
    function<int(int, int)> countLeaves = [&](int u, int p) {
        for (auto& [v, w, price]: edges[u])
            if (v != p)
            {
                leaves[u] += countLeaves(v, u);
                sum += w * 1ll * leaves[v];
                while (w)
                    c[price].pb((w - w / 2) * 1ll * leaves[v]),
                    w /= 2;
            }
        return leaves[u] = max(1, leaves[u]);
    };
    countLeaves(0, -1);
    vector<int> indices(2, 0);
    fori(2)
    {
        sort(all(c[i]));
        reverse(all(c[i]));
        while (sum > s && indices[i] < SZ(c[i]))
            sum -= c[i][indices[i]++];
    }
    int moves = indices[0] + indices[1] * 2;
    while (indices[0] > 0)
    {
        sum += c[0][--indices[0]];
        while (sum > s && indices[1] < SZ(c[1]))
            sum -= c[1][indices[1]++];
        if (sum > s)
            break;
        moves = min(moves, indices[0] + indices[1] * 2);
    }

    writeln(moves);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
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
