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
//umin
template<typename T1, typename T2>
T1 umin(T1& a, T2 b)
{
    return a > T2(b) ? a = b : a;
}

//}}}

void run()
{
    ints(n, c);
    vector<int> po, pz, nz, no;
    fori(n)
    {
        ints(x, t);
        if (x > 0)
            (t == 0 ? pz : po).pb(x);
        else
            (t == 0 ? nz : no).pb(-x);
    }
    auto solve = [&](vector<int>& zeros, vector<int>& ones) {
        sort(all(zeros));
        sort(all(ones));
        int n = zeros.size();
        int m = ones.size();
        const ll INF = numeric_limits<ll>::max();
        vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, INF));
        dp[n][m] = 0;
        for (int i = n; i >= 0; --i)
            for (int j = m; j >= 0; --j)
                if (dp[i][j] != INF)
                {
                    ll zero = 0;
                    ll one = 0;
                    if (i)
                    {
                        zero = zeros[i - 1];
                        umin(dp[i - 1][j], dp[i][j] + 2 * zero);
                    }
                    if (j)
                    {
                        one = ones[j - 1];
                        umin(dp[i][j - 1], dp[i][j] + 2 * one);
                    }
                    if (i >= 2)
                        umin(dp[i - 2][j], dp[i][j] + 2 * zero + c);
                    if (j >= 2)
                        umin(dp[i][j - 2], dp[i][j] + 2 * one + c);
                    if (i && j)
                        umin(dp[i - 1][j - 1], dp[i][j] + 2 * max(zero, one));
                }

        return dp[0][0];
    };
    writeln(solve(pz, po) + solve(nz, no));
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t);
    fori(t)
        cout << "Case #" << (i + 1) << ": ",
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
