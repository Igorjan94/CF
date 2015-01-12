
//compiler: MSVC 2010 (C++ obviously)
//one template to rule them all

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>

typedef unsigned long long ull;
typedef long long ll;

#define FN "test"

using namespace std;

class why
{
public:
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

int main()
{
#ifdef LOCALZ
    ifstream in(FN ".in");
    ofstream out(FN ".out");
#else
        istream &in = cin;
        ostream &out = cout;
#endif
    int n;
        in >> n;

        vector<int> v;
        v.reserve(n);

        for(int i = 0; i < n; i++)
        {
            int a;
            in >> a;
            v.push_back(a);
        }

        sort(v.begin(),v.end(), why());

        int m = 0;

        for(int i = 0; i < n; i++)
        {
            if(v[i]+i > m)
                m = v[i]+i;
        }

        out << m + 2;

#ifdef LOCALZ
    out.close();
#endif
    return 0;
}
