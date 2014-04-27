#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#define enter printf("\n");
#define pb push_back
#define ll long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define vi vector<int>

#define CLASSNAME BlackBoxDiv2
#define METHODNAME count
#define PARAMETRES string a, string b

using namespace std;
int INF = 1000000007;
string FILENAME = "input";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

bool IsOdd (char c)
{
    return c == 'B';
}

class CLASSNAME
{

    public :
        int METHODNAME(PARAMETRES)
        {
            int aa = count_if(a.begin(), a.end(), IsOdd);
            int bb = count_if(b.begin(), b.end(), IsOdd);
            if (aa == 0 ^ bb == 0)
                return 0;
            if (aa == 0 && bb == 0)
                return 1;
            if (aa == 1 || bb == 1)
                return 1;
            aa = min(aa, bb);
            bb = max(aa, bb);

        }
};

void run()
{
    int
    sum(s 0..n binomial(n, s)*(-1)^s*2^((n-s)*n)*(1-2^(-n+s))^n

    string a, b;
    CLASSNAME ss;
    cout << ss.METHODNAME(a, b) << "\n";
    vector<vi> s;
    int count = 0;
    int d = 4;

    s.resize(d);
    forn(i, d)
        s[i].resize(d);
    forn(i, (int)pow(2, d * d))
    {
        forn(k, d)
            forn(j, d)
                s[k][j] = i & (int)pow(2, d * d - 1 - k - j * d);

/*        forn(k, d)
            forn(j, d)
                printf("%d%c", s[k][j], j == d - 1 ? '\n' : ' ');
        enter;*/
/*        s[0][0] = i & 256;
        s[0][1] = i & 128;
        s[0][2] = i & 64;
        s[1][0] = i & 32;
        s[1][1] = i & 16;
        s[1][2] = i & 8;
        s[2][0] = i & 4;
        s[2][1] = i & 2;
        s[2][2] = i & 1;*/
        int ans = 0;
        forn(i, d)
        {
            int k = 0;
            forn(j, d)
                k += s[i][j];
            if (k >= 1)
                ans++;
        }
        forn(i, d)
        {
            int k = 0;
            forn(j, d)
                k += s[j][i];
            if (k >= 1)
                ans++;
        }
        if (ans == d + d)
            count++;
    }
    writeln(count);
}

int main()
{
    //freopen(FILEINPUT.append(".txt").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
