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

typedef    long long      ll;
typedef  pair<ll, ll>   pii;
typedef   vector<int>     vi;

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
//PDBS
#undef _GLIBCXX_HAVE_ICONV
#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds; 
typedef tree<int, int,       less<int>, rb_tree_tag, tree_order_statistics_node_update> orderedMap;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> orderedSet;

//}}}

void run()
{
    ints(n, m, q);
    vi a(n), b(m);
    readln(a, b);
    orderedSet x, y;
    fori(n) x.insert({a[i], i});
    fori(m) y.insert({-b[i], i});

    auto gx = [&](int index) {
        return x.find_by_order(index)->first;
    };
    auto gy = [&](int index) {
        return -y.find_by_order(index)->first;
    };

    auto cmp = [&](int i, int j, pii cur) {
        return gx(i) * cur.second < gy(j) * cur.first;
    };
    auto calc = [&](pii d) {
        int i = 0;
        int j = 0;
        int cnt = 0;
        pii largest = {0, 1};
        pii smallest = {1000001, 1};
        while (j < m && cmp(i, j, d)) ++j;
        for (--j; j >= 0; --j)
        {
            while (i < n && cmp(i, j, d)) ++i;
            if (!cmp(i - 1, j, largest))
                largest = {gx(i - 1), gy(j)};
            if (i < n && cmp(i, j, smallest))
                smallest = {gx(i), gy(j)};
            cnt += i;
        }
        return tuple(cnt, smallest, largest);
    };

    fori(q)
    {
        ints(t);
        if (t == 1)
        {
            ints(k);
            pii l = {0, 1};
            pii r = {1000001, 1};
            int N = 30;
            fori(N) 
            {
                ll num = l.first * r.second + l.second * r.first;
                ll den = l.second * 2ll * r.second;
                ll gg = gcd(num, den);
                num /= gg;
                den /= gg;
                pii mid = {num, den};
                auto [cnt, _, __] = calc(mid);
                if (cnt > k)
                    r = mid;
                else
                    l = mid;
            }
            auto [cnt, smallest, largest] = calc(l);
            if (cnt < k)
                largest = smallest;
            auto g = gcd(largest.first, largest.second);
            largest.first /= g;
            largest.second /= g;
            writeln(largest);
        }
        else if (t == 2)
        {
            ints(i, v); --i;
            x.erase(x.find({a[i], i}));
            a[i] = v;
            x.insert({a[i], i});
        }
        else if (t == 3)
        {
            ints(i, v); --i;
            y.erase(y.find({-b[i], i}));
            b[i] = v;
            y.insert({-b[i], i});
        }
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
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
