// Igorjan94, template version from 13 October 2017. C++17 version, modified 07 August 2018 (&&, whole) {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

typedef vector<long long> vll;
typedef  pair<int, int>   pii;
typedef  valarray<int>    va;
typedef   vector<int>     vi;
typedef    long long      ll;

#define    pb    push_back
#define whole(a) begin(a), end(a)
#define   next   next__
#define   prev   prev__
#define  count   count__

#define ints(a...)  int a; readln(a)
#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline

const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();
const ll LLMAX = numeric_limits<ll>::max();

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//}}}

void run()
{
    ints(n);
    vector<vi> a(n, vi(n));
    readln(a);
    forn(k, n)
        fori(n)
            forj(n)
                a[i][j] = a[i][j] || (a[i][k] && a[k][j]);
    vector<vector<int>> layers;
    vector<bool> used(n, false);
    fori(n)
        if (!used[i])
        {
            vector<int> layer = {i};
            forj(n) if (i != j && a[i][j] && a[j][i]) layer.pb(j), used[j] = true;
            layers.pb(layer);
        }

    int m = layers.size();
    auto hasEdge = [&](int u, int v) {
        return a[layers[u][0]][layers[v][0]];
    };
    vector<int> ts;
    vector<bool> lu(m, false);
    function<void(int)> dfs = [&](int u) {
        lu[u] = true;
        fori(m)
            if (!lu[i] && hasEdge(i, u))
                dfs(i);
        ts.pb(u);
    };
    fori(m)
        if (!lu[i])
            dfs(i);

    //fori(m)
        //writeln(layers[ts[i]]);
    //reverse(whole(ts));
    vector<vector<string>> ans(2 * m, vector<string>(3));
    fori(2 * m) forj(3) ans[i][j] = string(90, ".#"[i & 1]);

    fori(m)
        forj(layers[ts[i]].size())
            ans[i * 2][2][j] = layers[ts[i]][j] + '1';
    int hole = 1;
    fori(m)
        forj(m)
            if (i != j && hasEdge(ts[i], ts[j]))
            {
                FOR(k, i * 2 + 1, j * 2)
                    ans[k][0][hole - 1] = '#',
                    ans[k][0][hole - 0] = '.',
                    ans[k][0][hole + 1] = '#',
                    ans[k][1][hole - 1] = '#',
                    ans[k][1][hole - 0] = '#',
                    ans[k][1][hole + 1] = '#';
                //writeln("Hole between", layers[ts[i]][0], layers[ts[j]][0]);
                hole += 2;
            }
            
    writeln(90, 3, 2 * m);
    fori(2 * m)
        writeln(ans[i]),
        writeln();
}

//{{{
int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
#ifndef ONLINE_JUDGE
    writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
#endif
    return 0;
}

#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&& a){cout<<" "<<a;}
ttti void priws(T&& a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
