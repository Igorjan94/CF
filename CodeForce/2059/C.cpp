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
//hungarian
int hungarian(const vector<vector<int>>& a)
{
    int n = a.size() + 1;
    int m = a[0].size() + 1;
    vector<int> u(n), v(m), p(m), way(m);
    fori1(n)
    {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m, MOD);
        vector<bool> used(m, false);
        do 
        {
            used[j0] = true;
            int i0 = p[j0];
            int delta = MOD;
            int j1;
            forj1(m)
                if (!used[j]) 
                {
                    int cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur,
                        way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],
                        j1 = j;
                }
            forj(m)
                if (used[j])
                    u[p[j]] += delta,
                    v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } 
        while (p[j0] != 0);
        do 
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } 
        while (j0);
        if (-v[0] != i)
            return i - 1;
    }
    vector<int> ans(n + 1);
    forj1(m)
        ans[p[j] - 1] = j - 1;
    return n - 1;
}


//}}}

void run()
{
    ints(n);
    vector a(n, vector(n, 0));
    readln(a);
    vector p(n, vector(n + 1, 0ll));
    vector s(n, vector(n, 2));
    fori(n)
        for (int j = n - 1; j >= 0; --j)
        {
            p[i][j] = p[i][j + 1] + a[i][j];
            if (j == n - 1 || p[i][j + 1] == n - j - 1)
                s[n - j - 1][i] = 1;
        }
    auto ans = hungarian(s);
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
