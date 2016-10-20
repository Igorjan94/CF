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
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return v;}
 
///-------------------------------------------------------------------------------------------------------------------------------------
//Igorjan
string colors = "BGRWY";
int n, m;
int cccc = 0;
vector<vector<int>> sizes;
 
struct lol
{
    int mc = -1, mx = 100, my = -1;
    char color;
    lol(){}
     
    const bool operator<(const lol& b) const {
        if (mc != b.mc)
                return mc > b.mc;
        if (my != b.my)
                return my > b.my;
        return mx < b.mx;
    }
};
vector<lol> sss;
 
void dfs(vector<string>& f, int i, int j, lol& temp)
{
    if (i < 0 || j < 0 || i == n || j == m || sizes[i][j] || f[i][j] != temp.color)
        return;
    sizes[i][j] = ++cccc;
    temp.mc = max(temp.mc, cccc);
    temp.mx = min(temp.mx, j);
    temp.my = max(temp.my, i);
    dfs(f, i + 1, j, temp);
    dfs(f, i - 1, j, temp);
    dfs(f, i, j + 1, temp);
    dfs(f, i, j - 1, temp);
}
 
void kill(vector<string>& f, int i, int j, char color)
{
    if (i < 0 || j < 0 || i == n || j == m || f[i][j] != color || f[i][j] == 'P')
        return;
    f[i][j] = 'P';
    kill(f, i + 1, j, color);
    kill(f, i - 1, j, color);
    kill(f, i, j + 1, color);
    kill(f, i, j - 1, color);
}
 
lol hasColorToKill(vector<string>& f, char color)
{
    sss.clear();
    fori(n)
        forj(m)
        sizes[i][j] = 0;
    lol notColor, isColor;
    fori(n)
        forj(m)
            if (sizes[i][j] == 0 && f[i][j] != 'P')
            {
                lol temp;
                temp.color = f[i][j];
                cccc = 0;
                dfs(f, i, j, temp);
                if (temp.mc > 1)
                    if (color == f[i][j])
                        isColor = min(isColor, temp);
                    else
                        notColor = min(notColor, temp);
            }
    if (notColor.mc != -1)
        return notColor;
    return isColor;
}
 
void toDown(vector<string>& f)
{
        int col = -1;
        forj(m)
        {
            int last = -1;
            bool ok = true;
            for (int i = n - 1; i >= 0; --i)
            {
                ok &= f[i][j] == 'P';
                if (f[i][j] == 'P' && last == -1)
                    last = i;
                if (f[i][j] != 'P' && last != -1)
                    swap(f[i][j], f[last--][j]);
            }
     
            if (ok && col == -1)
                col = j;
            if (!ok && col != -1)
            {
                fori(n)
                    swap(f[i][col], f[i][j]);
                col++;
            }
        }
}
 
void toLeft(vector<string>& f)
{
    return;
    forn(q, n)
        forj(m)
        {
            int cc = 0;
            fori(n)
                cc += f[i][j] == 'P';
            if (cc == n && j + 1 < m)
                fori(n)
                    swap(f[i][j], f[i][j + 1]);
        }
}
 
ll proceed(vector<string> f, char color)
{
    ll ans = 0;
    while (true)
    {
        lol temp = hasColorToKill(f, color);
        if (temp.mc == -1)
                return ans;
        ans += temp.mc * (temp.mc - 1);
        kill(f, temp.my, temp.mx, temp.color);
//        writeln("ans +=", temp.mc, ans);
        //writeln("after kill");
        //writeln(f);
        //cout.flush();
        //int qwerqwerwqer;
  //      readln(qwerqwerwqer);
        toDown(f);
        toLeft(f);
//        writeln("after down and left");
        //writeln(f);
        //cout.flush();
//        readln(qwerqwerwqer);
    }
    return ans;
}
 
void run()
{
    readln(n, m);
    vector<string> s(n);
    readln(s);
    sizes.resize(n, vector<int>(m));
 
    for (char mainColor : colors)
    {
        fori(n)
            forj(m)
                if (s[i][j] == mainColor)
                {
                    printf("%c: %lld\n", mainColor, proceed(s, mainColor));
                    goto skip;
                }
        skip:
            42;
    }
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
    //writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
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
