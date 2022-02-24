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
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}

struct project
{
    string name;
    int d, s, b, r;
    map<string, int> skills;
    vector<string> assigned;
    vector<pair<string, int>> roles;

    project() {}
};

struct human
{
    string name;
    map<string, int> skills;
    int time = 0;
    int prevTime = 0;

    human() {}
};

istream& operator>>(istream& is, project& p) {
    is >> p.name >> p.d >> p.s >> p.b >> p.r;
    p.roles.resize(p.r);
    p.assigned.resize(p.r);
    fori(p.r)
        is >> p.roles[i].first >> p.roles[i].second;
    for (auto& [skill, level]: p.roles)
        p.skills[skill] = level;
    return is;
}

istream& operator>>(istream& is, human& h) {
    int n;
    is >> h.name >> n;
    string skill;
    int level;
    fori(n)
        is >> skill >> level,
        h.skills[skill] = level;
    return is;
}

void run()
{
    ints(c, p);
    vector<human> humans(c);
    vector<project> projects(p);
    readln(humans, projects);
    sort(all(projects), [&](const project& a, const project& b) {
        return a.s < b.s;
    });
    int M = 10;
    for (int i = 0; i < p; i += M)
        shuffle(projects.begin() + i, projects.begin() + i + M, rng);
    shuffle(all(humans), rng);
    sort(all(humans), [&](const human& a, const human& b) {
        return a.skills.size() > b.skills.size();
    });
    map<string, int> h_by_name;
    fori(c)
        h_by_name[humans[i].name] = i;
    int maxScore = 0;
    int score = 0;
    for (auto &p: projects) {
        maxScore += p.s;
        map<string, int> cur;
        bool can = true;
        int b = 0;
        map<string, bool> used;
        vector<int> perm(p.r);
        iota(all(perm), 0);
        shuffle(all(perm), rng);

        for (int i: perm)
        {
            const auto& [skill, level] = p.roles[i];
            int bestTime = MOD;

            vector<int> ppp(c);
            iota(all(ppp), 0);
            //shuffle(all(ppp), rng);

            human& best = humans[0];
            for (int j: ppp)
            {
                human& h = humans[j];
                if (!used.contains(h.name))
                    if (h.skills[skill] >= level || (h.skills[skill] + 1 == level && cur[skill] >= level))
                        if (h.time < bestTime)
                            bestTime = h.time,
                            best = h;
            }
            can &= bestTime < MOD;
            if (!can) break;

            b = max(b, bestTime);
            p.assigned[i] = best.name;
            used[best.name] = true;
            for (auto& [skill, level]: best.skills)
                cur[skill] = max(cur[skill], level);
        }
        if (can)
        {
            int time = b + p.d;
            int currentScore = max(0, p.s - max(0, time - p.b));
            if (currentScore == 0) continue;
            fori(p.r)
            {
                const auto& name = p.assigned[i];
                const auto& [skill, level] = p.roles[i];
                auto& h = humans[h_by_name[name]];
                h.time = time;
                if (h.skills[skill] <= level)
                    h.skills[skill]++;
            }
            writeln(p.name);
            writeln(p.assigned);
            score += currentScore;
        }
    }
    cerr << score << " / " << maxScore << endl;
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
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"  "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
