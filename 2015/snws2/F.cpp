//Igorjan94, template version from 08 January 2015
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
#define      vi      vector<int>
#define      pb      emplace_back
#define      vs      vector<string>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     vvi      vector<vector<int>>
#define     pll      pair<long long, long long>
#define   elohw(a)   a.rbegin(), a.rend()
#define   whole(a)   a.begin(), a.end()
#define    next      _next
#define    prev      _prev

#define argmax(a)    (max_element(whole(a)) - (a).begin())
#define argmin(a)    (min_element(whole(a)) - (a).begin())
#define wr(args...)  {err(split(#args,',').begin(),args);}

#define FILENAME "input"
#define INF 1000000007
#define DOUBLEFORMAT "%f"

#define tthti  template<typename Head, typename... Tail> inline
#define ttt12i template<typename T1, typename T2> inline
#define ttti   template<typename T> inline

inline void writeln2(){cout<<"\n";}
inline void writeln() {cout<<"\n";}
inline void readln()  {}
ttti void read(T &a);
ttti void priws(T a);
ttti void print(T a);

void err(vector<string>::iterator it){++it;}
tthti void readln (Head& head,Tail&... tail){read(head); readln  (tail...);}
tthti void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
tthti void writeln (Head head, Tail... tail){priws(head);writeln2(tail...);}
ttti  void writeln_range(T f,T s){priws(*f);for(auto i=++f;i!=s;++i)print(*i);}
tthti void err(vector<string>::iterator it,Head head,Tail...tail){writeln((*it).substr((*it)[0]==' '),"=",head);err(++it, tail...);}
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

///-------------------------------------------------------------------------------------------------------------------------------------

void run()
{
    vector<pair<ll, pair<pair<ll, ll>, pii>>> a;

#define X first
#define L second.first.first
#define R second.first.second
#define K second.second.first
#define J second.second.second
    ll x, y;
    int n;
    readln(n);
    a.resize(n);
    fori(n)
        readln(x, y),
        a[i] = {x, {{y, y}, {i, i}}};
    sort(whole(a));
    vi perm;
    fori(n)
        perm.pb(i);
    fori(n)
        swap(perm[i], perm[rand() % (i + 1)]);
    vi ans(n);
    int i;
    forn(q, n)
    {
        i = perm[q];
        ll l = a[i].L;
        ll r = a[i].R;
        int j, k;
        for (j = i + 1, k = i - 1; j < n || k >= 0; )
        {
            bool okj = false, okk = false;
            if (j < n)
                if (a[i].X + r >= a[j].X)
                    okj = true;
            if (k >= 0)
                if (a[i].X - l <= a[k].X)
                    okk = true;
            if (!okk && !okj)
                break;
            if (okj)
                r = max(r, a[j].X + a[j].R - a[i].X),
                l = max(l, a[i].X + a[j].L - a[j].X),
                j = max(j + 1, a[j].J);
            if (okk)
                r = max(r, a[k].X + a[k].R - a[i].X),
                l = max(l, a[i].X + a[k].L - a[k].X),
                k = min(k - 1, a[k].K);
        }
        a[i] = {a[i].X, {{l, r}, {k, j}}};
        ans[i] = j - k - 1;
    }
    writeln(ans);
}

int main()
{
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    int T;
    readln(T);
    fori(T)
        run();
    return 0;
}























#define a _a
#define n _n
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){os<<a[0];for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
