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

int f(int i)
{
    return (i / 2) * (i / 2 - 1) / 2;
}

void run()
{
    ints(n, k);
    vector<pii> points = {{1000, 1000}, {1000, 2000}, {2000, 2000}, {2000, 1002}};
    vector<pii> dx     = {{-2, 2}, {-2, -2}, {2, -2}, {2, 2}};
    vector<pii> ans;
    int i = 0;
    int j = 0;
    int pot = 0;
    for (; f(i) <= k; ++i)
    {
        j = i % 4;
        ans.pb(points[j]);
        points[j].first += dx[j].first;
        points[j].second += dx[j].second;
        pot += i >= 2 && i % 2 == 0;
        if (f(i) == k)
            break;
    }
    int need = k - f(i - 1);
    if (f(i) == k)
        need = 0;
    if (need)
    {
        if (j == 1) 
        {
            if (need > pot / 2)
                ans.pb({points[2].first - (need - pot / 2) * 2 - 1, points[2].second});
            else
                ans.pb({ans.back().first + need * 2 + 1, points[2].second});
        }
        if (j == 3) 
        {
            //writeln("lol", need, pot / 2);
            if (need <= pot / 2)
                //writeln("lol", points[3]),
                ans.pb({ans.back().first - need * 2 - 1, ans.back().second});
            else
                ans.pb({points[0].first + (need - pot / 2) * 2 + 1, points[0].second});
        }
    }
    vector<pii> ans2;
    vector<pii> dy = {{2, -2}, {2, 2}, {-2, 2}, {-2, -2}};
    vector<pii> points2;
    int mnx, mny, mxx, mxy;
    mnx = mny = mxx = mxy = 1000;
    for (auto www : ans)
        mnx = min(mnx, www.first),
        mxx = max(mxx, www.first),
        mny = min(mny, www.second),
        mxy = max(mxy, www.second);
    points2.pb({mxx + 2, mny});
    points2.pb({mxx + 2, mxy + 2});
    points2.pb({mnx - 2, mxy + 2});
    points2.pb({mnx - 2, mny - 2});
    for (int q = int(ans.size()) - 1, j = 0; q < n; q++, j++)
        ans2.pb(points2[j % 4]),
        points2[j % 4].first += dy[j % 4].first,
        points2[j % 4].second += dy[j % 4].second;
    reverse(whole(ans2));
    if (ans2.size())
        writeln(ans2);
    writeln(ans);
}

int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    ints(t);
    fori(t)
        run();
#ifndef ONLINE_JUDGE
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
