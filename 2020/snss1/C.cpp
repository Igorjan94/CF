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
//khun
vector<pii> khun(const vector<vector<int>>& g)
{
    int n = g.size();
    vector<int> mt(n, -1);
    vector<int> used(n, false);
    int counter = 0;

    function<bool(int)> dfs = [&](int u) {
        used[u] = counter;
        for (const int& v: g[u])
            if (mt[v] == -1 || (used[mt[v]] != counter && dfs(mt[v])))
                return mt[v] = u, mt[u] = v, true;
        return false;
    };

    for (bool run = 1; run; )
    {
        run = 0;
        counter++;
        fori(n)
            if (mt[i] == -1 && dfs(i))
                run = 1;
    }
    vector<pii> ans;
    fori(n)
        if (mt[i] != -1)
            ans.pb({mt[i], i});
    return ans;
}

//}}}

#define pss pair<string, string>
void run()
{
    ints(n);
    vector<pss> a(n);
    readln(a);
    map<string, int> m;
    vector<vector<int>> edges(n);
    a.resize(n * 100 * 101);
    forn(q, n)
    {
        const auto& [s, t] = a[q];
        fori1(s.size() + 1)
            forj1(t.size() + 1)
            {
                string temp = s.substr(0, i) + t.substr(0, j);
                if (m.find(temp) == m.end())
                    m[temp] = edges.size(),
                    edges.pb({});
                edges[q].pb(m[temp]);
                a[m[temp]] = {temp, ""};
                //writeln(temp); continue;
            }
    }
    auto ans = khun(edges);
    if (SZ(ans) != 2 * n)
        return writeln("No solution");
    vector<string> answer(n);
    for (auto [f, t]: ans)
        if (f < n)
            answer[f] = a[t].first;

    writeln(answer);
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
