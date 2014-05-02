//venk13
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

#define sz(a) (int)(a.size())
#define len(a) (int)(a.length())
#define pb push_back
#define mp make_pair/*
struct node {
	int tot;
	int col;
	bool operator<(const node &rhs) const {
		return tot < rhs.tot;
	}
};*/
struct comp{
bool operator()(const pair <int, int> &lhs, const pair <int, int> &rhs) {
    return lhs.first < rhs.first;
}
};

bool f(const pair <int, int> &lhs, const pair <int, int> &rhs) {
    return lhs.first < rhs.first;
}

int grid[300][300], rowRightPref[300][300], rowLeftPref[300][300], colDownPref[300][300], colUpPref[300][300];
int myDiff, ui, uj, di, dj;
set <pair <int, int>, comp > my, myneg;
set <pair <int, int>, comp >::iterator it;

inline int ab(int a) { return a < 0 ? -a : a; }

inline void updateIt(int nowDiff, int nui, int nuj, int dui, int duj) {
        if(ab(nowDiff) < ab(myDiff)) {
            ui = nui;
            uj = nuj;
            di = dui;
            dj = duj;
            myDiff = nowDiff;
        }
    }

int main() {
	ios_base::sync_with_stdio(0);
//	    freopen("input.in", "r", stdin);

	int n, m, t; scanf("%d%d%d", &n, &m, &t);
	int tp, tu, td; scanf("%d%d%d", &tp, &tu, &td);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			scanf("%d", &grid[i][j]);
	////
				for(int i = 0; i < n; i++) {
            for(int j = 1; j < m; j++) {
                if(grid[i][j] > grid[i][j - 1])
                rowRightPref[i][j] = tu + rowRightPref[i][j - 1];
                if(grid[i][j] < grid[i][j - 1])
                rowRightPref[i][j] = td + rowRightPref[i][j - 1];
                if(grid[i][j] == grid[i][j - 1])
                rowRightPref[i][j] = tp + rowRightPref[i][j - 1];
            }
        }
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < m; j++) {
                colDownPref[i][j] = grid[i][j] > grid[i - 1][j] ? tu + colDownPref[i - 1][j] : colDownPref[i][j];
                colDownPref[i][j] = grid[i][j] < grid[i - 1][j] ? td + colDownPref[i - 1][j] : colDownPref[i][j];
                colDownPref[i][j] = grid[i][j] == grid[i - 1][j] ? tp + colDownPref[i - 1][j] : colDownPref[i][j];
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = m - 2; j >= 0; j--) {
                rowLeftPref[i][j] = grid[i][j] > grid[i][j + 1] ? tu + rowLeftPref[i][j + 1] : rowLeftPref[i][j];
                rowLeftPref[i][j] = grid[i][j] < grid[i][j + 1] ? td + rowLeftPref[i][j + 1] : rowLeftPref[i][j];
                rowLeftPref[i][j] = grid[i][j] == grid[i][j + 1] ? tp + rowLeftPref[i][j + 1] : rowLeftPref[i][j];
            }
        }
        for(int i = n - 2; i >= 0; i--){
            for(int j = 0; j < m; j++) {
                colUpPref[i][j] = grid[i][j] > grid[i + 1][j] ? tu + colUpPref[i + 1][j] : colUpPref[i][j];
                colUpPref[i][j] = grid[i][j] < grid[i + 1][j] ? td + colUpPref[i + 1][j] : colUpPref[i][j];
                colUpPref[i][j] = grid[i][j] == grid[i + 1][j] ? tp + colUpPref[i + 1][j] : colUpPref[i][j];
            }
        }
  //////////
       myDiff = 1 << 30;
        ui = -1; uj = -1; di = -1; dj = -1;
  for(int i1 = 0; i1 < n - 1; i1++) {
            for(int i2 = i1 + 2; i2 < n; i2++) {
            		my.clear(); myneg.clear();
                pair <int, int> myLast, mySecondLast;
                for(int j = 0; j < m; j++) {
                    //boolean debug = i1 == 4 && i2 == 5 && j == 6;
                    int nowSum = rowRightPref[i1][j] + colDownPref[i2][j] - colDownPref[i1][j] + rowLeftPref[i2][0] - rowLeftPref[i2][j]
                            + colUpPref[i1][0] - colUpPref[i2][0];
                    int findSum = nowSum - t;
                    it = upper_bound(myneg.begin(), myneg.end(), mp(-findSum, 1), f);
                    if(it != myneg.end()) {
                        int nowDiff = (nowSum + (*it).first) - t;
                        updateIt(nowDiff, i1 + 1, (*it).second + 1, i2 + 1, j + 1);
                    }
                    it = lower_bound(my.begin(), my.end(), mp(findSum, 1), f);
	                    if(it != my.end()) {
                        int nowDiff = (nowSum - (*it).first) - t;
                        updateIt(nowDiff, i1 + 1, (*it).second + 1, i2 + 1, j + 1);
                    }
                    mySecondLast.first = myLast.first, mySecondLast.second = myLast.second;
                    myLast = mp(nowSum - (colDownPref[i2][j] - colDownPref[i1][j]) - (colUpPref[i1][j] - colUpPref[i2][j]), j);

                    if(j > 0) {
                    	assert(myLast != mySecondLast);
                        my.insert(mySecondLast);
                        myneg.insert(mp(-(mySecondLast.first), mySecondLast.second));
                    }
                    //if(myDiff == 0) goto here;
                }
            }
        }
  here:;
  printf("%d %d %d %d\n", ui, uj, di, dj);
	return 0;
}
