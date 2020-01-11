#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

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
 
void make_crc_table(vector<uint>& table) {
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
 
void make_crc_revtable(vector<uint>& table) {
    uint c;
    fori(256)
    {
        c = i << 24;
        forj(8)
            if (c & 0x80000000)
                c = ((c ^ CRCPOLY) << 1) | 1;
            else
                c <<= 1;
        table[i] = c;
    }
}
 
template <typename InputIterator>
std::uint_fast32_t calc_crc(InputIterator first, InputIterator last, const vector<uint>& crc_table)
{
    uint crcreg = INITXOR;
    for (auto it = first; it != last; ++it)
        crcreg = (crcreg >> 8) ^ crc_table[((crcreg ^ *it) & 0xFF)];
    return crcreg;
}
 
void fix_crc_pos(vector<uint> buffer, uint tcrcreg, int fix_pos, const vector<uint>& crc_table, const vector<uint>& crc_revtable)
{
    uint crcreg = calc_crc(buffer.begin(), buffer.begin() + fix_pos, crc_table);
    fori(4)
        buffer[fix_pos + i] = (crcreg >> i * 8) & 0xFF;
    tcrcreg ^= FINALXOR;
    for (int i = SZ(buffer) - 1; i >= fix_pos; --i)
        tcrcreg = (tcrcreg << 8) ^ crc_revtable[tcrcreg >> 24] ^ buffer[i];
    fori(4)
        buffer[fix_pos + i] = (tcrcreg >> i * 8) & 0xFF;
    writeln(buffer[fix_pos], buffer[fix_pos + 1], buffer[fix_pos + 2], buffer[fix_pos + 3]);
}
 
//}}}
 
void run()
{
    vector<uint> table(256), rev_table(256);
    make_crc_table(table);
    make_crc_revtable(rev_table);
 
    ints(n, q);
    vector<uint> a(n);
    readln(a);
    uint crc = calc_crc(whole(a), table) ^ FINALXOR;
    auto get = [&](vector<uint> a) {
        int i, j;
        vector<uint> x(4);
        readln(i, j, x);
        forn(k, 4) a[i + k] = x[k];
        fix_crc_pos(a, crc, j, table, rev_table);
    };
    forn(Q, q)
        get(a), cout.flush();
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
