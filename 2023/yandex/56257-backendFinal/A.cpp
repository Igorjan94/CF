// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#include <limits>
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
typedef __int128 ll;
map<ll, ll> memory;
vector<ll> r(8);

ll mx = 1; 
ll mn = -1;

auto myabs(auto t) {
    if (t < 0) return -t; else return t;
}

struct command 
{
    ll a;
    ll b;
    ll c;
    bool isAddressA;
    bool isAddressB;
    bool isAddressC;
    int code;

    bool checkAddress() {
        if (isAddressA && r[a] % 4 != 0)
            return false;
        if (isAddressB && r[b] % 4 != 0)
            return false;
        if (isAddressC && r[c] % 4 != 0)
            return false;
        return true;
    }

    bool emptyA() {
        return a == 0 && !isAddressA;
    }

    bool emptyB() {
        return b == 0 && !isAddressB;
    }

    bool emptyC() {
        return c == 0 && !isAddressC;
    }

    bool unused() {
        if (code == 0 || code == 15)
            return emptyA() && emptyB() && emptyC();
        if (code == 1)
            return emptyB();
        if (code == 11)
            return emptyB();
        if (code >= 13)
            return emptyA() && emptyB();
        return true;
    }

    ll& getA() {
        if (isAddressA)
            return memory[r[a]];
        return r[a];
    }

    ll& getB() {
        if (isAddressB)
            return memory[r[b]];
        return r[b];
    }

    ll& getC() {
        if (isAddressC)
            return memory[r[c]];
        return r[c];
    }

    bool checkOverFlow() {
        auto cc = getC();
        return cc > mx || cc < mn;
    }

    bool perform() {
        if (!unused()) return false;
        if (!checkAddress()) return false;
        if (code == 0)
            return true;

        auto& a = getA();
        auto& b = getB();
        auto& c = getC();
        auto copy = c;
        if (code == 1)
            //writeln("c = a"),
            c = a;
        if (code == 2)
            //writeln("c = a + b"),
            c = a + b;
        if (code == 3)
            //writeln("c = a - b"),
            c = a - b;
        if (code == 4)
            //writeln("c = a * b"),
            c = a * b;
        if (code == 5)
        {
            //writeln("c = a / b");
            if (b == 0)
                return false;
            c = a / b;
        }
        if (code == 6)
        {
            //writeln("c = myabs(a) << b");
            if (b <= 0)
                return false;
            auto ac = a;
            c = unsigned(ac) << b;
        }
        if (code == 7)
        {
            //writeln("c = myabs(a) >> b");
            if (b <= 0)
                return false;
            auto ac = a;
            //if (ac < 0) ac = (ac ^ 2147483647) + 1;
            c = unsigned(ac) >> b;
            //if (c < 0) c = (c ^ 2147483647) + 1;
        }
        if (code == 8)
            //writeln("c = a & b"),
            c = a & b;
        if (code == 9)
            //writeln("c = a | b"),
            c = a | b;
        if (code == 10)
            //writeln("c = a ^ b"),
            c = a ^ b;
        if (code == 11)
            //writeln("c = a ^ mx"),
            c = ~int(a);
        if (code == 12)
        {
            //writeln("c = myabs(a) % myabs(b)");
            if (b == 0)
                return false;
            c = myabs(a) % myabs(b);
        }
        if (code == 13)
            //writeln("++c"),
            ++c;
        if (code == 14)
            //writeln("--c"),
            --c;
        //writeln(c);
        if (code == 15)
            return false;
        bool wasO = checkOverFlow();
        if (wasO)
            c = copy;
        //fori(r.size())
            //cout << (long long) r[i] << " ";
        //writeln();
        //for (auto& [k, v]: memory)
            //cout << "(" << (long long) k << " " << (long long) v << ") ";
        //writeln();
        return !wasO;
    }

    command() {}
};

//ostream& operator<<(ostream& os, const command& c) {
    //return os << 
        //c.c << (c.isAddressC ? "[]" : "") << " " <<
        //c.a << (c.isAddressA ? "[]" : "") << " " <<
        //c.b << (c.isAddressB ? "[]" : "") << " " <<
        //c.code;
//}

istream& operator>>(istream& is, command& c) {
    string s;
    is >> s;
    unsigned long long x;   
    std::stringstream ss;
    ss << hex << s;
    ss >> x;
    c.c = x & 7;
    x >>= 3;
    c.isAddressC = x & 1;
    x >>= 1;
    c.b = x & 7;
    x >>= 3;
    c.isAddressB = x & 1;
    x >>= 1;
    c.a = x & 7;
    x >>= 3;
    c.isAddressA = x & 1;
    x >>= 1;
    c.code = x;
    return is;
}

void run()
{
    ints(n);
    vector<command> commands(n);
    readln(commands);
    fori(n)
    {
        if (!commands[i].perform())
            return writeln("ERROR", r[0]);
    }
    writeln("OK",  r[0]);
}

//Igorjanint128
inline istream&operator>>(istream&in,__int128&a){
    a = 0;
    bool neg = false;
    char c;
    in >> noskipws >> c;
    while (c < '0' || c > '9') {
        neg = c == '-';
        in >> noskipws >> c;
    }
    while (c >= '0' && c <= '9') {
        a = a * 10 + c - '0';
        in >> noskipws >> c;
    }
    if (neg) a *= -1;
    return in;
}
inline ostream&operator<<(ostream&out,const __int128& x) {
    auto a = x;
    if (a < 0)
    {
        out << "-";
        a *= -1;
    }
    string s;
    while (a >= 10)
        s.pb((a % 10) + '0'),
        a /= 10;
    s.pb(a + '0');
    reverse(all(s));
    return out << s;
}

//{{{
int main()
{
    fori(31)
        mn *= 2,
        mx *= 2;
    --mx;
    ios_base::sync_with_stdio(false); cin.tie(0);
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
