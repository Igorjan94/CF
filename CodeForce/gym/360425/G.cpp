// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

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
    ints(n, k);
    vector<array<int, 4>> a(n), b(n);
    fori(n)
        readln(a[i][0], a[i][1], a[i][2]),
        a[i][3] = i,
        b[i][3] = i,
        b[i][1] = a[i][0],
        b[i][0] = a[i][1],
        b[i][2] = a[i][2];
    set<array<int, 4>> s(all(a));
    set<array<int, 4>> t(all(b));
    vector<int> ans(n, -1);
    vector<int> comps;
    fori(n)
        if (ans[i] == -1)
        {
            vector<int> c;
            int mn = MOD;
            function<void(int)> dfs = [&](int u) {
                mn = min(mn, a[u][2]);
                ans[u] = 1;
                s.erase(a[u]);
                t.erase(b[u]);
                auto right = s.lower_bound(a[u]);
                if (right != s.end())
                    if ((*right)[0] == a[u][0] && (*right)[1] - a[u][1] <= k)
                        dfs((*right)[3]);
                auto left = s.lower_bound({a[u][0], a[u][1] - k, 0, 0});
                if (left != s.end())
                    if ((*left)[0] == a[u][0] && (*left)[1] < a[u][1])
                        dfs((*left)[3]);

                auto up = t.lower_bound(b[u]);
                if (up != t.end())
                    if ((*up)[0] == b[u][0] && (*up)[1] - b[u][1] <= k)
                        dfs((*up)[3]);
                auto down = t.lower_bound({b[u][0], b[u][1] - k, 0, 0});
                if (down != t.end())
                    if ((*down)[0] == b[u][0] && (*down)[1] < b[u][1])
                        dfs((*down)[3]);
            };
            dfs(i);
            comps.pb(mn);
        }
    sort(all(comps));
    reverse(all(comps));
    fori(comps.size())
        if (i + 1 == comps.size() || comps[i + 1] <= i)
            return writeln(i);
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
