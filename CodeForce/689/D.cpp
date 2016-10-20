// Igorjan94, template version from 19 March 2015 (deleted unused defines & reorganization from 05 November 2015)
#include <bits/stdc++.h>

using namespace std;

#define forit(it, r) for (auto it = r.begin(); it != r.end(); ++it)
#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn1(i, n)  for (int i = 1; i < (int) (n); ++i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     pll      pair<long long, long long>
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
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

///-------------------------------------------------------------------------------------------------------------------------------------

//segmentTree
template<typename T>
struct sparseTable
{
    int n;
    vector<vector<T>> st;
    vector<int> logs;
    typedef function<T (T, T)> F;
    F f;
    T NEITRAL_ELEMENT;

    sparseTable(vector<T>& a, F g, T ne = 0)
    {
        NEITRAL_ELEMENT = ne;
        n = a.size();
        f = g;

        logs.push_back(0);
        logs.push_back(0);
        FOR(i, 2, n + 1) logs.push_back(logs[i / 2] + 1);
        int L = logs.back() + 1;
        st.resize(L, vector<T>(n, ne));
        fori(n)
            st[0][i] = a[i];
        FOR(k, 1, L)
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = f(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }

    T get(int l, int r)
    {
        int len = logs[++r - l];
        return f(st[len][l], st[len][r - (1 << len)]);
    }
};

//Igorjan

void run()
{
    ints(n);
	vector<int> a(n), b(n);
	readln(a, b);
    sparseTable<int> fa(a, [](int x, int y){return max(x, y);}, numeric_limits<int>::min()), fb(b, [](int x, int y){return min(x, y);}, numeric_limits<int>::max());
    ll ans = 0;
    fori(n)
    {
        int m;
        int l1 = i;
        int r1 = n;
        while (r1 - l1 > 1)
        {
            m = (r1 + l1) >> 1;
            (fa.get(i, m) < fb.get(i, m)) ? l1 = m : r1 = m;
        }
        int index1 = l1 + (fa.get(i, l1) < fb.get(i, l1));
        if (index1 == n)
            continue;
        int temp = fa.get(i, index1);//min(n - 1, index1));
        int l2 = index1;
        int r2 = n;
        while (r2 - l2 > 1)
        {
            m = (r2 + l2) >> 1;
            (fa.get(i, m) == temp && fb.get(i, m) == temp) ? l2 = m : r2 = m;
        }
        int index2 = l2 + (fa.get(i, l2) == temp && fb.get(i, l2) == temp);
        ans += index2 - index1;
        //wr(index1, index2);
        //cout.flush();
    }
    writeln(ans);
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
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
