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

//printAns
ttti void printAnswerAndExit(T a){writeln(a);exit(0);}
//Igorjan

void run()
{
    lls(f, T, t0, a1, t1, p1, a2, t2, p2);
    if (min({t0, t1, t2}) * f > T)
        printAnswerAndExit(-1);
    //if (t2 > t1) swap(t2, t1), swap(a2, a1), swap(p2, p1);

    ll ans = numeric_limits<ll>::max();
    ll A, B, C;

    if (t0 <= min(t1, t2) || t0 * f <= T) //a is min or can use only priceless tariff
        printAnswerAndExit(0);
    for (ll b = 0; b <= f; ++b)
    {
        ll dt = t0 - t2;
        ll a = dt ? min(f - b, max(0ll, (T - b * t1 - f * t2 + b * t2) / dt)) : f;
        ll c = dt ? f - b - a : 0;
        assert(c >= 0);

        auto check = [&](ll a, ll b, ll c) {
            ll x = b / a1 + (b % a1 != 0);
            ll y = c / a2 + (c % a2 != 0);
            ll temp = x * p1 + y * p2;
            //writeln(a, b, c, temp);
            if (a + b + c >= f &&
                    a * t0 + b * t1 + c * t2 <= T &&
                    //(b % a1 == 0 || c % a2 == 0) && 
                    a >= 0 &&
                    b >= 0 &&
                    c >= 0 &&
                    a <= f &&
                    b <= f &&
                    c <= f &&
                    temp <= ans)
                ans = temp,
                A = a, B = b, C = c;
        };

        ll aa = max(0ll, f - b / a1 * a1);
        ll cc = max(0ll, f - b - aa);

        check(a, b, c);
        check(aa, b, cc);
    }
    assert(ans != numeric_limits<ll>::max());
    writeln(ans);
    //writeln(A, B, C);
    //writeln(ans == numeric_limits<ll>::max() ? -1 : ans);
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
