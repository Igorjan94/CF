// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
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
//printTuple
template<class Tuple, size_t... Is> ostream& print_tuple(ostream& os, const Tuple& t, index_sequence<Is...>) { ((os << (Is == 0 ? "" : " ") << get<Is>(t)), ...); return os; }
template<class Tuple, size_t... Is> istream& read_tuple(istream& is, Tuple& t, index_sequence<Is...>) { ((is >> get<Is>(t)), ...); return is; }
template<class... Args> inline ostream& operator<<(ostream& os, const tuple<Args...>& t) { return print_tuple(os, t, index_sequence_for<Args...>{}); }
template<class... Args> inline istream& operator>>(istream& is, tuple<Args...>& t) { return read_tuple(is, t, index_sequence_for<Args...>{}); }

//}}}
template<typename T = ll>
T extendedGcd(const T& a, const T& b, T& x, T& y)
{
	if (a == 0)
    {
		x = 0;
        y = 1;
		return b;
	}
	T x1, y1;
	T d = extendedGcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

template<typename T = ll>
bool diofant(const T& a, const T& b, const T& c, T& x0, T& y0, T& g)
{
	g = extendedGcd(abs(a), abs(b), x0, y0);
	if (c % g != 0)
		return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0) x0 *= -1;
	if (b < 0) y0 *= -1;
	return true;
}


void run()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ints(n);
    set<ll> s = {n};
    vector<ll> a = {n};
    vector<tuple<ll, char, ll>> actions;
    fori(90000)
    {
        ll x = a[rng() % a.size()];
        ll y = a[rng() % a.size()];
        int action = rng() % 2;
        ll z = action ? (x + y) : (x ^ y);
        if (s.find(z) != s.end())
            continue;
        else
        {
            s.insert(z);
            a.pb(z);
            actions.emplace_back(x, action ? '+' : '^', y);
        }
    }

    auto binMul = [&](ll a, ll n)
    {
        a = abs(a);
        n = abs(n);
        ll res = a; --n;
        while (n > 0)
        {
            if (n & 1)
            {
                actions.emplace_back(res, '+', a);
                res += a;
            }
            actions.emplace_back(a, '+', a);
            a += a;
            n >>= 1;
        }
        return res;
    };

    ll x0, y0, g;
    fori(a.size())
        FOR(j, i + 1, a.size())
            if (diofant(a[i], a[j], 1ll, x0, y0, g) && g == 1)
            {
                ll temp = abs(a[i] * 1ll * x0);
                ll temp2 = abs(a[j] * 1ll * y0);
                ll e = min(temp, temp2);
                ll r = max(temp, temp2);
                if (e % 2 == 0 && r == e + 1)
                {
                    ll q = binMul(a[i], x0);
                    ll w = binMul(a[j], y0);
                    actions.emplace_back(q, '^', w);
                    writeln(actions.size());
                    writeln(actions);
                    return;
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
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
