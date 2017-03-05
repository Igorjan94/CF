// Igorjan94, template version from 19 March 2015 (deleted unused defines & reorganization from 05 November 2015)
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define      va      valarray<int>
#define     pii      pair<int, int>
#define     vll      vector<long long>
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

int run(int n, ll k, vector<ll> a)
{
    map<ll, vector<int>> m;
    vector<int> sizes(n, 0);
    ll sum = 0;
    fori(n)
    {
        sum += a[i];
        m[sum].pb(i);
        sizes[i] = m[sum].size();
    }
    ll ans = 0;
    ll pref = 0;
    fori(n)
    {
        for (ll K = 1; K <= 1000000000ll * 100000ll; K *= k)
        {
            auto temp = m[K + pref];
            int l = 0;
            int r = temp.size();
            while (r - l > 1)
            {
                int m = (r + l) / 2;
                if (temp[m] > i)
                    r = m;
                else
                    l = m;
            }
            if (temp.size() && temp[l] < i)
                l++;
            //writeln(K, i, l, temp.size());
            ans += temp.size() - l;
            if (k == 1 || k == -1 && K == -1)
                break;
        }
        pref += a[i];
    }
    //ll correct = 0;
    //fori(n)
    //{
        //ll sum = 0;
        //for (int j = i; j < n; ++j)
        //{
            //sum += a[j];
            //for (ll K = 1; K <= 1000000000ll * 100000ll; K *= k)
            //{
                //if (sum == K)
                    //correct++;
                //if (abs(k) == 1)
                    //break;
            //}
        //}
    //}
    writeln(ans);
    return ans;
    //return ans == correct;
}

int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    lls(n, k);
	vector<ll> a(n);
    readln(a);
    //do
    //{
        //k = rand() % 20 - 10;
        //if (k == 0)
            //k++;
        //writeln(k);
        //cout.flush();
        //fori(n)
            //a[i] = rand() % 1000000000;
        //writeln("ok");
    //}
    run(n, k, a);
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
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,valarray<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
