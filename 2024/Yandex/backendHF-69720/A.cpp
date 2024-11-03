// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
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

void run()
{
    int Q = 0;
    auto get = [&]() {
        string s(4, 'a');
        int q = Q;
        fori(4)
            s[i] += q % 26,
            q /= 26;
        ++Q;
        return s;
    };
    string s;
    map<string, string> parts;
    map<string, string> artifacts;
    map<string, pair<string, string>> merges;
    set<string> banned;

    while (cin >> s) {
        if (s == "EXIT")
            return;
        if (s == "CREATE")
        {
            string p;
            readln(p);
            if (parts.contains(p))
                writeln("ERROR: EXISTING PART");
            else
            {
                string a = get();
                parts[p] = a;
                artifacts[a] = p;
                writeln(a);
            }
        }
        else if (s == "MERGE")
        {
            string a1, a2;
            readln(a1, a2);
            string a = get();
            merges[a] = {a1, a2};
            banned.insert(a1);
            banned.insert(a2);
            writeln(a);
        }
        else if (s == "GET_PARTS")
        {
            vector<string> ans;
            auto f = [&](auto f, const string& a) -> void {
                if (auto it = merges.find(a); it != merges.end())
                    f(f, it->second.first),
                    f(f, it->second.second);
                else
                    ans.pb(artifacts[a]);
            };
            string a;
            readln(a);
            if ((!merges.contains(a) && !artifacts.contains(a)) || banned.contains(a))
                writeln("ERROR: NO SUCH ARTEFACT");
            else 
            {
                f(f, a);
                for (auto& s: ans)
                    cout << s << " ";
                cout << "\n";
            }
            //writeln(ans);
        }
        cout.flush();
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
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
