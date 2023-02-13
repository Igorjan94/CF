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
//MO
inline ll hilbertOrder(int x, int y, int pow, int rotate = 0) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) ? (
        (y < hpow) ? 0 : 3
    ) : (
        (y < hpow) ? 1 : 2
    );
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    ll subSquareSize = ll(1) << (2*pow - 2);
    ll ans = seg * subSquareSize;
    ll add = hilbertOrder(nx, ny, pow-1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

template<typename S, typename T>
struct MO
{
    int n;
    int w;
    int q = 0;
    vector<tuple<ll, int, int, int, T>> queries;
    vector<S> answers;

    const void f(const int&);
    void (*addLeft)(const int&);
    void (*addRight)(const int&);
    void (*delLeft)(const int&);
    void (*delRight)(const int&);
    S (*getAnswer)(const int&, const int&, const T&);

    void addQuery(int l, int r, const T& t) {
        queries.push_back({hilbertOrder(l, r, w), l, r, q++, t});
    }

    MO(unsigned int maxN,
        void addLeft(const int&),
        void addRight(const int&),
        void delLeft(const int&),
        void delRight(const int&),
        S getAnswer(const int&, const int&, const T&)
    ) {
        n = maxN;
        w = bit_width(maxN);
        this->addLeft = addLeft;
        this->addRight = addRight;
        this->delLeft = delLeft;
        this->delRight = delRight;
        this->getAnswer = getAnswer;
    }

    vector<S> go(
    ) {
        answers.resize(q);
        sort(all(queries), [&](const auto& a, const auto& b) {
            return get<0>(a) < get<0>(b);
        });

        int L = 0;
        int R = -1;

        for (int i = 0; i < q; ++i)
        {
            const auto& [_, l, r, id, t] = queries[i];
            while (L > l) addLeft(--L);
            while (R < r) addRight(++R);
            while (L < l) delLeft(L++);
            while (R > r) delRight(R--);
            answers[id] = getAnswer(l, r, t);
        }
        return answers;
    }
};


//}}}

static const int N = 100'005;
int lefts[1 << 20];
int rights[1 << 20];
int sums[N];
int a[N];
ll answer = 0;
int n, m, k;

inline void addLeft(const int& x) {
    ++lefts[sums[x]];
    ++rights[sums[x + 1]];
    answer += rights[k ^ sums[x]];
}

inline void addRight(const int& x) {
    ++lefts[sums[x]];
    ++rights[sums[x + 1]];
    answer += lefts[k ^ sums[x + 1]];
}

inline void delLeft(const int& x) {
    answer -= rights[k ^ sums[x]];
    --lefts[sums[x]];
    --rights[sums[x + 1]];
}

inline void delRight(const int& x) {
    answer -= lefts[k ^ sums[x + 1]];
    --lefts[sums[x]];
    --rights[sums[x + 1]];
}

ll getAnswer(const int& l, const int& r, const int&) {
    return answer;
}

void run()
{
    readln(n, m, k);
    fori(n)
        readln(a[i]);
    sums[0] = 1;
    fori(n) sums[i + 1] = sums[i] ^ a[i];

    int l, r;
    MO<ll, int> mo(n, addLeft, addRight, delLeft, delRight, getAnswer);
    fori(m)
        readln(l, r),
        mo.addQuery(--l, --r, 0);

    auto ans = mo.go();
    fori(m)
        writeln(ans[i]);
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
