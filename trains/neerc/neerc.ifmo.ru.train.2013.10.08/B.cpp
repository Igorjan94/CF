#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>
#define north printf("NORTH\n"); cin >> s;
#define west printf("WEST\n"); cin >> s;
#define east printf("EAST\n"); cin >> s;
#define south printf("SOUTH\n"); cin >> s;
#define done printf("DONE\n"); cin >> s;
#define ss if(s == "EMPTY")


using namespace std;

int a[101][101];
string s;

void bfs(int i, int j)
{
    a[i][j] = 1;
    if (!a[i - 1][j])
    {
        north
        ss
        {
            bfs(i - 1, j);
            south
        } else
            a[i - 1][j] = 2;
    }
    if (!a[i + 1][j])
    {
        south
        ss
        {
            bfs(i + 1, j);
            north
        } else
            a[i + 1][j] = 2;
    }
    if (!a[i][j + 1])
    {
        east
        ss
        {
            bfs(i, j + 1);
            west
        } else
            a[i][j + 1] = 2;
    }
    if (!a[i][j - 1])
    {
        west
        ss
        {
            bfs(i, j - 1);
            east
        } else
            a[i][j] = 2;
    }
}

void run()
{
    string s;
    int i = 50, j = 50;
    bfs(i, j);
    done
}

int main()
{
//    freopen("matching.in", "r", stdin);
  //  freopen("matching.out", "w+", stdout);
    run();
    return 0;
}
