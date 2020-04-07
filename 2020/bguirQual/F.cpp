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

[[maybe_unused]] const int MOD = 100000007;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

#define ttt12i template<class T1, class T2> inline
#define  ttti  template<class T> inline

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

//Igorjan
//}}}

map<ll, vector<vector<ll>>> cache;
void run()
{
    ll n;
    readln(n);

    vector<ll> degs = {1};
    fori(19)
        degs.pb(degs.back() * 10);
    function<vector<vector<ll>>(ll)> get = [&](const ll& x) {
        if (auto it = cache.find(x); it != cache.end())
            return it->second;
        vector<vector<ll>> ans(10);
        if (x < 100)
        {
            if (x < 10)
                ans[x].pb(x);
            else
            {
                auto temp = abs(x % 10 - x / 10);
                if (!temp) return ans;
                ans[temp].pb(temp);
                ans[temp].pb(x);
            }
            return cache[x] = ans;
        }
        set<ll> values;
        int y = to_string(x).size();
        FOR(i, max(1, y / 2 - 3), min(y, y / 2 + 3))
        {
            ll left = x % degs[i];
            ll right = x / degs[i];
            ll t = abs(left - right);
            if (t)
                values.insert(t);
        }
        for (const ll& t: values)
        {
            auto temp = get(t);
            fori(10) if (ans[i].empty() && !temp[i].empty()) 
            {
                ans[i] = temp[i];
                ans[i].push_back(x);
                break;
            }
        }
        return cache[x] = ans;
    };

    if (n < 100 && n % 11 == 0)
        return writeln(1, n);
    auto answer = get(n);
    fori(10)
        if (!answer[i].empty())
        {
            reverse(all(answer[i]));
            return writeln(SZ(answer[i]), answer[i]);
        }

}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    double time = clock();
    ints(t); fori(t) run();
    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * (clock() - time) / CLOCKS_PER_SEC << "ms\n";
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
