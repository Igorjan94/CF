// Igorjan94, template version from 19 March 2015 (deleted unused defines & reorganization from 05 November 2015)
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)

#define      ll      long long
#define      pb      push_back
#define      vi      vector<int>
#define      va      valarray<int>
#define     pii      pair<int, int>
#define     vll      vector<long long>
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

//printAns
void printAnswerAndExit(string a){printf("%s\n", a.data());exit(0);}
//Igorjan

#define N 2002
int n, k, s, t;
int count[N];
int parent[N];
int available[N][N];
bool g[N][N];
char ss[N];

void setAvailable(int from, int p, int u)
{
    if (available[u][from] != -1)
        return;
    available[u][from] = p;
    fori(n)
        if (g[i][u])
            setAvailable(from, u, i);
};

void run()
{
    scanf("%d%d%d%d\n", &n, &k, &s, &t);--s;--t;
    fori(n) forj(n) available[i][j] = -1;
    vi a(k);
    fori(k)
        scanf("%d", &a[i]);
    fori(n)
    {
        available[i][i] = i;
        scanf("%s", ss);
        forj(n)
        {
            g[i][j] = ss[j] == '1';
            if (g[i][j])
                available[i][j] = j;
        }
    }
    if (find(whole(a), t + 1) == a.end())
        a.pb(t + 1),++k;
    if (find(whole(a), s + 1) != a.end())
        a.erase(find(whole(a), s + 1)), --k;
    for (int& x: a)--x;
    vector<int> answer;
    vector<bool> used(n, false);
    vector<pii> nodes;

    function<void(int)> dfs = [&](int u)
    {
        if (nodes.size() == 0)
            return;

        forj(nodes.size())
        {
            int i = nodes[j].second;
            if (i == u)
                return;
            int v = u;
            while (v != i)
            {
                answer.pb(v),
                v = available[v][i];
            }
            u = i;
        }
    };

	for (int i = 0; i < n; i++)
		for (int u = 0; u < n; u++) {
		    int j = available[u][i];
		    if (j != -1)
		        for (int v = 0; v < n; v++)
		            if (available[i][v] != -1 && available[u][v] == -1)
		                available[u][v] = j;
		}
    //fori(n)
        //forj(n)
            //printf("%d %d %d\n", i, j, available[i][j]);
    //return;
	
    fori(n)
        for (int v : a)
            count[i] += available[i][v] != -1;
    if (count[s] != k)
        printAnswerAndExit("NO");
    count[s] = 0;
    for (int v : a)
        nodes.pb({count[v], v});
    nodes.pb({0, t});
    sort(nodes.rbegin(), nodes.rend());
    int l = nodes.size();
    fori(l)
        if (nodes[i].first < l - i - 1)
            printAnswerAndExit("NO");

    dfs(s);
    if (answer.size() == 0 || answer.back() != t)
        answer.pb(t);

    vector<bool> isAnswerOk(n, true);
    for (int x : a)
        isAnswerOk[x] = false;
    isAnswerOk[t] = false;
    for (int x : answer)
        if (x >= 0 && x < n)
            isAnswerOk[x] = true;
        else
            printAnswerAndExit("NO");
    int ok = accumulate(whole(isAnswerOk), 0);
    if (ok != n)
        printAnswerAndExit("NO");

    printf("YES\n");
    printf("%d\n", answer.size());
    fori(answer.size())
        printf("%d ", answer[i] + 1);
    printf("\n");
}

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
    //writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
#endif
    return 0;
}























#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";for(int i=1;i<a.size();++i)os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,valarray<T>&a){for(int i=0;i<a.size();++i)is>>a[i];return is;}
ttti void print(T a){cout<<" "<<a;}
ttti void priws(T a){cout<<a;}
ttti void read(T& a){cin>>a;}
