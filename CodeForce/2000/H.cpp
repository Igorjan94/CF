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
static const int N = 2 * 1000 * 1000 + 1;
vector<pair<int,int>> t(4 * N + 2000, {MOD, 0});
 
pair<int,int> combine (pair<int,int> a, pair<int,int> b) {
	if (a < b)
		return a;
    return b;
}
 
pair<int,int> get_max (int v, int tl, int tr, int l, int r) {
	if (l > r)
		return make_pair (MOD, 0);
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	return combine (
		get_max (v*2, tl, tm, l, min(r,tm)),
		get_max (v*2+1, tm+1, tr, max(l,tm+1), r)
	);
}
 
void update (int v, int tl, int tr, int pos, int new_val) {
	if (tl == tr)
		t[v] = make_pair (new_val, pos);
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update (v*2, tl, tm, pos, new_val);
		else
			update (v*2+1, tm+1, tr, pos, new_val);
		t[v] = combine (t[v*2], t[v*2+1]);
	}
}
void run()
{
    ints(n);
    vector<int> a(n);
    readln(a);
    ints(q);
    set<int> s;
    s.insert(0);
    s.insert(N * 2);
    map<int, set<int>> mp;
    set<int> keys;
    auto clear = [&](int l, int r) {
        if (r - l > 1)
        {
            int dist = min(N, r - l - 1);
            int i = l + 1;
            mp[dist].erase(i);
            if (mp[dist].size())
                update(1, 0, N + 1, dist, *mp[dist].begin());
            else
            {
                keys.erase(dist);
                update(1, 0, N + 1, dist, MOD);
            }
        }
    };
    auto raw = [&](int l, int r) {
        if (r - l > 1)
        {
            int dist = min(N, r - l - 1);
            int i = l + 1;
            mp[dist].insert(i);
            keys.insert(dist);
            update(1, 0, N + 1, dist, *mp[dist].begin());
        }
    };
    auto add = [&](int x) {
        auto r = s.lower_bound(x);
        auto l = r; --l;
        clear(*l, *r);
        s.insert(x);
        raw(*l, x);
        raw(x, *r);
    };
    auto erase = [&](int x) {
        auto i = s.find(x);
        auto r = i; ++r;
        auto l = i; --l;
        clear(*l, *i);
        clear(*i, *r);
        s.erase(x);
        raw(*l, *r);
    };
    for (int x: a) add(x);
    forn(Q, q)
    {
        char c;
        int k;
        readln(c, k);
        if (c == '?')
            cout << get_max(1, 0, N + 1, k, N).first << " ";
        else if (c == '+')
            add(k);
        else
            erase(k);
    }
    writeln();
    for (int dist: keys) 
        update(1, 0, N + 1, dist, MOD);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ints(t); fori(t) run();
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
