#include <bits/stdc++.h>
#define fori(n) for (int i = 0; i < int(n); ++i)
#define forj(n) for (int j = 0; j < int(n); ++j)
#define      pb      push_back

using namespace std;

vector<string>split(string&s,const string&d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
int n, k, s, x;

bool get(const vector<string>& a, const vector<string>& b)
{
    bool qq = false;
    fori(s) {
        if (a[i] == "" || b[i] == "")
            continue;
        if (a[i] == b[i])
            qq = true;
        else
            return false;
    }
    if (!qq)
        return false;
    for (int i = s; i < k; ++i) {
        if (a[i] == "" || b[i] == "")
            continue;
        if (a[i] != b[i])
            return false;
    }
    return true;
}

int main()
{
    cin >> n >> k >> s;
    vector<int> q;
    fori(s)
    {
        cin >> x;
        q.push_back(x - 1);
    }
    fori(k)
        if (find(q.begin(), q.end(), i) == q.end())
            q.push_back(i);
    vector<vector<string>> a(n);
    string t;
    getline(cin, t);
    fori(n)
    {
        string t;
        getline(cin, t);
        auto temp = split(t, "\t");
        forj(k)
            a[i].pb(temp[q[j]]);

        //cout << a[i].size() << endl;
        //forj(a[i].size())
            //cout << a[i][j] << endl;
    }
    int ans = 0;
    fori(n)
        for (int j = i + 1; j < n; ++j)
            ans += get(a[i], a[j]);
    cout << ans;
    return 0;
}
