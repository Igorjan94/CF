#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
vector<int> a, b, c;
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
   //freopen("input.txt", "r", stdin);
    char c;
    int ans = 0;
    long long ss = 1;
    bool flag = false, flag2 = false;
    set<char> s;
    while (true)
    {
        scanf("%c", &c);
        if (c == '\n')
            break;
        else
            if (c >= '0' && c <= '9')
            flag2 = true;
                else
        if (c == '?')
        {
            if (!flag2)
                ss *= 9; else
            ans++;
        }
            else
            {
                s.insert(c);
                if (!flag2)
                    flag = true;
            }
        flag2 = true;
    }
    //printf("%d\n", s.size());
    for (int i = 0; i < s.size() - flag; i++)
        ss *= (10 - i - flag);
    if (flag)
        ss *= 9;
    cout << ss;
//    printf("1");
    //ans += s.size();
    for (int i = 0; i < ans; i++)
        printf("0");
    printf("\n");
   return 0;
}
