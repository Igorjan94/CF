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

#define point pair<long double, long double>

void run()
{
    ints(ax, ay, bx, by, tx, ty, n);
	vector<point> a(n);
    vector<long double> dists(n, 0.0), as(n, 0.0), bs(n, 0.0);
	readln(a);
    auto dist = [&](point x, long double tx, long double ty) {
        return sqrt((x.first - tx) * (x.first - tx) + (x.second - ty) * (x.second - ty));
    };
    auto argmin = [&](vector<long double>& a) {
        auto mn = numeric_limits<long double>::max();
        int index = -1;
        fori(a.size())
            //if (a[i] < dists[i])
                if (a[i] - dists[i] < mn)
                    index = i,
                    mn = a[i] - dists[i];
        return index;
    };
    if (a.size() == 1)
    {
        cout.precision(15);
        cout << fixed << dist(a[0], tx, ty) + min(dist(a[0], ax, ay), dist(a[0], bx, by)) << "\n";;
        return;
    }
    fori(n)
        dists[i] = dist(a[i], tx, ty),
        as[i]    = dist(a[i], ax, ay),
        bs[i]    = dist(a[i], bx, by);
    long double ans = accumulate(whole(dists), 0.0) * 2; 

    int ma = argmin(as);
    int mb = argmin(bs);
    long double da = as[ma] - dists[ma];
    long double db = bs[mb] - dists[mb];

    if (ma != mb)
    {
        if (da <= 0)
            ans += da;
        if (db <= 0)
            ans += db;
        if (da >= 0 && db >= 0)
            ans += min(da, db);
    }
    else
    {
        int m = ma;
        dists.erase(dists.begin() + m);
        as.erase(as.begin() + m);
        bs.erase(bs.begin() + m);
        ma = argmin(as);
        mb = argmin(bs);
        long double da2 = as[ma] - dists[ma];
        long double db2 = bs[mb] - dists[mb];
        ans += min(da + (db2 >= 0 ? 0 : db2), db + (da2 >= 0 ? 0 : da2));
    }
    cout.precision(15);
    cout << fixed << ans << "\n";
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
