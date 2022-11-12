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

vector<int> mx;

template<typename T = vector<int>>
vector<T> lis(const vector<T>& a)
{
    int n = a.size();
    vector<T> d(n + 1, numeric_limits<T>::max()), p(n + 1, -1), x(n + 1, -1);
    d[0] = numeric_limits<T>::min();
 
    fori(n)
    {
        int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[j - 1] < a[i] && a[i] < d[j])
    		d[j] = a[i],
            x[j] = i,
            p[i] = x[j - 1];
    }
    int index = 0;
    while (index <= n && d[index] < numeric_limits<T>::max()) ++index;
    index = x[--index];

    vector<T> ans;
    while (index != -1)
        ans.pb(a[index]),
        index = p[index];

    reverse(all(ans));
    return ans;
}

bool inside(const vector<int>& a, const vector<int>& b)
{
    fori(a.size())
        if (a[i] >= b[i])
            return false;
    return true;
}

void run()
{
    ints(n, k, A);
    vector<vector<int>> a(n, vector<int>(k));
    readln(a);
    fori(n)
        sort(all(a[i]));
    vector<int> order(n);
    iota(all(order), 0);
    sort(all(order), [&](int x, int y) {
        return a[x] < a[y];
    });
    vector<int> p(n, -1);
    vector<int> mx(n, 0);
    fori(n)
    {
        if (i % 1000 == 0)
            cerr << i << " / " << n << endl;
        int x = order[i];
        FOR(j, i + 1, min(n, i + 5000))
        {
            int y = order[j];
            if (!inside(a[x], a[y]))
                continue;
            if (mx[x] + 1 >= mx[y])
                p[y] = x,
                mx[y] = mx[x] + 1;
        }
    }
    int index = max_element(all(mx)) - mx.begin();
    vector<int> ans;
    do
    {
        ans.pb(index + 1);
        index = p[index];
    }
    while (index != -1);
    reverse(all(ans));
    writeln(ans.size());
    writeln(ans);
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
