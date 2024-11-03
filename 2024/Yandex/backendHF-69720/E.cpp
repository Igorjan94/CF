#include <algorithm>
#pragma GCC optimize("O3","unroll-loops")
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
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}

typedef int Q;

inline auto sb(int& section, int r) {
    return section ^= (1 << r);
}
inline auto sb(int& section, int row, int col) {
    return section ^= (1 << (row * 6 + col));
}
inline auto gb(int& section, int r) {
    return !!(section & (1 << r));
}
inline auto gb(int& section, int row, int col) {
    return !!(section & (1 << (row * 6 + col)));
}
inline auto cnt(int& section) {
    return __builtin_popcount(section);
}
vector<Q> slaves(6, 0);

void run()
{
    int all_bits = 0;
    fori(21) sb(all_bits, i);

    ints(n);
    auto sections = 0;

    fori(n)
    {
        ints(s, k); --s;
        forj(k)
        {
            ints(section, x); --section; --x;
            sb(slaves[s], section, x);
            sb(sections, section, x);
        }
    }
    ints(m);
    vector<array<int, 3>> requests(m);
    fori(m)
    {
        ints(s, a, b, c, t); --s; --a; --b; --c; --t;
        int q = 0;
        sb(q, 0, a);
        sb(q, 1, b);
        sb(q, 2, c);
        requests[i] = {s, q, t};
    }
    shuffle(all(requests), rng);

    auto validate = [&]() -> bool {
        for (auto& [s, q, t]: requests) {
            int needs = s;
            fori(6)
            {
                int nxt = (s + i + 1) % 6;
                auto& ss = slaves[nxt];
                if (ss & q)
                {
                    needs = nxt;
                    break;
                }
            }
            if (needs != t)
                return false;
        }
        return true;
    };

    int ans = 0;
    vector<int> sss;
    fori(21)
        if (!gb(sections, i))
            sss.push_back(i);
    vector<int> servers;
    fori(6)
        if (cnt(slaves[i]) != 3)
            servers.pb(i);
    if (SZ(servers) == 0)
    {
        if (validate()) ++ans;
        return writeln(ans);
    }

    fori(6) if (!gb(sections, 0, i))
        forj(6) if (!gb(sections, 1, j))
            forn(k, 9) if (!gb(sections, 2, k))
            {
                auto s = sections;
                sb(s, 0, i);
                sb(s, 1, j);
                sb(s, 2, k);
                auto check = [&](auto& check, Q& s, int i, int prev) -> void {
                    int server = servers[i];
                    if (i == SZ(servers) - 1) {
                        int cur = s ^ all_bits;
                        slaves[server] ^= cur;
                        if (validate())
                            ++ans;
                        slaves[server] ^= cur;
                        return;
                    } 
                    else 
                    {
                        if (cnt(slaves[server]) < 3) {
                            for (int fff = prev; fff < sss.size(); ++fff) if (!gb(s, sss[fff]))
                            {
                                int nxt = sss[fff];
                                sb(s, nxt);
                                sb(slaves[server], nxt);

                                check(check, s, i, fff + 1);

                                sb(slaves[server], nxt);
                                sb(s, nxt);
                            }
                        } else {
                            check(check, s, i + 1, 0);
                        }
                    }
                };
                check(check, s, 0, 0);
            }
    writeln(ans);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
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
