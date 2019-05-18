// Igorjan94, template version from 13 October 2017. C++17 version, modified 07 August 2018 (&&, whole) {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(size(a))

typedef  pair<int, int>   pii;
typedef  valarray<int>    va;
typedef   vector<int>     vi;
typedef    long long      ll;

#define    pb    push_back
#define whole(a) begin(a), end(a)
#define   next   next__
#define   prev   prev__
#define  count   count__

const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();
const ll LLMAX = numeric_limits<ll>::max();


//binSearch
//x -> min, f(x) == true
template<typename T, typename F>
T binSearch(T l, T r, F f, T eps = 1)
{
    T m;
    while (fabs(r - l) > eps)
        m = l + (r - l) / 2,
        (f(m) ? r : l) = m;
    return f(l) ? l : r;
}
//Igorjan
//}}}

struct rational
{
    int num, den;
    rational() : num(0), den(1) {}
    rational(int num, int den)
    {
        if (den == 0)
            this->den = 0,
            this->num = 1;
        else if (num == 0)
            this->den = 1,
            this->num = 0;
        else
        {
            int g = __gcd(abs(den), abs(num));
            den /= g;
            num /= g;
            if (den < 0)
                den *= -1,
                num *= -1;
            this->den = den;
            this->num = num;
        }
    }

    bool operator<(const rational& b) const {
        return num * 1ll * b.den < den * 1ll * b.num;
    }

    bool operator<=(const rational& b) const {
        return num * 1ll * b.den <= den * 1ll * b.num;
    }
};

ostream& operator<<(ostream& os, const rational& rat)
{
    return os << rat.num << "/" << rat.den;
}

void run()
{
    int n;
    cin >> n;
    vector<pii> a(n), b;
    rational mn(MOD, 1), mx, zero;
    fori(n) cin >> a[i].first >> a[i].second;
    fori(n)
        FOR(j, i + 1, n)
        {
            int A = a[j].first - a[i].first;
            int B = a[i].second - a[j].second;
            if ((A == 0 && B > 0) || (B == 0 && A < 0))
            {
                cout << "IMPOSSIBLE\n";
                return;
            }
            if (A == 0 || B == 0)
                continue;
            rational temp(B, A);
            if (A < 0)
                mn = min(mn, temp);
            else if (A > 0)
                mx = max(mx, temp);
            //cout << (i + 1) << " " << (j + 1) << " " << B << " " << A << " " << temp << "\n";
        }
    if (mn <= mx || mn <= zero)
        cout << "IMPOSSIBLE\n";
    else
    {
        for (int x = mx.num / mx.den + 1; x <= 10000; ++x)
        {
            int y = binSearch(1, MOD, [&](int m) {
                return x * 1ll * mn.den < m * 1ll * mn.num;
            });
            rational temp(x, y);
            if (mx < temp && temp < mn)
            {
                cout << x << " " << y << "\n";
                return;
            }
        }
        cout << "IMPOSSIBLE\n";
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    int t;
    cin >> t;
    fori(t)
        cout << "Case #" << (i + 1) << ": ",
        run();
    return 0;
}
