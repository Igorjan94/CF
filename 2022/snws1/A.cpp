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
template<typename T, typename F>
T binSearch(T l, T r, F f, T eps = 1)
{
    T m;
    while (abs(r - l) > eps)
        m = midpoint(l, r),
        (f(m) ? l : r) = m;
    return f(r) ? r : l;
}

//}}}

void run()
{
    ints(n, q);
    vector<ll> s(n);
    readln(s);

    forn(Q, q)
    {
        ints(a, b, c, d); --a; --b; --c; --d;
        if (c < a) swap(a, c), swap(b, d);

        int count = b - a + d - c + 2;
        ll left = s[a];
        ll right = s[c];
        bool eq = true;
        if (c > b)
        {
            auto getByIndex = [&](int i) {
                if (a + i <= b)
                    return s[a + i];
                else
                    return s[c + i - (b - a + 1)];
            };
            left = getByIndex((count - 1) / 2);
            right = getByIndex(count / 2);
        }
        else
        {
            auto bs = [&](int i) {
                int A = clamp(i - a + 1, 0, b - a + 1);
                int B = b - a + 1 - A;
                int C = clamp(i - c + 1, 0, d - c + 1);
                int D = d - c + 1 - C;
                if (A + C <= B + D)
                {
                    left = s[i];
                    ll temp1 = B > 0 ? s[i + 1] : numeric_limits<ll>::max();
                    ll temp2 = D > 0 ? s[C + c] : numeric_limits<ll>::max();
                    right = min(temp1, temp2);
                    eq = A + C == B + D;
                    return true;
                }
                return false;
            };
            ll m = binSearch<ll>(a, max(b, d), bs);
            bs(m);
        }
        if (count % 2 == 0 && eq)
        {
            ll ans = left + right;
            cout << ans / 2;
            if (ans % 2)
                cout << ".5";
            cout << "\n";
        }
        else
            writeln(right);
    }
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
