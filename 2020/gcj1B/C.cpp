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

typedef  pair<short, short>   pii;
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

vector<pii> run()
{
    ints(r, s);
    int n = r * s;
    vector<pii> a;
    if (r == 2)
    {
        for (int i = 2; i < n; i += 2)
            a.pb({i, 1});
        return a;
    }
    if (s == 2)
    {
        if (r % 2 == 1)
        {
            a.pb({1, r - 1});
            for (int i = r; i < n - 2; i += 2)
                a.pb({2, i});
        }
        else
        {
            for (int i = r - 1; i < n - 2; i += 2)
                a.pb({2, i});
        }
        return a;
    }
    fori(n)
        a.pb({i % r, i % s});

    auto isCorrect = [&](const vector<pii>& x) {
        fori1(n)
            if (x[i].first < x[i - 1].first)
                return false;
        return true;
    };
    vector<tuple<int, vector<pii>, vector<pii>>> states = {{0, a, {}}}, nn;
    while (true)
    {
        nn.clear();
        for (auto& state: states)
        {
            int s = get<0>(state);
            auto moves = get<2>(state);
            auto x = get<1>(state);
            if (isCorrect(x))
                return moves;
            if (s == 0)
                for (int a = 1; a < n; ++a)
                    for (int b = 1; a + b < n; ++b)
                    {
                        moves.pb({a, b});
                        vector<pii> y;
                        fori(b)
                            y.pb(x[a + i]);
                        fori(a)
                            y.pb(x[i]);
                        fori(n - a - b)
                            y.pb(x[a + b + i]);
                        nn.pb({a + b + 2, y, moves});
                        moves.pop_back();
                    }
            else
                for (int a = 1; a < min(n, s); ++a)
                {
                    int b = min(n, s) - a;
                    moves.pb({a, b});
                    vector<pii> y;
                    fori(b)
                        y.pb(x[a + i]);
                    fori(a)
                        y.pb(x[i]);
                    fori(n - a - b)
                        y.pb(x[a + b + i]);
                    nn.pb({a + b + 2, y, moves});
                    moves.pop_back();
                }
        }
        states = nn;
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t);
    fori(t)
    {
        cout << "Case #" << (i + 1) << ": ";
        auto v = run();
        writeln(SZ(v));
        writeln(v);
    }
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
