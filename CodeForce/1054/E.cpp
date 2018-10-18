// Igorjan94, template version from 13 October 2017. C++17 version, modified 07 August 2018 (&&, whole) {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

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

#define    pb    push_back
#define whole(a) begin(a), end(a)
#define   next   next__
#define   prev   prev__
#define  count   count__

#define ints(a...)  int a; readln(a)
#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline

const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();
const ll LLMAX = numeric_limits<ll>::max();

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//}}}

vector<tuple<int, int, int, int>> ans;
vector<vector<string>> s, t;
int n, m;

void move(int i, int j, int u, int v, char c = '$')
{
    if (c != '$')
        s[u][v].pb(c);
    ++i; ++j; ++u; ++v;
    if ((i == 1 && v == m) || (i == n && v == 1))
    {
        if (j != v)
            ans.emplace_back(i, j, i, v);
        if (i != u)
            ans.emplace_back(i, v, u, v);
    }
    else
    {
        if (i != u)
            ans.emplace_back(i, j, u, j);
        if (j != v)
            ans.emplace_back(u, j, u, v);
    }
}


void lul(vector<vector<string>>& ss)
{
    fori(n)
        forj(m)
            printf("%5s%c", ss[i][j].c_str(), " \n"[j == m - 1]);
    printf("\n");
}

#define ZEROS 0, 0
#define ONES (n - 1), (m - 1)
#define C1 0, (m - 1)
#define C2 (n - 1), 0

void run()
{
    auto moveCase = [&](int i, int j, char c) {
        if (c == '0')
            move(i, j, ZEROS, c);
        else
            move(i, j, ONES, c);
    };

    auto moveCaseStr = [&](int i, int j) {
        for (char& c: s[i][j])
            moveCase(i, j, c);
        s[i][j] = "";
    };

    auto getCase = [&](int i, int j, char c) {
        if (c == '0')
            move(ZEROS, i, j);
        else
            move(ONES, i, j);
    };

    auto getCaseStr = [&](int i, int j) {
        for (char& c: t[i][j])
            getCase(i, j, c);
    };

    readln(n, m);
    s.resize(n, vector<string>(m));
    t.resize(n, vector<string>(m));
    readln(s, t);
    fori(n)
        forj(m)
            reverse(whole(s[i][j])),
            reverse(whole(t[i][j]));
    for (char c : s[0][0]) move(ZEROS, C1, c);
    for (char c : s[n - 1][m - 1]) move(ONES, C2, c);
    s[0][0] = "";
    s[n - 1][m - 1] = "";

    moveCaseStr(C1);
    moveCaseStr(C2);
    fori1(n - 1) moveCaseStr(i, 0), moveCaseStr(i, m - 1);
    forj1(m - 1) moveCaseStr(0, j), moveCaseStr(n - 1, j);
    fori1(n - 1) forj1(m - 1) moveCaseStr(i, j);

    fori1(n - 1) forj1(m - 1) getCaseStr(i, j);
    forj1(m - 1) getCaseStr(0, j), getCaseStr(n - 1, j);
    fori1(n - 1) getCaseStr(i, 0), getCaseStr(i, m - 1);
    for (char& c: t[0][0]) getCase(C1, c);
    for (char& c: t[n - 1][m - 1]) getCase(C2, c);
    getCaseStr(C1);
    getCaseStr(C2);
    for (char& c: t[0][0]) move(C1, ZEROS);
    for (char& c: t[n - 1][m - 1]) move(C2, ONES);

    printf("%zu\n", ans.size());
    for (auto&[x, y, z, u]: ans)
        printf("%d %d %d %d\n", x, y, z, u);
}

//{{{
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
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&& a){cout<<" "<<a;}
ttti void priws(T&& a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
