#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
vector<int> a, b;
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

void readln(vector<int> &f, int n)
{
    int x;
    for (int i = 1; i <= n; i++)
    {
        read(x);
        f.push_back(x);
    }
}

void writeln(vector<int> &f)
{
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

int main()
{
   freopen("input.txt", "r", stdin);
   int n;
   readln(n);
   readln(a, n);
   if (n == 1)
   {
       printf("0\n");
       return 0;
   }
   a.push_back(INF);
   for (int i = 0; i <= n; i++)
        b.push_back(i + 1);
   int j = 0;
   int i, k, h, x;
   int as = 0;
   for (i = 0, k = 0; b[j] < n; )
   {
        for (int l = 0; l < n; l = b[l])
            printf("%d ", a[l]);
        enter
        while (a[j] < a[b[j]])
            j = b[j];
        if (j >= n)
            break;
        k = j;
        as = 0;
        while (k < n)
        {
            x = 0;
            h = k;
            while (a[k] > a[b[k]])
                k = b[k];
            if (b[k] >= n)
            {
                b[h] = k = b[k];
                as = 1;
                break;
            }
            do
            {
                k = b[k];
                x++;
            }
            while (a[k] < a[b[k]] && a[b[k]] < a[h]);
/*            if (k >= n)
                x--;
            else*/
                as = max(as, x);
                writeln(as);
            b[h] = k;
        }
        cout << "asdf\n";
        i += as;
        writeln(i);
   }
   printf("%d\n", i);
   return 0;
}
