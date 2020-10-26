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
//fenwickTree
//1-indexed, [l, r]
template <typename T>
struct fenwickTree
{
    vector<T> t;
    int n;

    fenwickTree(int size, T value = 0)
    {
        n = size;
        t.resize(n + 1, value);
    }

    fenwickTree(vector<T>& arr)
    {
        n = arr.size();
        t.resize(n + 1, 0);
        fori(n)
            update(i + 1, arr[i]);
    }

    void update(int index, T value)
    {
        for (; index <= n; index += index & -index)
            t[index] += value;
    }

    T sum(int i)
    {
        T res = 0;
        for (; i; i -= i & -i)
            res += t[i];
        return res;
    }

    T sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    T sum0(int l, int r)
    {
        return sum(r + 1) - sum(l);
    }
};

//}}}

void run()
{
    ints(n);
    vi a(n);
    readln(a);
    vector<int> b = a;
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    int l = b.size();
    map<int, int> indices;
    fori(l)
        indices[b[i]] = i + 1;
    fenwickTree<ll> f(l);
    f.update(indices[a[0]], a[0]);
    vector<ll> ans(n, 0);
    fori1(n)
    {
        int index = indices[a[i]];
        ans[i] = ans[i - 1] + f.sum(index + 1, l);
        f.update(index, a[i]);
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
