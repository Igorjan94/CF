#include <iostream>
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>
 
using namespace std;
 
long long res = 0, ost = 0;
 
int inf = 1e+9 + 9;
 
 
int n, cnt[1000500], ans[1000500];
vector <int> mp[1000500], a, b;
vector <int> bb[1000500];
int main(){
    freopen("gcs.in", "r", stdin);
    int n = 0;
    string s;
    getline (cin, s);
    s += ' ';
    int num = 0;
    for (int i = 0; i < s.length(); ++i){
        if (s[i] == ' '){
            a.push_back(num);
            num = 0;
        }
        else
            num = num * 10 + (s[i] - '0');
    }
    getline (cin, s);
    s += ' ';
    num = 0;
    for (int i = 0; i < s.length(); ++i){
        if (s[i] == ' '){
            b.push_back(num);
            num = 0;
        }
        else
            num = num * 10 + (s[i] - '0');
    }
    for (int i = 0; i < 1000500; ++i){
        cnt[i] = -1;
    }
    for (int i = 0; i < a.size(); ++i){
        mp[a[i]].push_back(i);
        cnt[a[i]]++;
    }
    for (int i = 0; i < b.size(); ++i){
        if (cnt[b[i]] == -1 || cnt[b[i]] >= mp[b[i]].size())
            bb[i].push_back(-1);
        else
            bb[i] = mp[b[i]];
    }
    int border = 1000500;
    ans[0] = -1 * inf;
    for (int i = 1; i < border; ++i){
        ans[i] = inf;
    }
 
    for (int i = 0; i < b.size(); ++i){
        int x = bb[i][bb[i].size() - 1];
        if (!(x + 1))
            continue;
        int r = border;
        int l = 0, m;
        while (r > l + 1){
            m = (r + l) / 2;
            if (ans[m] > x)
                r = m;
            else l = m;
        }
        ans[r] = x;
     //   cout << x << " ";
        int cnt = 1;
        while (cnt < bb[i].size() + 1 && bb[i][bb[i].size() - cnt] >= ans[r - 1] &&
               bb[i][bb[i].size() - cnt] < ans[r + 1])
            cnt++;
        cnt--;
        ans[r] = bb[i][bb[i].size() - cnt];
    }
    for (int i = 1; i < border; ++i){
        if (ans[i] == inf && i < 100){
            cout << i - 1 << '\n';
            return 0;
        }
    }
 
}
