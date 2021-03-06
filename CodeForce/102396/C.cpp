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
//dsu
struct dsu
{
    vector<int> a;
    vector<map<int, int>> friends;

    dsu(int n)
    {
        friends.resize(n);
        a.resize(n);
        iota(a.begin(), a.end(), 0);
    }

    int get(int i)
    {
        return a[i] == i ? i : a[i] = get(a[i]);
    }

    void uni(int i, int j)
    {
        //writeln("Adding trains", i, j);
        i = get(i);
        j = get(j);
        if (i == j) return;
        if (SZ(friends[i]) < SZ(friends[j]))
            swap(i, j);
        a[j] = i;
        auto& m = friends[j];
        for (auto& [x, c]: m)
            friends[i][x] += c;
        friends[j].clear();
    }

    void addFriends(int i, int j)
    {
        //writeln("Adding friends", i, j);
        friends[get(i)][j]++;
        friends[get(j)][i]++;
    }
};

//}}}

void run()
{
    ints(n, m, k);
    dsu d(n + 1);
    int x, y;
    auto write = [&]() {
        return;
        fori1(n + 1)
        {
            writeln(i, ":");
            for (auto& [y, z]: d.friends[i])
                writeln("----", y, z);
            writeln();
        }
        writeln("===============");
    };
    fori(m)
        readln(x, y),
        d.addFriends(x, y),
        write();

    fori(k)
        readln(x, y),
        d.uni(x, y),
        write();
    ints(q);
    fori(q)
    {
        char c;
        int x, y;
        readln(c, x);
        if (c == '?')
            writeln(d.friends[d.get(x)][x]);
        else
        {
            readln(y);
            if (c == 'F')
                d.addFriends(x, y);
            else
                d.uni(x, y);
        }
        write();
    }
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
