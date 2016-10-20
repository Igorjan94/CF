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

void run()
{
    string s, q, w, e, r, t;
    int k;
    readln(s, k);
    vector<string> ans;
    int l = s.size();
    set<string> se;
    [&]() {
    if (s.size() >= k)
        switch (k) 
        {
            case 1:
                ans.pb(s);
                break;
            case 2:
                FOR(i, 1, l)
                {
                    q = s.substr(0, i);
                    w = s.substr(i, l);
                    if (q != w)
                    {
                        ans.pb(q);
                        ans.pb(w);
                        return;
                    }
                }
                break;
            case 3:
                FOR(i, 1, l)
                {
                    q = s.substr(0, i);
                    se.insert(q);
                    FOR(j, i + 1, l)
                    {
                        w = s.substr(i, j - i);
                        se.insert(w);
                        if (se.size() == 2)
                        {
                            e = s.substr(j, l);
                            se.insert(e);
                            if (se.size() == 3)
                            {
                                ans.pb(q);
                                ans.pb(w);
                                ans.pb(e);
                                return;
                            }
                            se.erase(w);
                        }
                    }
                    se.erase(q);
                }
                break;
            case 4:
                FOR(i, 1, l)
                {
                    q = s.substr(0, i);
                    se.insert(q);
                    FOR(j, i + 1, l)
                    {
                        w = s.substr(i, j - i);
                        se.insert(w);
                        if(se.size() == 2)
                        {
                            FOR(k, j + 1, l)
                            {
                                e = s.substr(j, k - j);
                                se.insert(e);
                                if (se.size() == 3)
                                {
                                    r = s.substr(k, l);
                                    se.insert(r);
                                    if(se.size() == 4)
                                    {
                                        ans.pb(q);
                                        ans.pb(w);
                                        ans.pb(e);
                                        ans.pb(r);
                                        return;
                                    }
                                    se.erase(e);
                                }
                            }
                            se.erase(w);
                        }
                    }
                    se.erase(q);
                }
                break;
            case 5:
                FOR(i, 1, l)
                {
                    q = s.substr(0, i);
                    se.insert(q);
                    FOR(j, i + 1, l)
                    {
                        w = s.substr(i, j - i);
                        se.insert(w);
                        if(se.size() == 2)
                        {
                            FOR(k, j + 1, l)
                            {
                                e = s.substr(j, k - j);
                                se.insert(e);
                                if (se.size() == 3)
                                {
                                    FOR(g, k + 1, l)
                                    {
                                        r = s.substr(k, g - k);
                                        se.insert(r);
                                        if(se.size() == 4)
                                        {
                                            t = s.substr(g, l);
                                            se.insert(t);
                                            if (se.size() == 5)
                                            {
                                                ans.pb(q);
                                                ans.pb(w);
                                                ans.pb(e);
                                                ans.pb(r);
                                                ans.pb(t);
                                                return;
                                            }
                                            se.erase(r);
                                        }
                                    }
                                    se.erase(e);
                                }
                            }
                            se.erase(w);
                        }
                    }
                    se.erase(q);
                }
                break;
        }
    }();
    if (ans.size() == 0)
        writeln("NO");
    else
        writeln("YES"),
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
