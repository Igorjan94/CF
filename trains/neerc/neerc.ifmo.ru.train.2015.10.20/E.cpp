#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
 
using namespace std;
 
struct event
{
    int x;
    int y;
    int i;
    event(){}
    event(int x, int y, int i) : x(x), y(y), i(i) {};
};
 
bool operator<(const event& a, const event& b)
{
    if (b.x == a.x)
        if (b.y == a.y)
            return b.i > a.i;
        else
            return b.y > a.y;
    else
        return b.x > a.x;
}
 
//ostream& operator<<(ostream&out, event x)
//{
    //return out << (x.y < 0 ? "end" : "begin") << " " << x.i << "\n";
//}
 
int main() {
    //freopen("input.txt", "r", stdin);
    int n, k;
    vector<event> q;
    scanf("%d%d", &n, &k);
    int x, y;
    vector<bool> used(n, true);
    set<pair<int, int>> s;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &x, &y);
        q.push_back(event(x, y, i));
        q.push_back(event(y, -y, i));
    }
 
    sort(q.begin(), q.end());
 
    for (int i = 0; i < q.size(); ++i)
        if (used[q[i].i])
        {
            if (q[i].y < 0)
            {
                ans++;
                s.erase({q[i].y, q[i].i});
            }
            else
            {
                s.insert({-q[i].y, q[i].i});
                while (s.size() > k)
                    used[s.begin()->second] = false,
                    s.erase(s.begin());
            }
        }
    cout << ans << "\n";
}
