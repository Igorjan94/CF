//Igorjan94, template version from 19 March 2015
#include <bits/stdc++.h>

using namespace std;

#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn1(i, n)  for (int i = 1; i < (int) (n); ++i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define     fst      first
#define     snd      second
#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define      eb      emplace_back
#define      vs      vector<string>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     vvi      vector<vector<int>>
#define     pll      pair<long long, long long>
#define   elohw(a)   a.rbegin(), a.rend()
#define   whole(a)   a.begin(), a.end()
#define    next      _next
#define    prev      _prev
#define   count      _count

#define argmax(a)    (max_element(whole(a)) - (a).begin())
#define argmin(a)    (min_element(whole(a)) - (a).begin())
#define wr(args...)  err(split(#args,',').begin(),args)

#define FILENAME "input"
#define INF 1000000007

#define tthti  template<typename Head, typename... Tail> inline
#define ttt12i template<typename T1, typename T2> inline
#define ttti   template<typename T> inline

inline void writeln2(){cout<<"\n";}
inline void writeln() {cout<<"\n";}
inline void readln()  {}
ttti void read(T&);
ttti void priws(T);
ttti void print(T);

void err(vector<string>::iterator it){++it;}
tthti void readln (Head& head,Tail&... tail){read(head); readln  (tail...);}
tthti void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
tthti void writeln (Head head, Tail... tail){priws(head);writeln2(tail...);}
ttti  void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
tthti void err(vector<string>::iterator it,Head head,Tail...tail){writeln((*it).substr((*it)[0]==' '),"=",head);err(++it, tail...);}
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

#define  ints(args...) int args; readln(args)
#define   lls(args...)  ll args; readln(args)
#define vints(args...)  vi args; readln(args)

///-------------------------------------------------------------------------------------------------------------------------------------

#define x first
#define y second
void run()
{
    ints(n, m, k);
    vector<vector<ll>> g(n, vll(n, INF));
    vector<pll> p(k);
    ll x, y, z;
    fori(m)
        readln(x, y, z),--x,--y,
        g[x][y] = g[y][x] = min(g[x][y], z);
    readln(p);
    fori(k)p[i].x--,p[i].y--;
    p.insert(p.begin(), {0, 0});
    p.pb({p.back().y, p.back().y});
    p.pb(p.back());

    fori(n)
        g[i][i] = 0;
    FOR(k, 0, n)
        fori(n)
            forj(n)
                if (g[i][k] < INF && g[k][j] < INF)
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

    vll dp(k + 3, INF);
    dp[0] = 0;
    fori1(k + 1)
    {
        ll is = p[i].x;
        ll it = p[i].y;
        ll js = p[i + 1].x;
        ll jt = p[i + 1].y;

        dp[i + 0] = min(dp[i + 0], dp[i - 1] + g[p[i - 1].y][is] + g[is][it]);
        dp[i + 1] = min(dp[i + 1], dp[i - 1] + g[p[i - 1].y][is] + g[is][js] + g[js][it] + g[it][jt]);
    }
    writeln(dp[k] == INF ? -1 : dp[k]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    ints(T);
    fori(T)
        cerr << "running test " << (i + 1) << "/" << T << "\n",
        cout << "Case #" << (i + 1) << ": ",
        run(),
        cerr << "finished test " << (i + 1) << "/" << T << "\n";
    return 0;
}























#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
