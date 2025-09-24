// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <algorithm>
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
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}

void run()
{
    ints(n);
    vector<int> a(n);
    iota(all(a), 1);

    vector<int> q(2 * n - 1);
    iota(all(q), 1);
    shuffle(all(q), rng);
    auto ask = [&](int x, int l, int r) {
        vector<int> w;
        FOR(i, l, r + 1) w.push_back(q[i - 1]);
        writeln("?", x, w.size(), w);
        cout.flush();
        ints(s);
        if (s == -1)
            exit(1);
        return s;
    };

    int times = 0;
    auto solve = [&](auto solve, int l, int r, const vector<int>& inside, const vector<int>& both) -> void {
        if (++times == 2) {
            for (int x: inside) {
                int L = l;
                int R = r;
                while (L != R) {
                    int m = (L + R) / 2;
                    if (!ask(x, L, m))
                        L = m + 1;
                    else if (!ask(x, m + 1, R))
                        R = m;
                    else
                        break;
                }
                if (L == R) {
                    writeln("!", x);
                    return;
                }

            }
        }
        if (inside.size() == 1) {
            writeln("!", inside[0]);
            return;
        }

        int m = (l + r) / 2;
        vector<int> L, R, BL, BR;
        for (int x: both) 
            (ask(x, l, m) ? BL : BR).pb(x);
        for (int x: inside) {
            int qs = ask(x, l, m);
            if (qs == 0)
                R.pb(x);
            else {
                int qt = ask(x, m + 1, r);
                if (qt)
                    BL.pb(x),
                    BR.pb(x);
                else 
                    L.pb(x);
            }
        }
        int ll = m - l + 1;
        int cl = BL.size() + L.size() * 2;
        if (cl == ll)
            solve(solve, m + 1, r, R, BR);
        else
            solve(solve, l, m, L, BL);
    };
    solve(solve, 1, 2 * n - 1, a, {});
    cout.flush();
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
