// Igorjan94, template version from 13 October 2017. C++17 version, modified 07 August 2018 (&&, whole) {{{
#include <bits/stdc++.h>

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

map<tuple<int, int, int>, int> cache;

bool get(int x, int y, int z)
{
    if (x < z) swap(x, z);
    if (x == z) return false;
    if (x == y || y == z) return true;
    if (cache.find({x, y, z}) != cache.end())
        return cache[{x, y, z}];
    writeln("?", x + 1, y + 1, z + 1);
    cout.flush();
    string s;
    readln(s);
    return cache[{x, y, z}] = s == "Yes";
}

void printAnsAndExit(int ans)
{
    writeln('!', ans + 1);
    exit(0);
}

void run()
{
    vector<int> possible;
    ints(n, k);
    int d = 1;
    int cnt = 1;
    int cur = 1;
    while (cnt < n) cur *= k, cnt += cur, ++d;
    fori(n) possible.pb(i);
    while (true)
    {
        int x = possible[rng() % possible.size()];
        int z = possible[rng() % possible.size()];
        if (x == z) continue;
        vector<int> path;
        fori(n)
            if (get(x, i, z))
                path.pb(i);
        sort(whole(path), [&](int a, int b) {
            return get(x, a, b);
        });
        if (path.size() == d * 2 - 1)
            printAnsAndExit(path[d - 1]);
        else
            FOR(i, 1, path.size() - 1)
                if (auto it = find(whole(possible), path[i]); it != possible.end())
                    possible.erase(it);
    }
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
