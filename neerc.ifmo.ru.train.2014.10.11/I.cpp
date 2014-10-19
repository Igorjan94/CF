#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#define pb push_back
 
using namespace std;
 
 
void run()
{
    string s;
    int n;
    cin >> n;
    getline(cin, s);
    int a[26];
    for (int i = 0; i < 26; ++i)
        a[i] = 0;
    while(getline(cin, s))
    {
        int j = 0;
        while (s[j] == ' ')
            j++;
        a[s[j] - 'A'] = 1;
    }
    cout << "Yes\n";
    string t = "";
    for (int i = 0; i < 26; ++i)
        if (a[i])
            t.pb(i + 'A'),
            t += "| ~",
            t.pb(i + 'A'),
            t.pb('|');
    cout << t.substr(0, t.size() - 1);
}
 
int main()
{
    freopen("important.in", "r", stdin);
    freopen("important.out", "w", stdout);
    run();
    return 0;
}