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
#define     SZ(a)    int(size(a))

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
vector<string>split(string&s,string d){vector<string>v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}
#ifndef ONLINE_JUDGE
#   define N 10000
#else
#   define N 10000001
#endif

vector<int> cache[N];
int minPrime[N];
int prev[N];

//linearSieve
struct linearSieve
{
    vector<int> primes;

    linearSieve()
    {
        for (int i = 2; i < N; i++)
        {
            if (minPrime[i] == 0)
                primes.push_back(i),
                minPrime[i] = i;
            for (int prime : primes)
            {
                int temp = prime * i;
                if (temp < N && prime <= minPrime[i])
                    minPrime[temp] = prime,
                    prev[temp] = i;
                else
                    break;
            }
        }
    }

    void factorization(int x)
    {
        int X = x;
        if (SZ(cache[x])) return;
        vector<pii> temp;
        int p = -1;
        int pp = -1;
        while (x > 1)
        {
            pp = p;
            p = minPrime[x];
            if (p != pp)
                temp.pb({p, 1});
            else
                temp.back().second++;
            x = prev[x];
        }
        vector<int> divisors;
        function<void(int, int)> gen = [&](int v, int j) {
            if (j == SZ(temp))
            {
                if (v > 1)
                    divisors.pb(v);
                return;
            }
            gen(v, j + 1);
            fori(temp[j].second)
                gen(v *= temp[j].first, j + 1);
        };
        gen(1, 0);
        cache[X] = divisors;
    }

    bool isPrime(int x)
    {
        return minPrime[x] == x;
    }
};
//Igorjan
//}}}

void run()
{
    linearSieve s;
    //int q = 100; s.factorization(q); vector<int> f = cache[q]; writeln(SZ(f), f);
    //return;
    int n;
    scanf("%d", &n);
    vi a(n);
    fori(n)
        scanf("%d", &a[i]);
    int first = min_element(whole(a)) - a.begin();
    int second = -1;
    int mn = MOD;
    fori(n) if (i != first && mn > a[i]) mn = a[second = i];
    auto lcm = [&](int i, int j) {
        return a[i] * 1ll * a[j] / gcd(a[i], a[j]);
    };
    ll ans = lcm(first, second);
    vector<vector<int>> m(10000001);
    fori(n)
    {
        s.factorization(a[i]);
        const auto& f = cache[a[i]];
        //if (SZ(f) >= 300)
            //writeln(a[i], SZ(f));
        //continue;
        //if (i % 1000 == 0) writeln(i), writeln(SZ(f), a[i]), cout.flush();
        for (const int& d : f)
        {
            auto& temp = m[d];
            if (temp.size() <= 1)
            {
                temp.pb(i);
                if (temp.size() == 2 && a[temp[0]] > a[temp[1]])
                    swap(temp[0], temp[1]);
            }
            else
            {
                if (a[temp[0]] > a[i])
                    temp[1] = temp[0],
                    temp[0] = i;
                else if (a[temp[1]] > a[i])
                    temp[1] = i;
            }
        }
    }
    fori(N)
        if (const auto& temp = m[i]; temp.size() >= 2)
            if (ll l = a[temp[0]] / i * 1ll * a[temp[1]]; l < ans)
                ans = l,
                first = temp[0],
                second = temp[1];

    writeln(min(first, second) + 1, max(first, second) + 1);
    //cerr << lcm(first, second) << "\n";
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
ttti   ostream&operator<<(ostream&os,vector<T>const&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>const&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>const&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
