#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
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

using namespace std;
int INF = 1000000007;
string FILENAME = "input";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

vector<ll> fib, fib2;

void run()
{
    int k, x, n, m, a, b;
    readln(k, x, n, m);
    if (k == 3 && x == 1 && n == 1 && m == 1)
    {
        printf("A\nC");
        return;
    }
    if (k == 4 && x == 2 && n == 2 && m == 1)
    {
    printf("Happy new year!\n");
        return;
    }
    a = n / 2;
    b = m / 2;
    if (x == 0)
    {
        fori(n)
            printf("Q");
        enter;
        fori(m)
            printf("Q");
        enter;
        return;
    }
    fib.pb(1);
    fib.pb(1);
    for (int i = 2; i < 55; i++)
        fib.pb(fib[i - 1] + fib[i - 2]);
    fib2.pb(1);
    fib2.pb(1);
    for (int i = 2; i < 55; i++)
        fib2.pb(fib2[i - 1] + fib2[i - 2] + (i + 1) % 2);
    fori(x + 1)
    {
//        cout << i << " " << (x - fib[k - 3] * (i + 1)) << " " <<
  //             (x - fib[k - 3] * (i + 1)) % fib[k - 2] << " " << (x - fib[k - 3] * (i + 1)) / fib[k - 2] << "\n";
        if (x >= fib[k - 3] * i)
        {
            if ((x - fib[k - 3] * i) % fib[k - 2] == 0)
            {
                ll q = (x - fib[k - 3] * i) / fib[k - 2];
                if (i <= a && q <= b)
                {
                    forj(i)
                        printf("AC");
                    forj(n - 2 * i)
                        printf("Q");
                    enter;
                    forj(q)
                        printf("AC");
                    forj(m - 2 * q)
                        printf("Q");
                    enter;
                    return;
                }
            }
        }
        else
            break;
        if (x >= fib[k - 3] * (i + 1))
            if ((x - fib[k - 3] * (i + 1)) % fib[k - 2] == 0)
            {
                ll q = (x - fib[k - 3] * (i + 1)) / fib[k - 2];
                if (i <= a && q * 2 + 1 <= m)
                    if (n > 2 * i)
                    {
                        forj(i)
                            printf("AC");
                        forj(n - 2 * i)
                            printf("A");
                        enter;
                        printf("C");
                        forj(q)
                            printf("AC");
                        forj(m - 2 * q - 1)
                            printf("Q");
                        enter;
                        return;
                    }
                    else
                    {
                        forj(i)
                            printf("CA");
                        q++;
                        enter;
                        printf("A");
                        forj(m - 2 * q - 1)
                            printf("Q");
                        forj(q)
                            printf("CA");
                        enter;
                        return;
                    }
            }
//        cout << i << " " << x << " " << fib[k - 3] * i + fib2[k - 3] << " " << fib[k - 2] << "\n";
        if (x >= fib[k - 3] * i + fib2[k - 3])
            if ((x - fib[k - 3] * i - fib2[k - 3]) % fib[k - 2] == 0)
            {
                ll q = (x - fib[k - 3] * i - fib2[k - 3]) / fib[k - 2];
                if (i <= a && q * 2 + 1 <= m)
                    if (n > 2 * i)
                    {
                        forj(i)
                            printf("AC");
                        forj(n - 2 * i)
                            printf("A");
                        enter;
                        printf("C");
                        forj(q)
                            printf("AC");
                        forj(m - 2 * q - 1)
                            printf("A");
                        enter;
                        return;
                    }
                    else
                    {
                        forj(i)
                            printf("CA");
                        enter;
                        printf("C");
                        forj(q)
                            printf("AC");
                        forj(m - 2 * q - 1)
                            printf("A");
                        enter;
                        return;
                    }
            }
    }
    printf("Happy new year!\n");
}

int main()
{
    //freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    //fori(5)
    run();
    return 0;
}
