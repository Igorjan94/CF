// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#include <string>
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

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

vector<string>split(string&s,string_view d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}

void run(string f)
{
    ifstream file;
    file.open(f, ios::in);
    string s;
    ll c = 0;
    ll prev = 0;
    ll max_rps = 0;
    set<string> ok;
    while (getline(file, s))
    {
        auto v = split(s, ",");
        ll ts = stoll(v[0].c_str()) / 1000;
        string ip = v[1];
        if (ts == prev)
            max_rps = max(max_rps, ++c);
        else
            c = 1,
            prev = ts;
        ok.insert(ip);
    }
    file.close();
    cerr << "max_rps " << max_rps << endl;
    writeln("START");
    cout.flush();

    prev = -1;
    c = 0;
    ll ts;
    string ip, h, type;
    int used = 0;
    int qq = 0;

    map<string, int> m;
    while (cin >> type)
    {
        ++qq;
        ts /= 1000;
        if (type == "SHUTDOWN")
            break;
        cin >> ts >> ip >> h;
        if (ts == prev)
            ++c;
        else
            c = 1, prev = ts, used = 0;

        auto use = [&]() {
            ++used;
            writeln("OK");
        };
        auto ddos = [&]() {
            writeln("DDOS");
        };
        ++m[ip];
        //if (used < max_rps / 2)
            //use();
        if (used == max_rps)
            ddos();
        else
        {
            if (ok.contains(ip) || (m[ip] < max_rps))
                use();
            else
                ddos();
        }
        
        cout.flush();
    }
    cerr << qq << " " << m.size() << endl;
    vector<int> sizes;
    for (auto& [_, v]: m)
        sizes.pb(v);
    sort(all(sizes));
    reverse(all(sizes));
    for (int& x: sizes)
        cerr << x << " ";
    cerr << endl;
}

//{{{
int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s;
    s.assign(argv[1]);
    run(s);
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
