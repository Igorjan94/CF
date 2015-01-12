#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>
#include <set>
#define INF 1000000007

using namespace std;

struct point
{
    int x, y;
    point(){}
};

void run()
{
    point s, t, q;
    scanf("%d %d %d %d\n", &s.x, &s.y, &t.x, &t.y);
    if (s.x > t.x)
        swap(s, t); else
        if (s.x == t.x)
            if (s.y > t.y)
                swap(s, t);
   // printf("%d %d %d %d\n", s.x, s.y, t.x, t.y);

}

int main()
{
  //  freopen("matching.in", "r", stdin);
//    freopen("matching.out", "w+", stdout);
    run();
    return 0;
}
