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
#define     INF      1000000009
                    
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

vector<string> chars = {"L", "R", "U", "D"};
vector<string> states;

int getPrice(char to, string u, string v)
{
    if (u[0] == v[0] && u[1] == v[1])
    {
        if (to == 'N' && v[2] == '0' && v[3] == '0')
            return 0;
        if (to == 'N')
            return INF;
        if (to == v[0] && v[2] == '1' && v[3] == '0')
            return 1;
        if (to == v[1] && v[2] == '0' && v[3] == '1')
            return 1;
        return INF;
    }
    if (u[0] == v[0])
    {
        if ((v[1] == to || to == 'N') && v[2] == '0' && v[3] == '1')
            return u[3] == '1' ? 9 : 3;
        return INF;
    }
    if (u[1] == v[1])
    {
        if ((v[0] == to || to == 'N') && v[2] == '1' && v[3] == '0')
            return u[2] == '1' ? 9 : 3;
        return INF;
    }
    if (v[2] == '1' && v[3] == '1')
        return 10;
    return INF;
}

void run()
{
    ints(n);
    string s;
    readln(s);
    int start;
    for (string& c: chars)
        for (string& d: chars)
            if (c != d)
                if (c != "R" || d != "L")
                {
                    if (c == "L" && d == "R")
                        start = states.size();
                    states.pb(c + d + "00");
                    states.pb(c + d + "01");
                    states.pb(c + d + "10");
                    states.pb(c + d + "11");
                }
    int m = states.size();
    vector<vector<int>> dp(n + 1, vector<int>(m, INF));
    vector<vector<int>> last(n + 1, vector<int>(m));
    dp[0][start] = 0;
    fori1(n + 1)
        forj(m)
            if (dp[i - 1][j] < INF)
                forn(to, m)
                    if (states[to].find(s[i - 1]) != string::npos || (s[i - 1] == 'N'))
                    {
                        //writeln("needs:", s[i - 1], "    ", states[j], "->", states[to], getPrice(s[i - 1], states[j], states[to]));
                        auto temp = dp[i - 1][j] + getPrice(s[i - 1], states[j], states[to]);
                        if (temp < dp[i][to])
                            dp[i][to] = temp,
                            last[i][to] = j;
                    }
    int ans = numeric_limits<int>::max();
    int index = -1;
    fori(m)
        if (ans > dp[n][i])
            ans = dp[n][i],
            index = i;
    writeln(ans);
    vector<string> aaa;
    ROF(i, n, 1)
        aaa.pb(states[index].substr(0, 2)),
        index = last[i][index];
    reverse(whole(aaa));
    fori(aaa.size())
        writeln(aaa[i]);
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
