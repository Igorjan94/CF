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
//}}}

void run()
{

    auto get = [&](int mask, int i, int j) {
        return !!(mask & (1 << (i * 7 + j)));
    };
    auto printMask = [&](int mask) {
        fori(4)
        {
            forj(7) priws(get(mask, i, j));
            writeln();
        }
    };
    auto set = [&](int& mask, int i, int j) {
        mask |= (1 << (i * 7 + j));
    };
    auto simplify = [&](int mask) {
        while (true)
        {
            bool changed = false;
            fori(4)
            {
                int cnt = 0;
                forj(7) cnt += get(mask, i, j);
                if (cnt >= 5 && cnt <= 6)
                    forj(7) set(mask, i, j), changed = true;
            }
            forj(7)
            {
                int cnt = 0;
                fori(4) cnt += get(mask, i, j);
                if (cnt == 3)
                    fori(4) set(mask, i, j), changed = true;
            }
            if (!changed)
                break;
        }
        return mask;
    };
    vector<pair<double, double>> answers(29);
    forn(empty, 29)
    {
        int all = 0;
        int failed = 0;
        int notRestored = 0;
        FOR(mask, 0, 1 << 28)
            if (__builtin_popcount(mask) == 28 - empty)
            {
                all++;
                int temp = simplify(mask);
                //if (empty == 1)
                //{
                    //printMask(mask);
                    //printMask(temp);
                    //writeln();
                //}
                int cnt = 0; fori(3) forj(5) cnt += !get(temp, i, j);
                failed += !!cnt;
                notRestored += cnt;
            }
        answers[empty] = {failed / (0.0 + all), notRestored / (0.0 + all)};
        writeln(answers[empty]);
        cout.flush();
    }
}

//{{{
int main()
{
    cout << fixed << setprecision(12);
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
