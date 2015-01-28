//Igorjan94, template version from 23 January 2015
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
ttti  void writeln_range(T f,T s){if(f!=s){priws(*f);for(auto i=++f;i!=s;++i)print(*i);}writeln();}
tthti void err(vector<string>::iterator it,Head head,Tail...tail){writeln((*it).substr((*it)[0]==' '),"=",head);err(++it, tail...);}
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

#define  ints(args...) int args; readln(args)
#define   lls(args...)  ll args; readln(args)
#define vints(args...)  vi args; readln(args)

///-------------------------------------------------------------------------------------------------------------------------------------
vector<vi> a;
vector<string> s;
vector<pair<string, vector<pair<char, char>>>> xxx;
vector<pair<char, char>> q;
vi one;

void run()
{
    ints(n, h, w); 
    one.clear();
    s.clear();
    a.clear();
    q.clear();
    xxx.clear();
    s.resize(h);
    a.resize(h, vi(w, 0));
    one.resize(26, 0);
    string ss;
    readln(s);
    fori(s.size())
        forj(s[i].size())
            one[s[i][j] - 'A']++;
    string c;

    fori(h)
    {
        q.clear();
        forj(w)
            q.eb(i, j);
        xxx.eb(s[i], q);
    }
    forj(w)
    {
        c.clear();
        q.clear();
        fori(h)
            q.eb(i, j),
            c.pb(s[i][j]);
        xxx.eb(c, q);
    }

    for (int i = 0; i < w + h; i++)
    {
        c.clear();
        q.clear();
        for (int j = 0; j <= i; j++)
        {
            int y = h + j - i - 1;
            int u = j;
            if (y >= 0 && y < h && u >= 0 && u < w)
                q.eb(y, u),
                c.pb(s[y][u]);
        }
        if (c.size())
            xxx.eb(c, q);
    }

    for (int i = 0; i < w + h; i++)
    {
        c.clear();
        q.clear();
        for (int j = 0; j <= i; j++)
        {
            int y = i - j;
            int u = j;
            if (y >= 0 && y < h && u >= 0 && u < w)
                q.eb(y, u),
                c.pb(s[y][u]);
        }
        if (c.size())
            xxx.eb(c, q);
    }
    

    string ans = "";
    string temp, tt;
    fori(n)
    {
        int ok = -1, d, cnt = 0, rev = 0;
        readln(ss);
        if (ss.size() == 1)
        {
            if (one[ss[0] - 'A'] > 1)
                ans = "ambiguous";
            else
            {
                forn(r, s.size())
                    forj(s[r].size())
                        if (s[r][j] == ss[0])
                            a[r][j] = 1;
            }
            continue;
        }
        forj(xxx.size())
        {
            if ((d = xxx[j].first.find(ss)) != string::npos)
            {
                cnt++;
                ok = j;
                temp = xxx[j].first.substr(d + 1);
                if (temp.size() >= ss.size() && temp.find(ss) != string::npos)
                    cnt++;
            }
            reverse(whole(xxx[j].first));
            if ((d = xxx[j].first.find(ss)) != string::npos)
            {
                cnt++;
                ok = j;
                rev = 1;
                temp = xxx[j].first.substr(d + 1);
                if (temp.size() >= ss.size() && temp.find(ss) != string::npos)
                    cnt++;
            }
            reverse(whole(xxx[j].first));
        }
        tt = ss;
        reverse(whole(tt));
        if (ss == tt)
            cnt /= 2;
        if (cnt == 0)
        {
            writeln("no solution");
            return;
        }
        if (cnt > 1)
        {
            ans = "ambiguous";
            continue;
        }
        if (rev)
            reverse(whole(xxx[ok].first)),
            reverse(whole(xxx[ok].second));
        int t = xxx[ok].first.find(ss);
        forj(ss.size())
            a[xxx[ok].second[t + j].first][xxx[ok].second[t + j].second] = 1;
        if (rev)
            reverse(whole(xxx[ok].first)),
            reverse(whole(xxx[ok].second));
    }
    if (ans == "")
        fori(h)
            forj(w)
                if (!a[i][j])
                    ans.pb(s[i][j]);
    if (ans == "")
        ans = "empty spell";
    writeln(ans);

    writeln(xxx);
}

int main()
{
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    ints(T);
    fori(T)
        cerr << "test " << (i + 1) << "/" << T << "\n",
        //cout << "Case #" << (i + 1) << ": ",
        run();
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
