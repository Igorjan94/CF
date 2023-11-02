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
//fenwickTree
//1-indexed, [l, r]
template <typename T>
struct fenwickTree
{
    vector<T> t, p;
    int n;

    fenwickTree(vector<T>& arr)
    {
        n = arr.size();
        t.resize(n + 1, 0);
        p.resize(n + 1, 1);
        fori(n)
            update(i + 1, arr[i]);
    }

    void update(int index, T value)
    {
        for (; index <= n; index += index & -index)
            t[index] += value,
            p[index] *= max(T(1), value);
    }

    pair<T, T> sum(int i)
    {
        T res = 0;
        T pr = 1;
        for (; i; i -= i & -i)
            res += t[i],
            pr *= p[i];
        return {res, pr};
    }

    pair<T, T> sum0(int l, int r)
    {
        if (l > r) return {0, 1};
        auto [a, b] = sum(r + 1);
        auto [c, d] = sum(l);
        return {a - c, b / d};
    }
};

//}}}

void run()
{
    ints(n);
    vector<ll> a(n);
    readln(a);
    a.insert(a.begin(), 0);
    a.pb(0);
    if (*max_element(all(a)) == 1)
        return writeln(1, 1);
    int l = 1;
    int r = n;
    while (a[l] == 1) ++l;
    while (a[r] == 1) --r;
    if (l == r)
        return writeln(l, l);
    vector<int> indexes;
    ll prod = 1;
    FOR(i, l, r + 1)
    {
        prod *= a[i];
        if (prod >= MOD)
            return writeln(l, r);
        if (a[i] != 1)
            indexes.pb(i);
    }

    fenwickTree tree(a);
    pii ans = {-1, -1};
    ll mx = 0;
    fori(indexes.size())
        for (int j = i; j < indexes.size(); ++j)
        {
            int l = indexes[i];
            int r = indexes[j];

            ll left = tree.sum0(1, l - 1).first;
            ll right = tree.sum0(r + 1, n).first;
            ll p = tree.sum0(l, r).second;
            ll temp = left + right + p;
            if (temp > mx)
                mx = temp,
                ans = {l, r};
        }
    writeln(ans);

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
