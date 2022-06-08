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

template<typename T>
bool hasBit(T x, int b) {
    return !!((T(1) << b) & x);
}
template<typename T>
void setBit(T &x, int b) {
    x |= T(1) << b;
}

// vector<int> p(n);
// iota(all(p), 0);
// do {
//
// } while (next_permutation(all(p)));

//Igorjan
//}}}

map<string, int> m;
int getResult(string s)
{
    if (s.size() == 0)
        return 0;
    if (s.size() == 1)
        return 1;
    //if (m.find(s) != m.end())
        //return m[s];
    int ans = 0;
    string temp = "";
    fori(s.size())
    {
        if (!i || s[i] != s[i - 1])
        {
            string t = temp;
            int j = i;
            int cnt = 0;
            while (j + 1 < SZ(s) && s[j] == s[j + 1])
                ++j,
                ++cnt;
            ++cnt;
            ++j;
            while (j < SZ(s))
                t.pb(s[j++]);

            ans = max(ans, cnt * cnt + getResult(t));
        }
        temp += s[i];
    }
    return ans;
    //return m[s] = ans;
}

//{{{
//int main()
//{
    //writeln(getResult("acbbcb"));
//}

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
