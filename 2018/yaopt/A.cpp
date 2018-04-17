// Igorjan94, template version from 19 March 2015 (#define -> typedef, readln(vector) patched, version from 27 March 2017)
#include <bits/stdc++.h>

using namespace std;

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
#define      pb      push_back
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


struct site
{
    vector<int> themes;
    vector<int> sites;
    int t;
    int p;

    site(){}
};

istream& operator>>(istream& is, site& s)
{
    ints(q);
    s.themes.resize(q);
    for (auto& x : s.themes)
        is >> x, --x;
    is >> s.t >> s.p;
    ints(o);
    s.sites.resize(o);
    for (auto& x : s.sites)
        is >> x, --x;
    return is;
}

#define COUNT_OF_USED 2


void run()
{
    srand(clock());
    double time = clock();
    ints(n, k, r, t, s);
    vector<site> sites(n);
    vector<int> freq(k);
    vector<vi> dp(n);
    readln(sites, freq);
    vector<vi> sitesWithTopic(k);
    fori(n)
        for (auto& topic: sites[i].themes)
            sitesWithTopic[topic].pb(i);

    fori(n)
    {
        dp[i].resize(n, INF);
        dp[i][i] = 0;
        queue<int> q;
        q.push(i);
        while (q.size())
        {
            int u = q.front();
            q.pop();
            for (int& v : sites[u].sites)
                if (dp[i][v] == INF)
                    dp[i][v] = dp[i][u] + 1,
                    q.push(v);
        }
    }
    //writeln(dp);
    vector<vector<int>> ans;
    double answer = 0.0;
    int CCC = 1;
    int WWW = 0;

    auto F = [](int x) -> int {
        if (x < 50)
            return x * 3;
        return pow(x, 2.0 / 5) + 10;
    };




    std::vector<std::pair<int, int>> newsGeneration;
    std::vector<std::pair<int, int>> newsEvents;
    std::vector<std::list<int>> newsOnSite2(n);
    for (int topic = 0; topic < k; topic++)
        for (int curTime = 0; curTime <= t; curTime += freq[topic])
            newsGeneration.emplace_back(curTime, topic);
    sort(newsGeneration.begin(), newsGeneration.end());
    auto itG = newsGeneration.begin();
    for (int curTime = 0; curTime <= t; curTime++)
        for (; itG != newsGeneration.end() && itG->first == curTime; itG++)
        {
            const int topic = itG->second;
            bool newsAppeared = false;
            newsEvents.emplace_back(topic, curTime);
            while (!newsAppeared)
            {
                for (int ss : sitesWithTopic[topic])
                    if (rand() % 99 + 1 <= sites[ss].p)
                    {
                        newsOnSite2[ss].push_back(newsEvents.size() - 1);
                        newsAppeared = true;
                    }
            }
        }




    while ((clock() - time) / CLOCKS_PER_SEC < 1.8)
    {
        CCC++;
        set<int> starts;
        while (int(starts.size()) < r)
            starts.insert(rand() % n);
        int countVertices;
        vector<vector<int>> paths(r);
        int i = 0;
        int coeff = F(CCC);
        //rand() % (4 * r) + 10;
        vector<bool> used(n);

        auto dfs = [&](auto& f, int start, int u) -> void
        {
            used[u] = true;
            paths[i].pb(u);
            countVertices++;
            int mn = INF;
            int legit = -1;
            if (rand() % 7 == 0)
            {
                vector<pii> good, best;
                for (auto v : sites[u].sites)
                {
                    int temp = dp[v][start];
                    if (temp && temp + countVertices <= min(coeff, n))
                        (used[v] ? good : best).pb({temp, v});
                    else if (temp + countVertices <= n && mn > temp)
                        mn = temp,
                        legit = v;
                }
                sort(good.begin(), good.end());
                sort(best.begin(), best.end());
                int index = -1;
                int sz = best.size();
                int df = sz - 1;
                while (df > 0 && best[df].first == best.back().first) --df;
                int sz2 = good.size();
                int df2 = sz2 - 1;
                while (df2 > 0 && good[df2].first == good.back().first) --df2;

                if (sz)
                    index = best[df + rand() % (sz - df)].second;
                if (index == -1 && sz2)
                    index = good[df2 + rand() % (sz2 - df2)].second;
                if (index != -1)
                    f(f, start, index);
                else if (legit != -1 && dp[legit][start])
                    f(f, start, legit);
            } else {
                vector<pii> good;
                for (auto v : sites[u].sites)
                {
                    int temp = dp[v][start];
                    if (temp && temp + countVertices <= min(coeff, n))
                        good.pb({temp, v});
                    else if (temp + countVertices <= n && mn > temp)
                        mn = temp,
                        legit = v;
                }
                sort(good.begin(), good.end());
                int sz = good.size();
                //int j = sz - 1;
                //while (j >= 1 && good[j].first == good.back().first)
                    //--j;
                int df = 9 + rand() % 3;
                if (sz)
                    f(f, start, good[sz >= df ? (sz - df + rand() % df) : sz - 1].second);
                else if (legit != -1 && dp[legit][start])
                    f(f, start, legit);
            }
        };

        for (auto& u : starts)
        {
            countVertices = 0;
            forj(n) used[j] = false;
            dfs(dfs, u, u);
            ++i;
        }
        


    std::vector<std::pair<int, int>> indexFinishes;
    forj(r)
    {
        int curTime = 0;
        size_t nextSiteIndex = 0;
        while (true) {
            const int nextSite = paths[j][nextSiteIndex];
            const int finishTime = curTime + sites[nextSite].t;
            if (finishTime > t) break;
            indexFinishes.emplace_back(finishTime, nextSite);
            curTime = finishTime;
            nextSiteIndex = (nextSiteIndex + 1) % paths[j].size();
        }
    }

    sort(indexFinishes.begin(), indexFinishes.end());

    auto itF = indexFinishes.begin();
    std::vector<std::pair<int, int>> events(newsEvents);
    std::vector<std::list<int>> newsOnSite(newsOnSite2);;
    double score = 0;
    for (int curTime = 0; curTime <= t; curTime++) {
        for (; itF != indexFinishes.end() && itF->first == curTime; itF++) {
            const int site = itF->second;
            const int indexBeginTime = curTime - sites[site].t;
            auto& newsVector = newsOnSite[site];
            while (!newsVector.empty()) {
                const int ev = newsVector.front();
                if (events[ev].second <= indexBeginTime) {
                    if (events[ev].first != -1) {
                        score += std::max(0, s * freq[events[ev].first] - (curTime - events[ev].second));
                        events[ev].first = -1;
                    }
                    newsVector.pop_front();
                } else {
                    break;
                }
            }
        }
    }

    score = score / s / k / t;
    if (score >= answer)
        answer = score, 
        WWW = coeff,
        ans = paths;

    //cerr << CCC << "\n";
    //cerr << coeff << "\n";
    //cerr << score << "\n";
    //cerr << "\n";
        //break;
    }
    for (auto& x : ans)
    {
        for (auto& y : x) ++y;
        writeln(x.size(), x);
    }
}

//{{{
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
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
