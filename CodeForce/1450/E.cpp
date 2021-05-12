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
    ints(n, m);
    vector<vector<pii>> g(n);
    fori(m)
    {
        ints(u, v, b); --u; --v;
        g[u].pb({v, b});
        g[v].pb({u, -b});
    }
    int answer = -1;
    vector<int> qqq;
    fori(n)
    {
        bool ok = true;
        vector<pii> edges;
        queue<int> q;
        q.push(i);
        vector<int> d(n, MOD), tuda(n), suda(n), tt(n, 0), ss(n, 0);
        d[i] = 0;
        while (q.size())
        {
            int u = q.front();
            q.pop();
            forj(g[u].size()) 
            {
                auto [v, b] = g[u][j];
                if (d[v] + 1 == d[u]) continue;

                if (d[v] != MOD && d[u] + 1 != d[v]) //odd cycle
                {
                    //writeln("FAIL", u + 1, v + 1, d[u], d[v]); cout.flush();
                    ok = false;
                    break;
                }
                else
                {
                    if (d[v] == MOD)
                        d[v] = d[u] + 1,
                        q.push(v);
                    tuda[v] = max(tuda[v], tuda[u] + (b == 1));
                    suda[v] = max(suda[v], suda[u] + (b == -1));
                    edges.pb({u, j});
                }
            }
        }
        //writeln(i + 1);
        //writeln(d);
        //writeln(tuda);
        //writeln(suda);
        forj(n)
            ok &= tuda[j] + suda[j] <= d[j];
        if (!ok)
            continue;
        reverse(all(edges));
        for (auto [u, j]: edges)
        {
            auto& [v, b] = g[u][j];
            if (b == 1)
                tt[u]++;
            else if (b == -1)
                ss[u]++;
            else
                if (tuda[v] > ss[u])
                    ss[u]++,
                    b = -1;
                else
                    tt[u]++,
                    b = 1;
        }
        vector<int> ans(n, MOD);
        ans[i] = 0;
        q.push(i);
        while (q.size())
        {
            int u = q.front();
            q.pop();
            for (auto [v, b]: g[u])
                if (ans[v] == MOD)
                    ans[v] = ans[u] + b,
                    q.push(v);
                else
                    if (ans[v] != ans[u] + 1 && ans[u] != ans[v] + 1)
                        ok = false;
        }

        //writeln(tuda);
        //writeln(suda);
        if (!ok) continue;
        int mn = *min_element(all(ans));
        for (int& x: ans)
            x -= mn;
        int mx = *max_element(all(ans));
        if (mx > answer)
            answer = mx,
            qqq = ans;
        //writeln(ans);
        //writeln();
        cout.flush();
    }
    if (answer == -1)
        writeln("NO");
    else
        writeln("YES"),
        writeln(answer),
        writeln(qqq);
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
