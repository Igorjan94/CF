// Igorjan94, template version from 19 March 2015 (#define -> typedef, readln(vector) patched, version from 27 March 2017)
#include <bits/stdc++.h>

using namespace std;

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
#define      pb      push_back
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
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return v;}

///-------------------------------------------------------------------------------------------------------------------------------------
//Igorjan

struct edge
{
    int u, v, t, i;
    char maximize = '+', minimize = '+';

    edge(){};
    edge(int u, int v, int t, int i) : u(u), v(v), t(t), i(i) {}
};

void run()
{
    ints(n, m, start); start--;
    vector<vector<int>> g(n);
    vector<bool> used;
    vector<edge> edges;
    fori(m)
    {
        ints(t, u, v); --u; --v;
        edges.pb(edge(u, v, t, i));
        g[u].pb(i); //IN G -- index of edge
        if (t == 2)
            g[v].pb(i);
    }

    function<void(int)> dfsX = [&](int u) {
        used[u] = true;
        for (int index : g[u])
        {
            auto& e = edges[index];
            bool sameDirection = e.u == u;
            int v = (e.t == 1 || sameDirection) ? e.v : e.u;
            if (!used[v])
            {
                dfsX(v);
                if (e.t == 2) e.maximize = sameDirection ? '+' : '-';
            }
        }
    };

    function<void(int)> dfsN = [&](int u) {
        used[u] = true;
        for (int index : g[u])
        {
            auto& e = edges[index];
            bool sameDirection = e.u == u;
            int v = (e.t == 1 || sameDirection) ? e.v : e.u;
            if (!used[v])
            {
                if (e.t == 1)
                    dfsN(v);
                else
                    e.minimize = sameDirection ? '-' : '+';
            }
        }
    };

    used.clear();
    used.resize(n, false);
    dfsX(start);
    int countMaximal = accumulate(whole(used), 0);

    used.clear();
    used.resize(n, false);
    dfsN(start);
    int countMinimal = accumulate(whole(used), 0);

    int countOfUnoriented = 0;
    fori(m) countOfUnoriented += edges[i].t == 2;

    string maximize(countOfUnoriented, '!');
    string minimize(countOfUnoriented, '!');
    int j = 0;
    fori(m) if (edges[i].t == 2) maximize[j++] = edges[i].maximize;
    j = 0;
    fori(m) if (edges[i].t == 2) minimize[j++] = edges[i].minimize;
    writeln(countMaximal);
    writeln(maximize);
    writeln(countMinimal);
    writeln(minimize);
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
ttti   istream&operator>>(istream&is,vector<T>&a){for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,valarray<T>&a){for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
