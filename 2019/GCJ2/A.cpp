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

int run()
{
    int n;
    cin >> n;
    vector<pii> a(n), b, c;
    fori(n) cin >> a[i].first >> a[i].second;
    set<rational> s;
    fori(n)
        FOR(j, i + 1, n)
        {
            rational temp(a[i].first - a[j].first, a[i].second - a[j].second);
            if (temp.den < 0 ^ temp.num < 0)
                s.insert(temp);
        }
    return s.size() + 1;
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
        cout << "Case #" << (i + 1) << ": " << run() << "\n";
    return 0;
}
