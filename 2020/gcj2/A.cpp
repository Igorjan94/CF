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
#define     SZ(a)    int(a.size())

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

//binSearch
//x -> min, f(x) == true
template<typename T, typename F>
T binSearch(T l, T r, F f, T eps = 1)
{
    T m;
    while (abs(r - l) > eps)
        m = l + (r - l) / 2,
        (f(m) ? r : l) = m;
    return f(l) ? l : r;
}

//debug
vector<string>split(string&s,const string& d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
//}}}

tuple<ll, ll, ll> run()
{
    ll l, r;
    readln(l, r);
    ll start = 1;
    ll n = 0;
    while (true)
    {
        if (start > max(l, r)) break;

        ll mx = max(l, r) - min(l, r);
        if (start > mx)
        {
            n++;
            (l >= r ? l : r) -= start;
            start++;
            continue;
        }

        auto get = [](ll x) { return x * (x + 1) / 2; };
        ll x = binSearch(start, mx + 1, [&](ll m) {
            return get(m) - get(start - 1) > mx;
        });
        ll temp = get(x - 1) - get(start - 1);
        n += x - start;
        start = x;
        (l >= r ? l : r) -= temp;
    }
    return {n, l, r};
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t);
    fori(t)
        cout << "Case #" << (i + 1) << ": " << run() << "\n";
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
