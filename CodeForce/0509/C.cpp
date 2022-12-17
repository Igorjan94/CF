//Igorjan94, template version from 23 January 2015
#include <bits/stdc++.h>

using namespace std;

#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn1(i, n)  for (int i = 1; i < (int) (n); ++i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define     fst      first
#define     snd      second
#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define      eb      emplace_back
#define      vs      vector<string>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     vvi      vector<vector<int>>
#define     pll      pair<long long, long long>
#define   elohw(a)   a.rbegin(), a.rend()
#define   whole(a)   a.begin(), a.end()
#define    next      _next
#define    prev      _prev

#define argmax(a)    (max_element(whole(a)) - (a).begin())
#define argmin(a)    (min_element(whole(a)) - (a).begin())
#define wr(args...)  err(split(#args,',').begin(),args)

#define FILENAME "input"
#define INF 1000000007

#define tthti  template<typename Head, typename... Tail> inline
#define ttt12i template<typename T1, typename T2> inline
#define ttti   template<typename T> inline

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
ttti  void writeln_range(T f,T s){if(f!=s){priws(*f);for(auto i=++f;i!=s;++i)print(*i);}writeln();}
tthti void err(vector<string>::iterator it,Head head,Tail...tail){writeln((*it).substr((*it)[0]==' '),"=",head);err(++it, tail...);}
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

#define  ints(args...) int args; readln(args)
#define   lls(args...)  ll args; readln(args)
#define vints(args...)  vi args; readln(args)

///-------------------------------------------------------------------------------------------------------------------------------------

int deg(int a)
{
    int ans = 0;
    while (a)
        ans += a % 10,
        a /= 10;
    return ans;
}

#define Type int

void run()
{
    ints(n);
    vi a(n), b(n);
    readln(b);
    string s;
    int t = b[0];
    while (t > 9)
        t -= 9,
        s.pb('9');
    s.pb(t + '0');
    reverse(whole(s));
    writeln(s);
    fori1(n)
    {
        if (b[i] > b[i - 1])
        {
            int j = s.size() - 1;
            int temp = b[i - 1];
            while (j >= 0 && temp != b[i])
                if (s[j] == '9')
                    j--;
                else
                    s[j]++,
                    temp++;
            temp = b[i] - temp;
            while (temp)
                if (temp > 9)
                    s.insert(s.begin(), '9'),
                    temp -= 9;
                else
                    s.insert(s.begin(), '0' + temp),
                    temp = 0;
        }
        else
        {
            int j = s.size() - 1;
            int temp = b[i - 1];
            while (j >= 0 && temp != b[i] - 1)
                if (s[j] == '0')
                    j--;
                else
                    s[j]--,
                    temp--;
            j--;
            while (j >= 0 && s[j] == '9')
                j--;
            int sum = b[i] - 1, q;
            for (q = 0; q <= j; q++)
                sum -= s[q] - 48;
            for (q = s.size() - 1; q > j; q--)
                if (sum > 9)
                    s[q] = '9',
                    sum -= 9;
                else
                    s[q] = sum + 48,
                    sum = 0;
            if (j == -1)
                s.insert(s.begin(), '1');
            else
                s[j]++;
        }
        writeln(s);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
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
