#include <bits/stdc++.h>

#define enter printf("\n")
#define pb push_back
#define ll long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define forn1(i, n) for (int i = 1; i < n; i++)
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>

using namespace std;
int INF = 1000000007;
string FILENAME = "input";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

int n, m, k;
vector<pii> a;

void run()
{
    readln(n, k);
    int x, y;
    ll sum = 0ll;
    fori(n)
        readln(x, y),
        a.pb({x, y}),
        sum += y;
    ll ans = 0ll;
    int current = 0, rr;
    forn(wwww, max(1, n - 1))
    {
        n = a.size();
        sort(a.begin() + current, a.end());
        fori(n)
            cout << a[i].first << " " << a[i].second << endl;
        if (k == n + 1 || k == 1 || n < a[n - k].first - current)
        {
            if (k == n + 1)
                cout << 0 << endl;
            else
                if (n < a[n - k].first - current)
                    cout << "-1\n";
                else
                    if (k == 1)
                        cout << sum << endl;
            return;
        }
        int need = a[n - k].first - current;
        bool flag = false;
        writeln(need);
        if (need == 0)
            flag = true,
            need++;
//        cout << ans << endl;
        sort(a.begin() + current, a.end(), [](pii q, pii w){return q.second < w.second;});
        fori(need)
            ans += a[i + current].second;
        for(int i = need; i < n; i++)
            a[i].first++;
//        a.erase(a.begin(), a.begin() + need);
        rr = current;
        current += need;
        if (flag)
        {
            int mx = 0;
            fori(rr)
                mx = max(mx, a[i].second);
            ans -= mx;
            break;
        }
    }
    cout << ans << endl;
}

int main()
{
    freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
