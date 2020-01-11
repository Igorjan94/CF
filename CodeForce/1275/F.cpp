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
//umax
template<typename T1, typename T2>
T1 umax(T1& a, T2 b)
{
    return a < T2(b) ? a = b : a;
}

//umin
template<typename T1, typename T2>
T1 umin(T1& a, T2 b)
{
    return a > T2(b) ? a = b : a;
}

//binSearch
//x -> min, f(x) == true
template<typename T, typename F>
T binSearch(T l, T r, F f, T eps = T(1))
{
    T m;
    while (abs(r - l) > eps)
        m = l + (r - l) / 2,
        (f(m) ? r : l) = m;
    return r;
}

//}}}

void run()
{
    map<pair<int, int>, ll> cache;
    auto request = [&](int server, int post) {
        if (auto it = cache.find({server, post}); it != cache.end())
            return it->second;
        //cerr << "? " << (server + 1) << " " << post << "\n";
        writeln('?', server + 1, post);
        cout.flush();
        ll x;
        readln(x);
        return cache[{server, post}] = x;
    };
    auto answer = [&](ll ans) {
        writeln('!', ans);
        cout.flush();
    };

    ints(n, s);
    fori(n)
    {
        cache.clear();
        vector<int> c(s);
        int x;
        readln(c, x);
        answer(binSearch(ll(x), 1000000000000000001ll, [&](ll y) {
            vector<int> first(s);
            vector<int> last(s);
            int mn = 0;
            int mx = 0;
            fori(s)
            {
                first[i] = 0;
                last[i] = c[i];
                for (auto& [serverPost, id]: cache)
                    if (auto& [server, post] = serverPost; server == i)
                    {
                        if (id <= y)
                            umax(first[i], post);
                        if (id > y)
                            umin(last[i], post);
                    }
                mn += first[i];
                mx += last[i];
            }
            if (mn >= x) return true;
            if (mx < x) return false;
            vector<int> l(s);
            vector<int> r(s);
            fori(s)
            {
                l[i] = first[i];
                r[i] = last[i] + 1;
            }
            while (true)
            {
                bool changed = false;
                fori(s)
                {
                    int m;
                    if (r[i] - l[i] > 1)
                    {
                        changed = true;
                        m = l[i] + (r[i] - l[i]) / 2,
                        (request(i, m) > y ? r[i] : l[i]) = m;

                        mn = 0;
                        mx = 0;
                        forj(s)
                            mn += l[j],
                            mx += r[j];
                        if (mn >= x) return true;
                        if (mx < x) return false;

                    }
                }
                if (!changed)
                    break;
            }
            int count = 0;
            fori(s)
                count += r[i] - 1;
            return count >= x;
        }, 1ll));
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    run();
    //cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
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
