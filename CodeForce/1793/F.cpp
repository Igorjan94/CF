// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#include <cstddef>
#include <variant>

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

const int N = 3 * 100000 + 3;
const int Q = 1000001;
 
//Can correctly work with numbers in range [0; MAXN]. If element is not found return NOT_FOUND
//Supports all std::set operations in O(1) on random queries / dense arrays, O(log_64(N)) in worst case (sparce array).
//Count operation works in O(1) always.
//SOURCE: https://codeforces.com/contest/1793/submission/193330718
using uint = unsigned int;
using ull = unsigned long long;

template<uint MAXN, uint NOT_FOUND>           
class fastSet {
    static constexpr ull lowest_bitsll[] = {0ull, 1ull, 3ull, 7ull, 15ull, 31ull, 63ull, 127ull, 255ull, 511ull, 1023ull, 2047ull, 4095ull, 8191ull, 16383ull, 32767ull, 65535ull, 131071ull, 262143ull, 524287ull, 1048575ull, 2097151ull, 4194303ull, 8388607ull, 16777215ull, 33554431ull, 67108863ull, 134217727ull, 268435455ull, 536870911ull, 1073741823ull, 2147483647ull, 4294967295ull, 8589934591ull, 17179869183ull, 34359738367ull, 68719476735ull, 137438953471ull, 274877906943ull, 549755813887ull, 1099511627775ull, 2199023255551ull, 4398046511103ull, 8796093022207ull, 17592186044415ull, 35184372088831ull, 70368744177663ull, 140737488355327ull, 281474976710655ull, 562949953421311ull, 1125899906842623ull, 2251799813685247ull, 4503599627370495ull, 9007199254740991ull, 18014398509481983ull, 36028797018963967ull, 72057594037927935ull, 144115188075855871ull, 288230376151711743ull, 576460752303423487ull, 1152921504606846975ull, 2305843009213693951ull, 4611686018427387903ull, 9223372036854775807ull, 18446744073709551615ull};

    static const uint PREF = (MAXN <= 64 ? 0 :
                              MAXN <= 4096 ? 1 :
                              MAXN <= 262144 ? 1 + 64 :
                              MAXN <= 16777216 ? 1 + 64 + 4096 :
                              MAXN <= 1073741824 ? 1 + 64 + 4096 + 262144 : 227) + 1;
    static const uint SZ = PREF + (MAXN + 63) / 64 + 1;
    ull m[SZ] = {0};
 
    inline uint left(uint v) const {return (v - 62) * 64;}
    inline uint parent(uint v) const {return v / 64 + 62;}
    inline void setbit(uint v) {m[v >> 6] |= 1ull << (v & 63);}
    inline void resetbit(uint v) {m[v >> 6] &= ~(1ull << (v & 63));}
    inline uint getbit(uint v) const {return m[v >> 6] >> (v & 63) & 1;}
    inline ull childs_value(uint v) const {return m[left(v) >> 6];}
 
    inline uint left_go(uint x, const uint c) const {
        const ull rem = x & 63;
        uint bt = PREF * 64 + x;
        ull num = m[bt >> 6] & lowest_bitsll[rem + c];
        if (num) return (x ^ rem) | __lg(num);
        for (bt = parent(bt); bt > 62; bt = parent(bt)) {
            const ull rem = bt & 63;
            num = m[bt >> 6] & lowest_bitsll[rem];
            if (num) {bt = (bt ^ rem) | __lg(num); break;}
        }
        if (bt == 62) return NOT_FOUND;
        while (bt < PREF * 64) bt = left(bt) | __lg(m[bt - 62]);
        return bt - PREF * 64;
    }
 
    inline uint right_go(uint x, const uint c) const {
        const ull rem = x & 63;
        uint bt = PREF * 64 + x;
        ull num = m[bt >> 6] & ~lowest_bitsll[rem + c];
        if (num) return (x ^ rem) | __builtin_ctzll(num);
        for (bt = parent(bt); bt > 62; bt = parent(bt)) {
            const ull rem = bt & 63;
            num = m[bt >> 6] & ~lowest_bitsll[rem + 1];
            if (num) {bt = (bt ^ rem) | __builtin_ctzll(num); break;}
        }
        if (bt == 62) return NOT_FOUND;
        while (bt < PREF * 64) bt = left(bt) | __builtin_ctzll(m[bt - 62]);
        return bt - PREF * 64;
    }
 
public:
    fastSet() {
        assert(PREF != 228);
        setbit(62);
    }
 
    bool empty() const {return getbit(63);}
 
    void clear() {fill(m, m + SZ, 0); setbit(62);}
 
    bool count(uint x) const {return m[PREF + (x >> 6)] >> (x & 63) & 1;}
 
    void insert(uint x) {
        for (uint v = PREF * 64 + x; !getbit(v); v = parent(v)) {
            setbit(v);
        }
    }
 
    void erase(uint x) {
        if (!getbit(PREF * 64 + x)) return;
        resetbit(PREF * 64 + x);
        for (uint v = parent(PREF * 64 + x); v > 62 && !childs_value(v); v = parent(v)) {
            resetbit(v);
        }
    }
 
    uint lower_bound(uint x) const {return right_go(x, 0);}
    uint upper_bound(uint x) const {return right_go(x, 1);}
    uint inverse_lower_bound(uint x) const {return left_go(x, 1);}
    uint inverse_upper_bound(uint x) const {return left_go(x, 0);}
};
//Igorjan
//}}}

inline ll hilbertOrder(int x, int y, int pow, int rotate = 0) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) ? (
        (y < hpow) ? 0 : 3
    ) : (
        (y < hpow) ? 1 : 2
    );
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    ll subSquareSize = ll(1) << (2*pow - 2);
    ll ans = seg * subSquareSize;
    ll add = hilbertOrder(nx, ny, pow-1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

template<typename S, typename T>
struct MO
{
    int n;
    int w;
    int q = 0;
    vector<tuple<ll, int, int, int, T>> queries;
    vector<S> answers;

    const void f(const int&);
    void (*addLeft)(const int&);
    void (*addRight)(const int&);
    void (*delLeft)(const int&);
    void (*delRight)(const int&);
    S (*getAnswer)(const int&, const int&, const T&);

    void addQuery(int l, int r, const T& t) {
        queries.push_back({hilbertOrder(l, r, w), l, r, q++, t});
    }

    MO(unsigned int maxN,
        void addLeft(const int&),
        void addRight(const int&),
        void delLeft(const int&),
        void delRight(const int&),
        S getAnswer(const int&, const int&, const T&)
    ) {
        n = maxN;
        w = bit_width(maxN);
        this->addLeft = addLeft;
        this->addRight = addRight;
        this->delLeft = delLeft;
        this->delRight = delRight;
        this->getAnswer = getAnswer;
    }

    vector<S> go(
    ) {
        answers.resize(q);
        sort(all(queries), [&](const auto& a, const auto& b) {
            return get<0>(a) < get<0>(b);
        });

        int L = 0;
        int R = -1;

        for (int i = 0; i < q; ++i)
        {
            const auto& [_, l, r, id, t] = queries[i];
            while (L > l) addLeft(--L);
            while (R < r) addRight(++R);
            while (L < l) delLeft(L++);
            while (R > r) delRight(R--);
            answers[id] = getAnswer(l, r, t);
        }
        return answers;
    }
};

int a[N];

fastSet<N, N> m;
fastSet<N, N> diffs;
int diffsCNT[N];
int n, q;
    
inline void er(int x) {
    if (--diffsCNT[x] == 0)
        diffs.erase(x);
}

inline void ad(int x) {
    if (diffsCNT[x]++ == 0)
        diffs.insert(x);
}

inline void add(const int& id) {
    int x = a[id];
    //writeln("ADD", x); cout.flush();
    const auto& l = m.inverse_upper_bound(x);
    const auto& r = m.upper_bound(x);

    if (l == N && r == N)
        [](){}();
    else if (r == N)
    {
        auto mx = m.inverse_lower_bound(N);
        ad(x - mx);
    }
    else if (l == N)
    {
        auto mn = m.lower_bound(0);
        ad(mn - x);
    }
    else
    {
        er(r - l);
        ad(r - x);
        ad(x - l);
    }
    m.insert(x);
}

inline void del(const int& id) {
    const int& x = a[id];
    //writeln("DEL", x); cout.flush();
    const auto& r = m.upper_bound(x);
    const auto& l = m.inverse_upper_bound(x);
    if (r != N)
        er(r - x);
    if (l != N)
    {
        er(x - l);
        if (r != N)
            ad(r - l);
    }
    m.erase(x);
}

int getAnswer(const int& l, const int& r, const int&) {
    return diffs.lower_bound(0);
};

void run()
{
    readln(n, q);
    fori(n)
        readln(a[i]);

    MO<int, int> mo(n, add, add, del, del, getAnswer);
    fori(q)
    {
        ints(l, r); --l; --r;
        mo.addQuery(l, r, 0);
    }
    auto ans = mo.go();

    fori(q)
        writeln(ans[i]);
}

//{{{
int main()
{
    cin.tie(0); ios_base::sync_with_stdio(false);
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
