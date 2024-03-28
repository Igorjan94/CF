// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#include <ostream>
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
//modular
template<typename T = int, T mod = 1000000007>
struct modular
{
    T value;

    modular() : value(0) {}
    modular(const modular& other) : value(other.value) {}
    modular operator=(const modular& other) { value = other.value; return *this; }
    template<typename T1> modular operator=(const T1& other) { value = other % mod; if (value < 0) value += mod; return *this; }
    template<typename T1> modular(T1 const& other) { value = other % mod; if (value < 0) value += mod; }
    template<typename T1> modular(T1 const& num, T1 const& den) { *this = modular(den) ^ (mod - 2) * num; }
    template<typename T1> modular& operator^=(T1 const& deg) { modular a(*this); value = T(1); for (T1 n = deg; n > 0; n >>= 1) { if (n & 1) *this *= a; a *= a; } return *this; }
    template<typename T1> modular  operator^ (T1 const& deg) const { return modular(*this) ^= deg; }
    inline modular& operator+=(modular const& t)       { value += t.value; if (value >= mod) value -= mod; return *this; }
    inline modular& operator-=(modular const& t)       { value -= t.value; if (value < 0  ) value += mod; return *this; }
    inline modular& operator*=(modular const& t)       { value = (value * 1ll * t.value) % mod; return *this; }
    inline modular& operator/=(modular const& t)       { return *this *= ~t; }
    inline modular  operator+ (modular const& t) const { return modular(*this) += t; }
    inline modular  operator- (modular const& t) const { return modular(*this) -= t; }
    inline modular  operator* (modular const& t) const { return modular(*this) *= t; }
    inline modular  operator/ (modular const& t) const { return modular(*this) /= t; }
    inline modular  operator~ (                ) const { return modular(T(1), value); }
    inline bool     operator==(modular const& t) const { return value == t.value; }
    inline bool     operator!=(modular const& t) const { return value != t.value; }
    explicit operator T() const { return value; }

    inline friend ostream& operator<<(ostream& os, modular const& m) { return os << m.value; }
    inline friend istream& operator>>(istream& is, modular& m) { return is >> m.value; m.value %= mod; if (m.value < 0) m.value += mod; }
};

//}}}

struct Edge {
    int u, v;

    int& getTo()
    {
        return v;
    }

    Edge() {}
    Edge(int v, int u) : u(u), v(v) {}
};

struct Node {
	modular<int> f = 1;
	modular<int> s = 0;

	Node operator+(const Node& o) const {
		return { f * o.f, f * o.s + o.f * s + s * o.s };
	}

	Node promote(int u, const Edge& e) const {
		return { f, f + s };
	}
};

ostream& operator<<(ostream& os, const Node& u) {
    return os << (u.f + u.s);
}

template<class T, class E>
struct Rerooter {
	int n;
	vector<vector<E>> g;
	vector<vector<T>> pre, suf;
    vector<T> res;

	Rerooter(const vector<vector<E>>& g, bool addVertexToAns = false)
    {
        this->g = g;
        n = g.size();
        res.resize(n);
        pre.resize(n);
        suf.resize(n);
        fori(n)
        {
			pre[i].resize(SZ(g[i]) + 1);
			suf[i].resize(SZ(g[i]) + 1);
		}
		down(0);
		up(0);
        fori(n)
            res[i] = addVertexToAns
                ? pre[i].back().promote(i, Edge())
                : pre[i].back();
                
	}

	T get(int u, int i = 0)
    {
		T& v = suf[u][i + 1];
		if (i) v = pre[u][i] + v; 
		return v.promote(u, g[u][i]);
	};

	T down(int u, int p = -1)
    {
        fori(SZ(g[u])) {
            if (g[u][i].getTo() == p)
                swap(g[u][i], g[u][0]);
        }
		for (int i = SZ(g[u]) - 1; i > -(p < 0); --i)
			suf[u][i] = down(g[u][i].getTo(), u) + suf[u][i + 1];
		return get(u);
	}

	void up(int u, int p = -1) {
        for (int i = p != -1; i < SZ(g[u]); ++i)
        {
            int v = g[u][i].getTo();
			pre[u][i + 1] = pre[u][i] + get(v);
			pre[v][1] = get(u, i);
			up(v, u);
		}
	}
};

void run()
{
    ints(n);
    vi p(n - 1);
    readln(p);
    vector<vector<Edge>> g(n);
    fori(n - 1)
        g[i + 1].pb({p[i] - 1, i + 1}),
        g[p[i] - 1].pb({i + 1, p[i] - 1});
    auto r = Rerooter<Node, Edge>(g);
    writeln(r.res);
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
