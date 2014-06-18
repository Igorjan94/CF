#include <bits/stdc++.h>

#define pb push_back
#define ll long long
#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define forn1(i, n) for (int i = 1; i < n; i++)
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>
#ifndef ONLINE_JUDGE
#define lld I64d
#endif
#define FILENAME "input"
#define INF 1000000007

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void readln(){}
struct graph{vector<vector<int>> edges;int n;graph(int);graph(int, int);graph();void createGraph(int);void add_edge(int, int);void add_or_edge(int, int);void writelnMatrix();void writeln();};

///----------------------------------------------------------------------------------------------------------------------------

int n, m;
string ans;
vector< vi > edges;
vector< string > s;
vector< bool > used;

void readInput()
{
    ans = "";
    edges.clear();
    s.clear();
    used.clear();
    readln(n, m);
    s.resize(n);
    edges.resize(n);
    used.resize(n);
    readln(s);
    int x, y;
    fori(m)
        readln(x, y),
        edges[--x].pb(--y),
        edges[y].pb(x);
}

void writeOutput()
{
    writeln(ans);
}

void dfs(int u, vector<bool>&used)
{
    used[u] = true;
    fori(edges[u].size())
        if (!used[edges[u][i]])
            dfs(edges[u][i], used);
}

bool debug = true;
bool ckech(stack<int>st, vector<bool> used)
{
//    if (st.size())
  //      writeln(st.top());
    while (st.size())
        dfs(st.top(), used),
        st.pop();
    if (!debug)
        writeln(used);
    fori(n)
        if(!used[i])
            return false;
    return true;
}

void ff(){};
string dij(stack<int> path, int beg)
{
    int start = beg;
    debug ? ff() : writeln("started algo at", start + 1);
	string qwre = "";
    used[start] = true;
	set<pair<string, pii>> q;
	fori(edges[start].size())
        if (!used[edges[start][i]])
            q.insert({s[edges[start][i]], {start, edges[start][i]}}),
            debug ? ff() : writeln("added edge from", start + 1, "to", edges[start][i] + 1);
//    stack<int> path;
    path.push(start);
	while (!q.empty())
	{
        debug ? ff() : writeln("from", (q.begin()->second).first + 1, "to", (q.begin()->second).second + 1);
		start = (q.begin()->second).second;
		string sadf = q.begin()->first;
		q.erase(q.begin());
		if (used[start])
            continue;
        if (!debug)
            qwre += " ";
        qwre += sadf;
		used[start] = true;
		path.push(start);
        fori(edges[start].size())
            if (!used[edges[start][i]])
                q.insert({s[edges[start][i]], {start, edges[start][i]}}),
                debug ? ff() : writeln("added edge from", start + 1, "to", edges[start][i] + 1);
        debug ? ff() : writeln("start :", start + 1);
        while (q.size() > 0 && used[(q.begin()->second).second])
            q.erase(q.begin());
        debug ? ff() : writeln("wanted :", (q.begin()->second).second + 1);
		while (path.size() > 0 && ((q.begin()->second).first != path.top()))
		{
            start = path.top();
            if (start == beg)
                goto fin;
            path.pop();
            debug ? ff() : writeln("to delete", start + 1);
            fori(edges[start].size())
                q.erase({s[edges[start][i]], {start, edges[start][i]}});
            if (!ckech(path, used))
                qwre += dij(path, start);
		}
    //    qwre += dij(path, start);
	}
	fin:
//	writeln("exited");
    return qwre;
}

void solve()
{
    used.clear();
    used.resize(n, false);
    int st = min_element(s.begin(), s.end()) - s.begin();
    stack<int> wert;
    ans = s[st] + dij(wert, st);
}

void run(bool d)
{
    debug = !d;
    readInput();
    solve();
    writeOutput();
}

int main()
{
    freopen(FILENAME".in", "r", stdin);
    freopen(FILENAME".out", "w", stdout);
    int T;
    readln(T);
    forn(q, T)
        printf("Case #%d: ", q + 1),
        run(q==-1);
//        q + 1 == 17 ? writeln(edges), writeln(s) : ff();
    return 0;
}

























graph::graph(int n){this->n = n;edges.resize(n);int t;fori(n){edges[i].resize(n);forj(n)readln(t),edges[i][j] = t == '1';}}graph::graph(int n, int m){this->n = n;edges.resize(n);int u, v;fori(m)readln(u, v),add_edge(u - 1, v - 1);}void graph::add_edge(int u, int v){edges[u].pb(v);}void graph::add_or_edge(int u, int v){edges[u].pb(v);edges[v].pb(u);}graph::graph(){};void graph::createGraph(int n){edges.resize(n);}void graph::writeln(){fori(n)forj(edges[i].size())::writeln(i, edges[i][j]);}void graph::writelnMatrix(){::writeln(edges);}
void print(double a){printf("%f ", a);}
void print(int a){printf("%d ", a);}
void print(string a){printf("%s ", a.c_str());}
void print(long long a){printf("%lld ", a);}
void print(unsigned long a){printf("%ld ", a);}
void print(char a){printf("%c ", a);}
template<class Type>
void print(vector<Type>& a){for(int i = 0; i < a.size(); ++i)print(a[i]);}
template<class Type>
void print(vector<vector<Type>>& a){for(int i = 0; i < a.size(); ++i)writeln(a[i]);}
void read(double &a){scanf("%lf", &a);}
void read(int &a){scanf("%d", &a);}
void read(string &a){cin>>a;}
void read(long long &a){scanf("%lld", &a);}
void read(char &a){scanf("%c", &a);}
template<class Type>
void read(vector<Type> &a){if (a.size() == 0){int n; read(n); a.resize(n);}for(int i = 0; i < a.size(); ++i)read(a[i]);}
template<class Type>
void read(vector<vector<Type>> &a){for(int i = 0; i < a.size(); ++i)readln(a[i]);}
template <class Head, class... Tail>
void writeln(Head head, Tail... tail){print(head);writeln(tail...);}
template <class Head, class... Tail>
void readln(Head& head, Tail&... tail){read(head);readln(tail...);}
