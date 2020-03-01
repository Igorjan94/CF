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

//}}}

int bruteForce(int n, int k, vector<pii> orders) {
    sort(whole(orders));
    int c = 1 << n;
    int answer = 0;
    int foundMask = 0;
    for (int mask = 0; mask < c; ++mask)
    {
        int ans = 0;
        int lastTime = 0;
        int tired = 0;
        fori(n)
            if (mask & (1 << i))
                if (auto& [t, d] = orders[i]; lastTime <= t)
                {
                    if (tired - t + lastTime <= k)
                    {
                        tired = max(0, tired - t + lastTime);
                        ans += d;
                        lastTime = t + d;
                        tired += 2 * d;
                    }
                }
        if (answer < ans)
            answer = ans,
            foundMask = mask;
    }
    //writeln(foundMask);
    //fori(n)
        //if (foundMask & (1 << i))
            //writeln(orders[i]);
    return answer;
};

int run(int n, int k, vector<pii> orders)
{
    sort(whole(orders));
    k += 1000;
    map<int, map<int, int>> dp;
    dp[0] = {{k, 0}}; //time, tired, ans
    int answer = 0;
    //int I = 0;
    for (auto& [t, d]: orders)
    {
        int cur_ans = 0;
        int XXX = 300;
        while (dp.size() && (*dp.begin()).first <= t - XXX)
        {
            auto& temp = (*dp.begin()).second;
            for (auto& [_, ans]: temp)
                umax(cur_ans, ans);
            dp.erase(dp.begin());
        }
        dp[t - XXX][k] = cur_ans;
        //if (I++ % 100 == 0)
            //writeln(I, t, dp.size()), cout.flush();
        //if (I == 1000)
            //for (auto& [T, _]: dp)
                //writeln(T);
        for (auto& [x, m]: dp)
        {
            if (x >= t) break;
            for (auto& [tiredWas, ans]: m)
            {
                int tired = min(k, tiredWas + t - x);
                if (tired >= 1000)
                    umax(answer, ans + d),
                    umax(dp[t + d][tired - 2 * d], ans + d);
            }
        }
    }
    return answer;
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(n, k);
    vector<pii> orders(n);
    readln(orders);
    writeln(run(n, k, orders));
    //writeln(bruteForce(n, k, orders));

    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    if (true) return 0;

    writeln();
    while (true)
    {
        //n = rand() % 10;
        k = rand() % 100;
        //int mx = 100;
        fori(n)
            orders[i] = {rand() % 1000000000, rand() % 100};
        int correct = bruteForce(n, k, orders);
        int fast = run(n, k, orders);
        if (correct == fast)
            writeln("Correct", n, k);
        else
        {
            writeln();
            writeln("FAIL: found", fast, "need", correct);
            writeln(n, k);
            writeln(orders);
            break;
        }
    }
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
