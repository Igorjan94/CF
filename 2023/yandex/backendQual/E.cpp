// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#include <ostream>
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

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

//Igorjan
//}}}

struct Z
{
    int type = 0; // 0 -- SELL, 1 -- BUY
    int id = -1;
    ll price = 0;
    int volume = 0;

    bool operator<(const Z& o) const 
    {
        if (price != o.price)
            return price > o.price;
        if (type == 0)
            return id > o.id;
        return id < o.id;
    }

    Z(int id): id(id) {}
    Z() {}
};

bool cmp(const Z& t, const Z& o) 
{
    if (t.price != o.price)
        return t.price > o.price;
    if (t.type == 0)
        return t.id > o.id;
    return t.id < o.id;
}

ostream& operator<<(ostream& os, const Z& z) {
    ll l = z.price / 100;
    ll m = z.price % 100;
    os << z.id << " " << (z.type == 0 ? "SELL" : "BUY") << " " << l << ".";
    if (m < 10)
        os << "0" << m;
    else
        os << m;
    os << " " << z.volume;
    return os;
}

void run()
{
    cout << fixed << setprecision(2);
    ints(n);
    set<Z> bs[2];
    set<Z, decltype(&cmp)> zs(&cmp);
    vector<Z> alive(n + 1);
    vector<tuple<int, int, int, int>> operations;

    auto eraseZ = [&](int id) {
        auto& z = alive[id];
        zs.erase(z);
        bs[z.type].erase(z);
        z.id = -1;
    };

    auto insertZ = [&](const Z& z) {
        if (z.volume == 0) return;
        zs.insert(z);
        bs[z.type].insert(z);
        alive[z.id] = z;
    };

    auto process = [&](auto process) -> void {
        if (bs[0].empty() || bs[1].empty())
            return;
        auto s = *bs[0].rbegin();
        auto b = *bs[1].begin();
        if (s.price > b.price)
            return;
        if (s.price <= b.price)
        {
            for (auto it = bs[0].rbegin(); it != bs[0].rend() && it->price <= b.price; ++it)
                if (s.id > it->id)
                    s = *it;
            for (auto it = bs[1].begin(); it != bs[1].end() && s.price <= it->price; ++it)
                if (b.id > it->id)
                    b = *it;
        }
        int amount = min(s.volume, b.volume);
        int price = b.price;
        if (b.price > s.price && s.id < b.id)
            price = s.price;
        operations.pb({b.id, s.id, price, amount});
        eraseZ(b.id);
        eraseZ(s.id);
        s.volume -= amount;
        b.volume -= amount;
        insertZ(s);
        insertZ(b);
        process(process);
    };

    int id = 0;
    forn(q, n)
    {
        string op;
        readln(op);
        if (op == "ADD")
        {
            string type, price;
            int volume;
            readln(type, price, volume);
            Z z(++id);
            int index = price.find('.');
            if (index + 3 != price.size()) exit(1);
            price.erase(price.begin() + index);
            z.price = stoi(price);
            z.type = type == "BUY";
            z.volume = volume;
            insertZ(z);
            writeln(id);
            process(process);
        }
        if (op == "GET")
        {
            for (auto& z: zs)
                writeln(z);
        }
        if (op == "DELETE")
        {
            ints(id);
            if (id > n) {
                writeln("NOT FOUND");
                continue;
            }
            if (alive[id].id == -1)
                writeln("NOT FOUND");
            else
            {
                eraseZ(id);
                writeln("DELETED");
            }
        }
        if (op == "SHOW_OPERATIONS")
        {
            ints(cnt);
            int sz = operations.size();
            for (int i = max(0, sz - cnt); i < sz; ++i)
            {
                auto [b, s, p, v] = operations[i];
                ll l = p / 100;
                ll m = p % 100;
                cout << b << " " << s << " " << l << ".";
                if (m < 10)
                    cout << "0" << m;
                else
                    cout << m;
                cout << " " << v << "\n";

            }
        }
        cout.flush();
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
