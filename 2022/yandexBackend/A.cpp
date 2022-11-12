// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif
#include "json.hpp"

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
//lca
struct lca
{
    vector<vector<int>> g, up;
    vector<int> h;
    int n, l;

    lca(const vector<vector<int>>& g) //O(n * log(n))
    {
        this->g = g;
        n = SZ(g);
        l = 1;
        while ((1 << l) <= n) ++l;
        h.resize(n, -1);
        up.resize(l + 1, vector<int>(n));
        dfs(0, 0);
        fori(l)
            forj(n)
                up[i + 1][j] = up[i][up[i][j]];
    }
 
    int getParent(int u, int dist) { //O(log(n))
        fori(l)
            if (dist >> i & 1)
                u = up[i][u];
        return u;
    }

    void dfs(int u, int p) //O(n)
    {
        h[u] = h[p] + 1;
        up[0][u] = p;
        for (const int& v: g[u])
            if (v != p)
                dfs(v, u);
    }

    int get(int a, int b) //O(log(n))
    {
        if (h[a] < h[b]) swap(a, b);
        a = getParent(a, h[a] - h[b]);
        if (a == b) return a;
        ROF(i, l, 0)
            if (up[i][a] != up[i][b])
                a = up[i][a],
                b = up[i][b];
        return up[0][a];
    }

    int getChildWithVertex(int a, int b) //O(log(n))
    {
        if (a == b) return -1;
        return getParent(b, h[b] - h[a] - 1);
    }
};

//}}}

using json = nlohmann::json;

vector<string>split(string&s,string_view d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}

static const int N = 100005;
void run()
{
    json j;
    cin >> j;
    vector<vector<int>> g(N);
    vector<map<string, int>> f(N), b(N);
    vector<bool> isChild(N);
    vector<string> labelString(N);
    vector<int> labelInt(N);
    vector<bool> label(N);
    int V = 0;
    vector<int> children;
    auto dfs = [&](auto dfs, json& u, int root) -> void {
        for (const auto& v: u.items())
        {
            g[root].pb(++V);
            f[root][v.key()] = V;
            b[V][v.key()] = root;
            if (v.value().is_object())
                dfs(dfs, v.value(), V);
            else if (!v.value().is_null())
            {
                isChild[V] = true;
                children.pb(V);
                if (v.value().is_string())
                    labelString[V] = v.value();
                else
                    labelInt[V] = v.value(),
                    label[V] = true;
            }
        }
    };
    dfs(dfs, j, V);
    lca l(g);
    ints(q);
    fori(q)
    {
        json r;
        cin >> r;
        string p = r["path"];
        int cnt = r["count"];
        vector<int> ans;
        vector<string> ans2;

        auto x = split(p, "*");
        int root = 0;
        bool ok = true;
        for (auto& s: split(x[0], "."))
            if (s.size() && ok)
            {
                if (f[root].find(s) != f[root].end())
                    root = f[root][s];
                else
                    ok = false;
            }
        if (ok)
        {
            auto ss = split(x[1], ".");
            reverse(all(ss));
            for (int C: children)
            {
                bool ok = true;
                int child = C;
                for (string& s: ss)
                    if (s.size() && ok)
                    {
                        if (b[child].find(s) != b[child].end())
                            child = b[child][s];
                        else
                            ok = false;
                    }
                if (ok && child)
                {
                    child = b[child][b[child].begin()->first];
                    if (l.get(root, child) == root)
                    {
                        if (label[C])
                            ans.pb(labelInt[C]);
                        else
                            ans2.pb(labelString[C]);
                    }
                }
            }
        }
        sort(all(ans));
        sort(all(ans2));
        reverse(all(ans));
        reverse(all(ans2));
        json answer;
        if (ans.size() && ans2.size())
            writeln("{\"result\":null}");
        else
        {
            ans.resize(min(cnt, SZ(ans)));
            ans2.resize(min(cnt, SZ(ans2)));
            if (ans.size())
                answer["result"] = ans;
            else
                answer["result"] = ans2;
            cout << answer << "\n";
        }
    }
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
