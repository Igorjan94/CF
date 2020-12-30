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
//umin
template<typename T1, typename T2>
T1 umin(T1& a, T2 b)
{
    return a > T2(b) ? a = b : a;
}

//}}}

void run()
{
    ints(n, k);
    vi a(n);
    readln(a);
    if (k == 1) return writeln(0);
    auto get = [&](const vector<int>& a, int mul) {
        map<int, set<pair<int, ll>>> ans;
        multiset<int> s(all(a));
        ans[*s.begin() * mul].insert({1, 0});
        ll cnt = 1;
        ll cur = 0;
        auto take = [&]() {
            int x = *s.begin();
            s.erase(s.begin());
            return x;
        };
        fori1(n)
        {
            int x = take();
            int y = *s.begin();
            cur += cnt++ * (y - x);
            ans[mul * y].insert({i + 1, cur});
        }
        return ans;
    };
    auto ans1 = get(a, 1);
    for (int& y: a) y *= -1;
    auto ans2 = get(a, -1);
    ll ans = numeric_limits<ll>::max();
    for (auto& [key, value]: ans1)
        for (auto& [c1, x1]: value)
            if (c1 == k)
                umin(ans, x1);
    for (auto& [key, value]: ans2)
        for (auto& [c1, x1]: value)
            if (c1 == k)
                umin(ans, x1);
    auto update = [&](const auto& ans1, const auto& ans2) {
        for (auto& [key, value]: ans1)
        {
            auto& [c1, x1] = *value.rbegin();
            auto other = ans2.upper_bound(key);
            if (other == ans2.end())
                continue;
            auto& [key2, value2] = *other;
            auto& [c2, x2] = *value2.rbegin();
            ll diff = key2 - key;
            ll temp = x1 + x2 + (diff - 1) * c2 + (k - c1);
            umin(ans, temp);
        }
    };
    update(ans1, ans2);
    update(ans2, ans1);
    //writeln(ans1);
    //writeln(ans2);
    writeln(max(0ll, ans));
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
