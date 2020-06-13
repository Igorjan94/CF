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
    ints(n, m, k);
    int c = (k + 1) / 2;
    vector<vector<int>> g(n);
    fori(m)
    {
        ints(u, v); --u; --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<int> used(n, 0);
    vector<int> parent(n, -1);
    vector<int> l[2];
    function<void(int, int, int)> dfs = [&](int u, int p, int d) {
        l[d % 2].pb(u + 1);
        used[u] = 1;
        for (int v: g[u])
            if (used[v] == 0) {
                parent[v] = u;
                dfs(v, u, d + 1);
            }
            else if (used[v] == 1 && v != p) {
                vector<int> ans;
                while (v != u)
                    ans.pb(u),
                    u = parent[u];
                ans.pb(u);
                reverse(all(ans));

                vector<int> d(n, -1);
                fori(ans.size())
                    d[ans[i]] = i;
                vector<int> ans2;
                int sz = ans.size();
                for (int i = 0; i < sz; )
                {
                    int u = ans[i];
                    ans2.pb(u);
                    int mx = -1;
                    for (int v: g[u])
                        if (d[v] != -1 && d[v] != (d[u] + sz - 1) % sz && d[v] != (d[u] + 1) % sz)
                            if (d[v] > mx)
                                mx = d[v];
                    if (mx > i)
                        i = mx;
                    else
                        ++i;
                }
                for (int& u: ans2) ++u;
                if (SZ(ans2) <= k)
                    writeln(2),
                    writeln(ans2.size()),
                    writeln(ans2);
                else
                {
                    vector<int> ans3;
                    for (int i = 0; i < SZ(ans2) && SZ(ans3) < c; i += 2)
                        ans3.pb(ans2[i]);
                    writeln(1);
                    writeln(ans3);
                }
                exit(0);
            }
        used[u] = 2;
    };
    dfs(0, -1, 0);
    fori(2)
        if (SZ(l[i]) >= c)
        {
            l[i].resize(c);
            writeln(1);
            writeln(l[i]);
            return;
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
