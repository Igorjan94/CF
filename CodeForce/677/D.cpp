// Igorjan94, template version from 19 March 2015 (deleted unused defines & reorganization from 05 November 2015)
#include <bits/stdc++.h>

using namespace std;

#define forit(it, r) for (auto it = r.begin(); it != r.end(); ++it)
#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn1(i, n)  for (int i = 1; i < (int) (n); ++i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     pll      pair<long long, long long>
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
vector<string>split(const string&s,char c){vector<string>v;stringstream ss(s);string x;while(getline(ss,x,c))v.pb(x);return move(v);}

///-------------------------------------------------------------------------------------------------------------------------------------
//Igorjan

int d[303][303];

void run()
{
    ints(n, m, p);
	vector<vector<pii>> a(p);
    int x;
    fori(n)
        forj(m)
            scanf("%d", &x),
            d[i][j] = INF,
            a[--x].pb({i, j});
    vector<pii> start = {{0, 0}};
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    fori(p)
    {
        vector<pii> prev = i == 0 ? start : a[i - 1];
        if (int(prev.size()) * int(a[i].size()) > n * m)
        {
            vector<vector<int>> used(n, vector<int>(m, INF));
            vector<pair<int, pii>> list;
            for (auto pp : prev)
                list.pb({d[pp.first][pp.second], pp});
            sort(whole(list));
            int pointer = 1;
            queue<pair<int, pii>> q;
            q.push(list[0]);
            used[list[0].second.first][list[0].second.second] = list[0].first;
            while (q.size())
            {
                int u = q.front().second.first;
                int v = q.front().second.second;
                int val = q.front().first;
                q.pop();
                while (pointer < int(list.size()) && list[pointer].first <= val)
                    used[list[pointer].second.first][list[pointer].second.second] = list[pointer].first,
                    q.push(list[pointer++]);
                forj(4)
                {
                    int tox = u + dx[j];
                    int toy = v + dy[j];
                    if (tox >= 0 && toy >= 0 && tox < n && toy < m && used[tox][toy] == INF)
                        used[tox][toy] = min(used[tox][toy], used[u][v] + 1),
                        q.push({val + 1, {tox, toy}});
                }
            }
            for (auto pp : a[i])
                d[pp.first][pp.second] = used[pp.first][pp.second];
        }
        else 
            for (auto& from : prev)
                for (auto& to : a[i])
                    d[to.first][to.second] = min(d[to.first][to.second],
                        (i == 0 ? 0 : d[from.first][from.second]) + abs(to.first - from.first) + abs(to.second - from.second));
    }
    writeln(d[a[p - 1][0].first][a[p - 1][0].second]);
}

int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    //ios_base::sync_with_stdio(false);
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
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
