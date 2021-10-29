// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#include <ranges>

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

namespace r = std::ranges;
namespace v = std::views;

void run()
{
    ints(n, m);
    vector<vector<int>> a(n, vector<int>(m));
    readln(a);
    vector<int> order(n);
    iota(all(order), 0);
    r::sort(order, [&](int x, int y) {
        return a[x] < a[y];
    });
    auto getMinimums = [&](vector<int> order) {
        vector<vector<int>> minPrefix(n, vector<int>(m, 0));
        vector<vector<int>> minSuffix(n, vector<int>(m, MOD));
        for (int prev = order[0]; int i: order)
        {
            minPrefix[i][0] = max(minPrefix[prev][0], a[i][0]);
            forj1(m)
                minPrefix[i][j] = max({minPrefix[prev][j], minPrefix[i][j - 1], a[i][j]});
            
            minSuffix[i][m - 1] = min(minSuffix[prev][m - 1], a[i][m - 1]);
            ROF(j, m - 2, 0)
                minSuffix[i][j] = min({minSuffix[prev][j], minSuffix[i][j + 1], a[i][j]});

            prev = i;
        }
        return pair(minPrefix, minSuffix);
    };
    auto [mp, ms] = getMinimums(order);
    r::reverse(order);
    fori(n) r::reverse(a[i]);
    auto [xs, xp] = getMinimums(order);
    r::reverse(order);
    fori(n) r::reverse(xp[i]);
    fori(n) r::reverse(xs[i]);

    string ans(n, 'R');
    for (int prev = order[0]; int i: order | v::drop(1))
    {
        ans[prev] = 'B';
        forj(m - 1)
            if (mp[prev][j] < xp[i][j] && ms[prev][j + 1] > xs[i][j + 1])
            {
                writeln("YES");
                writeln(ans, j + 1);
                return;
            }
        prev = i;
    }

    writeln("NO");
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
