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
        m = l + (r - l) / 2,
        (f(m) ? r : l) = m;
    return f(l) ? l : r;
}

//}}}

pair<ll, ll> add(const pair<ll, ll>& a, const pair<ll, ll>& b)
{
    return {a.first + b.first, a.second ^ b.second};
}

void run()
{
    ints(n, q);
    vi a(n);
    readln(a);
    vector<ll> p = {0};
    vector<ll> x = {0};
    set<int> s, b;
    fori(n)
    {
        p.pb(p.back() + a[i]);
        x.pb(x.back() ^ a[i]);
        if (a[i])
            s.insert(i + 1),
            b.insert(-i - 1);
    }

    auto get = [&](int l, int r) {
        --l;
        return p[r] - p[l] - (x[r] ^ x[l]);
    };
    forn(Q, q)
    {
        ints(l, r);
        ll sum = get(l, r);
        if (sum == 0)
        {
            writeln(l, l);
            continue;
        }
        int index = l;
        int length = r - l;
        auto first = s.lower_bound(l);
        int cnt = 0;
        while (first != s.end() && *first <= r && cnt <= 31)
        {
            int ll = *first;
            auto second = b.lower_bound(-r);
            for (int i = cnt; i <= 31; ++i)
            {
                if (second == b.end() || -*second < ll)
                    break;
                int rr = -*second;
                if (get(ll, rr) == sum)
                    if (rr - ll < length)
                        length = rr - ll,
                        index = ll;
                ++second;
            }
            ++cnt;
            ++first;

        }
        writeln(index, index + length);
    }
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
