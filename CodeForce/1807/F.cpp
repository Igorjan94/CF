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
//binSearch
//x \in [l, r]-> min, f(x) == true
// l                           r
// 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1
//                 ^
template<typename T, typename F>
T binSearch(T l, T r, F f)
{
    T m;
    while (l < r)
    {
        m = (r + l + 1) / 2;
        if (f(m))
            r = m - 1;
        else
            l = m;
    }
    return l;
}

//}}}

int sign(int x) {
    return x > 0 ? 1 : -1;
}

void run()
{
    ints(n, m, a, b, x, y);
    string s;
    readln(s);
    if (a == x && b == y)
        return writeln(0);

    int dx = s[0] == 'U' ? -1 : 1;
    int dy = s[1] == 'L' ? -1 : 1;
    set<tuple<int, int, int, int>> was;
    int ans = 0;
    while (true)
    {
        int da = x - a;
        int db = y - b;
        if (abs(da) == abs(db) && sign(da) == sign(dx) && sign(db) == sign(dy))
            return writeln(ans);

        int step = binSearch(0, 25001, [&](int cnt) {
            int na = a + dx * cnt;
            int nb = b + dy * cnt;
            return na < 1 || na > n || nb < 1 || nb > m;
        });
        a += dx * step;
        b += dy * step;
        if (was.contains({a, b, dx, dy}))
            break;
        was.insert({a, b, dx, dy});
        if (a == 1 || a == n)
            dx *= -1;
        if (b == 1 || b == m)
            dy *= -1;
        if (a == 1 && b == 1)
            dx = 1, dy = 1;
        if (a == 1 && b == m)
            dx = 1, dy = -1;
        if (a == n && b == 1)
            dx = -1, dy = 1;
        if (a == n && b == m)
            dx = -1, dy = -1;
        ++ans;
    }
    writeln(-1);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
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