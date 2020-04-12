// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <numeric>
#include <iomanip>

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
//umax
template<typename T1, typename T2>
T1 umax(T1& a, T2 b)
{
    return a < T2(b) ? a = b : a;
}

//}}}

void run()
{
    ints(n);
    vi a(n);
    readln(a);
    ll r = 0;
    for (int i = n - 1; i >= 0; i -= 2)
        r += a[i];
    static const ll MN = numeric_limits<ll>::min();
    ll ans = MN;
    if (n % 2 == 0)
    {
        ans = r;
        for (int i = 0; i < n; i += 2)
            r += a[i] - a[i + 1],
            umax(ans, r);
    }
    else
    {
        for (int i = 0; i < n; i += 2)
            umax(ans, r - a[i]);
        vector<vector<ll>> dp(n, vector<ll>(3, MN));
        dp[0][0] = a[0];
        dp[1][0] = a[1];
        dp[2][0] = a[0] + a[2];
        dp[2][1] = a[2];
        for (int i = 3; i < n; ++i)
        {
            forj(3)
                if (dp[i - 2][j] != MN)
                    umax(dp[i][j], dp[i - 2][j] + a[i]);
            forj(2)
                if (dp[i - 3][j] != MN)
                    umax(dp[i][j + 1], a[i] + dp[i - 3][j]);
        }
        umax(ans, dp[n - 2][0]);
        umax(ans, dp[n - 2][1]);
        umax(ans, dp[n - 1][1]);
        umax(ans, dp[n - 1][2]);
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
