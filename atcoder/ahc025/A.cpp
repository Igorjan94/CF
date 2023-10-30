// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <algorithm>
#include <bits/stdc++.h>
#include <iterator>
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

void debug(){cerr<<"\n";cerr.flush();}ttti void dprint(T&& a);ttti void dpriws(T&& a);
void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
template<class H, class...T> inline void debug(H&& h,T&&...t){
#ifndef DEBUG
    priws("#");
    priws(h);(print(t),...);writeln();
    dpriws(h);(dprint(t),...);debug();
#endif
}

//Igorjan
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}

#define a _a
#define n _n
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void dprint(T&&a){cerr<<" "<<a;}
ttti void dpriws(T&&a){cerr<<a;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;}

int queries = 0;
int MAX_QUERIES = 0;
map<pair<vector<int>, vector<int>>, char> cache;

char ask(int& q, vector<int> a, vector<int> b, bool force = false)
{
    if (!a.size() && !b.size())
        return '=';
    if (!b.size())
        return '>';
    if (!a.size())
        return '<';
    //bool sw = a.size() > b.size();
    //if (sw) swap(a, b);
    if (!force) 
    {
        auto it = cache.find({a, b});
        if (it != cache.end()) return it->second;
    }
    if (queries == 0) debug("RUN OUT OF QUERIES");
    if (queries == 0) return cache[{a, b}] = '?';
    debug("queries", queries, MAX_QUERIES - queries);
    --queries;
    --q;
    writeln(a.size(), b.size(), a, b);
    cout.flush();
    char c;
    readln(c);
    //if (sw && c != '=' && c != '?')
        //c ^= '<' ^ '>';
    return cache[{a, b}] = c;
}

void cp(const vector<int>& from, set<int>& to)
{
    for (const int x: from) to.insert(x);
}

char raw_cmp(int& q, const vector<int>& a, const vector<int>& b, const vector<int>& c, const vector<int>& d)
{
    set<int> left, right;
    cp(a, right);
    cp(b, left);
    cp(c, left);
    cp(d, right);
    vector<int> keys(all(left));
    for (int x: keys)
        if (right.contains(x))
            left.erase(x),
            right.erase(x);
    return ask(q, vector(all(left)), vector(all(right)));
}

char needsUpdate(int& q, char p, char c, const vector<int>& A, const vector<int>& B, const vector<int>& C, const vector<int>& D)
{
    if (p == '<' && c == '<')
        return raw_cmp(q, A, B, C, D) == '>';
    else if (p == '<' && c == '>')
        return raw_cmp(q, A, B, D, C) == '>';
    else if (p == '>' && c == '<')
        return raw_cmp(q, B, A, C, D) == '>';
    else if (p == '>' && c == '>')
        return raw_cmp(q, B, A, D, C) == '>';
    return false;
}

void moveFrom(vector<int>& l, vector<int>& r, int index) {
    r.pb(l[index]);
    l.erase(l.begin() + index);
}

vector<int> order;
set<int> forced;

auto process(int n, int d, int q, char p, vector<int> A, vector<int> B, vector<int> ans, int xo)
{
    int stuck = 0;
    while (q >= 2 && ++stuck < 200) {
        auto C = A;
        auto D = B;
        int index = -1;
        if (p == '>')
        {
            int fl = rng() % A.size();
            index = A[fl];
            C.erase(C.begin() + fl);
            D.pb(index);
        }
        else if (p == '<')
        {
            auto fr = rng() % B.size();
            index = B[fr];
            D.erase(D.begin() + fr);
            C.pb(index);
        }
        else break;
        if (index != -1)
        {
            char c = ask(q, C, D);
            bool apply = c == p || c == '=';
            if (q && !apply)
                apply = needsUpdate(q, p, c, A, B, C, D);

            //if (apply)
            if (apply || (queries > MAX_QUERIES / 2 && rng() % 10 == 0))
            {
                debug("APPLIED", c, p, apply, index);
                ans[index] ^= xo;
                p = c;
                A = C;
                B = D;
                debug("c", ans);
            }
        }
    }

    return tuple(p, A, B, ans);
}

auto get(optional<vector<int>> prev, int n, int d, int q, int ll, int rr)
{
    debug("RUN", n, d, q, ll, rr, prev.has_value());
    debug("Queries left:", queries);
    vi ans(n, 0);
    if (prev.has_value())
        ans = prev.value();
    else if (d == 2)
    {
        debug("RESET");
        for (int i = 0; i < n; i += d)
            shuffle(order.begin() + i, order.begin() + min(n, i + d), rng);
        fori(n)
            ans[order[i]] = i % d;
    }
    debug("c", ans);
    vector<vector<int>> LR(d);
    fori(n) LR[ans[i]].pb(i);
    char p = ask(q, LR[ll], LR[rr]);
    return process(n, d, q, p, LR[ll], LR[rr], ans, ll ^ rr);
}

template <typename T>
void merge_sort(std::vector<T>& array, int l, int r, auto cmp) {
    if (1 < r - l) {
        int m = l + (r - l) / 2;
        merge_sort(array, l, m, cmp);
        merge_sort(array, m, r, cmp);
        vector<int> out(r - l);
        merge(
            array.begin() + l, array.begin() + m, 
            array.begin() + m, array.begin() + r, 
            out.begin(), cmp
        );
        copy(all(out), array.begin() + l);
    }
}

auto run2(vector<int> ans, int n, int d, int q)
{
    int cnt = q / 10;
    int ql = cnt;
    int qq = (q - cnt - 1) / cnt;
    debug("RUNNING TEST ", n, d, q, qq);
    int ll = 0;
    int rr = 1;
    auto [p, A, B, best] = get(ans, n, d, qq + (q % cnt > 0), ll, rr);
    fori1(cnt)
    {
        auto [c, C, D, cur] = get({}, n, d, qq + (q % cnt > i), ll, rr);
        debug("Iteration", i, "done.");
        bool update = needsUpdate(ql, p, c, A, B, C, D);

        if (update)
            debug("Updating", p, c, best),
            debug("To", p, c, cur),
            p = c,
            A = C,
            B = D,
            best = cur;
        debug("c", best);
    }
    return tuple(p, A, B, best);
}

void run()
{
    ints(n, d, q); queries = q; MAX_QUERIES = q;
    int m = n;
    while (q < m * log2(m) * 1.5) --m;
    {
        debug("SORTING:", q, m, m * log2(m));
        order.resize(n);
        iota(all(order), 0);
        shuffle(all(order), rng);
        if (false)
            merge_sort(order, 0, m, [&](int x, int y) {
                if (x == y) return false;
                return ask(q, {x}, {y}) == '>';
            });
        //fori(min(m, n / 4)) forced.insert(order[i]);
        debug("ORDER:", order);
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i += d)
        shuffle(order.begin() + i, order.begin() + min(n, i + d), rng);
    fori(n)
        ans[order[i]] = i % d;
    cerr << "LEFT " << queries << endl;
    if (d == 2) 
    {
        auto [p, A, B, best] = run2(ans, n, d, q);
        auto LEFT = queries;
        debug("LEFT, update LAST", LEFT);
        debug("c", best);
        auto [_, __, ___, ret] = get(best, n, d, LEFT, 0, 1);
        LEFT = queries;
        debug("LEFT, MAKE DUMMY", LEFT);
        while (LEFT) ask(LEFT, {0}, {1}, true);
        debug("c", best);
        writeln(best);
    }
    else
    {
        vector<int> buckets(d);
        iota(all(buckets), 0);
        vector<vector<int>> LR(d);
        fori(n) LR[ans[i]].pb(i);
        merge_sort(buckets, 0, d, [&](int lb, int rb) {
            return ask(q, LR[lb], LR[rb]) == '>';
        });
        debug("SORTED", buckets);
        int cnt = 4;
        auto [_, __, ___, cur] = get(ans, n, d, cnt, buckets[0], buckets.back());
        int stuck = 0;
        while (queries && ++stuck < 1000)
        {
            int mm = (d + 1) / 2;
            int ll = MAX_QUERIES - queries < MAX_QUERIES / 2 ? stuck % mm : rng() % d;
            int rr = MAX_QUERIES - queries < MAX_QUERIES / 2 ? d - 1 - rng() % (d - mm) : rng() % d;
            //int ll = rng() % d;
            //int rr = rng() % d;
            while (rr == ll)
                rr = rng() % d;
            auto [_, __, ___, ret] = get(cur, n, d, cnt, buckets[ll], buckets[rr]);
            cur = ret;
            debug("c", cur);
        }
        auto LEFT = queries;
        while (LEFT) ask(LEFT, {0}, {1}, true);
        writeln(cur);
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
//}}}
