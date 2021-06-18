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
//topsort
//Returns empty vector if cycle is found
vector<int> topsort(const vector<vector<int>>& edges, bool reversed = false)
{
    int n = edges.size();
    vector<int> ans;
    vector<int> used(n, 0);
    bool cycle = false;
    
    function<void(int)> dfs = [&](int u) {
        used[u] = 1;
        for (const int& v: edges[u])
            if (!used[v])
                dfs(v);
            else if (used[v] == 1)
                cycle = true;
        used[u] = 2;
        ans.pb(u);
    };

    fori(n)
        if (!used[i])
            dfs(i);
    if (cycle)
        return vector<int>();
    if (!reversed)
        reverse(ans.begin(), ans.end());
    return ans;
}

//}}}

void run()
{
    string s;
    readln(s);
    int l = 1;
    int r = 131072;
    auto run = [&](int n) {
        int q = 0;
        vector<vector<int>> g(n);
        vector<int> a(n);
        iota(all(a), 0);
        vector<int> b(n);

        function<bool(int, int)> mergeSort = [&](int l, int r) {
            if (r - l <= 1) return true;
            int m = (l + r) >> 1;
            if (!mergeSort(l, m)) return false;
            if (!mergeSort(m, r)) return false;
            int i = l;
            int j = m;
            int k = l;
            while (i < m && j < r)
            {
                if (q == SZ(s)) return false;
                if (s[q++] == '0')
                    b[k++] = a[i],
                    g[a[j]].pb(a[i++]);
                else
                    b[k++] = a[j],
                    g[a[i]].pb(a[j++]);
            }
            while (i < m)
                b[k++] = a[i++];
            while (j < r)
                b[k++] = a[j++];
            FOR(i, l, r)
                a[i] = b[i];
            return true;
        };
        if (!mergeSort(0, n))
            return 1;
        if (q < SZ(s))
            return -1;
        vector<int> ans = topsort(g, true);
        vector<int> x(n);
        fori(n)
            x[a[i]] = i + 1;
        writeln(n);
        writeln(x);
        exit(0);
    };
    while (r - l > 1)
    {
        int m = (r + l) / 2;
        int left = run(m);
        if (left == 1)
            r = m;
        else
            l = m;
    }
    run(l);
    run(r);
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
