// Igorjan94, template version from 19 March 2015
#include <bits/stdc++.h>
#define ONLINE_JUDGE

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
#define    next      next__
#define    prev      prev__
#define   count      count__

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

#define    ints(args...)     int args; readln(args)
#define     lls(args...)      ll args; readln(args)
#define   vints(args...)      vi args; readln(args)
#define strings(args...)  string args; readln(args)

///-------------------------------------------------------------------------------------------------------------------------------------
//Igorjan

map<char, ll> count;
vector<char> order = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
vector<int> prices = {1, 5, 10, 50, 100, 500, 1000};

void run()
{
    int n, cc;
    char c;
    string s;
    string ans = "NO";
    readln(n, s);
    fori(s.size())
        count[s[i]]++;
    vector<int> a;
    ROF(i, order.size() - 1, 0)
        if (count[order[i]])
        {
            n -= (cc = count[order[i]]) * prices[i];
            count[order[i]] = 0;
            c = order[i];
            break;
        }
    forn(q, count[order[0]] + 1)
        forn(w, count[order[1]] + 1)
            forn(e, count[order[2]] + 1)
                forn(r, count[order[3]] + 1)
                    forn(t, count[order[4]] + 1)
                        forn(y, count[order[5]] + 1)
                            forn(u, count[order[6]] + 1)
                                if (n == prices[0] * (count[order[0]] - q * 2) + 
                                         prices[1] * (count[order[1]] - w * 2) + 
                                         prices[2] * (count[order[2]] - e * 2) + 
                                         prices[3] * (count[order[3]] - r * 2) + 
                                         prices[4] * (count[order[4]] - t * 2) + 
                                         prices[5] * (count[order[5]] - y * 2) + 
                                         prices[6] * (count[order[6]] - u * 2))
                                    a = {q, w, e, r, t, y, u};

    if (a.size())
    {
        ans = "";
        ROF(i, 6, 0)
            forj(a[i])
                ans += order[i];
        fori(cc)
            ans += c;
        ROF(i, 6, 0)
            forj(count[order[i]] - a[i])
                ans += order[i];
    }
    writeln(ans);
}

int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
