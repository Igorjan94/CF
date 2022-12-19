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
//}}}

typedef bitset<37> state;

map<char, int> m = {
    {'6', 0},
    {'7', 1},
    {'8', 2},
    {'9', 3},
    {'T', 4},
    {'J', 5},
    {'Q', 6},
    {'K', 7},
    {'A', 8}
};
auto mm = "6789TJQKA";
map<char, int> z = {
    {'C', 0},
    {'D', 1},
    {'S', 2},
    {'H', 3},
};
auto zz = "CDSH";

int get(const string& s)
{
    return m[s[0]] + 9 * z[s[1]];
}

string unwrap(int x)
{
    int M = x % 9;
    int Z = x / 9;
    string s;
    s += mm[M];
    s += zz[Z];
    return s;
}

state convert(const vector<string>& ss) {
    state cc;
    for (const string& s: ss)
        cc[get(s)] = true;
    return cc;
};

vector<string> unconvert(const state& cc) {
    vector<string> ss;
    fori(36)
        if (cc[i])
            ss.pb(unwrap(i));
    return ss;
};

typedef array<state, 3> states;

vector<states> go(const state& s, const state& cur, const state& other) {
    vector<states> ans;
    bool step = s[36];
    const auto& cards = step ? cur : other;
    for (int i = cards._Find_first(); i < SZ(cards); i = cards._Find_next(i))
    {
        int value = i % 9;
        if (value == 3 || (value < 3 && s[i + 1]) || (value > 3 && s[i - 1]))
        {
            auto ns = s;
            auto nc = cards;
            ns[i].flip();
            nc[i].flip();
            ns[36].flip();
            ans.pb({ns, step ? nc : cur, step ? other : nc});
        }
    }

    if (ans.size() == 0)
    {
        auto ns = s;
        ns[36].flip();
        ans.pb({ns, cur, other});
    }
    return ans;
}

void run()
{
    vector<string> alice(18);
    vector<string> bob(18);
    readln(alice, bob);
    state a = convert(alice);
    state b = convert(bob);

    unordered_map<state, int> cache;

    states start = {state(), a, b};
    start[0][36] = true;

    auto dfs = [&](auto dfs, const states& s) -> int {
        auto it = cache.find(s[0]);
        if (it != cache.end())
            return it->second;

        auto f = [&]() -> int {
            bool step = s[0][36];
            //fori(3)
                //writeln(s[i].to_string());
            //writeln(); cout.flush();

            if (s[1].count() == 0)
                return s[2].count();
            if (s[2].count() == 0)
                return -int(s[1].count());
            auto nstates = go(s[0], s[1], s[2]);
            vector<int> pos;
            vector<int> neg;
            for (auto& ns: nstates)
            {
                auto ret = dfs(dfs, ns);
                if (ret > 0)
                    pos.pb(ret);
                else
                    neg.pb(ret);
                if ((step && ret > 0) || (!step && ret < 0))
                    break;
            }
            sort(all(pos));
            sort(all(neg));
            if (step) //Alice
            {
                if (pos.size())
                    return pos.back();
                return neg.back();
            }
            else
            {
                if (neg.size())
                    return neg.back();
                return pos.back();
            }
        };
        return cache[s[0]] = f();
    };
    auto winner = dfs(dfs, start);
    if (winner > 0)
        writeln("Alice");
    else
        writeln("Bob");
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
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"  "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
