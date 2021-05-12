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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
static const int STEP = 3;

struct sss 
{
    vector<vector<int>> s;
    map<int, int> m;

    sss(int maxDeg)
    {
        s.resize(maxDeg / STEP + 2);
    }

    void insert(int u, int d)
    {
        int l = d / STEP;
        s[l].pb(u);
        m[u] = l;
    }

    void erase(int u)
    {
        int l = m[u];
        s[l].erase(remove(all(s[l]), u), s[l].end());
    }

    int next()
    {
        fori(s.size())
            if (s[i].size() != 0)
            {
                int index = rng() % s[i].size();
                int u = s[i][index];
                s[i].erase(s[i].begin() + index);
                return u;
            }
        return -1;
    }
};

void run()
{
    ints(n, m);
    vector<vector<int>> g(n);
    vector<int> d(n);
    fori(m)
    {
        ints(u, v); --u; --v;
        g[u].pb(v);
        g[v].pb(u);
        d[u]++;
        d[v]++;
    }
    int md = *max_element(all(d));
    cerr << "n m MAXD " << n << " " << m << " " << md << endl;
    int ans = 0;
    vector<int> answer;
    static const int ITERATIONS = 0;
    fori(ITERATIONS)
    {
        int cur = 0;
        vector<int> curAns(n, 0);

        sss s(md);
        fori(n)
            s.insert(i, d[i]);

        while (true)
        {
            int u = s.next();
            if (u == -1) break;

            for (int v: g[u])
                s.erase(v);
            curAns[u] = 1;
            cur++;
        }
        cerr << i << " / " << ITERATIONS << " ( " << cur << " )" << endl;

        if (cur > ans)
            ans = cur,
            answer = curAns;
    }
    cerr << ans << endl;
    writeln(ans);
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
