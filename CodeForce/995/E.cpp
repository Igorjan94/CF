// Igorjan94, template version from 13 October 2017. C++17 version {{{
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
#define whole(a) a.begin(), a.end()
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
                    
void writeln(){cout<<"\n";}ttti void print(T a);ttti void priws(T a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H h,T...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}


//binpow
ll binpow(ll a, ll n, ll p)
{
    ll res = 1;
    while (n > 0)
    {
        if (n & 1)
            res = (res * a) % p;
        a = (a * a) % p;
        n >>= 1;
    }
    return res;
}
//Igorjan
//}}}
///-------------------------------------------------------------------------------------------------------------------------------------

void run()
{
    ints(u, v, p);
    int SIZE = 19;
    map<int, vi> can, can2;
    function<void(int, vi)> dfs = [&](int u, vi states)
    {
        if (can[u].size() != 0 || states.size() >= SIZE)
            return;
        can[u] = states;

        if (states.size() == 0 || states.back() != 2)
        {
            states.pb(1);
            dfs((u + 1) % p, states);
            states.pop_back();
        }
        if (states.size() == 0 || states.back() != 1)
        {
            states.pb(2);
            dfs((u + p - 1) % p, states);
            states.pop_back();
        }
        if (states.size() == 0 || states.back() != 3)
        {
            states.pb(3);
            dfs(binpow(u, p - 2, p), states);
            states.pop_back();
        }
    };

    function<void(int, vi)> dfs2 = [&](int u, vi states)
    {
        if (can2[u].size() != 0 || states.size() >= SIZE)
            return;
        can2[u] = states;

        if (states.size() == 0 || states.back() != 1)
        {
            states.pb(2);
            dfs2((u + 1) % p, states);
            states.pop_back();
        }
        if (states.size() == 0 || states.back() != 2)
        {
            states.pb(1);
            dfs2((u + p - 1) % p, states);
            states.pop_back();
        }
        if (states.size() == 0 || states.back() != 3)
        {
            states.pb(3);
            dfs2(binpow(u, p - 2, p), states);
            states.pop_back();
        }
    };

    dfs(u, {});
    dfs2(v, {});
    for (auto& [k, v]: can)
        if (can2[k].size() != 0)
        {
            vi ans;
            for (auto& x: v)
                ans.pb(x);
            auto temp = can2[k];
            reverse(whole(temp));
            for (auto& x: temp)
                ans.pb(x);
            writeln(ans.size());
            writeln(ans);
            return;
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
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
