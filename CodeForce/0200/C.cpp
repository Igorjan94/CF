// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
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

//Igorjan
//}}}

struct team
{
    int scored = 0;
    int losed = 0;
    int points = 0;
    string name;
    team() {}
    team(string name) : name(name) {}

    bool operator<(const team& other) const {
        return tuple(-points, losed - scored, -scored, name) < tuple(-other.points, other.losed - other.scored, -other.scored, other.name);
    }

    friend ostream& operator<<(ostream& os, const team& t) {
        return os << t.name << " " << t.points << " " << t.scored << " " << t.losed;
    };
};

void run()
{
    vector<team> teams;
    map<string, int> indices;
    set<string> names, other;
    string berland = "BERLAND";

    auto addTeam = [&](const string& name) {
        names.insert(name);
        if (indices.find(name) == indices.end())
            indices[name] = teams.size(),
            teams.emplace_back(name);
    };

    auto addMatch = [&](team& first, team& second, int a, int b) {
        first.scored += a;
        first.losed += b;
        second.scored += b;
        second.losed += a;
        if (a == b)
            first.points++,
            second.points++;
        else if (a < b)
            second.points += 3;
        else
            first.points += 3;
    };
    fori(5)
    {
        string f, s;
        char c;
        int a, b;
        readln(f, s, a, c, b);
        addTeam(f);
        addTeam(s);
        team& first = teams[indices[f]];
        team& second = teams[indices[s]];
        addMatch(first, second, a, b);
        if (f == berland)
            other.insert(s);
        if (s == berland)
            other.insert(f);
    }
    names.erase(berland);
    for (auto& x: other) names.erase(x);
    int i = indices[berland];
    int j = indices[*names.begin()];
    pii score;
    int mx = INTMAX;
    for (int x = 1; x < 100; x++)
        for (int y = 0; y < x; y++)
        {
            auto current = teams;
            addMatch(current[i], current[j], x, y);
            sort(all(current));
            if (current[0].name == berland || current[1].name == berland)
                if (x - y < mx)
                    mx = x - y,
                    score = {x, y};
        }
    if (mx == INTMAX)
        writeln("IMPOSSIBLE");
    else
        cout << score.first << ":" << score.second << "\n";
}

//{{{
int main()
{
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
