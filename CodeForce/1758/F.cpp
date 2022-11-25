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
//binSearch
//x \in [l, r]-> min, f(x) == true
template<typename T, typename F>
T binSearch(T l, T r, F f, T eps = 1)
{
    T m;
    while (abs(r - l) > eps)
        m = l + (r - l) / 2,
        (f(m) ? r : l) = m;
    return f(l) ? l : r;
}

//segmentTree
//0-indexed, [l..r]
template<typename T>
struct segmentTree
{
    int n;
    vector<T> t;
    vector<T> add;
    //vector<T> pos;
    function<T(const T&, const T&)> f = [](const T& a, const T& b) { return min(a, b); };
    T NEITRAL_ELEMENT = numeric_limits<T>::max();
 
    void push(int v, int tl, int tr)
    {
        if (add[v] == 0) return;

        t[v] += add[v];
        if (tl != tr)
            add[v * 2] += add[v],
            add[v * 2 + 1] += add[v];
        add[v] = 0;
    }

    void build(const vector<T>& a, int v, int l, int r)
    {
        if (l == r)
        {
            t[v] = a[l];
            //pos[v] = l;
        }
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            T left = t[v * 2];
            T right = t[v * 2 + 1];

            //if (left > right)
                //pos[v] = pos[v * 2];
            //else
                //pos[v] = pos[v * 2 + 1];
            t[v] = f(left, right);
        }
    };
 
    segmentTree(const vector<T>& a)
    {
        n = a.size();
        t.resize(n * 4 + 10);
        add.resize(n * 4 + 10, 0);
        //pos.resize(n * 4 + 10, 0);
        build(a, 1, 0, n - 1);
    }
 
    void update(int l, int r, T value)
    {
        update(1, 0, n - 1, l, r, value);
    }
 
    void update(int v, int tl, int tr, int l, int r, T value) 
    {
        push(v, tl, tr);
        if (l > r)
            return;
        if (tl == l && tr == r)
        {
            t[v] += value;
            if (tl != tr)
                add[v * 2] += value,
                add[v * 2 + 1] += value;
        }
        else 
        {
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), value);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, value);
            T left = t[v * 2];
            T right = t[v * 2 + 1];

            //if (left > right)
                //pos[v] = pos[v * 2];
            //else
                //pos[v] = pos[v * 2 + 1];
            t[v] = f(left, right);
        }
    }

    T get(int l, int r)
    {
        return get(1, 0, n - 1, l, r);
    }

    T get(int v, int tl, int tr, int l, int r) 
    {
        push(v, tl, tr);
        if (l > r) return NEITRAL_ELEMENT;

        if (tl == l && tr == r)
            return t[v];
        else 
        {
            int tm = (tl + tr) / 2;
            T left = get(v * 2, tl, tm, l, min(r, tm));
            T right = get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
            return f(left, right);
        }
    }

};

//}}}

void run()
{
    ints(n);
    int N = n * 2;
    vi a(N + 10, 0);
    set<pii> segments;
    segmentTree<int> tree(a);
    fori(N)
        tree.update(i, N, -1);

    auto getSegment = [&](int x) -> optional<pii> {
        if (segments.empty())
            return {};
        auto it = segments.lower_bound({x + 1, x + 1});
        if (it == segments.begin())
            return {};
        --it;
        if (it->second >= x)
            return *it;
        return {};
    };

    fori(n)
    {
        ints(x); --x;
        vector<pii> add, rem;
        auto it = getSegment(x);

        if (a[x] == 0)
        {
            a[x] = 1;
            tree.update(x, N, 2);

            int l = x;
            int r = x;
            if (it)
            {
                l = it->first;
                r = it->second;
                rem.pb(*it);
            }

            if (auto prev = getSegment(x - 1); prev && prev->second == x - 1)
            {
                l = prev->first;
                rem.pb(*prev);
            }

            forn(q, it ? 2 : 1)
            {
                ++r;
                if (auto nxt = getSegment(r); nxt && nxt->first == r)
                {
                    r = nxt->second + 1;
                    rem.pb(*nxt);
                }
            }

            if (auto nxt = getSegment(r + 1); nxt)
            {
                r = nxt->second;
                rem.pb(*nxt);
            }
            add.pb({l, r});
        }
        else
        {
            a[x] = 0;
            tree.update(x, N, -2);
            int l = it->first;
            int r = it->second;
            if (r - l > 2)
            {
                int p = l == 0 ? 0 : tree.get(l - 1, l - 1);
                int m = binSearch(l, r, [&](int m) {
                    return tree.get(l, m) - p <= -2;
                });
                if (m - 2 > l)
                    add.pb({l, m - 2});
                if (m + 1 < r)
                    add.pb({m + 1, r});
            }

            rem.pb(*it);
        }

        writeln(rem.size());
        for (auto& [x, y]: rem) segments.erase({x, y}), ++x, ++y;
        if (rem.size()) writeln(rem);
        writeln(add.size());
        for (auto& [x, y]: add) segments.insert({x, y}), ++x, ++y;
        if (add.size()) writeln(add);
        cout.flush();
    }
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
