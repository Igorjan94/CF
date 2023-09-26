// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <algorithm>
#include <bits/stdc++.h>
#include <iomanip>
#include <limits>
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

using namespace std;

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
mt19937 rng_gen(chrono::steady_clock::now().time_since_epoch().count());


//point
#define pointtt template<typename T = int>
//sorts only if z is corner point;
#define sortByPolarAngle(v, z, T) sort(v.begin(), v.end(), [&z](point<T>& a, point<T>& b) {\
    int q = orientation(z, a, b); return q == 0 ? dist(z, a) < dist(z, b) : q == -1;\
});

pointtt struct point
{
    T x, y;
    int index;
    point(){}
    point(T _x, T _y) : x(_x), y(_y) {}
    point(const point& other) : x(other.x), y(other.y), index(other.index) {}
    point operator=(const point& b) { x = b.x; y = b.y; index = b.index; return *this; }
    point operator+(const point& b) const { return point(x + b.x, y + b.y); }
    point operator-(const point& b) const { return point(x - b.x, y - b.y); }
    point operator-() const { return point(-x, -y); }
    T operator*(const point& b) const { return x * b.x + y * b.y; }
    T operator^(const point& b) const { return x * b.y - y * b.x; }
    T operator!() const { return sqrt(x * x + y * y); }
    bool operator<(const point& b) const { return x == b.x ? y < b.y : x < b.x; }
};
pointtt istream&operator>>(istream&is,point<T>&a){return is>>a.x>>a.y;}
pointtt ostream&operator<<(ostream&os,const point<T>&a){return os<<a.x<<" "<<a.y;}
pointtt T dist(const point<T>&a,const point<T>&b){return!(a-b);}
//dist from point C to line AB equals to answer.first / sqrt(answer.second);
pointtt pair<T,T> dist(const point<T>&a,const point<T>&b,const point<T>&c){return{abs((a-b)*c)+(a^b),dist(a,b)};}
static const int CW = 1;
static const int CCW = -1;
pointtt int orientation(const point<T>&a,const point<T>&b,const point<T>&c){T q=a.x*b.y-a.y*b.x-a.x*c.y+a.y*c.x+b.x*c.y-b.y*c.x;return q>0?CCW:q<0?CW:0;}
//reflects point C to line AB (in doubles)
pointtt point<T> reflect(const point<T>&a,const point<T>&b,const point<T>&c){
    T A = a.y - b.y;
    T B = b.x - a.x;
    T C = a ^ b;
    T D = A * A - B * B;
    T S = A * A + B * B;
    return {(-D * c.x - 2 * A * B * c.y - 2 * A * C) / S, (D * c.y - 2 * A * B * c.x - 2 * B * C) / S};
};

//}}}

#define INLINE   inline __attribute__ ((always_inline))
#define FOR(i,a,b)  for(int i=(a);i<(b);++i)
#define REP(i,a)    FOR(i,0,a)
struct RNG {
    unsigned int MT[624];
    int index;
    RNG(int seed = 1) {init(seed);}
    void init(int seed = 1) {MT[0] = seed; FOR(i, 1, 624) MT[i] = (1812433253UL * (MT[i-1] ^ (MT[i-1] >> 30)) + i); index = 0; }
    void generate() {
        const unsigned int MULT[] = {0, 2567483615UL};
        REP(i, 227) {unsigned int y = (MT[i] & 0x8000000UL) + (MT[i+1] & 0x7FFFFFFFUL); MT[i] = MT[i+397] ^ (y >> 1); MT[i] ^= MULT[y&1]; }
        FOR(i, 227, 623) {unsigned int y = (MT[i] & 0x8000000UL) + (MT[i+1] & 0x7FFFFFFFUL); MT[i] = MT[i-227] ^ (y >> 1); MT[i] ^= MULT[y&1]; }
        unsigned int y = (MT[623] & 0x8000000UL) + (MT[0] & 0x7FFFFFFFUL); MT[623] = MT[623-227] ^ (y >> 1); MT[623] ^= MULT[y&1];
    }
    unsigned int rand() { if (index == 0) generate(); unsigned int y = MT[index]; y ^= y >> 11; y ^= y << 7  & 2636928640UL; y ^= y << 15 & 4022730752UL; y ^= y >> 18; index = index == 623 ? 0 : index + 1; return y;}
    INLINE int next() {return rand(); }
    INLINE int next(int x) {return rand() % x; }
    INLINE int next(int a, int b) {return a + (rand() % (b - a)); }
    INLINE double next_double() {return (rand() + 0.5) * (1.0 / 4294967296.0); }
    INLINE double next_double(double a, double b) {return a + next_double() * (b - a); }
};
 
static RNG rng;

int n;

double get(double score) {
    return 1.0 / (score / (n * 1.0));
};

optional<pair<int, int>> generateSegment() {
    int fr = rng.next(n);
    int to = rng.next(n + 1);
    if (to < fr) swap(to, fr);
    if (to - fr + 1 >= n || fr + 1 == to || fr == to)
        return {};
    return pair(fr, to);
}

double getTime() {timeval tv; gettimeofday(&tv, NULL); return tv.tv_sec + tv.tv_usec * 1e-6;}

void answer(double score, const vector<point<double>>& a)
{
    cout << "{ \"score\": " << get(score) << ", \"order\": [ ";
    fori(n)
        cout << a[i].index << ", "[i == n - 1];
    writeln("]}");
    exit(0);
}

tuple<ll, double, vector<point<double>>> sa(vector<point<double>> a, double TL)
{

    auto calcScore = [&]() {
        double score = 0.0;
        fori(n)
            score += dist(a[i], a[(i + 1) % n]);
        return score;
    };

    double S = 1;
    double E = 0.000000001;

    vector<point<double>> ans;
    double p = numeric_limits<double>::max();
    double best = p;
    fori(100000) {
        shuffle(all(a), rng_gen);
        p = calcScore();
        if (p < best)
            best = p,
            ans = a;
    }
    cerr << "Started from " << get(best) << endl;
    
    ll iterations = 0;
    double T = 0.0;
    auto start = getTime();
    while (true) 
    {
        ++iterations;
        if ((iterations & 255) == 0) {
            auto diff = getTime() - start;
            if (diff > TL)
                break;
            T = S * pow(E / S, diff / TL);
        }

        const auto segment = generateSegment();
        if (!segment.has_value())
            continue;
        const auto& [fr, to] = segment.value();

        auto& v1 = a[fr == 0 ? n - 1 : fr - 1];
        auto& v2 = a[fr];
        auto& v3 = a[to - 1];
        auto& v4 = a[to == n ? 0 : to];
        double d = dist(v1, v3) + dist(v2, v4) - dist(v1, v2) - dist(v3, v4);
        double ns = p + d;
        if (ns < p || rng.next_double() < exp(-d / T)) {
            p = ns;
            if (ns < best) {
                best = ns;
                ans = a;
            }
            reverse(a.begin() + fr, a.begin() + to);
        }
    }

    return tuple(iterations, best, ans);
}

void run()
{
    cerr.precision(3);
    cerr << fixed;
    cout.precision(15);
    cout << fixed;
    readln(n);

    vector<point<double>> a(n);
    readln(a);
    fori(n) a[i].index = i;

    static const int T = 1;
    double TL = 1;
    double best = numeric_limits<double>::max();
    vector<point<double>> order;
    cerr << "Starting... TL: " << TL << ", T: " << T << endl;
    fori(T)
    {
        const auto& [iterations, curAns, cur] = sa(a, TL);
        cerr << "Done " << (i + 1) << " / " << T << ", it/s: " << (iterations / TL) << ", cur: " << get(curAns) << ", best: " << get(best) << endl;
        if (curAns < best)
            best = curAns,
            order = cur;
    }
    cerr << get(best) << endl;
    answer(best, order);
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
