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

void run()
{
    ints(n);
    vi x(n);
    readln(x);
    sort(whole(x));
    set<pii> a;
    set<pii, greater<pii>> b;
    fori1(n - 1)
        a.insert({x[i + 1] - x[i - 1], i});
    b.insert({x[1] - x[0], 0});
    b.insert({x[n - 1] - x[n - 2], n - 1});
    set<int> nn, pp;
    fori(n)
        nn.insert(i),
        pp.insert(-i);

    fori(n - 2)
    {
        if (i % 2 == 0)
        {
            int w = b.begin()->second, u, v;
            b.erase(b.begin());
            nn.erase(w);
            pp.erase(w);
            //wr(w);
            auto c = nn.lower_bound(w + 1);
            if (c != nn.end())
            {
                u = *c;
                v = *nn.lower_bound(u + 1);
                b.insert({x[v] - x[u], u});
            }
            else
            {
                v = w;
                u = -*pp.lower_bound(-v + 1);
                w = -*pp.lower_bound(-u + 1);
                b.insert({x[u] - x[w], u});
            }
            a.erase({x[v] - x[w], u});
            //detele first or last
        }
        else
        {
            int u = a.begin()->second;
            int v = *nn.lower_bound(u + 1);
            int w = -*pp.lower_bound(-u + 1);
            auto d = nn.lower_bound(v);
            auto c = pp.lower_bound(-w + 1);
            a.erase({x[v] - x[w], u});
            nn.erase(u);
            pp.erase(u);
            if (d != nn.end())
            {
                a.erase({x[*d] - x[u], v});
                a.insert({x[*d] - x[w], v});
            }
            else
            {
                b.erase({x[v] - x[u], v});
                b.insert({x[v] - x[w], v});
            }
            if (c != pp.end())
            {
                a.erase({x[v] - x[*c], w});
                a.insert({x[v] - x[*c], w});
            } 
            else
            {
                b.erase({x[u] - x[w], w});
                b.insert({x[v] - x[w], w});
            }
            //delete with smallest dist
        }
        //writeln("b");
        //writeln_range(whole(b));
        //writeln();
        //for (auto t : nn)
            //print(x[t]);
        //writeln();
    }
    writeln(abs(x[b.begin()->second] - x[b.rbegin()->second]));
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
