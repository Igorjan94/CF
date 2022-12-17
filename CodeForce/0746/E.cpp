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

void run()
{
    ints(n, m);
    m = min(m, n * 3);
    int k = n / 2;
    vector<int> a(n), ans(n, -1);
    readln(a);
    vector<pii> even, odd, tempEven, tempOdd;
    fori(n)
        (a[i] % 2 == 0 ? even : odd).pb({a[i], i});
    sort(even.rbegin(), even.rend());
    sort(odd.rbegin(), odd.rend());

    int prev = -1;
    int last = int(even.size()) - 1;

    fori(even.size())
    {
        if (prev != even[i].first)
            tempEven.pb(even[i]);
        prev = even[i].first;
    }
    prev = -1;
    last = int(odd.size()) - 1;
    fori(odd.size())
    {
        if (prev != odd[i].first)
            tempOdd.pb(odd[i]);
        prev = odd[i].first;
    }
    even = tempEven;
    odd = tempOdd;
    even.resize(min(int(even.size()), k));
    odd.resize(min(int(odd.size()), k));

    set<int> was;
    for (auto& x : even)
        ans[x.second] = x.first,
        was.insert(x.first);
    for (auto& x : odd)
        ans[x.second] = x.first,
        was.insert(x.first);
    int needsEven = k - even.size();
    int needsOdd = k - odd.size();

    vector<int> indices;
    fori(n) if (ans[i] == -1) indices.pb(i);
    int ANS = indices.size();

    //writeln();
    //wr(needsEven, needsOdd, minEven, minOdd, indices);
    //writeln(ans);
    int i = 0;
    FOR(k, 1, m + 1)
        if (was.find(k) == was.end())
        {
            if (k % 2 == 0 && needsEven) ans[indices[i++]] = k, needsEven--;
            if (k % 2 == 1 && needsOdd ) ans[indices[i++]] = k, needsOdd --;
        }
    if (needsEven + needsOdd == 0)
        writeln(ANS),
        writeln(ans);
    else
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
ttti   istream&operator>>(istream&is,vector<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,valarray<T>&a){if(a.size()==0){int n;is>>n;a.resize(n);}for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
