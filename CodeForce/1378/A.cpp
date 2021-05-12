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


static const int ITERATIONS = 1;
static const int N = 200000;
vector<vector<int>> g(N);
vector<int> d(N);
unordered_set<int> V;
int E = 0;

double getScore(const vector<vector<int>>& x)
{
    unordered_set<int> V1;
    for (const auto& c: x)
        for (const int& u: c)
            V1.insert(u);
    if (V1 != V)
    {
        writeln("Not all vertices are in components or some are included more than once");
        exit(1);
    }

    auto ein = [&](const vector<int>& c) {
        unordered_set s(all(c));
        int edges = 0;
        for (const int& u: c)
            for (const int& v: g[u])
                edges += s.find(v) != s.end();
        return edges / 2.0;
    };

    auto eout = [&](const vector<int>& c) {
        int s = 0;
        for (const int& u: c)
            s += d[u];
        return s / 2.0 / E;
    };

    auto density = [&](const vector<int>& c) {
        int n = c.size();
        if (n == 1)
            return 1.0;
        else
            return ein(c) * 2.0 / n / (n - 1);
    };

    auto modularity = [&](const vector<vector<int>>& x) {
        double ans = 0.0;
        for (const auto& c: x)
            ans += ein(c) / E - pow(eout(c), 2.0);
        return ans;
    };
    
    auto regularization = [&](const vector<vector<int>>& x) {
        double ans = 0.0;
        for (const auto& c: x)
            ans += density(c);
        return 0.5 * (ans / x.size() - x.size() * 1.0 / V.size());
    };

    return (1.0 + modularity(x) + regularization(x)) * 100000.0;
}

void run()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cerr << fixed << setprecision(3);
    int u, v;
    while (cin >> u >> v)
        ++E,
        V.insert(u),
        V.insert(v),
        d[u]++,
        d[v]++,
        g[u].pb(v),
        g[v].pb(u);
    int n = SZ(V);
    vector<vector<int>> ans;
    double answer = 0;
    forn(q, ITERATIONS)
    {
        vector<vector<int>> cur;

        vector<int> used(n, -1);
        set<pii> degrees;
        fori(n) degrees.emplace(-d[i], i);
        while (degrees.size())
        {
            auto [_, u] = *degrees.begin();
            degrees.erase(degrees.begin());
            if (used[u] != -1) continue;
            used[u] = cur.size();
            cur.pb({u});
            for (const int& v: g[u])
                if (used[v] == -1)
                    used[v] = used[u],
                    cur[used[u]].pb(v);
        }

        int lastSize = 0;
        forn(qqq, 15)
        {
            set<pii> sizes;
            fori(cur.size())
                sizes.emplace(cur[i].size(), i);
            if (lastSize == cur.size()) break;
            lastSize = cur.size();
            cerr << "COMPS: " << lastSize << endl;
            while (!sizes.empty())
            {
                auto [sz, comp] = *sizes.begin();
                sizes.erase(sizes.begin());
                map<int, int> m;
                for (int u: cur[comp])
                    for (int v: g[u])
                        m[used[v]]++;
                int toMerge = -1;
                int X = -1;

                if (m.size() >= 80)
                    continue;
                for (const auto& [k, v]: m)
                    if (k != comp)
                        if (v > X)
                            X = v, toMerge = k;
                //if (X > 1)
                    //cerr << X  << " " << sz << endl;
                if (X < m[comp] || toMerge == -1 || (sz > 1 && X < sz * sqrt(3))) continue;
                for (int u: cur[comp])
                    used[u] = toMerge,
                    cur[toMerge].pb(u);
                cur[comp].clear();
            }
            for (int i = 0; i < SZ(cur); )
                if (cur[i].size() == 0)
                    swap(cur[i], cur.back()),
                    cur.pop_back();
                else
                    ++i;
            fori(cur.size())
                for (int u: cur[i])
                    used[u] = i;
        }

        double temp = getScore(cur);
        cerr << "ITERATION " << (q + 1) << " / " << ITERATIONS << ", curScore " << temp << ", maxScore " << answer << endl;
        if (temp > answer)
            answer = temp,
            ans = cur;
    }
    for (const auto& u: ans)
        if (u.size())
            writeln(u);
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
