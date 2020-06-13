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
//cached
template<class T, class... Args>
struct cached
{
    function<T(Args...)> f;
    map<tuple<Args...>, T> m;

    cached(const function<T(Args...)>& f) : f(f) { }

    T operator()(Args... args) {
        auto x = tuple(forward<Args>(args)...);
        if (auto it = m.find(x); it != m.end())
            return it->second;
        return m[x] = f(forward<Args>(args)...);
    }
};

//}}}

void run()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ints(n);
    auto ask = cached<int, int, int>([&](int i, int j) -> int {
        if (i == j) return 2047;
        writeln("?", i + 1, j + 1);
        cout.flush();
        ints(x);
        return x;
    });
    auto f = [&](int i, int j) {
        return ask(min(i, j), max(i, j));
    };
    auto getAns = [&](int i) {
        vector<int> ans;
        forj(n)
            if (i != j)
                ans.pb(f(i, j));
            else
                ans.pb(0);
        writeln("!", ans);
        exit(0);
    };
    vector<pii> s;
    fori(n) s.emplace_back(12, i);
    int m = n;
    while (s.size() > 2)
    {
        cerr << s.size() << endl;
        vector<pii> t;
        int cur;
        while (true)
        {
            int x = s[rng() % s.size()].second;
            int y = s[rng() % s.size()].second;
            if (x == y)
                continue;
            int temp = ask(x, y);
            if (1 << (2 *__builtin_popcount(temp) - 1) <= s.size())
            {
                cur = x;
                break;
            }
        }
        for (const auto& [_, i]: s)
            t.emplace_back(__builtin_popcount(f(i, cur)), i);
        sort(all(t));
        while (t.rbegin()->first != t.begin()->first)
            t.pop_back();
        t.emplace_back(t[0].first, cur);
        s = move(t);
    }
    if (s.size() == 2)
    {
        while (true)
        {
            int X = rng() % n;
            int a = s[0].second;
            int b = s[1].second;
            if (X == a || X == b)
                continue;
            int x = f(X, a);
            int y = f(X, b);
            if (x < y)
                getAns(a);
            if (y < x)
                getAns(b);
        }
    }
    else if (s.size() == 0)
        cerr << "NOT FOUND" << endl;
    else
        getAns(s.begin()->second);

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
