#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>

struct sport
{
    int laps_more;
    int finish_time;
    int speed;
    sport() {}
    sport(int a, int b, int s)
    {
        finish_time = a;
        laps_more = b;
        speed = s;
    }
    bool operator<(const sport &o) const
    {
        return o.speed < speed;
    }
};

using namespace std;

int main()
{
    //freopen("output.txt","w",stdout);
    while (true)
    {
        int n;
        scanf("%d",&n);
        if(n == 0)
            break;
        deque<sport> q1, q2;
        vector<sport> to_1;
        vector<sport> to_2;
        for(int i = 0; i < n; i++)
        {
            int t,c;
            scanf("%d %d",&t,&c);

            to_1.push_back(sport(t,c,t));
        }
        int cur_time = 0;
        while(true)
        {
            if(to_1.empty() && to_2.empty() && q1.empty() && q2.empty())
                break;

            sort(to_1.begin(), to_1.end());
            sort(to_2.begin(), to_2.end());


            q1.insert(q1.begin(),to_1.begin(), to_1.end());
            to_1.clear();

            q2.insert(q2.begin(),to_2.begin(), to_2.end());
            to_2.clear();

            int next_time;
            if(!q1.empty() && !q2.empty())
                next_time = min(q1.back().finish_time,q2.back().finish_time);
            else if(q1.empty())
            {
                next_time = q2.back().finish_time;
            }
            else
                next_time = q1.back().finish_time;

            while(!q1.empty() && q1.back().finish_time <= next_time)
            {
                to_2.push_back(sport(next_time + q1.back().speed,q1.back().laps_more,q1.back().speed));
                q1.pop_back();
            }

            while(!q2.empty() && q2.back().finish_time <= next_time)
            {
                if(q2.back().laps_more != 1)
                    to_1.push_back(sport(next_time + q2.back().speed,q2.back().laps_more-1,q2.back().speed));
                q2.pop_back();
            }

            cur_time = next_time;

        }

        printf("%d\n",cur_time);
    }
    return 0;
}
