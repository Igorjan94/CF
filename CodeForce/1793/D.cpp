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
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}

int mex(const vector<int>& a, int l, int r)
{
    vector used(a.size(), true);
    FOR(i, l, r + 1)
        used[a[i]] = false;
    fori(a.size())
        if (used[i])
            return i;
    return a.size();
}

ll dumb(const vector<int>& p, const vector<int>& q)
{
    int n = p.size();
    ll ans = 0;
    fori(n)
        FOR(j, i, n)
            ans += mex(p, i, j) == mex(q, i, j);
    return ans;
}

void run()
{
    ints(n);
    vi p(n), q(n), a(n), b(n);
    //iota(all(p), 1);
    //iota(all(q), 1);
    //shuffle(all(p), rng);
    //shuffle(all(q), rng);
    readln(p, q);
    for (int& x: p) --x;
    for (int& x: q) --x;
    fori(n)
        a[p[i]] = i,
        b[q[i]] = i;

    auto get = [&](ll x) {
        return x * (x + 1) / 2;
    };

    int l = a[0];
    int r = b[0];
    if (l > r)
        swap(l, r);
    //writeln(l, r, l - 1, r - l - 1, n - r - 1);
    ll ans = get(l) + get(r - l - 1) + get(n - r - 1);
    //writeln("START", ans);
    fori1(n)
    {
        int nl = a[i];
        int nr = b[i];
        if (nl > nr) swap(nl, nr);

        {
            int cr = nr;
            int cl = nl;
            if (nr < l)
                cl = cr,
                cr = n;
            if (nl > r)
                cr = cl,
                cl = -1;

            bool aa = l <= nl && nl <= r;
            bool bb = l <= nr && nr <= r;
            if (!aa && !bb)
                //writeln(i, cl, l, r, cr),
                ans += (l - cl) * 1ll * (cr - r);
        }
        l = min(l, nl);
        r = max(r, nr);
    }

    writeln(ans + 1);
    //writeln(dumb(p, q));
    //writeln("=======");
    //writeln(n);
    //for (int& x: p) ++x;
    //for (int& x: q) ++x;
    //writeln(p);
    //writeln(q);
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
