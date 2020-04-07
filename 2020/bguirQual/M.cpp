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
//dsu
struct dsu
{
    vector<int> a, size;

    dsu(int n)
    {
        a.resize(n);
        size.resize(n, 1);
        iota(a.begin(), a.end(), 0);
    }

    int get(int i)
    {
        return a[i] == i ? i : a[i] = get(a[i]);
    }

    int operator[](int i)
    {
        return get(i);
    }

    void uni(int i, int j)
    {
        i = get(i);
        j = get(j);
        if (i == j) return;
        if (size[i] > size[j])
            swap(i, j);
        a[i] = j;
        size[j] += size[i];
    }
};

//}}}

void run()
{
    int n, m, q, a, b, x, y;
    scanf("%d%d", &n, &m);
    vector<string> s(n, string(m, 'a'));
    fori(n)
        scanf("%s", s[i].data());
    dsu d(n * m);
    auto get = [&](int i, int j) {
        return i * m + j;
    };
    fori(n)
    {
        vector<int> r[26];
        forj(m)
            r[s[i][j] - 'a'].pb(j);
        forj(26)
            if (r[j].size() > 3)
                FOR(k, 1, r[j].size())
                    d.uni(get(i, r[j][k - 1]), get(i, r[j][k]));
            else if (SZ(r[j]) == 3)
                d.uni(get(i, r[j][0]), get(i, r[j].back()));
    }
    forj(m)
    {
        vector<int> r[26];
        fori(n)
            r[s[i][j] - 'a'].pb(i);
        fori(26)
            if (r[i].size() > 3)
                FOR(k, 1, r[i].size())
                    d.uni(get(r[i][k - 1], j), get(r[i][k], j));
            else if (SZ(r[i]) == 3)
                d.uni(get(r[i][0], j), get(r[i].back(), j));
    }
    scanf("%d", &q);
    fori(q)
    {
        scanf("%d%d%d%d", &a, &b, &x, &y);
        printf(d[get(--a, --b)] == d[get(--x, --y)] ? "Yes\n" : "No\n");
    }
}

//{{{
int main()
{
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
