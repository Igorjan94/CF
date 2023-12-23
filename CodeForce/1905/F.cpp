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
//persistentSegmentTree
//0-indexed, [l..r]
template<typename V, typename T, typename U>
struct persistentSegmentTree
{
    int n;

    struct treeNode {
        T t;
        U u = U(0);
        int l = -1;
        int r = -1;

        treeNode(const T& t) : t(t) {}
        treeNode() {}
    };
    vector<treeNode> t;
    vector<int> roots;

    int create(const T& v, int ll = -1, int rr = -1, const U& u = U(0))
    {
        int index = t.size();
        auto temp = treeNode(v);
        temp.l = ll;
        temp.r = rr;
        temp.u = u;
        t.pb(temp);
        return index;
    }

    int clone(const treeNode& node)
    {
        return create(node.t, node.l, node.r, node.u);
    }
 
    int push(int v, int tl, int tr)
    {
        if (t[v].u.empty()) return v;
        
        v = clone(t[v]);
        t[v].t += t[v].u;
        if (tl != tr)
        {
            int ll = clone(t[t[v].l]);
            int rr = clone(t[t[v].r]);
            t[ll].u += t[v].u;
            t[rr].u += t[v].u;
            t[v].l = ll;
            t[v].r = rr;
        }
        t[v].u.reset();
        return v;
    }

    int build(const vector<V>& a, int l, int r)
    {
        if (l == r)
            return create(T(a[l], l));
        else 
        {
            int m = (l + r) / 2;
            int ll = build(a, l, m);
            int rr = build(a, m + 1, r);
            return create(t[ll].t + t[rr].t, ll, rr);
        }
    };
 
    persistentSegmentTree(const vector<V>& a)
    {
        n = a.size();
        roots.push_back(build(a, 0, n - 1));
    }
 
    int update(int version, int l, int r, U value)
    {
        int index = update(version, 0, n - 1, l, r, value);
        roots.push_back(index);
        return index;
    }
 
    int update(int v, int tl, int tr, int l, int r, U value) 
    {
        v = push(v, tl, tr);
        if (l > r)
            return v;
        if (tl == l && tr == r)
        {
            t[v].u += value;
            int index = push(v, tl, tr);
            t[v].u.reset();
            return index;
        }
        else 
        {
            int tm = (tl + tr) / 2;
            int ll = update(t[v].l, tl, tm, l, min(r, tm), value);
            int rr = update(t[v].r, tm + 1, tr, max(l, tm + 1), r, value);
            return create(t[ll].t + t[rr].t, ll, rr);
        }
    }

    T get(int version, int l, int r)
    {
        return get(version, 0, n - 1, l, r);
    }

    T get(int v, int tl, int tr, int l, int r) 
    {
        v = push(v, tl, tr);
        if (l > r) return T();

        if (tl == l && tr == r)
            return t[v].t;
        else 
        {
            int tm = (tl + tr) / 2;
            T left = get(t[v].l, tl, tm, l, min(r, tm));
            T right = get(t[v].r, tm + 1, tr, max(l, tm + 1), r);
            return left + right;
        }
    }
};

struct Update {
    ll value = 0;
 
    Update() {}
 
    Update(ll value) : value(value) {}
 
    void operator+=(const Update& b) {
        value += b.value;
    };
 
    Update operator-() {
        return Update(-value);
    };
 
    bool empty() const {
        return value == 0;
    }
 
    void reset() {
        value = 0;
    }
};
 
struct Node 
{
    ll v;
    int pos;
    int l = 1;
 
    Node() : v(0), pos(0) {}
    Node(ll v, int pos) : v(v), pos(pos) {}
    Node(ll v, int pos, int l) : v(v), pos(pos), l(l) {}
 
    Node operator+(const Node& b) const {
        return Node(v + b.v, min(pos, b.pos), l + b.l);
    }
 
    void operator+=(const Update& update) {
        v += update.value * l;
    }
};
//}}}

void run()
{
    ints(n);
    vi a(n);
    readln(a);
    for (int& x: a) --x;
    persistentSegmentTree<int, Node, Update> s(vector(n, 0));
    vector l(n, 0);
    fori(n)
        l[i] = s.get(s.roots.back(), 0, a[i]).v,
        s.update(s.roots.back(), a[i], a[i], 1);

    int stable = 0;
    fori(n)
        if (l[i] == i && a[i] == i)
            ++stable;
    if (stable == n)
        return writeln(n - 2);
    vector good(n, 0);
    fori(n)
        if (a[i] == i && l[i] + 1 == i)
            good[i] = 1;
    writeln();
    writeln(a);
    writeln(l);
    writeln(good);
    fori(n)
    {
        if (a[i] == i)
            continue;
        int k = i;
        int j = a[i];

    }
    writeln(stable);
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
