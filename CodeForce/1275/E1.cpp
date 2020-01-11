// Igorjan94, template version from 13 October 2017. C++17 version, modified 14 september 2019 (writeln<T>, main) {{{
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

#define    pb    push_back
#define whole(a) begin(a), end(a)
#define   next   next__
#define   prev   prev__
#define  count   count__

#define ints(a...)  int a; readln(a)
#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline

const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
vector<string>split(string&s,string d){vector<string>v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
#define CRCPOLY 0xEDB88320
#define INITXOR 0xFFFFFFFF
#define FINALXOR 0xFFFFFFFF
#define uint unsigned int
vector<uint> table(256), rev_table(256);

void make_crc_table() {
    uint c;
    fori(256)
    {
        c = i;
        forj(8)
            if (c & 1)
                c = CRCPOLY ^ (c >> 1);
            else
                c >>= 1;
        table[i] = c;
    }
}

void make_crc_revtable() {
    uint c;
    fori(256)
    {
        c = i << 24;
        forj(8)
            if (c & 0x80000000)
                c = ((c ^ CRCPOLY) << 1) | 1;
            else
                c <<= 1;
        rev_table[i] = c;
    }
}

template <typename InputIterator>
uint calc_crc(InputIterator first, InputIterator last)
{
    uint crcreg = INITXOR;
    for (auto it = first; it != last; ++it)
        crcreg = (crcreg >> 8) ^ table[((crcreg ^ *it) & 0xFF)];
    return crcreg;
}

template <typename InputIterator>
uint calc_crc_all(InputIterator first, InputIterator last)
{
    return calc_crc(first, last) ^ FINALXOR;
}

//https://github.com/madler/zlib (c)
#define SIZE 32

uint mtimes(vector<uint>& mat, uint vec)
{
    uint sum = 0;
    int i = 0;
    while (vec) {
        if (vec & 1)
            sum ^= mat[i];
        vec >>= 1;
        i++;
    }
    return sum;
}

void msquare(vector<uint>& square, vector<uint>& mat)
{
    fori(SIZE)
        square[i] = mtimes(mat, mat[i]);
}

vector<uint> EVEN, ODD;

uint crc32_combine(uint crc1, uint crc2, int len2)
{
    vector<uint> even = EVEN;
    vector<uint> odd = ODD;
    if (len2 <= 0)
        return crc1;
    do {
        msquare(even, odd);
        if (len2 & 1)
            crc1 = mtimes(even, crc1);
        len2 >>= 1;

        if (len2 == 0)
            break;

        msquare(odd, even);
        if (len2 & 1)
            crc1 = mtimes(odd, crc1);
        len2 >>= 1;

    } while (len2 != 0);

    crc1 ^= crc2;
    return crc1;
}

//IgorjansparseTable
//0-indexed, [l, r)
template<typename T>
struct sparseTable
{
    int n;
    vector<vector<T>> st;
    vector<int> logs;
    typedef function<T (T, T, int)> F;
    F f;

    sparseTable(vector<T>& a, F g, function<uint(int)> init)
    {
        n = a.size();
        f = g;

        logs.push_back(0);
        logs.push_back(0);
        FOR(i, 2, n + 1) logs.push_back(logs[i / 2] + 1);
        int L = logs.back() + 1;
        st.resize(L, vector<T>(n));
        fori(n)
            st[0][i] = init(i);
        FOR(k, 1, L)
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = f(st[k - 1][i], st[k - 1][i + (1 << (k - 1))], 1 << (k - 1));
    }

    T get(int l, int r)
    {
        T sum = 0;
        for (int j = logs.back(); j >= 0; j--) {
            if ((1 << j) <= r - l + 1) {
                sum = f(sum, st[j][l], 1 << j);
                l += 1 << j;
            }
        }
        return sum;
    }
};
//}}}

struct request
{
    int i, j, id, crc, l;
    vector<uint> x = {0, 0, 0, 0};
    vector<uint> ans = {0, 0, 0, 0};
};

istream& operator>>(istream& is, request& r)
{
    is >> r.i >> r.j >> r.x[0] >> r.x[1] >> r.x[2] >> r.x[3];
    r.crc = calc_crc_all(whole(r.x));
    r.l = r.j - r.i - 4;
    return is;
}

ostream& operator<<(ostream& os, const request& r)
{
    return os << r.i << " " << r.j << " " << r.x[0] << " " << r.x[1] << " " << r.x[2] << " " << r.x[3];
}

void run()
{
    make_crc_table();
    make_crc_revtable();
    EVEN.resize(SIZE);
    ODD.resize(SIZE);
    ODD[0] = CRCPOLY;
    uint row = 1;
    fori1(SIZE) {
        ODD[i] = row;
        row <<= 1;
    }

    msquare(EVEN, ODD);
    msquare(ODD, EVEN);

    ints(n, q);
    vector<uint> a(n);
    readln(a);
    uint crc = calc_crc_all(whole(a));
    sparseTable<uint> t(a, crc32_combine, [&](int i) { return calc_crc_all(a.begin() + i, a.begin() + i + 1); });

    vector<request> requests(q);
    readln(requests); fori(q) requests[i].id = i;
    sort(whole(requests), [](const request& a, const request& b) { return a.j > b.j; });
    //{
        //vector<uint> b = a;
        //reverse(whole(b));
        //sparseTable<uint> tt(b, crc32_combine, [&](int i) { return (INITXOR << 8) ^ rev_table[INITXOR >> 24] ^ a[i] ^ FINALXOR; });
        //uint crcreg = INITXOR;
        //fori(n)
        //{
            //crcreg = (crcreg << 8) ^ rev_table[crcreg >> 24] ^ a[i];
            //printf("%x\n%x\n\n", crcreg ^ FINALXOR, tt.get(0, i));
        //}
        //return;
    //}

    auto dumpValue = [&](uint value, vector<uint>& ans) {
        forn(k, 4) ans[k] = (value >> k * 8) & 0xFF;
    };

    int i = 0;
    uint crcreg = crc ^ FINALXOR;
    for (int j = n - 1; j >= 0; --j)
    {
        for ( ; i < q && requests[i].i < requests[i].j && requests[i].j + 3 == j; ++i)
        {
            auto& r = requests[i];
            uint cur = r.crc;
            if (r.i)
                cur = crc32_combine(t.get(0, r.i - 1), cur, 4);
            if (r.i + 4 < r.j)
                cur = crc32_combine(cur, t.get(r.i + 4, r.j - 1), r.l);
            uint AZB = t.get(0, r.j - 1);
            forn(k, 4) r.x[k] ^= a[r.i + k];
            uint Z = calc_crc_all(whole(r.x));
            Z = crc32_combine(Z, 0, r.l);
            printf("%x\n%x\n\n", cur ^ FINALXOR, AZB ^ Z);
            dumpValue(cur ^ FINALXOR, r.ans);

            uint tcrcreg = crcreg;
            forn(k, 4) tcrcreg = (tcrcreg << 8) ^ rev_table[tcrcreg >> 24] ^ r.ans[3 - k];
            dumpValue(tcrcreg, r.ans);
        }
        crcreg = (crcreg << 8) ^ rev_table[crcreg >> 24] ^ a[j];
    }

    sort(whole(requests), [](const request& a, const request& b) { return a.id < b.id; });
    fori(q)
        if (auto& r = requests[i]; r.i > r.j)
        {
            uint crcreg = 0;
            if (r.j)
                crcreg = t.get(0, r.j - 1);
            dumpValue(crcreg ^ FINALXOR, r.ans);

            uint tcrcreg = crc ^ FINALXOR;
            for (int k = n - 1; k >= r.i + 4; --k)
                tcrcreg = (tcrcreg << 8) ^ rev_table[tcrcreg >> 24] ^ a[k];
            for (int k = 3; k >= 0; --k)
                tcrcreg = (tcrcreg << 8) ^ rev_table[tcrcreg >> 24] ^ r.x[k];
            for (int k = r.i - 1; k >= r.j + 4; --k)
                tcrcreg = (tcrcreg << 8) ^ rev_table[tcrcreg >> 24] ^ a[k];
            for (int k = 3; k >= 0; --k)
                tcrcreg = (tcrcreg << 8) ^ rev_table[tcrcreg >> 24] ^ r.ans[k];
            dumpValue(tcrcreg, r.ans);
        }
    //{
        //uint crcreg = calc_crc(a.begin(), a.begin() + j);
        //crcreg ^= FINALXOR;
        //for (int k = n - 1; k >= j; --k)
            //crcreg = (crcreg << 8) ^ rev_table[crcreg >> 24] ^ a[k];
        //forn(k, 4)
            //a[i + k] = (crcreg >> k * 8) & 0xFF;
        //writeln(a[j], a[j + 1], a[j + 2], a[j + 3]);
    //};

    fori(q)
        writeln(requests[i].ans);
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
