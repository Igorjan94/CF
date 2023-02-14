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
//IgorjandownTree
//0-indexed, [l..r)
template<typename T, typename F>
struct downTree {
    F f;
    vector<T> t;
    int n;

    downTree(int sz, const F &g, T default_value = T()) : f(g)
    {
        n = 1;
        while (n < sz) n <<= 1;
        t.resize(n * 2, default_value);
    }

    downTree(vector<T> &a, const F &g, T default_value = T()) : downTree(a.size(), g, default_value)
    {
        for (int i = 0; i < n; ++i)
            t[i + n] = a[i];
        for (int i = n - 1; i >= 1; --i)
            t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    void update(int i, const T& x)
    {
        i += n;
        t[i] = f(t[i], x);
        for (i >>= 1; i > 1; i >>= 1)
            t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    T get(int l, int r)
    {
        T resL = t[0];
        T resR = t[0];
        l += n;
        r += n;
        while (l < r)
        {
            if (l & 1)
                resL = f(resL, t[l++]);
            if (r & 1)
                resR = f(t[--r], resR);
            l >>= 1;
            r >>= 1;
        }
        return f(resL, resR);
    }
};

void run()
{
    ints(n);
    vector<int> a(n);
    readln(a);
    ints(q);

    auto b(a);
    sort(all(b));
    map<int, int> m;
    b.erase(unique(all(b)), b.end());
    fori(SZ(b))
        m[b[i]] = i;

    vector<int> answers(q, MOD);
    vector<vector<pii>> requests(n);
    vector<vector<pii>> revRequests(n);
    fori(q)
    {
        ints(l, r); --l; --r;
        requests[r].pb({l, i});
        revRequests[n - l - 1].pb({n - r - 1, i});
    }

    auto get = [&](const vector<int>& a, const vector<vector<pii>>& requests) {
        downTree indices(n + 1, [](const int& a, const int& b) { return max(a, b); }, -1);
        downTree values(n + 1, [](const int& a, const int& b) { return min(a, b); }, MOD);
        fori(n)
        {
            auto x = m[a[i]];
            int limit = MOD;
            while (true)
            {   
                auto it = m.lower_bound(a[i] + limit + 1);
                int y = it == m.end() ? n + 1 : it->second;
                int j = indices.get(x, y);
                if (j == -1)
                    break;
                int diff = a[j] - a[i];
                values.update(j, diff);
                if (limit == 0)
                    break;
                limit /= 2;
            }
            for (auto& [l, index]: requests[i])
                answers[index] = min(answers[index], values.get(l, i));
            indices.update(x, i);
        }
    };
    get(a, requests);
    reverse(all(a));
    get(a, revRequests);
 
    fori(q)
        writeln(answers[i]);
}
//{{{
int main()
{
    cin.tie(0); ios_base::sync_with_stdio(false);
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
