// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("Ofast")
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

[[maybe_unused]] const int MOD = 1000000000;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

#define ttt12i template<class T1, class T2> inline
#define  ttti  template<class T> inline

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

//Igorjan
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//}}}

static const int M = 3000;
static const int N = 1000;

typedef bitset<M> roads;

int RUNS = 0;
int n, m, k, d, need;
vector<array<int, 3>> edges;
vector<array<int, 3>> g[N];
ll degree[N];
ll importance[M];
ll dist[N][N];
ll CUR[N][N];

void get(ll (&dist)[N], int start, const roads& repaired) {
    fori(n) dist[i] = MOD;
    dist[start] = 0;
    priority_queue<pair<ll, int>> q;
    q.push({0, start});
    while (q.size())
    {
        auto [D, u] = q.top(); D *= -1;
        q.pop();

        for (const auto& [v, w, e]: g[u])
            if (!repaired[e])
                if (ll cur = D + w; dist[v] > cur)
                    dist[v] = cur,
                    q.push({-cur, v});
    }
}

void calc(ll (&ans)[N][N], const roads& repaired) {
    fori(n) get(ans[i], i, repaired);
}

ll score() {
    ll f = 0;
    fori(n)
        forj(i)
            f += CUR[i][j] - dist[i][j];
    return f * 2;
}

ll fullScore(const vector<roads>& days, bool debug = false) {
    ++RUNS;
    ll ans = 0;
    for (auto& day: days)
    {
        calc(CUR, day);
        const auto& curScore = score();

        if (debug)
            writeln(curScore * 1.0 / n / (n - 1));
        ans += curScore;
    }
    return ans;
}

double getTime() {
    return clock() * 1000. / CLOCKS_PER_SEC;
}

int random(int from, int to) {
    return from + rng() % (to - from);
}

auto solve(int tl)
{
    ll s = numeric_limits<ll>::max();
    vector<int> ans(m);
    vector<roads> daysAns;
    double start = getTime();

    vector<int> permutation(m);
    iota(all(permutation), 0);
    sort(all(permutation), [&](const int& a, const int& b) {
        return edges[a][2] < edges[b][2];
    });

    while (getTime() - start < tl)
    {
        vector<roads> days(d);

        auto setRoad = [&](int road, int day) {
            days[day][road] = true;
            ans[road] = day + 1;
        };

        if (false)
        {
            shuffle(all(permutation), rng);
            int mn = m / d;
            vector<int> a(d);
            fori(d)
                a[i] = random(mn, k + 1);
            int sum = accumulate(all(a), 0);
            while (sum > m)
            {
                int i = random(0, d);
                if (a[i])
                    --a[i], --sum;
            }

            int j = 0;
            fori(d)
                forn(q, a[i])
                {
                    int road = permutation[j++];
                    setRoad(road, i);
                }
        }

        if (false) 
        {
            for (int i = 0; i < m; i += d)
                shuffle(permutation.begin() + i, permutation.begin() + min(m, i + d), rng);

            for (int i = 0; i < m; i += d)
                for (int day = 0; day < d && i + day < m; ++day)
                {
                    int road = permutation[i + day];
                    setRoad(road, day);
                }
        }

        if (true)
        {
            sort(all(permutation), [&](const auto& x, const auto& y) {
                return importance[x] > importance[y];
            });


            vector<bool> used(m);
            for (int day = 0; day < d; ++day)
            {
                vector<ll> deg(n);
                int cnt = 0;
                int prev = -100;
                auto use = [&](int road) {
                    const auto& [u, v, w] = edges[road];
                    const ll im = importance[road];
                    deg[u] += im;
                    deg[v] += im;
                    ++cnt;
                    setRoad(road, day);
                    used[road] = true;
                    for (auto& vv: g[u])
                        deg[vv[0]] += im / 10;
                    for (auto& vv: g[v])
                        deg[vv[0]] += im / 10;
                };

                for (int i = 0; i < m && cnt < need; ++i)
                {
                    int road = permutation[i];
                    const auto& [u, v, w] = edges[road];
                    if (used[road] || i - prev < d * 2)
                        continue;
                    const ll curImportance = importance[road] * 10;
                    const ll lowImportance = -1;
                    if ((deg[u] > lowImportance && deg[u] <= curImportance) || (deg[v] > lowImportance && deg[v] <= curImportance))
                        continue;
                    use(road);
                    prev = i;
                }
                prev = -100;
                for (int i = 0; i < m && cnt < need; ++i)
                {
                    int road = permutation[i];
                    const auto& [u, v, w] = edges[road];
                    if (used[road])
                        continue;
                    const ll curImportance = importance[road] * 10;
                    const ll lowImportance = importance[road] / 5;
                    if ((deg[u] > lowImportance && deg[u] <= curImportance) || (deg[v] > lowImportance && deg[v] <= curImportance))
                        continue;
                    use(road);
                    prev = i;
                }
            }
            fori(d)
                cerr << "TTT " << i << ": " << days[i].count() << endl;
            cerr << endl;
            for (int i = 0; i < m; ++i)
            {
                int road = permutation[i];
                int day = rng() % d;
                while (int(days[day].count()) == k)
                    day = rng() % d;

                if (!used[road])
                    used[road] = true,
                    setRoad(road, day);

            }
    }
        
        auto cur = fullScore(days);
        if (cur < s)
            s = cur,
            daysAns = days;
    }
    return tuple(s, ans, daysAns);
}

void calcImportance()
{
    fori(n)
    {
        vector<int> used(n);
        auto dfs = [&](auto dfs, int u) -> int {
            used[u] = true;
            int cnt = 1;
            for (const auto& [v, w, index]: g[u])
                if (!used[v] && dist[i][u] + w == dist[i][v])
                {
                    int cur = dfs(dfs, v);
                    importance[index] += cur;
                    cnt += cur;
                }
            return cnt;
        };
        dfs(dfs, i);
    }
    for (int i = 0; i < m; ++i)
        importance[i] *= edges[i][2] * 1ll * edges[i][2];
}

void run()
{
    readln(n, m, d, k);
    need = m / d;
    fori(m) 
    {
        ints(u, v, w); --u; --v;
        g[u].pb({v, w, i});
        g[v].pb({u, w, i});
        edges.pb({u, v, w});
        ++degree[u];
        ++degree[v];
    }

    calc(dist, {});
    calcImportance();
    fori(n)
        sort(all(g[i]), [&](const auto& x, const auto& y) {
            return importance[x[2]] > importance[y[2]];
        });

    const auto& [sum, ans, days] = solve(3000);
    writeln(ans);
    cerr << sum * 1000.0 / n / (n - 1) / d << endl;
    fori(d)
        cerr << "DAY " << i << ": " << days[i].count() << endl;
    cerr << "RUNS " << RUNS << endl;
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cerr << fixed << setprecision(3);
    cout << fixed << setprecision(3);
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
