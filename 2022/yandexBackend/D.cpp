// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
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

typedef bitset<1024> bs;

struct commit {
    ll t;
    bs d;
};

struct service {
    int n;
    ll ct;
    bs d;

    vector<pair<int, ll>> s;

    void add(const vector<commit>& commits)
    {
        int m = commits.size();
        ll last = 0;

        int i = 0;
        while (i < m)
        {
            int j = i;
            int c = 0;
            while (j < m)
            {
                bool ok = (commits[j].d & d).any();
                if (ok)
                    if (++c == n)
                        break;
                ++j;
            }
            if (c == n)
            {
                ll start = max(last, commits[j].t);
                while (j < m && commits[j].t <= start)
                    ++j;
                --j;
                if (commits[j].t <= start)
                {
                    last = start + ct;
                    s.emplace_back(j, last);
                }
            }
            i = j + 1;
        }
    }

    ll get(int commit)
    {
        auto it = lower_bound(s.begin(), s.end(), pair(commit, 0ll));
        if (it == s.end())
            return -1;
        else
            return it->second;
    }

    service() {}
};

istream& operator>>(istream& is, service& s)
{
    int n, x;
    is >> s.n >> s.ct >> n;
    fori(n)
        is >> x,
        s.d.set(x);
    return is;
}

istream& operator>>(istream& is, commit& c)
{
    int n, x;
    is >> c.t >> n;
    fori(n)
        is >> x,
        c.d.set(x);
    return is;
}

void run()
{
    ints(d, s);
    vector<service> services(s);
    readln(services);
    ints(c);
    vector<commit> commits(c);
    readln(commits);
    for (auto& service: services)
        service.add(commits);
    ints(q);
    fori(q)
    {
        ints(commit, service); --commit; --service;
        writeln(services[service].get(commit));
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
