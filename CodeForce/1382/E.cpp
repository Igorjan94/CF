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
//}}}

void run()
{
    ints(n, X, Y);
    vi b(n);
    readln(b);
    map<int, vector<int>> m;
    set<int> unused;
    fori1(n + 2) unused.insert(i);
    fori(n) unused.erase(b[i]), m[b[i]].pb(i);
    int left = *unused.begin();
    vector<int> a(n);
    set<pii> q;
    for (auto& [k, v]: m)
        q.insert({-SZ(v), k});
    
    int cnt = 0;
    while (!q.empty())
    {
        if (cnt == X) break;
        auto [d, x] = *q.begin();
        q.erase(q.begin());

        cnt++;

        int index = m[x].back();
        a[index] = x;
        m[x].pop_back();

        if (d != -1)
            q.insert({d + 1, x});
    }
    vector<int> colors;
    vector<int> positions;
    int mx = 0;
    int index = 0;
    for (auto& [k, v]: m)
    {
        if (int temp = SZ(v); temp > mx)
            mx = temp,
            index = SZ(colors);
        for (int pos: v)
            colors.pb(k),
            positions.pb(pos);
    }
    fori(n - Y)
        colors[(i + index) % SZ(colors)] = left;
    rotate(colors.begin(), colors.begin() + mx, colors.end());
    fori(SZ(colors))
    {
        a[positions[i]] = colors[i];
        if (colors[i] == b[positions[i]])
            return writeln("NO");
    }
    writeln("YES");
    writeln(a);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
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
