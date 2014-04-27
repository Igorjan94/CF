#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
int mn = INF, mx = 0;
vector<int> a(1001);
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

bool readl(vector<int> &a)
{
    char x;
    bool f = true;
    while (true)
    {
        scanf("%c", &x);
        if (!f)
            printf(">\n"),
            f = true;
        if (x == '\n')
            break;
        if (x == '"')
        {
            x = 'a';
            printf("<");
            while (true)
            {
                scanf("%c", &x);
                if (x == '"')
                    break;
                printf("%c", x);
            }
            printf(">\n");
            f = true;
            continue;
        }
        if (x == ' ')
            continue;
        printf("<");
        f = false;
        while (true)
        {
            printf("%c", x);
            scanf("%c", &x);
            if (x == ' ' || x == '"' || x == '\n')
                break;
        }
    }
        if (!f)
            printf(">\n");
    return true;
}

void writeln(vector<int> &f)
{
    int x;
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

int main()
{
 //  freopen("input.txt", "r", stdin);
//freopen("output.txt", "w+", stdout);
   int count = 0, n;
   readln(n);
   bool f = false;
   readl(a);
   return 0;
}
