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
static const long double EPS = 1e-15;

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
//x \in [l, r]-> min, f(x) == true
template<typename T, typename F>
T binSearch(T l, T r, F f)
{
    T m;
    fori(60)
        m = l + (r - l) / 2,
        (f(m) ? r : l) = m;
    return f(l) ? l : r;
}

//point
#define pointtt template<typename T = int>
//sorts only if z is corner point;
#define sortByPolarAngle(v, z, T) sort(v.begin(), v.end(), [&z](point<T>& a, point<T>& b) {\
    int q = orientation(z, a, b); return q == 0 ? dist(z, a) < dist(z, b) : q == -1;\
});

pointtt struct point
{
    T x, y;
    point(){}
    point(T _x, T _y) : x(_x), y(_y) {}
    point operator=(const point& b) { x = b.x; y = b.y; return *this; }
    point operator+(const point& b) const { return point(x + b.x, y + b.y); }
    point operator-(const point& b) const { return point(x - b.x, y - b.y); }
    point operator-() const { return point(-x, -y); }
    point operator*(T b) { return point(x * b, y * b); }
    T operator*(const point& b) const { return x * b.x + y * b.y; }
    T operator^(const point& b) const { return x * b.y - y * b.x; }
    T operator!() const { return x * x + y * y; }
    bool operator<(const point& b) const { return x == b.x ? y < b.y : x < b.x; }
};
pointtt istream&operator>>(istream&is,point<T>&a){return is>>a.x>>a.y;}
pointtt ostream&operator<<(ostream&os,point<T>&a){return os<<a.x<<" "<<a.y;}
pointtt T dist(const point<T>&a,const point<T>&b){return!point<T>(a-b);}
//dist from point C to line AB equals to answer.first / sqrt(answer.second);
pointtt pair<T,T> dist(const point<T>&a,const point<T>&b,const point<T>&c){return{abs((a-b)*c)+(a^b),dist(a,b)};}
static const int CW = 1;
static const int CCW = -1;
pointtt int orientation(const point<T>&a,const point<T>&b,const point<T>&c){T q=(b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);return q>EPS?CCW:q<-EPS?CW:0;}
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

template<typename T>
struct segment
{
    point<T> p, q;
    int i;

	T get_y(T x) const {
		if (abs(p.x - q.x) < EPS) return p.y;
		return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
	}

    bool operator<(const segment& b) const
    {
        T x = max (min(p.x, q.x), min(b.p.x, b.q.x));
        return get_y(x) < b.get_y(x) - EPS;
    };

    friend ostream& operator<<(ostream& os, const segment& s) {
        return os << s.p.x << " " << s.p.y << " " << s.q.x << " " << s.q.y << " " << s.i;
    };
};

template<typename T>
struct event {
    T x;
    int type;
    int i;

    bool operator<(const event& b) const {
        if (abs(x - b.x) > EPS)
            return x < b.x;
        return type < b.type;
    };
};

typedef long double T;
typedef point<T> p;

inline bool intersect1d(T l1, T r1, T l2, T r2) {
	if (l1 > r1) swap(l1, r1);
	if (l2 > r2) swap(l2, r2);
	return max(l1, l2) <= min(r1, r2) + EPS;
}

void run()
{
    ints(n);
    vector<tuple<p, p, int>> cars(n);
    readln(cars);
    cout << fixed << setprecision(15);
    const T mx = 1e10;
    //const T mx = 100;
    T m = binSearch(T(0), mx, [&](T t) {
        vector<event<T>> events;
        vector<segment<T>> segments(n);
        fori(n)
        {
            auto [f, d, speed] = cars[i];
            auto s = f + d * (speed * t / sqrt(!d));
            events.pb({min(f.x, s.x), -1, i});
            events.pb({max(f.x, s.x),  1, i});
            segments[i] = {f, s, i};
        }
        sort(all(events));
        set<segment<T>> s;
        using it = decltype(s.begin());
        vector<it> iterators(n);

        auto prev = [&](auto it) {
            return it == s.begin() ? s.end() : --it;
        };
        auto next = [&](auto it) {
            return ++it;
        };
        auto vec = [&](const p& a, const p& b, const p& c) {
            double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
            return abs(s) < EPS ? 0 : s > 0 ? +1 : -1;
        };
        auto intersects = [&](it A, const segment<T>& b) {
            if (A == s.end())
                return false;
            auto a = *A;

            bool ok = intersect1d(a.p.x, a.q.x, b.p.x, b.q.x)
                && intersect1d(a.p.y, a.q.y, b.p.y, b.q.y)
                && orientation(a.p, a.q, b.p) * orientation(a.p, a.q, b.q) <= 0
                && orientation(b.p, b.q, a.p) * orientation(b.p, b.q, a.q) <= 0;
            return ok;
        };
        for (auto [x, t, id]: events)
            if (t == -1) // begin
            {
                auto nxt = s.lower_bound(segments[id]);
                auto prv = prev(nxt);
                if (intersects(nxt, segments[id]))
                    return true;
                if (intersects(prv, segments[id]))
                    return true;
                iterators[id] = s.insert(nxt, segments[id]);
            }
            else
            {
                auto nxt = next(iterators[id]);
                auto prv = prev(iterators[id]);
                if (nxt != s.end() && intersects(prv, *nxt))
                    return true;
                s.erase(iterators[id]);
            }
        return false;
    });
    if (m == mx)
        writeln("No show :(");
    else
        writeln(m);
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
