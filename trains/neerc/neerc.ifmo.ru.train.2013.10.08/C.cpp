#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stdio.h>


typedef unsigned long long ull;
typedef long long ll;

#define FN "cave"

using namespace std;

struct pp {
    int f, c;
};

pp data[1000010];

class why {
public:
    bool operator()(int a, int b) {
        return data[a].c < data[b].c;
    }
};

int main()
{
    //ifstream in(FN ".in");
    //ofstream out(FN ".out");
    //istream &in = cin;
    //ostream &out = cout;

    int t;
    //in >> t;
    scanf("%d",&t);

    vector<int> order;

    for(int T = 1; T <= t; T++)
    {
        int n;
        //in >> n;
        scanf("%d",&n);

        int total_area = 0;

        order.clear();
        order.reserve(n);
        for(int i = 0; i < n; i++)
            //in >> data[i].f;
            scanf("%d",&data[i].f);
        for(int i = 0; i < n; i++)
        {
            //in >> data[i].c;
            scanf("%d",&data[i].c);
            total_area += data[i].c-data[i].f;
            order.push_back(i);
        }

        sort(order.begin(),order.end(),why());

        for(int i = 0; i < n; i++)
        {
            int cx = order[i];
            int cc = data[cx].c;
            for(int j = cx-1; j >= 0; j--)
            {
                if(data[j].c < cc || data[j].f == data[j].c)
                    break;
                cc = max(data[j].f,cc);
                total_area -= (data[j].c - cc);
                data[j].c = cc;
            }
            for(int j = cx+1; j < n; j++)
            {
                if(data[j].c < cc || data[j].f == data[j].c)
                    break;
                cc = max(data[j].f,cc);
                total_area -= (data[j].c - cc);
                data[j].c = cc;
            }
        }

        //out << total_area;
        printf("%d",total_area);
    }

    //out.close();
    return 0;
}
