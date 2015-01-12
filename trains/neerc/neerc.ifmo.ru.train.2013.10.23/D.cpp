#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct point
{
    int x, y;
    point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

int orientation(point &a, point &b, point &c)
{
    return (c.x - a.x)*(c.y - b.y) - (c.x - b.x)*(c.y - a.y);
}

int main()
{
    vector<point> b, w;
    int n, m, x, y;
    //freopen("output.txt", "w", stdout);
    //freopen("input.txt", "r", stdin);
    while (true)
    {
        b.clear();
        w.clear();
        scanf("%d %d", &n, &m);
        if (n + m == 0)
            break;
        if (n+m == 2)
        {
            scanf("%d %d\n", &x, &y);
            scanf("%d %d\n", &x, &y);
            printf("YES\n");
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%d %d\n", &x, &y);
            b.push_back(point(x, y));
        }
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d\n", &x, &y);
            w.push_back(point(x, y));
        }
        /*int f;
        if (n < 2)
            f = orientation(w[0], w[1], b[0]); else
            f = orientation(b[0], b[1], w[0]);*/
        /*if (f == 0)
        {
                   printf("NO\n");
                   continue;
        }*/
        /*if (m + n == 3)
        {
                  printf("YES\n");
                   continue;
        }*/
        bool ans = false;
        bool oneline = true;
        for(int i = 1; i < m; i++)
        {
            if(orientation(w[0],b[0],w[i]) != 0)
            {

                oneline = false;
                break;
            }
        }
        // printf("%d\n", oneline);
        if(oneline)
            for(int i = 1; i < n; i++)
            {
                if(orientation(w[0],b[0],b[i]) != 0)
                {
                    oneline = false;
                    break;
                }
            }

        //printf("%d\n",oneline);
        if(oneline)
        {
            if(w[0].x-b[0].x == 0)
            {
                int lb, lw, rb, rw;
                lb = rb = b[0].y;
                lw = rw = w[0].y;

                for(int i = 0; i < m; i++)
                {
                    if(w[i].y < lw)
                        lw = w[i].y;
                    if(w[i].y > rw)
                        rw = w[i].y;
                }
                for(int i = 0; i < n; i++)
                {
                    if(b[i].y < lb)
                        lb = b[i].y;
                    if(b[i].y > rb)
                        rb = b[i].y;
                }
                if((rb < lw) ^ (rw < lb))
                {
                    printf("YES\n");
                }
                else
                {
                    printf("NO\n");
                }
            }
            else
            {
                int lb, lw, rb, rw;
                lb = rb = b[0].x;
                lw = rw = w[0].x;

                for(int i = 0; i < m; i++)
                {
                    if(w[i].x < lw)
                        lw = w[i].x;
                    if(w[i].x > rw)
                        rw = w[i].x;
                }
                for(int i = 0; i < n; i++)
                {
                    if(b[i].x < lb)
                        lb = b[i].x;
                    if(b[i].x > rb)
                        rb = b[i].x;
                }
                if((rb < lw) ^ (rw < lb))
                {
                    printf("YES\n");
                }
                else
                {
                    printf("NO\n");
                }
            }
            continue;
        }

        if (n >= 2)
            for (int i = 0; i < n && !ans; i++)
                for (int j = i + 1; j < n && !ans; j++)
                {
                    int cur = orientation(b[i], b[j], w[0]);
                    if(cur == 0)
                        continue;
                    bool ans2 = true;
                    for (int k = 1; k < m && ans2; k++)
                    {
                        int z = orientation(b[i], b[j], w[k]);
                        if (z > 0 && cur < 0 || z < 0 && cur > 0 || z == 0)
                            ans2 = false;
                    }
                    if (!ans2)
                        continue;
                    cur = -cur;
                    if (n < 3)
                        ans = true;
                    else
                        for (int k = 0; k < n; k++)
                            if (k != j && k != i)
                            {
                                int z = orientation(b[i], b[j], b[k]);
                                if (z > 0 && cur < 0 || z < 0 && cur > 0)
                                    ans2 = false;
                            }
                    if (ans2)
                        ans = true;
                }
        if (m >= 2 && !ans)
            for (int i = 0; i < m && !ans; i++)
                for (int j = i + 1; j < m && !ans; j++)
                {
                    int cur = orientation(w[i], w[j], b[0]);
                    if(cur == 0)
                        continue;
                    bool ans2 = true;
                    for (int k = 1; k < n && ans2; k++)
                    {
                        int z = orientation(w[i], w[j], b[k]);
                        if (z > 0 && cur < 0 || z < 0 && cur > 0 || z == 0)
                            ans2 = false;
                    }
                    if (!ans2)
                        continue;
                    cur = -cur;
                    if (m < 3)
                        ans = true;
                    else
                        for (int k = 0; k < m; k++)
                            if (k != j && k != i)
                            {
                                int z = orientation(w[i], w[j], w[k]);
                                if (z > 0 && cur < 0 || z < 0 && cur > 0)
                                    ans2 = false;
                            }
                    if (ans2)
                        ans = true;
                }

        printf(ans ? "YES\n" : "NO\n");
    }
    return 0;
}
