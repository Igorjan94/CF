// Igorjan94, template version from 13 October 2017. C++17 version, modified 14 september 2019 (writeln<T>, main) {{{
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(size(a))

typedef  pair<int, int>   pii;
typedef   vector<int>     vi;
typedef    long long      ll;

#define    pb    push_back
#define whole(a) begin(a), end(a)

#define ints(a...)  int a; readln(a)
#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline

const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();

void writelnce(){cerr<<"\n";}void writeln(){cout<<"\n";}ttti void printce(T&& a);ttti void priwsce(T&& a);ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
tthti void writelnce(H&& h,T&&...t){priwsce(h);(printce(t),...);writelnce();}
vector<string>split(string&s,string d){vector<string>v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//printAns
ttta void printAnswerAndExit(Args... args){writelnce(args...);exit(0);}

//}}}

void run()
{
    srand((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define   next   next__
#define   prev   prev__
#define  count   count__
    int S = 5;
    int n = 100000;
    //int n = 1000;
    ll diff = 1000000;
    ll last = 1;
    int server = 0;
    vector<vector<ll>> s(S);
    vector<ll> all;
    fori(n)
    {
        ll next = last + rand() % diff;
        if (rand() % 2)
            server = (server + 1) % S;
        s[server].pb(next);
        all.pb(next);
        last = next;
    }
    writeln(1, S);
    vector<int> count(S);
    fori(S) count[i] = s[i].size();
    writeln(count);
    int guess = 1 + rand() % (n - 1);
    writeln(guess);
    int ccc = 0;
    while (true)
    {
        if (ccc > 1001)
            printAnswerAndExit("REQUEST LIMIT EXCEEDED", ccc - 1);
        char c;
        readln(c);
        if (c == '!')
        {
            if (ccc > 101)
                printAnswerAndExit("REQUEST LIMIT EXCEEDED", ccc - 1);
            ll x;
            readln(x);
            if (x == all[guess - 1])
                printAnswerAndExit("OK", ccc - 1);
            else
                printAnswerAndExit("FAIL", x, all[guess - 1]);
        }
        else
        {
            ll x, y;
            readln(x, y);
            writeln(s[--x][--y]);
            ++ccc;
        }
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    run();
    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

#define a _a
#define n _n
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void printce(T&&a){cerr<<" "<<a;}
ttti void priwsce(T&&a){cerr<<a;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
