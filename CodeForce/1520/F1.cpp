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
#include <ext/pb_ds/tree_policy.hpp> // Содержит класс tree_order_statistics_node_update
#include <ext/pb_ds/assoc_container.hpp> // Общий файл. 

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, __gnu_pbds::rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void run()
{
    ordered_set plus;
    map<int, int> cache;
    auto ask = [&](int r) -> int {
        if (cache.find(r) != cache.end())
            return cache[r] + plus.order_of_key(r + 1);
        writeln('?', 1, r + 1);
        cout.flush();
        ints(ans);
        cache[r] = ans - plus.order_of_key(r + 1);
        return ans;
    };

    ints(n, t);
    fori(t)
    {
        ints(k);
        int l = 0;
        int r = n;
        while (r - l > 1)
        {
            int m = l + (r - l) / 2;
            int cnt = ask(m);
            if (m + 1 - cnt < k)
                l = m;
            else
                r = m;
        }
        int cnt = ask(l);
        if (l + 1 - cnt != k) ++l;
        plus.insert(l);
        cerr << l + 1 << endl;
        writeln('!', l + 1); cout.flush();
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
