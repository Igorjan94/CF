// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (long long i = 0; i < (long long) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    (long long)(size(a))

typedef  pair<int, int>   pii;
typedef   vector<int>     vi;
typedef    long long      ll;

#define pb push_back
#define all(a) begin(a), end(a)
#define ints(a...) int a; readln(a)
#define int long long

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
    auto ask = [&](int x) {
        writeln(x);
        cout.flush();
        ints(ans);
        return ans;
    };
    auto toK = [&](int x) {
        vector<int> ans;
        while (x > 0)
            ans.pb(x % k),
            x /= k;
        return ans;
    };
    auto toDec = [&](vector<int>& ans) {
        int x = 0;
        reverse(all(ans));
        fori(SZ(ans))
            x = x * k + ans[i];
        return x;
    };

    auto calcXor = [&](int x, int y) {
        vector<int> X = toK(x);
        vector<int> Y = toK(y);
        while (X.size() < Y.size())
            X.pb(0);
        while (X.size() > Y.size())
            Y.pb(0);
        fori(SZ(X))
            X[i] = (X[i] + Y[i]) % k;
        return toDec(X);
    };
    auto invert = [&](int x) {
        vector<int> X = toK(x);
        fori(SZ(X))
            X[i] = (k - X[i]) % k;
        return toDec(X);
    };
    fori(n)
    {
        int sum = 0;
        if (i % 2 == 0)
            sum = calcXor(i, i == 0 ? 0 : invert(i - 1));
        else
            sum = calcXor(invert(i), i - 1);

        int ans = ask(sum);
        if (ans) return;
    }
    exit(1);
}

//{{{
int32_t main()
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
