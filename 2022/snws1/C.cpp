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
//}}}

void run()
{
    ints(n);
    vi a(n), p(n);
    readln(a, p);
    vector<ll> sums(n + 1);
    fori(n)
        sums[i + 1] = sums[i] + a[i];
    set<int> l, r;
    auto sum = [&](int l, int r) { //[l, r], 0
        ll temp = sums[r + 1] - sums[l];
        if (temp % 10 != 0)
            temp += 10 - temp % 10;
        return temp;
    }; 
    auto alive = [&](int x) {
        if (x < 0 || x >= n)
            return false;
        return r.count(x) == 0;
    };
    ll ans = sum(0, n - 1);
    ll cur = ans;
    ll count = 1;
    for (int i : p)
    {
        --i;
        auto lit = l.lower_bound(-i);
        auto rit = r.lower_bound(i);

        int left = lit == l.end() ? 0 : (-*lit + 1);
        int right = rit == r.end() ? n - 1 : (*rit - 1);
        l.insert(-i);
        r.insert(i);
        cur -= sum(left, right);
        cur += sum(left, i - 1);
        cur += sum(i + 1, right);
        bool leftAlive = alive(i - 1);
        bool rightAlive = alive(i + 1);
        if (leftAlive && rightAlive)
            count++;
        if (!leftAlive && !rightAlive)
            count--;
        ans = max(ans, cur * count);
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