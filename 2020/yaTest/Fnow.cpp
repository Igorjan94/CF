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

inline bool inside(int lx, int ly, int rx, int ry, int x, int y)
{
    return lx <= x && x < rx && ly <= y && y < ry;
}

static const int N = 1048576;
static const int R = 16;
static const int CCC = int(N * 1.33) + 100;
int w = 0;

struct quadro
{
    set<pii> points;
    int lx, ly, sz;
    int i = 0;

    quadro() {}
    quadro(int lx, int ly, int sz): lx(lx), ly(ly), sz(sz) {
        w++;
    }

    void init(int lx, int ly, int sz)
    {
        this->lx = lx;
        this->ly = ly;
        this->sz = sz;
    }

    void insert(int x, int y);
    void erase(int x, int y);
    pii get(int left, int down, int right, int up);
};

quadro Q[CCC];
int ii[CCC][16];

void quadro::insert(int x, int y)
{
    //writeln("Adding", x, y, "to", lx, ly, sz); cout.flush();

    auto create = [&](const int& index, int x, int y, int lx, int ly) {
        if (ii[i][index] == -1)
        {
            ii[i][index] = w++;
            Q[ii[i][index]].init(lx, ly, sz / 4);
            Q[ii[i][index]].i = ii[i][index];
        }
        Q[ii[i][index]].insert(x, y);
    };

    auto iii = [&](const int& x, const int& y) {
        int ix = (x - lx) / sz;
        int iy = (y - ly) / sz;
        int index = ix * 4 + iy;
        create(index, x, y, lx + ix * sz, ly + iy * sz);
    };

    if (points.size() == R)
        for (const auto& [yy, mxx]: points)
            iii(-mxx, yy);
    if (points.size() >= R)
        iii(x, y);
    points.emplace(y, -x);
}

void quadro::erase(int x, int y)
{
    points.erase({y, -x});

    auto create = [&](const int& index) {
        if (ii[i][index] != -1) {
            Q[ii[i][index]].erase(x, y);
            if (Q[ii[i][index]].points.size() == 0)
                ii[i][index] = -1;
        }
    };
    int ix = (x - lx) / sz;
    int iy = (y - ly) / sz;
    int index = ix * 4 + iy;
    create(index);
}


pii quadro::get(int left, int down, int right, int up)
{
    int rx = lx + sz * 4;
    int ry = ly + sz * 4;
    //writeln("Asking", left, down, right, up, lx, ly, rx, ry);
    if (points.size() == 0 || rx <= left || ry <= down || lx >= right || ly >= up) //No points or we are outside of query 
        return {-1, -1};
    //writeln("Found points, searching");
    if (lx >= left && ly >= down && rx <= right && ry <= up) //We are inside in query
        return *points.begin();

    pii ans = {-1, -1};

    if (points.size() <= R)
    {
        for (const auto& pp: points)
            if (inside(left, down, right, up, -pp.second, pp.first))
                if (ans.first == -1)
                    return pp;
        return ans;
    }
    //writeln("2 queries");

    auto update = [&](const int& index) {
        if (ii[i][index] == -1)
            return;
        auto a = Q[ii[i][index]].get(left, down, right, up);
        if (a.first != -1)
        {
            if (ans.first != -1)
                ans = min(a, ans);
            else
                ans = a;
        }
    };

    update(0);
    update(4);
    update(8);
    update(12);
    if (ans.first == -1)
    {
        update(1);
        update(5);
        update(9);
        update(13);
    }
    if (ans.first == -1)
    {
        update(2);
        update(6);
        update(10);
        update(14);
    }
    if (ans.first == -1)
    {
        update(3);
        update(7);
        update(11);
        update(15);
    }
    return ans;
}

struct pair_hash {
    inline long long operator()(const pii& v) const {
        return (v.first << 20) + v.second;
    }
};

//static const int N = 16;
void run()
{
    fori(CCC) forj(16) ii[i][j] = -1;
    ints(n, m, k);
    Q[0] = quadro(0, 0, N / 4);
    vector<pii> a(k);
    readln(a);
    unordered_set<pii, pair_hash> p(all(a));
    sort(all(a));
    for (const auto& [x, y]: a)
        //writeln("Inserting", x, y, w), cout.flush(),
        Q[0].insert(x, y);

    //fori(w)
        //Q[i].points = set<pii>(all(W[i]));

    int ans = 0;
    while (p.size())
    {
        //writeln("New iteration"); cout.flush();
        int l = -1;
        int r = 0;
        int px = 0;
        while (true)
        {
            //writeln("Asking", l, r, N, N);
            auto point = Q[0].get(l, r, N, N);
            if (point.first == -1)
                break;
            auto& [qy, qx] = point; qx *= -1;
            if (qx == n - 1 && qy == 0) --ans;
            //writeln(qx, qy);

            int x = qx;
            int y = qy;
            if (y != r)
                px = l + 1;
            while (true)
            {
                auto it = p.find({x, y});
                if (it == p.end() || x < px)
                    break;
                //writeln("Erasing", x, y);
                p.erase({x, y});
                Q[0].erase(x, y);
                --x;
            }
            px = x + 1;
            //writeln("PX", px);
            l = qx;
            r = qy + 1;
        }
        ans += 2;
    }
    writeln(ans);
    cerr << "w = " << w << endl;
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
