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

int p = 2000;

void run()
{
    ints(n, m, k);
    vi a(n);
    readln(a);
    vector<array<int, 3>> requests(m);
    fori(m)
        readln(requests[i][0], requests[i][1]),
        requests[i][2] = i;
    sort(all(requests), [&](const auto& a, const auto& b) {
        int sign = (a[0] / p) % 2 == 0 ? 1 : -1;
        return tuple(a[0] / p, a[1] * sign) < tuple(b[0] / p, b[1] * sign);
    });

    vector<int> sums(1, 0);
    fori(n)
        sums.pb(sums.back() ^ a[i]);
    vector<int> left(1 << 20, 0);
    vector<int> right(1 << 20, 0);
    ll answer = 0;
    auto addLeft = [&](int x) {
        ++left[sums[x]];
        ++right[sums[x + 1]];
        answer += right[k ^ sums[x]];
    };
    auto addRight = [&](int x) {
        ++left[sums[x]];
        ++right[sums[x + 1]];
        answer += left[k ^ sums[x + 1]];
    };
    auto delLeft = [&](int x) {
        answer -= right[k ^ sums[x]];
        --left[sums[x]];
        --right[sums[x + 1]];
    };
    auto delRight = [&](int x) {
        answer -= left[k ^ sums[x + 1]];
        --left[sums[x]];
        --right[sums[x + 1]];
    };


    int L = 0;
    int R = -1;
    vector<ll> ans(m, 0);
    for (auto& [l, r, id]: requests) {
        --l;--r;
        while (L > l) addLeft(--L);
        while (R < r) addRight(++R);
        while (L < l) delLeft(L++);
        while (R > r) delRight(R--);
        ans[id] = answer;
    }

    fori(m)
        writeln(ans[i]);
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
