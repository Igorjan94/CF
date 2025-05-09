// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

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

#define pb push_back
#define all(a) begin(a), end(a)
#define ints(a...) int a; readln(a)

[[maybe_unused]] const int MOD = 1000000007;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

#define ttt12i template<class T1, class T2> inline
#define  ttti  template<class T> inline

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

//Igorjan
//linearSieve
struct linearSieve
{
    vector<int> primes;
    vector<int> mobius;
    vector<int> phi;
    vector<int> minPrime, prev;

    linearSieve(int N, bool calcPhi = false)
    {
        ++N;
        minPrime.resize(N, 0);
        prev.resize(N, 0);
        mobius.resize(N, 0);
        mobius[1] = 1;
        for (int i = 2; i < N; i++)
        {
            if (minPrime[i] == 0)
                mobius[i] = -1,
                primes.push_back(i),
                minPrime[i] = i;
            for (int prime : primes)
            {
                int temp = prime * i;
                if (temp < N && prime <= minPrime[i])
                    minPrime[temp] = prime,
                    mobius[temp] = minPrime[i] == prime ? 0 : -mobius[i],
                    prev[temp] = i;
                else
                    break;
            }
        }
        if (calcPhi) 
        {
            phi.resize(N, 0);
            iota(all(phi), 0);
            for (int i = 2; i < N; i++)
                if (phi[i] == i)
                    for (int j = i; j < N; j += i)
                        phi[j] -= phi[j] / i;
        }
    }

    vector<pair<int, int>> foldedFactorization(int x)
    {
        vector<pair<int, int>> temp;
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
        return temp;
    }

    vector<int> divisors(int x, bool nonTrivial = true)
    {
        vector<int> ans = {x};

        const vector<pair<int, int>>& fold = foldedFactorization(x);
        function<void(int, int)> gen = [&](int v, int j) {
            if (j == int(fold.size()))
            {
                if (!nonTrivial || (v != 1 && v != x))
                    ans.pb(v);
                return;
            }
            gen(v, j + 1);
            fori(fold[j].second)
                gen(v *= fold[j].first, j + 1);
        };
        gen(1, 0);

        return ans;
    }

    vector<int> sortedDivisors(int x, bool nonTrivial = true)
    {
        vector<int> ans = divisors(x, nonTrivial);
        sort(ans.begin(), ans.end());
        return ans;
    }

    vector<int> factorization(int x)
    {
        vector<int> temp;
        while (x > 1)
            temp.push_back(minPrime[x]),
            x = prev[x];
        return temp;
    }

    bool isPrime(int x)
    {
        return minPrime[x] == x;
    }
};

//}}}

linearSieve s(100005);

ll f(vector<int>& a, int l, int r, int k) {
    ll ans = 0;
    FOR(i, l, r + 1) {
        while (k % a[i] == 0)
            k /= a[i];
        ans += k;
    }
    return ans;
}

void run()
{
    ints(n, q);
    vector a(n, 0);
    readln(a);
    map<int, set<int>> m;
    fori(n)
        m[a[i]].insert(i);
    forn(Q, q)
    {
        ints(k, l, r); --l; --r;
        ll ans = 0;
        while (l <= r) {
            auto divs = s.divisors(k);
            int index = r + 1;
            for (int d: divs)
                if (auto it = m.find(d); it != m.end()) {
                    auto has = it->second.lower_bound(l);
                    if (has != it->second.end())
                        index = min(index, *has);
                }
            ans += (index - l) * 1ll * k;
            if (index > r) break;
            while (k % a[index] == 0)
                k /= a[index];
            l = index;
        }
        writeln(ans);
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ints(t); fori(t) run();
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
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
