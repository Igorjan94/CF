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
//}}}

//segmentTree
//0-indexed, [l..r]
template<typename T>
struct segmentTree
{
    int n;
    vector<T> t;
    vector<T> add;
    vector<T> pos;
 
    void build(const vector<T>& a, int v, int l, int r)
    {
        if (l == r)
            t[v] = a[l],
            pos[v] = l;
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            T left = t[v * 2];
            T right = t[v * 2 + 1];

            if (left > right)
                pos[v] = pos[v * 2];
            else
                pos[v] = pos[v * 2 + 1];
            t[v] = max(left, right);
        }
    };
 
    segmentTree(const vector<T>& a)
    {
        n = a.size();
        t.resize(n * 4 + 10);
        add.resize(n * 4 + 10, 0);
        pos.resize(n * 4 + 10, 0);
        build(a, 1, 0, n - 1);
    }
 
    void update(int l, int r, T value)
    {
        //writeln("ADDING", l, r, value);
        update(1, 0, n - 1, l, r, value);
    }
 
    void update(int v, int tl, int tr, int l, int r, T value) 
    {
        if (add[v] != 0)
        {
            t[v] += add[v];
            if (tl != tr)
                add[v * 2] += add[v],
                add[v * 2 + 1] += add[v];
            add[v] = 0;
        }
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

            if (left > right)
                pos[v] = pos[v * 2];
            else
                pos[v] = pos[v * 2 + 1];
            t[v] = max(left, right);
        }
    }
};

void run()
{
    ints(n);
    vector<string> s(n);
    readln(s);
    s.insert(s.begin(), "blue");
    s.pb("lock");
    s.pb("unlock");
    s.pb("lock");
    s.pb("unlock");
    n = SZ(s);
    ints(q);

    set<int> locks, unlocks;
    vector<int> a(n, 0);
    segmentTree<int> tree(a);

    auto addString = [&](int i) {
        if (s[i] == "lock")
            locks.insert(i);
        else if (s[i] == "unlock")
            unlocks.insert(i);
    };
    auto getUnlock = [&](int l) {
        return min(*unlocks.lower_bound(l), *locks.upper_bound(l));
    };
    auto updatePos = [&](int i, int diff, bool rec) {
        auto l = locks.upper_bound(i);
        if (l != locks.begin())
        {
            --l;
            int u = getUnlock(*l);
            if (u < i) return;
            tree.update(*l, u, diff);
            if (l != locks.begin() && rec)
            {
                --l;
                int u = getUnlock(*l);
                if (u < i) return;
                tree.update(*l, u, diff);
            }
        }
    };
    fori(n)
        addString(i);

    for (int u: unlocks)
        tree.update(u, u, -1);
    for (int l: locks)
    {
        tree.update(l, l, -1);
        int u = getUnlock(l);
        tree.update(l, u, -1);
    }
    writeln(s[tree.pos[1]]);

    forn(w, q)
    {
        int i;
        string t;
        readln(i, t);
        //writeln(s);
        if (s[i] != t)
        {
            if (s[i] == "unlock" || s[i] == "lock")
                tree.update(i, i, 1),
                updatePos(i, 1, s[i] == "lock"),
                (s[i] == "lock" ? locks : unlocks).erase(i),
                updatePos(i, -1, false);

            s[i] = t;

            if (s[i] == "lock" || s[i] == "unlock")
                updatePos(i, 1, false),
                (s[i] == "lock" ? locks : unlocks).insert(i),
                updatePos(i, -1, s[i] == "lock"),
                tree.update(i, i, -1);
        }
        //writeln(s);
        writeln(s[tree.pos[1]]);
        //writeln();
    }
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
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"  "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
