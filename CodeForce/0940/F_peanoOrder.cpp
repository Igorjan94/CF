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
typedef    unsigned int      uint;
typedef    unsigned long long      ull;

#define pb push_back
#define all(a) begin(a), end(a)
#define ints(a...) int a; readln(a)

[[maybe_unused]] const int MOD = 1000000007;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

static const auto IOSetup = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(6) << std::fixed;
    return nullptr;}();
struct IOPre {static constexpr int TEN = 10, SZ = TEN * TEN * TEN * TEN;std::array<char, 4 * SZ> num;constexpr IOPre() : num{} {for (int i = 0; i < SZ; i++) {int n = i;for (int j = 3; j >= 0; j--) {num[i * 4 + j] = static_cast<char>(n % TEN + '0');n /= TEN;}}}};

const int N = 100010;
const int Q = 100010;
 
int64_t peanoOrder(int x,int y,int z,int m) {
    vector<vector<int>> a(3, vector<int>(m));
    int sum0 = 0, sum1 = 0, sum2 = 0;
    int ptr = m-1;
    while (x) {
        a[0][ptr] = x%3;
        sum0 += a[0][ptr];
        ptr--;
        x /= 3;
    }
    ptr = m-1;
    while (y) {
        a[1][ptr] = y%3;
        sum1 += a[1][ptr];
        ptr--;
        y /= 3;
    }
    ptr = m-1;
    while (z) {
        a[2][ptr] = z%3;
        sum2 += a[2][ptr];
        ptr--;
        z /= 3;
    }
 
    for (int i = m-1; i >= 0; i--) {
        sum2 -= a[2][i];
        if ((sum0 + sum1)&1)
            a[2][i] = 2 - a[2][i];
 
        sum1 -= a[1][i];
        if ((sum0 + sum2)&1)
            a[1][i] = 2 - a[1][i];
 
        sum0 -= a[0][i];
        if ((sum1 + sum2)&1)
            a[0][i] = 2 - a[0][i];
    }
 
    int64_t num = 0, base = 1;
    for (int j = m-1; j >= 0; j--) {
        num += base * a[2][j];
        base *= 3;
        num += base * a[1][j];
        base *= 3;
        num += base * a[0][j];
        base *= 3;
    }
    return num;
}

tuple<int, int, int, int, int64_t> requests[Q];
array<int, 3> updates[Q];
int a[N];
int ans[Q];

map<int, int> coords;
int m[N * 3];
int diffsCNT[N + 10];
int n, q;
int L = 0;
int R = -1;
int T = 0;
int A = 0;
int B = 0;

inline void er(int x) {
    --diffsCNT[x];
}

inline void ad(int x) {
    ++diffsCNT[x];
}

inline void add(int id) {
    int x = a[id];
    er(m[x]);
    ad(++m[x]);
}

inline void del(int id) {
    int x = a[id];
    er(m[x]);
    ad(--m[x]);
}

inline void update(int index, bool forward) {
    auto [i, from, to] = updates[index];
    if (!forward) to = from;
    if (L <= i && i <= R)
        del(i);
    a[i] = to;
    if (L <= i && i <= R)
        add(i);
}

int get(int x) {
    auto it = coords.find(x);
    if (it != coords.end())
        return it->second;
    int sz = coords.size();
    return coords[x] = sz;
}

void run()
{
    cin >> n >> q;
    fori(n)
    {
        cin >> a[i];
        a[i] = get(a[i]);
    }

    fori(q)
    {
        int type, l, r;
        cin >> type >> l >> r; --l;
        if (type == 1)
        {
            --r;
            auto order = peanoOrder(l, r, B, 13);
            requests[A] = {B, l, r, A, order};
            ++A;
        }
        else
        {
            r = get(r);
            updates[B++] = {l, a[l], r};
            a[l] = r;
        }
    }
    for (int i = B - 1; i >= 0; --i)
        a[updates[i][0]] = updates[i][1];

    sort(requests, requests + A, [&](const auto& a, const auto& b) {
        return get<4>(a) < get<4>(b);
    });

    fori(A)
    {
        const auto& [t, l, r, id, _] = requests[i];
        while (T < t) update(T++, true);
        while (T > t) update(--T, false);
        while (R < r) add(++R);
        while (L > l) add(--L);
        while (R > r) del(R--);
        while (L < l) del(L++);
        for (int mex = 1; ; ++mex)
            if (diffsCNT[mex] == 0)
            {
                ans[id] = mex;
                break;
            }
    }
    fori(A)
        cout << ans[i] << "\n";
}

//{{{
int main()
{
    cin.tie(0); ios_base::sync_with_stdio(false);
    run();
    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
