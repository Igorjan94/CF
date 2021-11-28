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

vector<string> strings = {"a", "b", "c", "ab", "bc"};
bool getBit(int x, int b) {
    return (x & (1 << b)) != 0;
}
void setBit(int& x, int b) {
    x |= 1 << b;
}

struct node
{
    vector<int> dp = vector<int>(33, MOD);
    int mask = 0;

    node(){}

    node(int x)
    {
        setBit(mask, x);
        dp[mask] = 0;
        dp[0] = 1;
    }
};

const int M = 5;
vector<vector<int>> merged = vector<vector<int>>(1 << M, vector<int>(1 << M, -1));

//Igorjan
//segmentTree
//0-indexed, [l..r]
template<typename T = node>
struct segmentTree
{
    int n;
    vector<T> t;
    function<T(T&, const T&, const T&)> f = [](T& m, const T& a, const T& b) {
        forn(i, 1 << M)
            m.dp[i] = MOD;
        m.mask = 0;
        forn(l, 1 << M)
            if (a.dp[l] != MOD)
                forn(r, 1 << M)
                    if (b.dp[r] != MOD)
                        if (auto mask = merged[l][r]; mask != -1)
                            m.dp[mask] = min(m.dp[mask], a.dp[l] + b.dp[r]);

        return m;
    };

    T NEITRAL_ELEMENT = numeric_limits<T>::max();
 
    void build(const vector<T>& a, int v, int l, int r)
    {
        if (l == r)
            t[v] = a[l];
        else 
        {
            int m = (l + r) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            T left = t[v * 2];
            T right = t[v * 2 + 1];

            f(t[v], left, right);
        }
    };
 
    segmentTree(const vector<T>& a)
    {
        n = a.size();
        t.resize(n * 4 + 10);
        build(a, 1, 0, n - 1);
    }
 
    void update(int l, int r, T value)
    {
        update(1, 0, n - 1, l, r, value);
    }
 
    void update(int v, int tl, int tr, int l, int r, T value) 
    {
        if (l > r)
            return;
        if (tl == l && tr == r)
            t[v] = value;
        else 
        {
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), value);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, value);
            T left = t[v * 2];
            T right = t[v * 2 + 1];

            f(t[v], left, right);
        }
    }

    T get(int l, int r)
    {
        return get(1, 0, n - 1, l, r);
    }

    T get(int v, int tl, int tr, int l, int r) 
    {
        if (l > r) return NEITRAL_ELEMENT;

        //if (tl == l && tr == r)
            return t[v];
        //else 
        //{
            //int tm = (tl + tr) / 2;
            //T left = get(v * 2, tl, tm, l, min(r, tm));
            //T right = get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
            //return f(left, right);
        //}
    }

};

//}}}

void run()
{
    auto concatString = [&](int mask) {
        vector<string> s = {""};
        fori(M)
            if (getBit(mask, i))
                s.pb(strings[i]);
        return s;
    };
    auto merge = [&](vector<string> l, vector<string> r) {
        int mask = 0;
        for (const string& s: l)
            for (const string& t: r)
            {
                string S = s + t;
                if (S.find("abc") != string::npos)
                    return -1;
                fori(M)
                    if (S.find(strings[i]) != string::npos)
                        setBit(mask, i);
            }
        return mask;
    };
    forn(l, 1 << M)
        forn(r, 1 << M)
        {
            auto L = concatString(l);
            auto R = concatString(r);
            merged[l][r] = merge(L, R);
        }

    ints(n, q);
    string s;
    readln(s);
    vector<node> a;
    vector<node> nodes;
    fori(3)
        nodes.emplace_back(i);

    fori(n)
        a.pb(nodes[s[i] - 'a']);

    segmentTree<node> tree(a);

    forn(_, q)
    {
        int i;
        char c;
        readln(i, c); --i;
        tree.update(i, i, nodes[c - 'a']);
        node ans = tree.get(0, n - 1);
        writeln(*min_element(all(ans.dp)));
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
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
