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
    map<int, pii> p1, p2;
    queue<int> q1, q2;
    int found = -1;
    q1.push(u);
    q2.push(v);

    auto contains = [&](map<int, pii>& m, int value) { return m.find(value) != m.end(); };

    auto push1 = [&](int next, pii prev) {
        if (contains(p1, next))
            return;
        p1[next] = prev;
        q1.push(next);
    };

    auto push2 = [&](int next, pii prev) {
        if (contains(p2, next))
            return;
        p2[next] = prev;
        q2.push(next);
        if (contains(p1, next))
            found = next;
    };

    auto next = [&](int x) { return (x + 1) % p; };
    auto prev = [&](int x) { return (x + p - 1) % p; };
    auto inverse = [&](int x) { return binpow(x, p - 2, p); };

    while (found == -1)
    {
        int x = q1.front();
        int y = q2.front();
        q1.pop();
        q2.pop();

        push1(next(x), {x, 1});
        push1(prev(x), {x, 2});
        push1(inverse(x), {x, 3});

        push2(next(y), {y, 2});
        push2(prev(y), {y, 1});
        push2(inverse(y), {y, 3});
    }

    vi ans;
    int x = found;
    int y = found;
    while (x != u)
        ans.pb(p1[x].second),
        x = p1[x].first;
    reverse(whole(ans));
    while (y != v)
        ans.pb(p2[y].second),
        y = p2[y].first;
    writeln(ans.size());
    writeln(ans);
    return;
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
