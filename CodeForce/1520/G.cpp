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
    ll inf = numeric_limits<ll>::max();
    ints(n, m, w);
    vector<vector<int>> s(n, vector<int>(m));
    readln(s);
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    vector<vector<ll>> dp0(n, vector<ll>(m, inf));
    vector<vector<ll>> dp1(n, vector<ll>(m, inf));
    auto get = [&](vector<vector<ll>>& dp, int i, int j) {
        dp[i][j] = 0;
        queue<pii> q;
        q.push({i, j});
        ll best = inf;
        if (s[i][j]) best = s[i][j];
        while (q.size())
        {
            auto [i, j] = q.front();
            q.pop();
            forn(Q, 4)
            {
                int x = i + dx[Q];
                int y = j + dy[Q];
                if (x < 0 || x == n || y < 0 || y == m || s[x][y] == -1 || dp[x][y] != inf)
                    continue;
                dp[x][y] = dp[i][j] + w;
                if (s[x][y] && dp[x][y] + s[x][y] < best)
                    best = dp[x][y] + s[x][y];

                q.push({x, y});
            }
        }
        return best;
    };
    auto from = get(dp0, 0, 0);
    auto to = get(dp1, n - 1, m - 1);
    ll ans = dp1[0][0];
    if (from != inf && to != inf)
        ans = min(ans, from + to);
    if (ans == inf)
        writeln(-1);
    else
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
