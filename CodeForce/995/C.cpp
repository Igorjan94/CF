// Igorjan94, template version from 13 October 2017. C++17 version {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

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

#define    pb    push_back
#define whole(a) a.begin(), a.end()
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
const ll LLMAX = numeric_limits<ll>::max();
                    
void writeln(){cout<<"\n";}ttti void print(T a);ttti void priws(T a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H h,T...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}


//point
#define pointtt template<typename T>
//sorts only if z is corner point;
#define sortByPolarAngle(v, z, T) sort(v.begin(), v.end(), [&z](point<T>& a, point<T>& b) {\
    int q = orientation(z, a, b); return q == 0 ? dist(z, a) < dist(z, b) : q == -1;\
});

pointtt struct point
{
    T x, y;
    int i;
    point(T _x, T _y) : x(_x), y(_y) {}
    point(){}
    point operator+(point b) { return point(x + b.x, y + b.y); }
    point operator-(point b) { return point(x - b.x, y - b.y); }
    point operator-() { return point(-x, -y); }
    T operator*(point b) { return x * b.x + y * b.y; }
    T operator^(point b) { return x * b.y - y * b.x; }
    T operator!() { return x * x + y * y; }
    bool operator<(point b) { return x == b.x ? y < b.y : x < b.x; }
};
pointtt istream&operator>>(istream&is,point<T>&a){return is>>a.x>>a.y;}
pointtt ostream&operator<<(ostream&os,point<T>&a){return os<<a.x<<" "<<a.y;}
pointtt T dist(point<T>&a,point<T>&b){return!point<T>(a+-b);}
//dist from point C to line AB equals to answer.first / sqrt(answer.second);
pointtt pair<T,T> dist(point<T>&a,point<T>&b,point<T>&c){return{abs((a+-b)*c)+(a^b),dist(a,b)};}
pointtt int orientation(point<T>&a,point<T>&b,point<T>&c){T q=a.x*b.y-a.y*b.x-a.x*c.y+a.y*c.x+b.x*c.y-b.y*c.x;return q>0?1:q<0?-1:0;}
//Igorjan
//}}}
///-------------------------------------------------------------------------------------------------------------------------------------

ll inf = 1500000ll * 1500000ll;

void run()
{
    srand(time(NULL));
    ints(n);
    vector<point<int>> a(n);
    readln(a);
    fori(n) a[i].i = i;

    auto ttt = [&](vector<point<int>> a) -> optional<vi> {
        vector<int> ans(n, 1);
        point<ll> now = {0, 0};
        fori(n)
        {
            point<ll> temp1 = now;
            point<ll> temp2 = now;
            temp1.x += a[i].x;
            temp1.y += a[i].y;
            temp2.x -= a[i].x;
            temp2.y -= a[i].y;
            auto l1 = !temp1;
            auto l2 = !temp2;
            if (l2 < l1)
                now = temp2,
                ans[a[i].i] *= -1;
            else
                now = temp1;
        }
        if (!now > inf)
            return {};
        return ans;
    };

    for (;;)
    {
        auto temp = a;
        random_shuffle(whole(temp));
        auto ans = ttt(temp);
        if (ans.has_value())
        {
            writeln(ans.value());
            return;
        }
    }
}

//{{{
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
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
