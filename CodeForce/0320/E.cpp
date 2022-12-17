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
//chtTrick
// Allows to add kx+b lines. Returns max(x). min(x) = -max(-kx-b)
// Author: Simon Lindholm
// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
template<typename T>
struct line
{
    mutable T k, b, p;
    bool operator<(const line& other) const { return k < other.k; }
    bool operator<(const T& other) const { return p < other; }
    T get(const T& x) const { return k * x + b; }
};

template<typename T>
struct chtTrick : multiset<line<T>, less<>>
{
    static const T inf = numeric_limits<T>::max();
    int sign = 1;

    chtTrick(bool mn) 
    {
        if (mn) sign = -1;
    }

    T div(const T& a, const T& b)
    {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool isect(typename multiset<line<T>, less<>>::iterator x, typename multiset<line<T>, less<>>::iterator y) {
        auto& [kx, bx, px] = *x;
        auto& [ky, by, py] = *y;
		if (y == this->end())
        {
            px = inf;
            return false;
        }
		if (kx == ky)
            px = bx > by ? inf : -inf;
		else
            px = div(by - bx, kx - ky);
		return px >= py;
	}

	void addLine(const T& k, const T& b) {
		auto z = this->insert({k * sign, b * sign, 0});
        auto y = z++;
        auto x = y;
		while (isect(y, z))
            z = this->erase(z);

		if (x != this->begin() && isect(--x, y))
            isect(x, y = this->erase(y));

		while ((y = x) != this->begin() && (--x)->p >= y->p)
			isect(x, this->erase(y));
	}

	T get(const T& x) {
		assert(!this->empty());
        return sign * this->lower_bound(x)->get(x);
	}
};

//}}}

void run()
{
    ints(n);
    vi a(n), b(n);
    readln(a, b);
    chtTrick<ll> tree(true);
    vector<ll> ans(n, 0);
    fori(n)
    {
        if (tree.size())
            ans[i] = tree.get(a[i]);
        tree.addLine(b[i], ans[i]);
    }
    writeln(ans.back());
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
