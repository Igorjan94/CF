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
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}

int p = 500;

void run()
{
    ints(n, q);
    vi a(n);
    readln(a);
    vector<array<int, 4>> requests(q);
    fori(q)
        readln(requests[i][0], requests[i][1], requests[i][2]),
        requests[i][3] = i;
    sort(all(requests), [&](const auto& a, const auto& b) {
        int sign = (a[0] / p) % 2 == 0 ? 1 : -1;
        return tuple(a[0] / p, a[1] * sign) < tuple(b[0] / p, b[1] * sign);
    });

    vector<int> counts(n + 1, 0);
    auto add = [&](int x) {
        ++counts[a[x]];
    };
    auto del = [&](int x) {
        --counts[a[x]];
    };
    auto addLeft = add;
    auto addRight = add;
    auto delLeft = del;
    auto delRight = del;

    int L = 0;
    int R = -1;
    vector<int> ans(q, 0);
    for (auto& [l, r, k, id]: requests) {
        --l;--r;
        while (L > l) addLeft(--L);
        while (R < r) addRight(++R);
        while (L < l) delLeft(L++);
        while (R > r) delRight(R--);
        int mn = MOD;
        forn(_, 100)
        {
            int length = r - l + 1;
            int index = rng() % length + l;
            if (counts[a[index]] * k > length)
                mn = min(mn, a[index]);
        }
        ans[id] = mn == MOD ? -1 : mn;
    }

    fori(q)
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
