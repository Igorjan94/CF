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
    int mx = n * n * 2;
    vector<int> primes = {2, 3, 5, 7, 11, 13};
    map<int, vector<int>> m;
    set<pii> s = {{1, 0}};
    while (s.size())
    {
        auto [x, mask] = *s.begin();
        s.erase(s.begin());
        m[mask].pb(x);
        fori(primes.size())
            if (x * 1LL * primes[i] <= mx)
                s.insert({x * primes[i], mask | (1 << i)});
    }
    set<array<int, 3>> ans;
    int N = (n + 1) / 2;

    vector<int> cnt(SZ(primes));
    for (auto& [mask, v]: m)
    {
        int pop = __builtin_popcount(mask);
        for (int x: v)
            if (SZ(ans) < n)
            {
                ans.insert({pop, mask, x});
                fori(SZ(primes))
                    if (mask & (1 << i))
                        cnt[i]++;
            }
            else
            {
                bool ok = true;
                fori(primes.size())
                    ok &= cnt[i] >= N || cnt[i] == 0;
                if (ok)
                {
                    vector<int> aa;
                    for (auto& [_, __, x]: ans)
                        aa.pb(x);
                    writeln(aa);
                    return;
                }
                else
                {
                    auto [_, mask, __] = *ans.begin();
                    fori(SZ(primes))
                        if (mask & (1 << i))
                            cnt[i]--;
                    ans.erase(ans.begin());
                }
            }
    }
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
