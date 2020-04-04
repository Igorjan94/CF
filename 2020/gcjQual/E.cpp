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
    ints(n, k);
    if (k == n * n - 1 || k == n + 1 || (set<int>({5, 7}).count(k) && n == 3))
        return writeln("IMPOSSIBLE");
    writeln("POSSIBLE");
    vector<vector<int>> A(n, vector<int>(n));
    set<int> q;
    fori1(n + 1) q.insert(i);
    int a, b, c, d, e;
    FOR(X, 1, n + 1)
        FOR(Y, 1, n + 1)
            if (2 * X + (n - 2) * Y == k && X != Y)
                a = X, b = Y;
    q.erase(a);
    q.erase(b);
    if (n >= 3)
        c = *q.begin(), q.erase(q.begin());
    if (n >= 4)
        d = *q.begin(), q.erase(q.begin());
    if (n >= 5)
        e = *q.begin(), q.erase(q.begin());
    if (k % n == 0)
        fori(n) forj(n) A[i][(i + j - k / n + n + 1) % n] = j + 1;
    else if (n == 4)
    {
        if (k % 2 == 0)
            A = {
                {a, b, c, d},
                {b, a, d, c},
                {c, d, b, a},
                {d, c, a, b}
            };
        else if (k == 7)
            A = {
                {1, 3, 4, 2},
                {2, 1, 3, 4},
                {3, 4, 2, 1},
                {4, 2, 1, 3}
            };
        else if (k == 9)
            A = {
                {3, 1, 4, 2},
                {2, 3, 1, 4},
                {1, 4, 2, 3},
                {4, 2, 3, 1}
            };
        else if (k == 11)
            A = {
                {4, 1, 3, 2},
                {2, 4, 1, 3},
                {1, 3, 2, 4},
                {3, 2, 4, 1}
            };
        else if (k == 13)
            A = {
                {4, 3, 1, 2},
                {2, 4, 3, 1},
                {3, 1, 2, 4},
                {1, 2, 4, 3}
            };
    }
    else if (n == 5)
    {
        A = {
            {a, b, c, d, e},
            {b, a, e, c, d},
            {e, d, b, a, c},
            {c, e, d, b, a},
            {d, c, a, e, b}
        };
    }
    writeln(A);
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
