




//Не читайте этот код, у Вас вытекут глаза :(





//Объезжалочка
//Я умею говнокодить 2
#include "MyStrategy.h"

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES
#define go(p, a, b) { if (p) goto a; else goto b; }

#include <bits/stdc++.h>
//#ifdef ONLINE_JUDGE
//#define debug 1
//#endif
#ifdef debug
//#undef debug
//#endif
#include "library.h"
#endif

#ifdef vis
#include "Debug.h"
Debug visual;
#endif

using namespace model;
using namespace std;

double DIST_TO_NEXT = 750;
int COUNT_OF_FAILS = 90;
int FORCE_BACK = 130;
int FORCE_RIGHT = 60;
int FORCE = 100;
int BREAK = 30;
double MAX_SPEED = 16;
int FORCE_SLOW_DOWN = 1;
int GLOBAL_FAIL = 2;
double ANGLE_THROW = PI / 30;
int PLANB = 123456;
double tileSize = 0.0;
int dir[15][4];
double eps = 5;

double power = 1;
bool changed = false;
double distToNext = -10000, prevDistance;
int countOfFails = 0;
int forceBack = 0;
int forceRight = 0;
int force = 0;
int prevx = 0;
int currx = -1234;
int forceSlow = 0;
int globalFail = 0;
double turn = 0.0;
bool init = true;
bool snake = false;
bool drift = false;
double width;
double height;
int d = 0;
int pd = 0;
set<pair<int, int>> bad;
vector<pair<int, int>> old;
int planB = 0;
vector<vector<bool>> visited;
vector<vector<bool>> once;

bool changedj = false;
double distToNextij = -10000;
double prevDistanceij = -10000;
int countOfFailsj = 0;
int forceBackj = 0;
int forceRightj = 0;
int forcej = 0;
int prevxj = 0;
int currxj = -1234;
int forceSlowj = 0;
int globalFailj = 0;
double turnj = 0.0;
bool initj = true;
bool snakej = false;
bool driftj = false;
double widthj;
double heightj;
int dj = 0;
int pdj = 0;
set<pair<int, int>> badj;
vector<pair<int, int>> oldj;
int planBj = 0;
double powerj = 1;
vector<vector<bool>> visitedj;
vector<vector<bool>> oncej;

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

vector<int> ddx = {1, 0, -1, 0};
vector<int> ddy = {0, -1, 0, 1};
map<pair<int, int>, int> directions;

vector<vector<vector<int>>> goforward = { /* сначала шли вправо*/ {  { RIGHT, UP, DOWN, LEFT },  { RIGHT, UP, LEFT, DOWN },  { LEFT, UP, DOWN, RIGHT },  { RIGHT, DOWN, LEFT, UP } }, /*1 сначала шли вверх*/ {  { UP, RIGHT, DOWN, LEFT },  { UP, LEFT, RIGHT, DOWN },  { UP, LEFT, DOWN, RIGHT },  { DOWN, LEFT, RIGHT, UP } }, /*2 сначала шли влево*/ {  { RIGHT, UP, DOWN, LEFT },  { LEFT, UP, RIGHT, DOWN },  { LEFT, UP, DOWN, RIGHT },  { LEFT, DOWN, RIGHT, UP } }, /*3 сначала шли вниз*/ {  { DOWN, RIGHT, UP, LEFT },  { UP, RIGHT, LEFT, DOWN },  { DOWN, LEFT, UP, RIGHT },  { DOWN, RIGHT, LEFT, UP } } }; //СНАЧАЛА ИДЕМ ПРЯМО ЕСЛИ МОЖЕМ

vector<vector<vector<int>>> FUUUUU = {
/*0 сначала шли вправо*/
    {
        //->
        {
            UP, DOWN, RIGHT, LEFT
        },
        //^
        {
            RIGHT, UP, LEFT, DOWN
        },
        //<-
        {
            UP, DOWN, LEFT, RIGHT
        },
        //V
        {
            RIGHT, DOWN, LEFT, UP
        }
    },
/*1 сначала шли вверх*/ 
    {
        //->
        {
            UP, RIGHT, DOWN, LEFT
        },
        //^
        {
            LEFT, RIGHT, UP, DOWN
        },
        //<-
        {
            UP, LEFT, DOWN, RIGHT
        },
        //V
        {
            LEFT, RIGHT, DOWN, UP
        }
    },
/*2 сначала шли влево*/ 
    {
        //->
        {
            UP, DOWN, RIGHT, LEFT
        },
        //^
        {
            LEFT, UP, RIGHT, DOWN
        },
        //<-
        {
            UP, DOWN, LEFT, RIGHT
        },
        //V
        {
            LEFT, DOWN, RIGHT, UP
        }
    },
/*3 сначала шли вниз*/ 
    {
        //->
        {
            DOWN, RIGHT, UP, LEFT
        },
        //^
        {
            RIGHT, LEFT, UP, DOWN
        },
        //<-
        {
            DOWN, LEFT, UP, RIGHT
        },
        //V
        {
            RIGHT, LEFT, DOWN, UP
        }
    }
}, FU;

int opposite(int x, int y)
{
    return abs(x - y) == 2;
}

struct vertex
{
    int x, y, qd, qpd; 
    vertex(){} 
    vertex(int x, int y, int pd, int d) : x(x), y(y), qd(d), qpd(pd) {}
};

template <typename T>
void ppp(vector<vector<T>> a)
{
    int n = a.size();
    int m = a[0].size();
    for (int j = 0; j < m; ++j)
        for (int i = 0; i < n; ++i)
            printf("%6d%c", a[i][j], "\n "[i != n - 1]);
    printf("\n");
}

bool isCorner(TileType a) 
{
    return !(a == VERTICAL || a == HORIZONTAL || a == CROSSROADS);
}

double getCenter(double xxx)
{
    return (xxx + 0.5) * tileSize;
}

double get(double xxx)
{
    return xxx * tileSize;
}

double get34(double xxx)
{
    return (xxx + 0.9) * tileSize;
}

double get14(double xxx)
{
    return (xxx + 0.1) * tileSize;
}

bool isVertical(pair<int, int> a, pair<int, int> b)
{
    return a.first == b.first;
}

bool isHorizontal(pair<int, int> a, pair<int, int> b)
{
    return a.second == b.second;
}

bool is32(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return 
            (
                isHorizontal(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isHorizontal(a[3], a[4]))
            ||
            (
                isVertical(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isVertical(a[3], a[4])
            );
    else
        return false;
}

bool is3_2(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return 
            (
                isHorizontal(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isVertical(a[1], a[4]) &&
                isHorizontal(a[3], a[4])
            )
            ||
            (
                isVertical(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isHorizontal(a[1], a[4]) &&
                isVertical(a[3], a[4])
            );
    else
        return false;
}

bool is212(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return
            (
                isHorizontal(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isVertical(a[3], a[4]) &&
                isHorizontal(a[1], a[4])
            )
            ||
            (
                isVertical(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isHorizontal(a[3], a[4]) &&
                isVertical(a[1], a[4])
            );
    else
        return false;
}

bool is41(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return 
            (
                isHorizontal(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isVertical(a[3], a[4])
            )
            ||
            (
                isVertical(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isHorizontal(a[3], a[4])
            );
    else
        return false;
}

bool is4(vector<pair<int, int>>& a)
{
    if (a.size() >= 4)
        return 
            (
                isHorizontal(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isHorizontal(a[2], a[3])
            )
            ||
            (
                isVertical(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isVertical(a[2], a[3])
            );
    else
        return false;
}

bool is131(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return 
            (
                isVertical(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isVertical(a[3], a[4])
            )
            ||
            (
                isHorizontal(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isHorizontal(a[3], a[4])
            );
    else
        return false;
}

pair<int, int> getXX(pair<int, int>& a, pair<int, int>& b)
{
    if (isVertical(a, b))
        return make_pair(getCenter(a.first), get(max(a.second, b.second)));
    else
        return make_pair(get(max(a.first, b.first)), getCenter(a.second));
}

double get(double x, double v)
{
    return (x + v) * tileSize;
}

pair<int, int> getCorner(pair<int, int>& a, pair<int, int>& b, pair<int, int>& c)
{
    // a
    //cbc
    double xxx = 0.25;
    if (isVertical(a, b))
        return make_pair(get(max(b.first, c.first)), get(b.second, a.second < b.second ? xxx : 1 - xxx));
    else
    //  c
    // ab
    //  c
        return make_pair(get(b.first, a.first < b.first ? xxx : 1 - xxx), get(max(b.second, c.second)));
    //if (isVertical(a, b))
        //return make_pair(c.first > b.first ? get14(a.first) : get34(a.first), a.second > b.second ? get14(b.second) : get34(b.second));
    //else
        //return make_pair(a.first < b.first ? get34(b.first) : get14(b.first), c.second > b.second ? get14(b.second) : get34(b.second));
}

int opposite(int x)
{
    switch (x)
    {
        case LEFT:
        case RIGHT:
            return 2 - x;
        default:
            return 4 - x;
    }
}

bool isRightTo(pair<int, int> a, pair<int, int> b) // ba
{
    return a.first - 1 == b.first && a.second == b.second;
}

bool isLeftTo(pair<int, int> a, pair<int, int> b) // ab
{
    return a.first + 1 == b.first && a.second == b.second;
}

bool isUpTo(pair<int, int> a, pair<int, int> b) // ab
{
    return a.first == b.first && a.second + 1 == b.second;
}

bool isDownTo(pair<int, int> a, pair<int, int> b) // ba
{
    return a.first == b.first && a.second - 1 == b.second;
}

int getDirectionByAngle(double angle)
{
    double sasdfasdf = PI / 9;
    if (fabs(angle) < sasdfasdf)
        return RIGHT;
    if (fabs(angle - PI / 2) < sasdfasdf)
        return DOWN;
    if (fabs(angle + PI / 2) < sasdfasdf)
        return UP;
    if (fabs(angle - PI) < sasdfasdf)
        return LEFT;
    if (fabs(angle + PI) < sasdfasdf)
        return  LEFT;
    return -1;
}

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
    //cout << (self.getType() == BUGGY ? "BUGGY\n" : "JEEP\n");
    if (self.getType() == BUGGY)
    {
#ifdef vis
        visual.beginPre();
#endif
        tileSize = game.getTrackTileSize();
        auto a = world.getTilesXY();
        if (init)
        {
            FU = goforward;
            //мне стало лень думать
            if (world.getMapName() == "map07" || world.getMapName() == "map08" || world.getMapName() == "map14")
                FUUUUU = goforward;
            old.push_back({self.getX() / tileSize, self.getY() / tileSize});
            //cout << self.getX() << " " << self.getY() << "\n";
            init = false;
            width = self.getWidth() / 2;
            height = self.getHeight() / 2;
            visited.resize(a.size());
            once.resize(a.size());
            for (int i = 0; i < visited.size(); ++i)
                visited[i].resize(a[0].size(), false),
                once[i].resize(a[0].size(), false);
            d = getDirectionByAngle(self.getAngle());
            pd = d;
#ifdef debug
            cout << self.getAngle() << "   ANGLE " << pd << " " << d << "\n";
            writeln(world.getWaypoints());
#endif
            srand(game.getRandomSeed());
        }
        int waypointIndex = self.getNextWaypointIndex();
        int qx = self.getX() / tileSize;
        int qy = self.getY() / tileSize;
        int wx, wy;
        tie(wx, wy) = old.back();
        if (wx != qx || wy != qy)
        {
            //cout << wx << " " << wy << " " << qx << " " << qy << "         " << pd << " " << d << "\n";
            old[0] = {qx, qy};
            pd = d;
            d = directions[make_pair(qx - wx, qy - wy)];
            //int tqwer = getDirectionByAngle(self.getAngle());
            if (pd != d && a[self.getNextWaypointX()][self.getNextWaypointY()] != UNKNOWN && waypointIndex != 0)
                FU = FUUUUU;
            //if (tqwer != -1)
                //d = tqwer;
            //if (forceBack)
                //d = opposite(d);
        }

        prevx = currx;
        if (prevx == -1234)
            prevx = self.getX();
        currx = self.getX();
        if (currx - prevx != 0)
            changed = true;
        int ti = self.getNextWaypointX();
        int tj = self.getNextWaypointY();
        auto wp = world.getWaypoints();
        for (int i = 0; i < min(3, int(wp.size())); ++i)
            wp.push_back(wp[i]);
        int fi, fj, pi, pj;
        double speedModule = hypot(self.getSpeedX(), self.getSpeedY());
        //if (waypointIndex < int(wp.size()) - 1)
        //{
            //int cx = int(self.getX() / tileSize);
            //int cy = int(self.getY() / tileSize);
            //int wx1 = wp[waypointIndex][0];
            //int wx2 = wp[waypointIndex + 1][0];
            //int wy1 = wp[waypointIndex][1];
            //int wy2 = wp[waypointIndex + 1][1];
            //if (
                    //(cx == wx1 && cx == wx2 && ((cy < wy1 && wy1 < wy2) || (cy > wy1 && wy1 > wy2)))
                    //||
                    //(cy == wy1 && cy == wy2 && ((cx < wx1 && wx1 < wx2) || (cx > wx1 && wx1 > wx2)))
            //)
                //ti = wp[++waypointIndex][0],
                //tj = wp[waypointIndex][1];
            //if (waypointIndex + 1 < int(wp.size()))
                //fi = wp[waypointIndex + 1][0],
                //fj = wp[waypointIndex + 1][1];
        //}
        double targetX = getCenter(ti);
        double targetY = getCenter(tj);
            int si = self.getX() / tileSize;
            int sj = self.getY() / tileSize;
            pair<int, int> S = make_pair(si, sj);
            visited[si][sj] = true;
            vector<int> qwerqsdfgsdf = {si, sj};
            if (wp[max(0, self.getNextWaypointIndex() - 1)] == qwerqsdfgsdf && !once[si][sj])
            {
                once[si][sj] = true;
                for (int i = 0; i < visited.size(); ++i)
                    for (int j = 0; j < visited[0].size(); ++j)
                        visited[i][j] = false;
            }
            if (bad.find(S) == bad.end())
                bad.clear();
            int n = a.size();
            int m = a[0].size();
            auto ok = [&](int x, int N)
            {
                return x >= 0 && x < N;
            };

        auto getPath = [&](int si, int sj, int tti, int ttj, int pd, int dd, vector<vector<vector<int>>> FUUUUU)
        {
#ifdef debug
            writeln("GET", si, sj, tti, ttj, waypointIndex);
#endif
            auto fffpath = [](int si, int sj, int u, int v, vector<vector<pair<int, int>>> prev)
            {
                vector<pair<int, int>> path;
                while (u != si || v != sj)
                    path.push_back({u, v}),
                    tie(u, v) = prev[u][v];
                path.push_back({si, sj});
                reverse(path.begin(), path.end());
                return path;
            };
            auto bfs = [&](int si, int sj, int tti, int ttj, int pd, int dd, vector<vector<vector<int>>> FUUUUU)
            {
                queue<vertex> q;
                q.push(vertex(si, sj, pd, dd));
                vector<vector<int>> d(n, vector<int>(m, 10000));
                vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(m));
                d[si][sj] = 0;
                int u, v, prevD, prevprevD;
                while (q.size())
                {
                    u = q.front().x;
                    v = q.front().y;
                    prevD = q.front().qd;
                    prevprevD = q.front().qpd;
                    q.pop();
                    if (a[u][v] == UNKNOWN)
                        continue;
                    vector<int> dx;
                    vector<int> dy;
                    for (int i = 0; i < 4; ++i)
                        dx.push_back(ddx[FUUUUU[prevprevD][prevD][i]]),
                        dy.push_back(ddy[FUUUUU[prevprevD][prevD][i]]);
                    for (int i = 0; i < 4; ++i)
                    {
                        auto iAmIdiot = directions[make_pair(dx[i], dy[i])];
                        if (ok(u + dx[i], n) && ok(v + dy[i], m) && a[u][v] != UNKNOWN && dir[a[u][v]][iAmIdiot] && (dx[i] != 0 || dy[i] != 0))
                        {
                            int isReverse = opposite(prevD, iAmIdiot);
                            int isShpilka = opposite(prevprevD, iAmIdiot);
                            int temp = d[u][v] + 1 + isShpilka * 3 + isReverse * 6;
                            if (d[u + dx[i]][v + dy[i]] > temp)
                            {
                                d[u + dx[i]][v + dy[i]] = temp;
                                prev[u + dx[i]][v + dy[i]] = {u, v};
                                q.push(vertex(u + dx[i], v + dy[i], prevD, iAmIdiot));
                            }
                        }
                    }
                }
                return make_pair(d, prev);
            };
            auto qqwerwer = bfs(si, sj, ti, tj, pd, d, FUUUUU);
            auto d = qqwerwer.first;
            int u, v;
            auto prev = qqwerwer.second;
            {
                u = tti;
                v = ttj;
                //ppp(d);
                int known = 10000;
                if (d[tti][ttj] != 10000)
                    known = fffpath(si, sj, tti, ttj, bfs(si, sj, tti, ttj, pd, dd, FUUUUU).second).size();
                int ytrewq = d[tti][ttj] == 10000 || (known / 2 > (abs(si - tti) + abs(sj + ttj)));
                if (ytrewq)
                {
                    int indexi = -1;
                    int indexj = -1;
                    int mn = 11234123;
                    for (int i = 0; i < d.size(); ++i)
                        for (int j = 0; j < d[0].size(); ++j)
                            if (d[i][j] < 10000)
                            {
                                int length = fffpath(si, sj, i, j, bfs(si, sj, i, j, pd, dd, FUUUUU).second).size();
                                bool hasGoodNeighbor = false;
                                for (int dx = -1; dx < 2; ++dx)
                                    for (int dy = -1; dy < 2; ++dy)
                                        if (abs(dx + dy) == 1)
                                            hasGoodNeighbor |= ok(i + dx, a.size()) && ok(j + dy, a[0].size()) && a[i + dx][j + dy] == UNKNOWN;
#ifdef vis
        if (hasGoodNeighbor)
            visual.fillCircle(getCenter(i), getCenter(j), 50, 0xff00ff);
        else
            visual.fillCircle(getCenter(i), getCenter(j), 50, 0x00ffff);
#endif
                                int gamno = abs(i - tti) + abs(j - ttj) + length;
                                if ((gamno < mn || (gamno == mn && abs(si - i) + abs(sj - j) < abs(si - indexi) + abs(sj - indexj))) && !visited[i][j] && hasGoodNeighbor)
                                    mn = gamno,
                                    indexi = i,
                                    indexj = j;
                            }
                    if (indexi == -1)
                        cout << "FAAAAAAAAAAAAAIL\n";
                    else
                        //cout << "indices == " << indexi << " " << indexj << "\n",
                        u = ti = indexi,
                        v = tj = indexj,
#ifdef vis
                        visual.fillCircle(getCenter(tti), getCenter(ttj), 600, 0x555555),
#endif
                        targetX = getCenter(ti),
                        targetY = getCenter(tj);
                }
                auto path = fffpath(si, sj, u, v, prev);
                if (ytrewq)
                    path.push_back({-1, -1});
                return path;
            }
            return vector<pair<int, int>>(0);
        };
        vector<pair<int, int>> path;
        int qqq = ti;
        int www = tj;
        path = getPath(si, sj, ti, tj, pd, d, FU);
        for (int i = 0; i + 4 < min(7, int(path.size())); ++i)
            if (
                    (
                        isVertical(path[i + 0], path[i + 1]) &&
                        isVertical(path[i + 2], path[i + 3]) &&
                        isHorizontal(path[i + 0], path[i + 3]) &&
                        isHorizontal(path[i + 1], path[i + 2])
                    )
                    ||
                    (
                        isHorizontal(path[i + 0], path[i + 1]) &&
                        isHorizontal(path[i + 2], path[i + 3]) &&
                        isVertical(path[i + 0], path[i + 3]) &&
                        isVertical(path[i + 1], path[i + 2])
                    )
                )
            {
                path = getPath(si, sj, qqq, www, pd, d, goforward);
                break;
            }
        //cout << "RAW PATH = \n" << path;
        int ai, aj, bi, bj, ci, cj, di, dj;
        auto banana = path.back();
        if (banana.first == -1)
            path.pop_back();
        else
        while (waypointIndex + 1 < int(wp.size()))
        {
            banana = path.back();
            if (banana.first == -1)
                path.pop_back();
            int t = 0;
            int y = 0;
            auto zxcv = path.back();
            auto asdf = path.back();
            auto qwer = path.back();
            if (path.size() >= 2)
                asdf = path[path.size() - 2];
            if (path.size() >= 3)
                zxcv = path[path.size() - 3];
            t = directions[make_pair(asdf.first - zxcv.first, asdf.second - zxcv.second)];
            y = directions[make_pair(qwer.first - asdf.first, qwer.second - asdf.second)];
            if (path.size() < 3)
                t = d;
            int q = wp[waypointIndex][0];
            int w = wp[waypointIndex][1];
            int e = wp[waypointIndex + 1][0];
            int r = wp[waypointIndex + 1][1];
            auto temp = getPath(q, w, e, r, t, y, FU);
            banana = temp.back();
            if (banana.first == -1)
                temp.pop_back();
            if (temp.size() <= 1)
                break;
            for (auto x : temp)
                path.push_back(x);
            waypointIndex++;
        }
        for (int i = 1; i < int(path.size()); ++i)
            if (path[i] == path[i - 1])
                path.erase(path.begin() + --i);
        //for (int i = 0; i + 5 < int(path.size()); ++i)
        //{
            //auto s = path[i];
            //auto d = path[i + 1];
            //auto f = path[i + 2];
            //auto g = path[i + 3];
            //auto h = path[i + 4];
            //auto j = path[i + 5];
            //if (isDownTo(s, d) && isDownTo(d, f) && isLeftTo(f, g) && isLeftTo(g, h) && !isDownTo(h, j) && dir[a[d.first][d.second]][RIGHT] && dir[a[g.first][g.second]][DOWN])
                //cout << "EPIC WIN\n",
                //path[i + 2] = {d.first + 1, d.second};
            //if (isDownTo(s, d) && isDownTo(d, f) && isLeftTo(f, g) && isLeftTo(g, h) && !isDownTo(h, j) && dir[a[d.first][d.second]][RIGHT] && dir[a[g.first][g.second]][DOWN])
                //path[i + 2] = {d.first + 1, d.second};

        //}
        auto checkBonus = path;
        for (int i = 1; i < int(path.size()) - 1; ++i)
            if ((abs(path[i + 1].first - path[i - 1].first) == 1 && abs(path[i + 1].second - path[i - 1].second) == 1) || path[i - 1] == path[i + 1])
            {
#ifdef debug
                if (debug)
                {
                    vector<string> xxx(m);
                    for (int i = 0; i < m; ++i)
                        for (int j = 0; j < n; ++j)
                            xxx[i].push_back('.');
                    for (int i = 0; i < path.size(); ++i)
                        xxx[path[i].second][path[i].first] = i + 48;
                    xxx[sj][si] = 'S';
                    xxx[path[i].second][path[i].first] = 'X';
                    xxx[tj][ti] = 'F';
                    //ppp(d);
                    //writeln();
                    //writeln(xxx);
                    //writeln();
                }
#endif
                //fi = ti;
                //fj = tj;
                tie(ti, tj) = path[i];
                targetX = getCenter(path[i].first);//(path[i].first + 0.5) * tileSize;
                targetY = getCenter(path[i].second);//(path[i].second + 0.5) * tileSize;
                break;
            }
#ifdef debug
        wr(path);
        //cout.flush();
#endif
        if (path.size() >= 3)
        {
            tie(ai, aj) = path[0];
            tie(bi, bj) = path[1];
            tie(ci, cj) = path[2];
        }
        if (path.size() >= 4)    //SNAKE
        {
            tie(di, dj) = path[3];
            snake = true;
            if (
            (ai + 1 == ci && aj - 1 == cj && bi + 1 == di && bj - 1 == dj)
            || (ai - 1 == ci && aj + 1 == cj && bi - 1 == di && bj + 1 == dj)
            || (ai + 1 == ci && aj + 1 == cj && bi + 1 == di && bj + 1 == dj)
            || (ai - 1 == ci && aj - 1 == cj && bi - 1 == di && bj - 1 == dj)
            )
                tie(targetX, targetY) = getXX(path[1], path[2]);
            else
            {
                drift = true;
                snake = false;
                if (
                        (
                            isVertical(path[0], path[1]) &&
                            isVertical(path[2], path[3]) &&
                            isHorizontal(path[0], path[3]) &&
                            isHorizontal(path[1], path[2])
                        )
                        ||
                        (
                            isHorizontal(path[0], path[1]) &&
                            isHorizontal(path[2], path[3]) &&
                            isVertical(path[0], path[3]) &&
                            isVertical(path[1], path[2])
                        )
                    )
                {
                    bad.insert(path[1]);
                    if (d != directions[make_pair(path[1].first - path[0].first, path[1].second - path[0].second)])
                        bad.insert(path[0]);
                    bad.insert(path[2]);
                    //if (self.getDistanceTo(getCenter(path[1].first), getCenter(path[1].second)) < tileSize)
                    tie(targetX, targetY) = getCorner(path[0], path[1], path[2]);
                }
                else
                    drift = false;
            }
        } else
            drift = false,
            snake = false;
        double temp = self.getDistanceTo(targetX, targetY);
        double temp2 = temp / tileSize;
        prevDistance = distToNext;
        distToNext = temp;
        auto interpolation = [&](double x)
        {
            return + 5.28596 * pow(x, 8) - 49.1259 * pow(x, 7) + 189.037 * pow(x, 6) - 388.625 * pow(x, 5) + 458.98  * pow(x, 4) - 310.246 * pow(x, 3) + 110.424 * pow(x, 2) - 15.6552 * pow(x, 1) + 0.2;//идеально при малой скорости
            return + 7.16332 * pow(x, 8) - 67.0616 * pow(x, 7) + 260.855 * pow(x, 6) - 544.344 * pow(x, 5) + 655.525 * pow(x, 4) - 453.69  * pow(x, 3) + 165.888 * pow(x, 2) - 24.2604 * pow(x, 1) + 0.2; //хреново входит в поворот
            return + 1.68041 * pow(x, 7) - 14.0981 * pow(x, 6) + 47.7581 * pow(x, 5) - 82.7825 * pow(x, 4) + 76.7515 * pow(x, 3) - 36.3308 * pow(x, 2) + 7.15476 * pow(x, 1)
    + 0.2; //на скорости влезает, но задевает угол ~-2
            return - 0.57084 * pow(x, 10) + 10.9758 * pow(x, 9) - 91.814  * pow(x, 8) + 438.632 * pow(x, 7) - 1320.67 * pow(x, 6) + 2608.54 * pow(x, 5) - 3408.95 * pow(x, 4) + 2898.79 * pow(x, 3) - 1530.02 * pow(x, 2) + 451.546 * pow(x, 1) - 56.1279; //шикарно в большие повороты
        };
        double MAAAAAGIC = interpolation(temp2);
        if (temp2 > 2)
            MAAAAAGIC = -0.25;
        if (temp2 < 0.6)
            MAAAAAGIC = interpolation(0.6);
        bool found = false;
        for (int i = 0; i < int(path.size()); ++i)
            if (path[i].first == ti && path[i].second == tj)
            {
                pi = path[max(0, i - 1)].first;
                pj = path[max(0, i - 1)].second;
                fi = path[min(int(path.size()) - 1, i + 1)].first;
                fj = path[min(int(path.size()) - 1, i + 1)].second;
                found = true;
                break;
            }
        double nextWaypointX = targetX;
        double nextWaypointY = targetY;

        double cornerTileOffset = MAAAAAGIC * tileSize;
        //auto pathtitj = getPath(ti, tj, fi, fj);
        //if (pathtitj.size() >= 2)
            //fi = pathtitj[1].first,
            //fj = pathtitj[1].second;
        //else
            //fi = ti,
            //fj = tj;
#ifdef debug
        wr(si, sj, pi, pj, ti, tj, fi, fj);
        cout.flush();
        //writeln(pathtitj);
        //writeln();
#endif
        auto changeCoords = [&](int i, int j) {
            if (snake || drift)
                return;
            if (pj == tj)
                swap(pi, fi),
                swap(pj, fj);
            switch (a[i][j]) 
            {
                case LEFT_TOP_CORNER:
    lt:
                    //a[i][j] = LEFT_TOP_CORNER;
                    nextWaypointX += cornerTileOffset;
                    nextWaypointY += cornerTileOffset;
                    break;
                case RIGHT_TOP_CORNER:
    rt:
                    //a[i][j] = RIGHT_TOP_CORNER;
                    nextWaypointX -= cornerTileOffset;
                    nextWaypointY += cornerTileOffset;
                    break;
                case LEFT_BOTTOM_CORNER:
    lb:
                    //a[i][j] = LEFT_BOTTOM_CORNER;
                    nextWaypointX += cornerTileOffset;
                    nextWaypointY -= cornerTileOffset;
                    break;
                case RIGHT_BOTTOM_CORNER:
    rb:
                    //a[i][j] = RIGHT_BOTTOM_CORNER;
                    nextWaypointX -= cornerTileOffset;
                    nextWaypointY -= cornerTileOffset;
                    break;
                case TOP_HEADED_T:
    th:
                    if (pj == tj && pj == fj);
                    else
                        go(fi + 1 == ti, rb, lb);
                    break;
                case BOTTOM_HEADED_T:
    bh:
                    if (pj == tj && pj == fj);
                    else
                        go(fi + 1 == ti, rt, lt);
                    break;
                case RIGHT_HEADED_T:
                    if (pi == ti && pi == fi);
                    else
                        go(pj + 1 == tj, lb, lt);
                    break;
                case LEFT_HEADED_T:
                    if (pi == ti && pi == fi);
                    else
                        go(pj + 1 == tj, rb, rt);
                    break;
                case CROSSROADS:
                    if (pi == ti && pi == fi);
                    else if (pj == tj && pj == fj);
                    else go(pj + 1 == tj, th, bh);
                default:
                    break;
            }
        };
        changeCoords(ti, tj);
        bool B = false;
        double bonusMin = 1000000;
        Bonus bonus;
        if (!snake && self.getRemainingNitroTicks() == 0 && !drift)
            for (Bonus b : world.getBonuses())
                if (self.getDistanceTo(b) < distToNext)
                    if ((b.getDistanceTo(targetX, targetY) > tileSize * 2 && fabs(self.getAngleTo(b)) < PI / 27) && fabs(self.getAngleTo(targetX, targetY) < PI / 36) && self.getDistanceTo(b) > tileSize)
                    {
                        pair<int, int> bbb = {b.getX() / tileSize, b.getY() / tileSize};
                        pair<int, int> qwerty = {ti, tj};
                        for (auto point : path)
                        {
                            if (point == qwerty)
                                break;
                            if (point == bbb)
                            {
                                B = true;
                                if (bonusMin > self.getDistanceTo(b))
                                    bonus = b,
                                    bonusMin = self.getDistanceTo(b);
                            }
                        }
                    }
        if (B)
        {
            pair<int, int> bbb = {bonus.getX() / tileSize, bonus.getY() / tileSize};
            nextWaypointX = bonus.getX();
            nextWaypointY = bonus.getY();
            nextWaypointX = min(nextWaypointX, get(bbb.first + 1) - height - bonus.getWidth() / 2 - 78);
            nextWaypointX = max(nextWaypointX, get(bbb.first) + height + bonus.getWidth() / 2 + 78);
            nextWaypointY = min(nextWaypointY, get(bbb.second + 1) - height - bonus.getHeight() / 2 - 78);
            nextWaypointY = max(nextWaypointY, get(bbb.second) + height + bonus.getHeight() / 2 + 78);
        }
        if (is32(path))
            tie(nextWaypointX, nextWaypointY) = make_pair(getCenter(path[2].first), getCenter(path[2].second));

        auto cars = world.getCars();
        sort(cars.begin(), cars.end(), [&self](const Car& aaa, const Car& bbb) { return self.getDistanceTo(aaa) < self.getDistanceTo(bbb);});
        for (Car car : world.getCars())
            if (!car.isFinishedTrack() && !car.isTeammate())
                if (hypot(car.getSpeedX(), car.getSpeedY()) * 1.2 < speedModule || fabs(car.getAngleTo(self)) < PI / 2 || speedModule < 10 && world.getTick() > 300)
                {
                    pair<int, int> ccc = {car.getX() / tileSize, car.getY() / tileSize};
                    pair<int, int> qwerty = {ti, tj};
                    int index = 0;
                    for (auto point : path)
                    {
                        if (point == qwerty)
                            break;
                        if (point == ccc && index + 1 < int(path.size()) && (self.getDistanceTo(car) > tileSize || speedModule < 10))
                        {
                            if (isHorizontal(point, path[index + 1]))
                            {
                                if (targetX <= self.getX() && self.getX() <= car.getX() || targetX >= self.getX() && self.getX() >= car.getX())
                                    continue;
                                double lower = get(ccc.second) + 80 + height + 15;
                                double lower2 = car.getY() - height - 15 - car.getWidth();
                                double upper = get(ccc.second + 1) - 80 - height - 15;
                                double upper2 = car.getY() + height + 15 + car.getWidth();
                                double cgy = car.getY();
                                double dist1 = self.getDistanceTo(car.getX(), lower) + hypot(nextWaypointX - car.getX(), nextWaypointY - lower);
                                double dist2 = self.getDistanceTo(car.getX(), lower2) + hypot(nextWaypointX - car.getX(), nextWaypointY - lower2);
                                double dist3 = self.getDistanceTo(car.getX(), upper) + hypot(nextWaypointX - car.getX(), nextWaypointY - upper);
                                double dist4 = self.getDistanceTo(car.getX(), upper2) + hypot(nextWaypointX - car.getX(), nextWaypointY - upper2);
                                nextWaypointX = car.getX();
                                nextWaypointY = (cgy - lower > upper - cgy) ? (dist1 < dist2 ? lower : lower2) : (dist3 < dist4 ? upper : upper2);
                            }
                            if (isVertical(point, path[index + 1]))
                            {
                                if (targetY <= self.getY() && self.getY() <= car.getY() || targetY >= self.getY() && self.getY() >= car.getY())
                                    continue;
                                double lower = get(ccc.first) + 80 + height + 15;
                                double lower2 = car.getX() - height - 15 - car.getWidth();
                                double upper = get(ccc.first + 1) - 80 - height - 15;
                                double upper2 = car.getX() + height + 15 + car.getWidth();
                                double cgy = car.getX();
                                double dist1 = self.getDistanceTo(car.getY(), lower) + hypot(nextWaypointY - car.getY(), nextWaypointX - lower);
                                double dist2 = self.getDistanceTo(car.getY(), lower2) + hypot(nextWaypointY - car.getY(), nextWaypointX - lower2);
                                double dist3 = self.getDistanceTo(car.getY(), upper) + hypot(nextWaypointY - car.getY(), nextWaypointX - upper);
                                double dist4 = self.getDistanceTo(car.getY(), upper2) + hypot(nextWaypointY - car.getY(), nextWaypointX - upper2);
                                nextWaypointY = car.getY();
                                nextWaypointX = (cgy - lower > upper - cgy) ? (dist1 < dist2 ? lower : lower2) : (dist3 < dist4 ? upper : upper2);
                            }
                            break;
                        }
                        ++index;
                    }

                }
        auto os = world.getOilSlicks();
        sort(os.begin(), os.end(), [&self](const OilSlick& aaa, const OilSlick& bbb) { return self.getDistanceTo(aaa) < self.getDistanceTo(bbb);});
        for (auto o : os)
        {
            pair<int, int> ccc = {o.getX() / tileSize, o.getY() / tileSize};
            pair<int, int> qwerty = {ti, tj};
            int index = 0;
            for (auto point : path)
            {
                if (point == qwerty)
                    break;
                if (point == ccc && index + 1 < int(path.size()) && self.getDistanceTo(o) > tileSize && self.getDistanceTo(o) < self.getDistanceTo(nextWaypointX, nextWaypointY))
                {
                    if (isHorizontal(point, path[index + 1]))
                    {
                        if (targetX <= self.getX() && self.getX() <= o.getX() || targetX >= self.getX() && self.getX() >= o.getX())
                            continue;
                        double lower = get(ccc.second) + 80 + height + 15;
                        double lower2 = o.getY() - height - 15 - o.getRadius();
                        double upper = get(ccc.second + 1) - 80 - height - 15;
                        double upper2 = o.getY() + height + 15 + o.getRadius();
                        double cgy = o.getY();
                        double dist1 = self.getDistanceTo(o.getX(), lower) + hypot(nextWaypointX - o.getX(), nextWaypointY - lower);
                        double dist2 = self.getDistanceTo(o.getX(), lower2) + hypot(nextWaypointX - o.getX(), nextWaypointY - lower2);
                        double dist3 = self.getDistanceTo(o.getX(), upper) + hypot(nextWaypointX - o.getX(), nextWaypointY - upper);
                        double dist4 = self.getDistanceTo(o.getX(), upper2) + hypot(nextWaypointX - o.getX(), nextWaypointY - upper2);
                        nextWaypointX = o.getX();
                        nextWaypointY = (cgy - lower > upper - cgy) ? (dist1 < dist2 ? lower : lower2) : (dist3 < dist4 ? upper : upper2);
                    }
                    if (isVertical(point, path[index + 1]))
                    {
                        if (targetY <= self.getY() && self.getY() <= o.getY() || targetY >= self.getY() && self.getY() >= o.getY())
                            continue;
                        double lower = get(ccc.first) + 80 + height + 15;
                        double lower2 = o.getX() - height - 15 - o.getRadius();
                        double upper = get(ccc.first + 1) - 80 - height - 15;
                        double upper2 = o.getX() + height + 15 + o.getRadius();
                        double cgy = o.getX();
                        double dist1 = self.getDistanceTo(o.getY(), lower) + hypot(nextWaypointY - o.getY(), nextWaypointX - lower);
                        double dist2 = self.getDistanceTo(o.getY(), lower2) + hypot(nextWaypointY - o.getY(), nextWaypointX - lower2);
                        double dist3 = self.getDistanceTo(o.getY(), upper) + hypot(nextWaypointY - o.getY(), nextWaypointX - upper);
                        double dist4 = self.getDistanceTo(o.getY(), upper2) + hypot(nextWaypointY - o.getY(), nextWaypointX - upper2);
                        nextWaypointY = o.getY();
                        nextWaypointX = (cgy - lower > upper - cgy) ? (dist1 < dist2 ? lower : lower2) : (dist3 < dist4 ? upper : upper2);
                    }
                    break;
                }
                ++index;
            }

        }

        double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
        //double check = self.getAngleTo(getCenter(ti), getCenter(tj));
        //if ((fabs(check - PI) < PI / 6 || fabs(check + PI) < PI / 6) && planB == 0)
            //planB = PLANB,
            //power *= -1;
        //if (fabs(check) < PI / 3 && planB)
            //power *= -1,
            //planB = 0;
        auto getTurn = [&](double d)
        {
            return angleToWaypoint * d * pow(DIST_TO_NEXT / distToNext, 0.8) / PI;
        };
        if (forceBack)
        {
            forceBack--;
            if (forceBack == 0)
            {
                power *= -1;
                forceRight = FORCE_RIGHT;
                turn *= -1;
            }
        }

        else if (forceRight)
        {
            if (forceRight > FORCE_RIGHT - BREAK)
                move.setBrake(true);
            forceRight--;
            if (forceRight == 0)
                force = FORCE;
        } 
        if (forceBack == 0 && forceRight == 0)
        {
            if (changed && fabs(prevDistance - distToNext) < eps)
            {
                countOfFails++;
                {
                    if (countOfFails > COUNT_OF_FAILS)
                    {
                        globalFail++;
                        countOfFails = 0;
                        //if (planB)
                            //planB = 0,
                            //power *= -1,
                            //forceRight = FORCE_RIGHT;
                        //else
                            forceBack = FORCE_BACK;
                        turn = getTurn(32);
                        if (isCorner(a[si][sj]))
                        {
                            //cout << "CORNER";
                            turn = turn > 0 ? 1 : -1;
                            if (globalFail > GLOBAL_FAIL)
                                //cout << "GLOBAL_FAIL",
                                turn *= -1;
                        }
                        else
                            if (globalFail > GLOBAL_FAIL)
                                //cout << "NOT CORNER GLOBAL_FAIL",
                                turn = turn > 0 ? 1 : -1;
                        turn *= -1;
                        power *= -1;
                    }
                }
                //else
                    //if (countOfFails > COUNT_OF_FAILS / 5)
                    //{
                        //forceRight = 0;
                        //force = 0;
                        //countOfFails = COUNT_OF_FAILS;
                    //}
            }
            else
            {
                if (force)
                    force--;
                forceSlow = path.size() <= 4 ? 14 : 100;
                if (is4(path))
                    forceSlow *= 1.5;
                countOfFails = 0;
                globalFail = 0;

                if (forceRight == 0)
                    turn = getTurn(36);
                double dd = speedModule / MAX_SPEED;
                if (is32(path))
                    dd *= 1.3;
                if (is3_2(path))
                    dd /= 2;
                if (is212(path))
                    dd /= 2;
                if (is41(path))
                    dd *= 1.2;
                bool fas = is131(path) && speedModule > 16.5;
                //cout << si << " " << sj << " " << badX << " " << badY << "\n";
                if ((!snake && distToNext < tileSize * dd && distToNext > tileSize && bad.find(S) == bad.end()) || speedModule > forceSlow || (bad.find(S) != bad.end() && speedModule > 11) || fas)
                    move.setBrake(true);
            }
        }
        //cout << "END OF MOVE\n";
        //cout.flush();
        //else
            //if (changed && fabs(prevDistance - distToNext) < eps)
            //{
                //countOfFails++;
                //if (countOfFails > COUNT_OF_FAILS / 3)
                    //forceRight = FORCE_RIGHT;
            //}
            //else
                //countOfFails = 0;
        if (forceRight == 0 && forceBack == 0 && planB)
        {
            if (angleToWaypoint > 0)
                angleToWaypoint = PI - angleToWaypoint;
            else
                angleToWaypoint = -PI + angleToWaypoint;
            turn = getTurn(32);
            //cout << "PLANB\n";
        }
        move.setWheelTurn(turn);
        move.setEnginePower(power);
        for (auto car : world.getCars())
            if (!car.isTeammate())
            {
                if (world.getTick() > 250 && self.getDistanceTo(car) <= tileSize * 2)
                {
                    if (fabs(self.getAngleTo(car)) < ANGLE_THROW && car.getDurability() > 0 && !car.isFinishedTrack())
                        move.setThrowProjectile(true);
                }
                if (self.getDistanceTo(car) <= tileSize * 6 && isCorner(a[si][sj]) && planB == 0)
                    move.setSpillOil(true);
            }
        //if (world.getTick() > 210 && distToNext > prevDistance)
        //{
            //forceSlow = FORCE_SLOW_DOWN;
            //if (distToNext > tileSize * 5)
                //forceSlow /= 2;
        //}
        bool okSnake = false;
        if (snake && path.size() >= 2)
        {
            int count = 0;
            vector<int> fff = {
                directions[make_pair(path[0].first - path[1].first, path[0].second - path[1].second)],
                directions[make_pair(path[1].first - path[2].first, path[1].second - path[2].second)]
            };
            for (int i = 2; i < path.size(); ++i)
                if (directions[make_pair(path[i].first - path[i + 1].first, path[i].second - path[i + 1].second)] == fff[i % 2])
                    count++;
                else
                    break;
            //cout << count << "\n";
            okSnake = count >= 9;
        }
        if (forceRight == 0 && forceBack == 0 && world.getTick() > 195 && (distToNext > tileSize * 5 || (okSnake && bad.find(S) == bad.end() && speedModule > 20)) && planB == 0)
            move.setUseNitro(true);
#ifdef vis
        //cout << "VISUALIZATION\n";
        //cout.flush();
        for (int i = 0; i < a.size(); ++i)
            for (int j = 0; j < a[0].size(); ++j)
                if (a[i][j] == UNKNOWN)
                    visual.fillRect(get(i), get(j), get(i + 1), get(j + 1), 0xCC0000);
                else if (visited[i][j])
                    visual.fillRect(get(i), get(j), get(i + 1), get(j + 1), 0x008800);
        for (auto p : wp)
            visual.fillRect(get(p[0]), get(p[1]), get(p[0] + 1), get(p[1] + 1), 0x0000CC);

        visual.fillRect(get(ti), get(tj), get(ti + 1), get(tj + 1), 0x008888);
        visual.endPre();
        visual.beginPost();
        visual.circle(getCenter(ti), getCenter(tj), 600, 0x54618f);
        visual.line(self.getX(), self.getY(), nextWaypointX, nextWaypointY);
        char sss[45];
        sprintf(sss, "%d %d  s:%.2f  a:%.2f  t:%.2f", pd, d, speedModule, angleToWaypoint, turn);
        visual.text(self.getX() + 120, self.getY() + 120, sss);
        sss[44] = 0;
        //char qqq[35];
        //int ttt = 0;
        //for (auto ee : bad)
            //ttt += sprintf(qqq + ttt, "%d %d, ", ee.first, ee.second);
        //for (int i = 0; i < 35; ++i)
            //qqq[i] = ' ';
        //qqq[34] = 0;
        //visual.text(self.getX() + 120, self.getY() + 200, qqq);
        for (int i = 1; i < min(10, int(path.size())); ++i)
            visual.line(getCenter(path[i - 1].first), getCenter(path[i - 1].second), getCenter(path[i].first), getCenter(path[i].second), 0xff0000);
        visual.line(getCenter(pi), getCenter(pj), getCenter(ti), getCenter(tj), 0x00ff00);
        visual.line(getCenter(ti), getCenter(tj), getCenter(fi), getCenter(fj), 0x00ff00);
        visual.fillCircle(getCenter(ti), getCenter(tj), 10);
        visual.endPost();
#endif
        //cout << "END OF MOVE\n";
        //cout.flush();
    }

    else //надо было думать раньше
    {
#define changed       changedj       
#define distToNext    distToNextij   
#define prevDistance  prevDistanceij 
#define countOfFails  countOfFailsj  
#define forceBack     forceBackj     
#define forceRight    forceRightj    
#define force         forcej         
#define prevx         prevxj         
#define currx         currxj         
#define forceSlow     forceSlowj     
#define globalFail    globalFailj    
#define turn          turnj          
#define power         powerj          
#define init          initj          
#define snake         snakej         
#define drift         driftj         
#define width         widthj         
#define height        heightj        
#define d             dj             
#define pd            pdj            
#define bad           badj
#define old           oldj
#define planB         planBj         
#define visited       visitedj
#define once          oncej
#ifdef vis
        visual.beginPre();
#endif
        tileSize = game.getTrackTileSize();
        auto a = world.getTilesXY();
        if (init)
        {
            FU = goforward;
            //мне стало лень думать
            if (world.getMapName() == "map07" || world.getMapName() == "map08" || world.getMapName() == "map14")
                FUUUUU = goforward;
            old.push_back({self.getX() / tileSize, self.getY() / tileSize});
            //cout << self.getX() << " " << self.getY() << "\n";
            init = false;
            width = self.getWidth() / 2;
            height = self.getHeight() / 2;
            visited.resize(a.size());
            once.resize(a.size());
            for (int i = 0; i < visited.size(); ++i)
                visited[i].resize(a[0].size(), false),
                once[i].resize(a[0].size(), false);
            d = getDirectionByAngle(self.getAngle());
            pd = d;
            //cout << self.getAngle() << "   ANGLE " << pd << " " << d << "\n";
#ifdef debug
            writeln(world.getWaypoints());
#endif
            srand(game.getRandomSeed());
        }
        int waypointIndex = self.getNextWaypointIndex();
        int qx = self.getX() / tileSize;
        int qy = self.getY() / tileSize;
        int wx, wy;
        tie(wx, wy) = old.back();
        if (wx != qx || wy != qy)
        {
            //cout << wx << " " << wy << " " << qx << " " << qy << "         " << pd << " " << d << "\n";
            old[0] = {qx, qy};
            pd = d;
            d = directions[make_pair(qx - wx, qy - wy)];
            //int tqwer = getDirectionByAngle(self.getAngle());
            if (pd != d && a[self.getNextWaypointX()][self.getNextWaypointY()] != UNKNOWN && waypointIndex != 0)
                FU = FUUUUU;
            //if (tqwer != -1)
                //d = tqwer;
            //if (forceBack)
                //d = opposite(d);
        }

        prevx = currx;
        if (prevx == -1234)
            prevx = self.getX();
        currx = self.getX();
        if (currx - prevx != 0)
            changed = true;
        int ti = self.getNextWaypointX();
        int tj = self.getNextWaypointY();
        auto wp = world.getWaypoints();
        for (int i = 0; i < min(3, int(wp.size())); ++i)
            wp.push_back(wp[i]);
        int fi, fj, pi, pj;
        double speedModule = hypot(self.getSpeedX(), self.getSpeedY());
        //if (waypointIndex < int(wp.size()) - 1)
        //{
            //int cx = int(self.getX() / tileSize);
            //int cy = int(self.getY() / tileSize);
            //int wx1 = wp[waypointIndex][0];
            //int wx2 = wp[waypointIndex + 1][0];
            //int wy1 = wp[waypointIndex][1];
            //int wy2 = wp[waypointIndex + 1][1];
            //if (
                    //(cx == wx1 && cx == wx2 && ((cy < wy1 && wy1 < wy2) || (cy > wy1 && wy1 > wy2)))
                    //||
                    //(cy == wy1 && cy == wy2 && ((cx < wx1 && wx1 < wx2) || (cx > wx1 && wx1 > wx2)))
            //)
                //ti = wp[++waypointIndex][0],
                //tj = wp[waypointIndex][1];
            //if (waypointIndex + 1 < int(wp.size()))
                //fi = wp[waypointIndex + 1][0],
                //fj = wp[waypointIndex + 1][1];
        //}
        double targetX = getCenter(ti);
        double targetY = getCenter(tj);
            int si = self.getX() / tileSize;
            int sj = self.getY() / tileSize;
            pair<int, int> S = make_pair(si, sj);
            visited[si][sj] = true;
            vector<int> qwerqsdfgsdf = {si, sj};
            if (wp[max(0, self.getNextWaypointIndex() - 1)] == qwerqsdfgsdf && !once[si][sj])
            {
                once[si][sj] = true;
                for (int i = 0; i < visited.size(); ++i)
                    for (int j = 0; j < visited[0].size(); ++j)
                        visited[i][j] = false;
            }
            if (bad.find(S) == bad.end())
                bad.clear();
            int n = a.size();
            int m = a[0].size();
            auto ok = [&](int x, int N)
            {
                return x >= 0 && x < N;
            };

        auto getPath = [&](int si, int sj, int tti, int ttj, int pd, int dd, vector<vector<vector<int>>> FUUUUU)
        {
#ifdef debug
            writeln("GET", si, sj, tti, ttj, waypointIndex);
#endif
            auto fffpath = [](int si, int sj, int u, int v, vector<vector<pair<int, int>>> prev)
            {
                vector<pair<int, int>> path;
                while (u != si || v != sj)
                    path.push_back({u, v}),
                    tie(u, v) = prev[u][v];
                path.push_back({si, sj});
                reverse(path.begin(), path.end());
                return path;
            };
            auto bfs = [&](int si, int sj, int tti, int ttj, int pd, int dd, vector<vector<vector<int>>> FUUUUU)
            {
                queue<vertex> q;
                q.push(vertex(si, sj, pd, dd));
                vector<vector<int>> d(n, vector<int>(m, 10000));
                vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(m));
                d[si][sj] = 0;
                int u, v, prevD, prevprevD;
                while (q.size())
                {
                    u = q.front().x;
                    v = q.front().y;
                    prevD = q.front().qd;
                    prevprevD = q.front().qpd;
                    q.pop();
                    if (a[u][v] == UNKNOWN)
                        continue;
                    vector<int> dx;
                    vector<int> dy;
                    for (int i = 0; i < 4; ++i)
                        dx.push_back(ddx[FUUUUU[prevprevD][prevD][i]]),
                        dy.push_back(ddy[FUUUUU[prevprevD][prevD][i]]);
                    for (int i = 0; i < 4; ++i)
                    {
                        auto iAmIdiot = directions[make_pair(dx[i], dy[i])];
                        if (ok(u + dx[i], n) && ok(v + dy[i], m) && a[u][v] != UNKNOWN && dir[a[u][v]][iAmIdiot] && (dx[i] != 0 || dy[i] != 0))
                        {
                            int isReverse = opposite(prevD, iAmIdiot);
                            int isShpilka = opposite(prevprevD, iAmIdiot);
                            int temp = d[u][v] + 1 + isShpilka * 3 + isReverse * 6;
                            if (d[u + dx[i]][v + dy[i]] > temp)
                            {
                                d[u + dx[i]][v + dy[i]] = temp;
                                prev[u + dx[i]][v + dy[i]] = {u, v};
                                q.push(vertex(u + dx[i], v + dy[i], prevD, iAmIdiot));
                            }
                        }
                    }
                }
                return make_pair(d, prev);
            };
            auto qqwerwer = bfs(si, sj, ti, tj, pd, d, FUUUUU);
            auto d = qqwerwer.first;
            int u, v;
            auto prev = qqwerwer.second;
            {
                u = tti;
                v = ttj;
                //ppp(d);
                int known = 10000;
                if (d[tti][ttj] != 10000)
                    known = fffpath(si, sj, tti, ttj, bfs(si, sj, tti, ttj, pd, dd, FUUUUU).second).size();
                int ytrewq = d[tti][ttj] == 10000 || (known / 2 > (abs(si - tti) + abs(sj + ttj)));
                if (ytrewq)
                {
                    int indexi = -1;
                    int indexj = -1;
                    int mn = 11234123;
                    for (int i = 0; i < d.size(); ++i)
                        for (int j = 0; j < d[0].size(); ++j)
                            if (d[i][j] < 10000)
                            {
                                int length = fffpath(si, sj, i, j, bfs(si, sj, i, j, pd, dd, FUUUUU).second).size();
                                bool hasGoodNeighbor = false;
                                for (int dx = -1; dx < 2; ++dx)
                                    for (int dy = -1; dy < 2; ++dy)
                                        if (abs(dx + dy) == 1)
                                            hasGoodNeighbor |= ok(i + dx, a.size()) && ok(j + dy, a[0].size()) && a[i + dx][j + dy] == UNKNOWN;
#ifdef vis
        if (hasGoodNeighbor)
            visual.fillCircle(getCenter(i), getCenter(j), 50, 0xff00ff);
        else
            visual.fillCircle(getCenter(i), getCenter(j), 50, 0x00ffff);
#endif
                                int gamno = abs(i - tti) + abs(j - ttj) + length;
                                if ((gamno < mn || (gamno == mn && abs(si - i) + abs(sj - j) < abs(si - indexi) + abs(sj - indexj))) && !visited[i][j] && hasGoodNeighbor)
                                    mn = gamno,
                                    indexi = i,
                                    indexj = j;
                            }
                    if (indexi == -1)
                        cout << "FAAAAAAAAAAAAAIL\n";
                    else
                        //cout << "indices == " << indexi << " " << indexj << "\n",
                        u = ti = indexi,
                        v = tj = indexj,
#ifdef vis
                        visual.fillCircle(getCenter(tti), getCenter(ttj), 600, 0x555555),
#endif
                        targetX = getCenter(ti),
                        targetY = getCenter(tj);
                }
                auto path = fffpath(si, sj, u, v, prev);
                if (ytrewq)
                    path.push_back({-1, -1});
                return path;
            }
            return vector<pair<int, int>>(0);
        };
        vector<pair<int, int>> path;
        int qqq = ti;
        int www = tj;
        path = getPath(si, sj, ti, tj, pd, d, FU);
        for (int i = 0; i + 4 < min(7, int(path.size())); ++i)
            if (
                    (
                        isVertical(path[i + 0], path[i + 1]) &&
                        isVertical(path[i + 2], path[i + 3]) &&
                        isHorizontal(path[i + 0], path[i + 3]) &&
                        isHorizontal(path[i + 1], path[i + 2])
                    )
                    ||
                    (
                        isHorizontal(path[i + 0], path[i + 1]) &&
                        isHorizontal(path[i + 2], path[i + 3]) &&
                        isVertical(path[i + 0], path[i + 3]) &&
                        isVertical(path[i + 1], path[i + 2])
                    )
                )
            {
                path = getPath(si, sj, qqq, www, pd, d, goforward);
                break;
            }
        cout << "RAW PATH = \n" << path;
        int ai, aj, bi, bj, ci, cj, di, dj;
        auto banana = path.back();
        if (banana.first == -1)
            cout << "banana\n";
        else
            cout << "!banana\n";
        if (banana.first == -1)
            path.pop_back();
        else
        while (waypointIndex + 1 < int(wp.size()))
        {
            banana = path.back();
            if (banana.first == -1)
                path.pop_back();
            int t = 0;
            int y = 0;
            auto zxcv = path.back();
            auto asdf = path.back();
            auto qwer = path.back();
            if (path.size() >= 2)
                asdf = path[path.size() - 2];
            if (path.size() >= 3)
                zxcv = path[path.size() - 3];
            t = directions[make_pair(asdf.first - zxcv.first, asdf.second - zxcv.second)];
            y = directions[make_pair(qwer.first - asdf.first, qwer.second - asdf.second)];
            if (path.size() < 3)
                t = d;
            int q = wp[waypointIndex][0];
            int w = wp[waypointIndex][1];
            int e = wp[waypointIndex + 1][0];
            int r = wp[waypointIndex + 1][1];
            auto temp = getPath(q, w, e, r, t, y, FU);
            banana = temp.back();
            if (banana.first == -1)
                temp.pop_back();
            if (temp.size() <= 1)
                break;
            for (auto x : temp)
                path.push_back(x);
            waypointIndex++;
        }
        for (int i = 1; i < int(path.size()); ++i)
            if (path[i] == path[i - 1])
                path.erase(path.begin() + --i);
        //for (int i = 0; i + 5 < int(path.size()); ++i)
        //{
            //auto s = path[i];
            //auto d = path[i + 1];
            //auto f = path[i + 2];
            //auto g = path[i + 3];
            //auto h = path[i + 4];
            //auto j = path[i + 5];
            //if (isDownTo(s, d) && isDownTo(d, f) && isLeftTo(f, g) && isLeftTo(g, h) && !isDownTo(h, j) && dir[a[d.first][d.second]][RIGHT] && dir[a[g.first][g.second]][DOWN])
                //cout << "EPIC WIN\n",
                //path[i + 2] = {d.first + 1, d.second};
            //if (isDownTo(s, d) && isDownTo(d, f) && isLeftTo(f, g) && isLeftTo(g, h) && !isDownTo(h, j) && dir[a[d.first][d.second]][RIGHT] && dir[a[g.first][g.second]][DOWN])
                //path[i + 2] = {d.first + 1, d.second};

        //}
        auto checkBonus = path;
        for (int i = 1; i < int(path.size()) - 1; ++i)
            if ((abs(path[i + 1].first - path[i - 1].first) == 1 && abs(path[i + 1].second - path[i - 1].second) == 1) || path[i - 1] == path[i + 1])
            {
#ifdef debug
                if (debug)
                {
                    vector<string> xxx(m);
                    for (int i = 0; i < m; ++i)
                        for (int j = 0; j < n; ++j)
                            xxx[i].push_back('.');
                    for (int i = 0; i < path.size(); ++i)
                        xxx[path[i].second][path[i].first] = i + 48;
                    xxx[sj][si] = 'S';
                    xxx[path[i].second][path[i].first] = 'X';
                    xxx[tj][ti] = 'F';
                    //ppp(d);
                    //writeln();
                    //writeln(xxx);
                    //writeln();
                }
#endif
                //fi = ti;
                //fj = tj;
                tie(ti, tj) = path[i];
                targetX = getCenter(path[i].first);//(path[i].first + 0.5) * tileSize;
                targetY = getCenter(path[i].second);//(path[i].second + 0.5) * tileSize;
                break;
            }
#ifdef debug
        wr(path);
        cout.flush();
#endif
        if (path.size() >= 3)
        {
            tie(ai, aj) = path[0];
            tie(bi, bj) = path[1];
            tie(ci, cj) = path[2];
        }
        if (path.size() >= 4)    //SNAKE
        {
            tie(di, dj) = path[3];
            snake = true;
            if (
            (ai + 1 == ci && aj - 1 == cj && bi + 1 == di && bj - 1 == dj)
            || (ai - 1 == ci && aj + 1 == cj && bi - 1 == di && bj + 1 == dj)
            || (ai + 1 == ci && aj + 1 == cj && bi + 1 == di && bj + 1 == dj)
            || (ai - 1 == ci && aj - 1 == cj && bi - 1 == di && bj - 1 == dj)
            )
                tie(targetX, targetY) = getXX(path[1], path[2]);
            else
            {
                drift = true;
                snake = false;
                if (
                        (
                            isVertical(path[0], path[1]) &&
                            isVertical(path[2], path[3]) &&
                            isHorizontal(path[0], path[3]) &&
                            isHorizontal(path[1], path[2])
                        )
                        ||
                        (
                            isHorizontal(path[0], path[1]) &&
                            isHorizontal(path[2], path[3]) &&
                            isVertical(path[0], path[3]) &&
                            isVertical(path[1], path[2])
                        )
                    )
                {
                    bad.insert(path[1]);
                    if (d != directions[make_pair(path[1].first - path[0].first, path[1].second - path[0].second)])
                        bad.insert(path[0]);
                    bad.insert(path[2]);
                    //if (self.getDistanceTo(getCenter(path[1].first), getCenter(path[1].second)) < tileSize)
                    tie(targetX, targetY) = getCorner(path[0], path[1], path[2]);
                }
                else
                    drift = false;
            }
        } else
            drift = false,
            snake = false;
        double temp = self.getDistanceTo(targetX, targetY);
        double temp2 = temp / tileSize;
        prevDistance = distToNext;
        distToNext = temp;
        auto interpolation = [&](double x)
        {
            return + 5.28596 * pow(x, 8) - 49.1259 * pow(x, 7) + 189.037 * pow(x, 6) - 388.625 * pow(x, 5) + 458.98  * pow(x, 4) - 310.246 * pow(x, 3) + 110.424 * pow(x, 2) - 15.6552 * pow(x, 1) + 0.2;//идеально при малой скорости
            return + 7.16332 * pow(x, 8) - 67.0616 * pow(x, 7) + 260.855 * pow(x, 6) - 544.344 * pow(x, 5) + 655.525 * pow(x, 4) - 453.69  * pow(x, 3) + 165.888 * pow(x, 2) - 24.2604 * pow(x, 1) + 0.2; //хреново входит в поворот
            return + 1.68041 * pow(x, 7) - 14.0981 * pow(x, 6) + 47.7581 * pow(x, 5) - 82.7825 * pow(x, 4) + 76.7515 * pow(x, 3) - 36.3308 * pow(x, 2) + 7.15476 * pow(x, 1)
    + 0.2; //на скорости влезает, но задевает угол ~-2
            return - 0.57084 * pow(x, 10) + 10.9758 * pow(x, 9) - 91.814  * pow(x, 8) + 438.632 * pow(x, 7) - 1320.67 * pow(x, 6) + 2608.54 * pow(x, 5) - 3408.95 * pow(x, 4) + 2898.79 * pow(x, 3) - 1530.02 * pow(x, 2) + 451.546 * pow(x, 1) - 56.1279; //шикарно в большие повороты
        };
        double MAAAAAGIC = interpolation(temp2);
        if (temp2 > 2)
            MAAAAAGIC = -0.25;
        if (temp2 < 0.6)
            MAAAAAGIC = interpolation(0.6);
        bool found = false;
        for (int i = 0; i < int(path.size()); ++i)
            if (path[i].first == ti && path[i].second == tj)
            {
                pi = path[max(0, i - 1)].first;
                pj = path[max(0, i - 1)].second;
                fi = path[min(int(path.size()) - 1, i + 1)].first;
                fj = path[min(int(path.size()) - 1, i + 1)].second;
                found = true;
                break;
            }
        double nextWaypointX = targetX;
        double nextWaypointY = targetY;

        double cornerTileOffset = MAAAAAGIC * tileSize;
        //auto pathtitj = getPath(ti, tj, fi, fj);
        //if (pathtitj.size() >= 2)
            //fi = pathtitj[1].first,
            //fj = pathtitj[1].second;
        //else
            //fi = ti,
            //fj = tj;
#ifdef debug
        wr(si, sj, pi, pj, ti, tj, fi, fj);
        cout.flush();
        //writeln(pathtitj);
        //writeln();
#endif
        auto changeCoords = [&](int i, int j) {
            if (snake || drift)
                return;
            if (pj == tj)
                swap(pi, fi),
                swap(pj, fj);
            switch (a[i][j]) 
            {
                case LEFT_TOP_CORNER:
    lt:
                    //a[i][j] = LEFT_TOP_CORNER;
                    nextWaypointX += cornerTileOffset;
                    nextWaypointY += cornerTileOffset;
                    break;
                case RIGHT_TOP_CORNER:
    rt:
                    //a[i][j] = RIGHT_TOP_CORNER;
                    nextWaypointX -= cornerTileOffset;
                    nextWaypointY += cornerTileOffset;
                    break;
                case LEFT_BOTTOM_CORNER:
    lb:
                    //a[i][j] = LEFT_BOTTOM_CORNER;
                    nextWaypointX += cornerTileOffset;
                    nextWaypointY -= cornerTileOffset;
                    break;
                case RIGHT_BOTTOM_CORNER:
    rb:
                    //a[i][j] = RIGHT_BOTTOM_CORNER;
                    nextWaypointX -= cornerTileOffset;
                    nextWaypointY -= cornerTileOffset;
                    break;
                case TOP_HEADED_T:
    th:
                    if (pj == tj && pj == fj);
                    else
                        go(fi + 1 == ti, rb, lb);
                    break;
                case BOTTOM_HEADED_T:
    bh:
                    if (pj == tj && pj == fj);
                    else
                        go(fi + 1 == ti, rt, lt);
                    break;
                case RIGHT_HEADED_T:
                    if (pi == ti && pi == fi);
                    else
                        go(pj + 1 == tj, lb, lt);
                    break;
                case LEFT_HEADED_T:
                    if (pi == ti && pi == fi);
                    else
                        go(pj + 1 == tj, rb, rt);
                    break;
                case CROSSROADS:
                    if (pi == ti && pi == fi);
                    else if (pj == tj && pj == fj);
                    else go(pj + 1 == tj, th, bh);
                default:
                    break;
            }
        };
        changeCoords(ti, tj);
        bool B = false;
        double bonusMin = 1000000;
        Bonus bonus;
        if (!snake && self.getRemainingNitroTicks() == 0 && !drift)
            for (Bonus b : world.getBonuses())
                if (self.getDistanceTo(b) < distToNext)
                    if ((b.getDistanceTo(targetX, targetY) > tileSize * 2 && fabs(self.getAngleTo(b)) < PI / 27) && fabs(self.getAngleTo(targetX, targetY) < PI / 36) && self.getDistanceTo(b) > tileSize)
                    {
                        pair<int, int> bbb = {b.getX() / tileSize, b.getY() / tileSize};
                        pair<int, int> qwerty = {ti, tj};
                        for (auto point : path)
                        {
                            if (point == qwerty)
                                break;
                            if (point == bbb)
                            {
                                B = true;
                                if (bonusMin > self.getDistanceTo(b))
                                    bonus = b,
                                    bonusMin = self.getDistanceTo(b);
                            }
                        }
                    }
        if (B)
        {
            pair<int, int> bbb = {bonus.getX() / tileSize, bonus.getY() / tileSize};
            nextWaypointX = bonus.getX();
            nextWaypointY = bonus.getY();
            nextWaypointX = min(nextWaypointX, get(bbb.first + 1) - height - bonus.getWidth() / 2 - 78);
            nextWaypointX = max(nextWaypointX, get(bbb.first) + height + bonus.getWidth() / 2 + 78);
            nextWaypointY = min(nextWaypointY, get(bbb.second + 1) - height - bonus.getHeight() / 2 - 78);
            nextWaypointY = max(nextWaypointY, get(bbb.second) + height + bonus.getHeight() / 2 + 78);
        }
        if (is32(path))
            tie(nextWaypointX, nextWaypointY) = make_pair(getCenter(path[2].first), getCenter(path[2].second));

        auto cars = world.getCars();
        sort(cars.begin(), cars.end(), [&self](const Car& aaa, const Car& bbb) { return self.getDistanceTo(aaa) < self.getDistanceTo(bbb);});
        for (Car car : world.getCars())
            if (!car.isFinishedTrack() && !car.isTeammate())
                if (hypot(car.getSpeedX(), car.getSpeedY()) * 1.2 < speedModule || fabs(car.getAngleTo(self)) < PI / 2 || speedModule < 10 && world.getTick() > 300)
                {
                    pair<int, int> ccc = {car.getX() / tileSize, car.getY() / tileSize};
                    pair<int, int> qwerty = {ti, tj};
                    int index = 0;
                    for (auto point : path)
                    {
                        if (point == qwerty)
                            break;
                        if (point == ccc && index + 1 < int(path.size()) && (self.getDistanceTo(car) > tileSize || speedModule < 10))
                        {
                            if (isHorizontal(point, path[index + 1]))
                            {
                                if (targetX <= self.getX() && self.getX() <= car.getX() || targetX >= self.getX() && self.getX() >= car.getX())
                                    continue;
                                double lower = get(ccc.second) + 80 + height + 15;
                                double lower2 = car.getY() - height - 15 - car.getWidth();
                                double upper = get(ccc.second + 1) - 80 - height - 15;
                                double upper2 = car.getY() + height + 15 + car.getWidth();
                                double cgy = car.getY();
                                double dist1 = self.getDistanceTo(car.getX(), lower) + hypot(nextWaypointX - car.getX(), nextWaypointY - lower);
                                double dist2 = self.getDistanceTo(car.getX(), lower2) + hypot(nextWaypointX - car.getX(), nextWaypointY - lower2);
                                double dist3 = self.getDistanceTo(car.getX(), upper) + hypot(nextWaypointX - car.getX(), nextWaypointY - upper);
                                double dist4 = self.getDistanceTo(car.getX(), upper2) + hypot(nextWaypointX - car.getX(), nextWaypointY - upper2);
                                nextWaypointX = car.getX();
                                nextWaypointY = (cgy - lower > upper - cgy) ? (dist1 < dist2 ? lower : lower2) : (dist3 < dist4 ? upper : upper2);
                            }
                            if (isVertical(point, path[index + 1]))
                            {
                                if (targetY <= self.getY() && self.getY() <= car.getY() || targetY >= self.getY() && self.getY() >= car.getY())
                                    continue;
                                double lower = get(ccc.first) + 80 + height + 15;
                                double lower2 = car.getX() - height - 15 - car.getWidth();
                                double upper = get(ccc.first + 1) - 80 - height - 15;
                                double upper2 = car.getX() + height + 15 + car.getWidth();
                                double cgy = car.getX();
                                double dist1 = self.getDistanceTo(car.getY(), lower) + hypot(nextWaypointY - car.getY(), nextWaypointX - lower);
                                double dist2 = self.getDistanceTo(car.getY(), lower2) + hypot(nextWaypointY - car.getY(), nextWaypointX - lower2);
                                double dist3 = self.getDistanceTo(car.getY(), upper) + hypot(nextWaypointY - car.getY(), nextWaypointX - upper);
                                double dist4 = self.getDistanceTo(car.getY(), upper2) + hypot(nextWaypointY - car.getY(), nextWaypointX - upper2);
                                nextWaypointY = car.getY();
                                nextWaypointX = (cgy - lower > upper - cgy) ? (dist1 < dist2 ? lower : lower2) : (dist3 < dist4 ? upper : upper2);
                            }
                            break;
                        }
                        ++index;
                    }

                }
        auto os = world.getOilSlicks();
        sort(os.begin(), os.end(), [&self](const OilSlick& aaa, const OilSlick& bbb) { return self.getDistanceTo(aaa) < self.getDistanceTo(bbb);});
        for (auto o : os)
        {
            pair<int, int> ccc = {o.getX() / tileSize, o.getY() / tileSize};
            pair<int, int> qwerty = {ti, tj};
            int index = 0;
            for (auto point : path)
            {
                if (point == qwerty)
                    break;
                if (point == ccc && index + 1 < int(path.size()) && self.getDistanceTo(o) > tileSize && self.getDistanceTo(o) < self.getDistanceTo(nextWaypointX, nextWaypointY))
                {
                    if (isHorizontal(point, path[index + 1]))
                    {
                        if (targetX <= self.getX() && self.getX() <= o.getX() || targetX >= self.getX() && self.getX() >= o.getX())
                            continue;
                        double lower = get(ccc.second) + 80 + height + 15;
                        double lower2 = o.getY() - height - 15 - o.getRadius();
                        double upper = get(ccc.second + 1) - 80 - height - 15;
                        double upper2 = o.getY() + height + 15 + o.getRadius();
                        double cgy = o.getY();
                        double dist1 = self.getDistanceTo(o.getX(), lower) + hypot(nextWaypointX - o.getX(), nextWaypointY - lower);
                        double dist2 = self.getDistanceTo(o.getX(), lower2) + hypot(nextWaypointX - o.getX(), nextWaypointY - lower2);
                        double dist3 = self.getDistanceTo(o.getX(), upper) + hypot(nextWaypointX - o.getX(), nextWaypointY - upper);
                        double dist4 = self.getDistanceTo(o.getX(), upper2) + hypot(nextWaypointX - o.getX(), nextWaypointY - upper2);
                        nextWaypointX = o.getX();
                        nextWaypointY = (cgy - lower > upper - cgy) ? (dist1 < dist2 ? lower : lower2) : (dist3 < dist4 ? upper : upper2);
                    }
                    if (isVertical(point, path[index + 1]))
                    {
                        if (targetY <= self.getY() && self.getY() <= o.getY() || targetY >= self.getY() && self.getY() >= o.getY())
                            continue;
                        double lower = get(ccc.first) + 80 + height + 15;
                        double lower2 = o.getX() - height - 15 - o.getRadius();
                        double upper = get(ccc.first + 1) - 80 - height - 15;
                        double upper2 = o.getX() + height + 15 + o.getRadius();
                        double cgy = o.getX();
                        double dist1 = self.getDistanceTo(o.getY(), lower) + hypot(nextWaypointY - o.getY(), nextWaypointX - lower);
                        double dist2 = self.getDistanceTo(o.getY(), lower2) + hypot(nextWaypointY - o.getY(), nextWaypointX - lower2);
                        double dist3 = self.getDistanceTo(o.getY(), upper) + hypot(nextWaypointY - o.getY(), nextWaypointX - upper);
                        double dist4 = self.getDistanceTo(o.getY(), upper2) + hypot(nextWaypointY - o.getY(), nextWaypointX - upper2);
                        nextWaypointY = o.getY();
                        nextWaypointX = (cgy - lower > upper - cgy) ? (dist1 < dist2 ? lower : lower2) : (dist3 < dist4 ? upper : upper2);
                    }
                    break;
                }
                ++index;
            }

        }

        double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
        //double check = self.getAngleTo(getCenter(ti), getCenter(tj));
        //if ((fabs(check - PI) < PI / 6 || fabs(check + PI) < PI / 6) && planB == 0)
            //planB = PLANB,
            //power *= -1;
        //if (fabs(check) < PI / 3 && planB)
            //power *= -1,
            //planB = 0;
        auto getTurn = [&](double d)
        {
            return angleToWaypoint * d * pow(DIST_TO_NEXT / distToNext, 0.8) / PI;
        };
        if (forceBack)
        {
            forceBack--;
            if (forceBack == 0)
            {
                power *= -1;
                forceRight = FORCE_RIGHT;
                turn *= -1;
            }
        }

        else if (forceRight)
        {
            if (forceRight > FORCE_RIGHT - BREAK)
                move.setBrake(true);
            forceRight--;
            if (forceRight == 0)
                force = FORCE;
        } 
        if (forceBack == 0 && forceRight == 0)
        {
            if (changed && fabs(prevDistance - distToNext) < eps)
            {
                countOfFails++;
                {
                    if (countOfFails > COUNT_OF_FAILS)
                    {
                        globalFail++;
                        countOfFails = 0;
                        //if (planB)
                            //planB = 0,
                            //power *= -1,
                            //forceRight = FORCE_RIGHT;
                        //else
                            forceBack = FORCE_BACK;
                        turn = getTurn(32);
                        if (isCorner(a[si][sj]))
                        {
                            //cout << "CORNER";
                            turn = turn > 0 ? 1 : -1;
                            if (globalFail > GLOBAL_FAIL)
                                //cout << "GLOBAL_FAIL",
                                turn *= -1;
                        }
                        else
                            if (globalFail > GLOBAL_FAIL)
                                //cout << "NOT CORNER GLOBAL_FAIL",
                                turn = turn > 0 ? 1 : -1;
                        turn *= -1;
                        power *= -1;
                    }
                }
                //else
                    //if (countOfFails > COUNT_OF_FAILS / 5)
                    //{
                        //forceRight = 0;
                        //force = 0;
                        //countOfFails = COUNT_OF_FAILS;
                    //}
            }
            else
            {
                if (force)
                    force--;
                forceSlow = path.size() <= 4 ? 14 : 100;
                if (is4(path))
                    forceSlow *= 1.5;
                countOfFails = 0;
                globalFail = 0;

                if (forceRight == 0)
                    turn = getTurn(36);
                double dd = speedModule / MAX_SPEED;
                if (is32(path))
                    dd *= 1.3;
                if (is3_2(path))
                    dd /= 2;
                if (is212(path))
                    dd /= 2;
                if (is41(path))
                    dd *= 1.2;
                bool fas = is131(path) && speedModule > 16.5;
                //cout << si << " " << sj << " " << badX << " " << badY << "\n";
                if ((!snake && distToNext < tileSize * dd && distToNext > tileSize && bad.find(S) == bad.end()) || speedModule > forceSlow || (bad.find(S) != bad.end() && speedModule > 11) || fas)
                    move.setBrake(true);
            }
        }
        cout << "END OF MOVE\n";
        cout.flush();
        //else
            //if (changed && fabs(prevDistance - distToNext) < eps)
            //{
                //countOfFails++;
                //if (countOfFails > COUNT_OF_FAILS / 3)
                    //forceRight = FORCE_RIGHT;
            //}
            //else
                //countOfFails = 0;
        if (forceRight == 0 && forceBack == 0 && planB)
        {
            if (angleToWaypoint > 0)
                angleToWaypoint = PI - angleToWaypoint;
            else
                angleToWaypoint = -PI + angleToWaypoint;
            turn = getTurn(32);
            cout << "PLANB\n";
        }
        move.setWheelTurn(turn);
        move.setEnginePower(power);
        for (auto car : world.getCars())
            if (!car.isTeammate())
            {
                if (world.getTick() > 250 && self.getDistanceTo(car) <= tileSize * 2)
                {
                    if (fabs(self.getAngleTo(car)) < ANGLE_THROW && car.getDurability() > 0 && !car.isFinishedTrack())
                        move.setThrowProjectile(true);
                }
                if (self.getDistanceTo(car) <= tileSize * 6 && isCorner(a[si][sj]) && planB == 0)
                    move.setSpillOil(true);
            }
        //if (world.getTick() > 210 && distToNext > prevDistance)
        //{
            //forceSlow = FORCE_SLOW_DOWN;
            //if (distToNext > tileSize * 5)
                //forceSlow /= 2;
        //}
        bool okSnake = false;
        if (snake && path.size() >= 2)
        {
            int count = 0;
            vector<int> fff = {
                directions[make_pair(path[0].first - path[1].first, path[0].second - path[1].second)],
                directions[make_pair(path[1].first - path[2].first, path[1].second - path[2].second)]
            };
            for (int i = 2; i < path.size(); ++i)
                if (directions[make_pair(path[i].first - path[i + 1].first, path[i].second - path[i + 1].second)] == fff[i % 2])
                    count++;
                else
                    break;
            cout << count << "\n";
            okSnake = count >= 9;
        }
        if (forceRight == 0 && forceBack == 0 && world.getTick() > 195 && (distToNext > tileSize * 5 || (okSnake && bad.find(S) == bad.end() && speedModule > 20)) && planB == 0)
            move.setUseNitro(true);
#ifdef vis
        cout << "VISUALIZATION\n";
        cout.flush();
        for (int i = 0; i < a.size(); ++i)
            for (int j = 0; j < a[0].size(); ++j)
                if (a[i][j] == UNKNOWN)
                    visual.fillRect(get(i), get(j), get(i + 1), get(j + 1), 0xCC0000);
                else if (visited[i][j])
                    visual.fillRect(get(i), get(j), get(i + 1), get(j + 1), 0x008800);
        for (auto p : wp)
            visual.fillRect(get(p[0]), get(p[1]), get(p[0] + 1), get(p[1] + 1), 0x0000CC);

        visual.fillRect(get(ti), get(tj), get(ti + 1), get(tj + 1), 0x008888);
        visual.endPre();
        visual.beginPost();
        visual.circle(getCenter(ti), getCenter(tj), 600, 0x54618f);
        visual.line(self.getX(), self.getY(), nextWaypointX, nextWaypointY);
        char sss[45];
        sprintf(sss, "%d %d  s:%.2f  a:%.2f  t:%.2f", pd, d, speedModule, angleToWaypoint, turn);
        visual.text(self.getX() + 120, self.getY() + 120, sss);
        sss[44] = 0;
        //char qqq[35];
        //int ttt = 0;
        //for (auto ee : bad)
            //ttt += sprintf(qqq + ttt, "%d %d, ", ee.first, ee.second);
        //for (int i = 0; i < 35; ++i)
            //qqq[i] = ' ';
        //qqq[34] = 0;
        //visual.text(self.getX() + 120, self.getY() + 200, qqq);
        for (int i = 1; i < min(10, int(path.size())); ++i)
            visual.line(getCenter(path[i - 1].first), getCenter(path[i - 1].second), getCenter(path[i].first), getCenter(path[i].second), 0xff0000);
        visual.line(getCenter(pi), getCenter(pj), getCenter(ti), getCenter(tj), 0x00ff00);
        visual.line(getCenter(ti), getCenter(tj), getCenter(fi), getCenter(fj), 0x00ff00);
        visual.fillCircle(getCenter(ti), getCenter(tj), 10);
        visual.endPost();
#endif
        cout << "END OF MOVE\n";
        cout.flush();
    }
}

MyStrategy::MyStrategy() 
{
    directions[make_pair(1, 0)] = RIGHT;
    directions[make_pair(-1, 0)] = LEFT;
    directions[make_pair(0, 1)] = DOWN;
    directions[make_pair(0, -1)] = UP;
#define rht RIGHT_HEADED_T
#define lht LEFT_HEADED_T
#define tht TOP_HEADED_T 
#define bht BOTTOM_HEADED_T
#define cr CROSSROADS
    dir[VERTICAL][UP] = dir[VERTICAL][DOWN] = true;
    dir[HORIZONTAL][LEFT] = dir[HORIZONTAL][RIGHT] = true;

    dir[LEFT_TOP_CORNER][RIGHT] = dir[LEFT_TOP_CORNER][DOWN] = true;
    dir[RIGHT_TOP_CORNER][LEFT] = dir[RIGHT_TOP_CORNER][DOWN] = true;
    dir[LEFT_BOTTOM_CORNER][RIGHT] = dir[LEFT_BOTTOM_CORNER][UP] = true;
    dir[RIGHT_BOTTOM_CORNER][LEFT] = dir[RIGHT_BOTTOM_CORNER][UP] = true;

    dir[rht][UP] = dir[rht][DOWN] = dir[rht][RIGHT] = true;
    dir[lht][DOWN] = dir[lht][UP] = dir[lht][LEFT] = true;
    dir[bht][DOWN] = dir[bht][LEFT] = dir[bht][RIGHT] = true;
    dir[tht][UP] = dir[tht][LEFT] = dir[tht][RIGHT] = true;

    dir[cr][DOWN] = dir[cr][UP] = dir[cr][LEFT] = dir[cr][RIGHT] = true;
    freopen("lol", "w", stdout);
#ifdef debug
    writeln(FUUUUU);
#endif
}

//interpolate({0.5, 0.4}, {0.65, 0.365}, {0.85, 1/3}, {1.2, 0.2}, {1.4142135624, 0}, {1.66666, -1/8}, {2, -1/4}, {2.5, -1/3}, {3, -0.365}, {3.5, -0.365}, {3.25, -0.365})
