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

const int N = 202;
int da[N][N];
int db[N][N];

void run()
{
    ints(m, n);
    vector<set<int>> createdStories(n);
    fori(m)
    {
        ints(user); --user;
        createdStories[user].insert(i);
    }
    ints(p, q);
    vector<set<int>> fu(n);
    vector<set<int>> fs(n);
    fori(p)
    {
        ints(u, v); --u; --v;
        fu[u].insert(v);
    }
    fori(q)
    {
        ints(u, v); --u; --v;
        fs[u].insert(v);
    }
    auto a = [&](int i, int j) {
        if (i == j)
            return 0;
        if (fu[i].find(j) != fu[i].end())
            return 3;
        for (int k: createdStories[j])
            if (fs[i].find(k) != fs[i].end())
                return 2;
        for (int k: fs[j])
            if (fs[i].find(k) != fs[i].end())
                return 1;
        return 0;
    };
    auto b = [&](int j, int k) {
        if (createdStories[j].find(k) != createdStories[j].end())
            return 2;
        if (fs[j].find(k) != fs[j].end())
            return 1;
        return 0;
    };
    fori(n)
        forj(n)
            da[i][j] = a(i, j);
    forj(n)
        forn(k, m)
            db[j][k] = b(j, k);
    fori(n)
    {
        vector<int> scores(m, 0);
        vector<int> order(m);
        iota(all(order), 0);
        forn(k, m)
        {
            if (createdStories[i].find(k) != createdStories[i].end() ||
                fs[i].find(k) != fs[i].end())
                scores[k] = -1;
            else
                forj(n)
                    scores[k] += da[i][j] * db[j][k];
        }
        sort(all(order), [&](int u, int v) {
            return pair(scores[u], -u) > pair(scores[v], -v);
        });
        writeln(order[0] + 1, order[1] + 1, order[2] + 1);
    }
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
