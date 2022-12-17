// Igorjan94, template version from 19 March 2015 (deleted unused defines & reorganization from 05 November 2015)
#include <bits/stdc++.h>

using namespace std;

#define forit(it, r) for (auto it = r.begin(); it != r.end(); ++it)
#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn1(i, n)  for (int i = 1; i < (int) (n); ++i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     pll      pair<long long, long long>
#define   whole(a)   a.begin(), a.end()
#define    next      next__
#define    prev      prev__
#define   count      count__
#define  argmax(a)   (max_element(whole(a)) - (a).begin())
#define  argmin(a)   (min_element(whole(a)) - (a).begin())

#define  ints(a...)  int a; readln(a)
#define  lls(a...)   ll a; readln(a)
#define wr(args...)  err(split(#args,',').begin(),args)
                    
#define  FILENAME    "input"
#define     INF      1000000007
                    
#define    tthti     template<typename Head, typename... Tail> inline
#define   ttt12i     template<typename T1, typename T2> inline
#define    ttti      template<typename T> inline

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

///-------------------------------------------------------------------------------------------------------------------------------------
//Igorjan

int n;
vector<int> d;
vector<vector<int>> edges;
int answer = -1;
int ccc = 0;
vector<int> curr;
vector<bool> ok;
bool oneCycle;

void dfs(int u, int CCC, int depth = 0, int p = -1)
{
    curr[u] = CCC;
    //wr(u, p);
    if (answer == -1 && d[u] != -1)
    {
        //wr(u, depth, d[u]);
        answer = depth - d[u];
        return;
    }
    if (d[u] != -1)
        return;
    ccc++;
    oneCycle |= ok[u];
    d[u] = depth;
    for (int v : edges[u])
        if (p != v)
            dfs(v, CCC, depth + 1, u);
}

void run()
{
    readln(n);
    d.resize(n, -1);
    edges.resize(n);
    curr.resize(n, -1);
    ok.resize(n, false);

    vi a(n);
    readln(a);
    fori(n)
        edges[i].pb(--a[i]),
        edges[a[i]].pb(i);
    fori(n)
        ok[i] = a[a[i]] == i;
    vector<ll> asdas;
    vector<ll> degs;
    degs.pb(1);
    fori(n)
        degs.pb((degs.back() * 2) % INF);
    fori(n)
        if (d[i] == -1)
        {
            ll ans = 1;
            answer = -1;
            ccc = 0;
            oneCycle = false;
            dfs(i, i);
            if (oneCycle)
            {
                ans = degs[ccc - 1];
                //forj(ccc - 1)
                    //ans = (ans * 2) % INF;
            }
            else
            {
                //forj(answer)
                    //ans = (ans * 2) % INF;
                ans = degs[answer];
                ans = (ans - 2 + INF) % INF;
                ans = (ans * degs[ccc - answer]) % INF;
                //forj(ccc - answer)
                    //ans = (ans * 2) % INF;
            }
            asdas.pb(ans);
        }
    ll ANS = 1;
    fori(asdas.size())
        ANS = (ANS * asdas[i]) % INF;
    writeln(ANS);
}

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
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
