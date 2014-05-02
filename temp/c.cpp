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
#define mp make_pair
/*#define tot first
#define col second
#define node pair<int, int>*/
struct node {
	int tot;
	int col;
//	bool operator<(const node &rhs) const {
	//	return tot < rhs.tot || tot == rhs.tot && col < rhs.col;
	//}
};

struct comp {
	bool operator()(const node &lhs, const node &rhs) const {
	printf("c");
		return lhs.tot < rhs.tot;
	}
};
int grid[300][300], rowRightPref[300][300], rowLeftPref[300][300], colDownPref[300][300], colUpPref[300][300];
int myDiff, ui, uj, di, dj;
set <node, comp> my, myneg;
set <node, comp>::iterator it;

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
    freopen("input.in", "r", stdin);
	ios_base::sync_with_stdio(0);
	int n, m, t; cin >> n >> m >> t;
	int tp, tu, td; cin >> tp >> tu >> td;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> grid[i][j];
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
                node myLast, mySecondLast;
                for(int j = 0; j < m; j++) {
                    //boolean debug = i1 == 4 && i2 == 5 && j == 6;
                    int nowSum = rowRightPref[i1][j] + colDownPref[i2][j] - colDownPref[i1][j] + rowLeftPref[i2][0] - rowLeftPref[i2][j]
                            + colUpPref[i1][0] - colUpPref[i2][0];
                    int findSum = nowSum - t;
                    it = upper_bound(myneg.begin(), myneg.end(), (node){-findSum, 1}, comp);
                    //Block largestSmaller = my.lower(new Block(findSum + 1, 1));
                    if(it != myneg.end()) {
                        int nowDiff = (nowSum + (*it).tot) - t;
                        updateIt(nowDiff, i1 + 1, (*it).col + 1, i2 + 1, j + 1);
                    }
                    it = lower_bound(my.begin(), my.end(), (node){findSum, 1}, comp);
	                    if(it != my.end()) {
                        int nowDiff = (nowSum - (*it).tot) - t;
                        updateIt(nowDiff, i1 + 1, (*it).col + 1, i2 + 1, j + 1);
                    }
                    mySecondLast = myLast;
                    myLast = (node){nowSum - (colDownPref[i2][j] - colDownPref[i1][j]) - (colUpPref[i1][j] - colUpPref[i2][j]), j};
                    if(j > 0) {
                        my.insert(mySecondLast);
                        myneg.insert((node) {-mySecondLast.tot, mySecondLast.col});
                    }
                    if(myDiff == 0) goto here;
                }
            }
        }
  here:;
  cout << ui << ' ' << uj << ' ' << di << ' ' << dj << '\n';
	return 0;
}
