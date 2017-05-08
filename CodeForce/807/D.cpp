// Igorjan94, template version from 19 March 2015 (#define -> typedef, readln(vector) patched, version from 27 March 2017)
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

typedef vector<long long> vll;
typedef  pair<int, int>   pii;
typedef  valarray<int>    va;
typedef   vector<int>     vi;
typedef    long long      ll;
#define      pb      push_back
#define   whole(a)   a.begin(), a.end()
#define    next      next__
#define    prev      prev__
#define   count      count__
#define  argmax(a)   (max_element(whole(a)) - (a).begin())
#define  argmin(a)   (min_element(whole(a)) - (a).begin())

#define  ints(a...)  int a; readln(a)
#define  lls(a...)   ll a; readln(a)
#define wr(args...)  err(split(#args,',').begin(),args)
                    
#define  FILENAME    "input"
#define     INF      1000000007
                    
#define    tthti     template<typename Head, typename... Tail> inline
#define   ttt12i     template<typename T1, typename T2> inline
#define    ttti      template<typename T> inline

inline void writeln2(){cout<<"\n";}
inline void writeln() {cout<<"\n";}
inline void readln()  {}
ttti void read(T&);
ttti void priws(T);
ttti void print(T);

void err(vector<string>::iterator it){++it;}
tthti void readln (Head& head,Tail&... tail){read(head); readln  (tail...);}
tthti void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
tthti void writeln (Head head, Tail... tail){priws(head);writeln2(tail...);}
ttti  void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
tthti void err(vector<string>::iterator it,Head head,Tail...tail){writeln((*it).substr((*it)[0]==' '),"=",head);err(++it, tail...);}
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return v;}

///-------------------------------------------------------------------------------------------------------------------------------------
//Igorjan
vector<int> prices = {500, 1000, 1500, 2000, 2500, 3000};
vector<int> pricesrev = {3000, 2500, 2000, 1500, 1000, 500};
map<int, int> qs;
vector<int> q(5, 0);
int n;

int getScores(vector<vector<int>>& people, int fakes, vector<int> prices)
{
    bool ok = true;
    forj(5)
    {
        int z = qs[prices[j]];
        int a = n + fakes;
        int ac = (a - z * q[j]) / z;
        auto check = [&](int ac) {
            return ac >= 0 && ac <= fakes && z * (q[j] + ac) <= a && (z == 32 || a < 2 * z * (q[j] + ac));
        };
        if (people[0][j] == -1) ok &= check(0);
        else ok &= check(ac) || check(fakes);
    }

    return ok;
}

int result(vector<int>& x, vector<int> prices)
{
    int ans = 0;
    fori(x.size())
        if (x[i] != -1)
            ans += (prices[i] / 250) * (250 - x[i]);
    return ans;
}

vector<vector<int>> checks;
void run()
{
    qs[500] = 1;
    qs[1000] = 2;
    qs[1500] = 4;
    qs[2000] = 8;
    qs[2500] = 16;
    qs[3000] = 32;
    readln(n);
    vector<vector<int>> people(n, vector<int>(5));
    readln(people);
    fori(n)
        forj(5)
            if (people[i][j] != -1)
                q[j]++;

    //-1 check

    vector<int> ppp;
	vector<vector<int>> ccc;
    forj(5)
        if ((people[0][j] != -1 && people[0][j] <= people[1][j]) || people[1][j] == -1)
            ppp.pb(3000),
			ccc.pb(prices);
        else
            ppp.pb(500),
			ccc.pb(pricesrev);
    int v = result(people[0], ppp);
    int p = result(people[1], ppp);
    //writeln(v, p, ppp);
    //cout.flush();
    if (v <= p)
    {
        writeln(-1);
        return;
    }

    //int a = 1000, b = 1000, c = 500, d = 500, e = 500;
    double time = clock();
    for (int a = 0; a < prices.size(); ++a)
    for (int b = 0; b < prices.size(); ++b)
    for (int c = 0; c < prices.size(); ++c)
    for (int d = 0; d < prices.size(); ++d)
    for (int e = 0; e < prices.size(); ++e)
        if (result(people[0], {prices[a], prices[b], prices[c], prices[d], prices[e]}) >
            result(people[1], {prices[a], prices[b], prices[c], prices[d], prices[e]}))
            checks.pb({prices[a], prices[b], prices[c], prices[d], prices[e]});
    forn(fakes, 4000)
    {
        for (auto& check: checks)
        {
            int can = getScores(people, fakes, check);
            if (can)
            {
                writeln(fakes);
                return;
            }
            //if ((clock() - time) / CLOCKS_PER_SEC > 1.9)
            //{
                //writeln(-1);
                //return;
            //}
        }
    }
    writeln(-1);
}

int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
#ifndef ONLINE_JUDGE
    writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
#endif
    return 0;
}























#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,valarray<T>&a){for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
