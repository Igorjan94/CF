#include <bits/stdc++.h>

#define fori(n) for(int i = 0; i < (int) (n); i++)
#define forj(n) for(int j = 0; j < (int) (n); j++)

using namespace std;

class BichromeBoard 
{
public:
    string ableToDraw(vector <string> board) 
    {
        vector<int> dx = { 1, 0, -1, 0};
        vector<int> dy = { 0, 1, 0, -1};
        int n = board.size();
        int m = board[0].size();
        auto f = [n, m](int i, int j){ return i >= 0 && j >= 0 && i < n && j < m;};
        while (true)
        {
            bool ch = false;
            fori(n)
                forj(m)
                    if (board[i][j] != '?')
                    {
                        char c = board[i][j] == 'W' ? 'B' : 'W';
                        for (int u = 0; u < 4; u++)
                            if (f(i + dx[u], j + dy[u]))
                            {
                                char d = board[i + dx[u]][j + dy[u]];
                                if (d == '?')
                                    board[i + dx[u]][j + dy[u]] = c,
                                    ch = true;
                                else
                                    if (d != c)
                                        return "Impossible";
                            }
                    }
            if (!ch)
                break;
        }
        return "Possible";
    }
};
