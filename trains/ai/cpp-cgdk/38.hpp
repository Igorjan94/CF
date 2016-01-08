#include "MyStrategy.h"

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES
#define go(p, a, b) { if (p) goto a; else goto b; }

#include <bits/stdc++.h>
//#ifdef ONLINE_JUDGE
//#define debug 1
//#endif
#ifdef debug
#undef debug
#endif
//#include "library.h"
//#endif

using namespace model;
using namespace std;

double DIST_TO_NEXT = 750;
int COUNT_OF_FAILS = 90;
int FORCE_BACK = 130;
int FORCE_RIGHT = 60;
int FORCE = 100;
int BREAK = 30;
double MAX_SPEED = 17;
int FORCE_SLOW_DOWN = 1;
int GLOBAL_FAIL = 2;
double ANGLE_THROW = PI / 30;

bool changed = false;
double eps = 5;
double power = 0.85;
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
double tileSize = 0.0;
int dir[15][4];
vector<vector<TileType>> TEMP;
bool init = true;
bool snake = false;
bool drift = false;
double width;
double height;
int d = 0;
int pd = 0;
set<pair<int, int>> bad;
vector<pair<int, int>> old;

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

vector<int> ddx = {1, 0, -1, 0};
vector<int> ddy = {0, -1, 0, 1};
map<pair<int, int>, int> directions;

vector<vector<vector<int>>> FUUUUU = {
/*0 сначала шли вправо*/
    {
        //->
        {
            RIGHT, UP, DOWN, LEFT
        },
        //^
        {
            UP, RIGHT, LEFT, DOWN
        },
        //<-
        {
            LEFT, UP, DOWN, RIGHT
        },
        //V
        {
            DOWN, RIGHT, LEFT, UP
        }
    },
/*1 сначала шли вверх*/ 
    {
        //->
        {
            RIGHT, UP, DOWN, LEFT
        },
        //^
        {
            UP, LEFT, RIGHT, DOWN
        },
        //<-
        {
            LEFT, UP, DOWN, RIGHT
        },
        //V
        {
            DOWN, LEFT, RIGHT, UP
        }
    },
/*2 сначала шли влево*/ 
    {
        //->
        {
            RIGHT, UP, DOWN, LEFT
        },
        //^
        {
            UP, LEFT, RIGHT, DOWN
        },
        //<-
        {
            LEFT, UP, DOWN, RIGHT
        },
        //V
        {
            DOWN, LEFT, RIGHT, UP
        }
    },
/*3 сначала шли вниз*/ 
    {
        //->
        {
            RIGHT, DOWN, UP, LEFT
        },
        //^
        {
            UP, RIGHT, LEFT, DOWN
        },
        //<-
        {
            LEFT, DOWN, UP, RIGHT
        },
        //V
        {
            DOWN, RIGHT, LEFT, UP
        }
    }
};

struct vertex
{
    int x, y, d, pd; 
    vertex(){} 
    vertex(int x, int y, int pd, int d) : x(x), y(y), d(d), pd(pd) {}
};

template <typename T>
void ppp(vector<vector<T>> a)
{
    int n = a.size();
    int m = a[0].size();
    for (int j = 0; j < m; ++j)
        for (int i = 0; i < n; ++i)
            printf("%6d%c", a[i][j], "\n "[i != n - 1]);
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
    return (xxx + 0.75) * tileSize;
}

double get14(double xxx)
{
    return (xxx + 0.25) * tileSize;
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

pair<int, int> getXX(pair<int, int>& a, pair<int, int>& b)
{
    if (isVertical(a, b))
        return make_pair(getCenter(a.first), get(max(a.second, b.second)));
    else
        return make_pair(get(max(a.first, b.first)), getCenter(a.second));
}

pair<int, int> getCorner(pair<int, int>& a, pair<int, int>& b)
{
    if (isVertical(a, b))
        return make_pair(get14(a.first), a.second > b.second ? get14(a.second) : get34(a.second));
    else
        return make_pair(get14(a.first), get14(a.second));
}

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
    int countOfMyCars = 0;
    for (auto car : world.getCars())
        countOfMyCars += car.isTeammate();
    if (countOfMyCars == 2)
        return;
    if (init)
    {
        init = false;
        ppp(world.getTilesXY());
        TEMP = world.getTilesXY();
        width = self.getWidth() / 2;
        height = self.getHeight() / 2;
#ifdef debug
        writeln(world.getWaypoints());
#endif
        srand(game.getRandomSeed());
    }
    pd = d;
    int qx = self.getX() / tileSize;
    int qy = self.getY() / tileSize;
    if (old.size())
    {
        int wx, wy;
        tie(wx, wy) = old.back();
        if (wx != qx || wy != qy)
            d = directions[make_pair(qx - wx, qy - wy)];
    }
    old.push_back({qx, qy});

    tileSize = game.getTrackTileSize();
    auto a = world.getTilesXY();
    prevx = currx;
    if (prevx == -1234)
        prevx = self.getX();
    currx = self.getX();
    if (currx - prevx != 0)
        changed = true;
    int ti = self.getNextWaypointX();
    int tj = self.getNextWaypointY();
    auto wp = world.getWaypoints();
    wp.push_back(wp[0]);
    int waypointIndex = self.getNextWaypointIndex();
    int fi, fj, pi, pj;
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
        if (bad.find({si, sj}) == bad.end())
            bad.clear();
        int n = a.size();
        int m = a[0].size();
        auto ok = [&](int x, int N)
        {
            return x >= 0 && x < N;
        };

    auto getPath = [&](int si, int sj, int ti, int tj, int pd, int dd)
    {
#ifdef debug
        writeln("GET");
#endif
        queue<vertex> q;
        q.push(vertex(si, sj, pd, dd));
        vector<vector<int>> d(n, vector<int>(m, 10000));
        vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(m));
        d[si][sj] = 0;
        while (q.size())
        {
            int u = q.front().x;
            int v = q.front().y;
            int prevD = q.front().d;
            int prevprevD = q.front().pd;
            q.pop();
            if (a[u][v] == UNKNOWN)
                continue;
            vector<int> dx;
            vector<int> dy;
            for (int i = 0; i < 4; ++i)
                dx.push_back(ddx[FUUUUU[prevprevD][prevD][i]]),
                dy.push_back(ddy[FUUUUU[prevprevD][prevD][i]]);
            if (u == ti && v == tj)
            {
                vector<pair<int, int>> path;
                pair<int, int> start = {si, sj};
                while (u != start.first || v != start.second)
                    path.push_back({u, v}),
                    tie(u, v) = prev[u][v];
                path.push_back(start);
                reverse(path.begin(), path.end());
                return path;
            }
            for (int i = 0; i < 4; ++i)
            {
                auto iAmIdiot = directions[make_pair(dx[i], dy[i])];
                if (ok(u + dx[i], n) && ok(v + dy[i], m) && a[u][v] != UNKNOWN && dir[a[u][v]][iAmIdiot] && (dx[i] != 0 || dy[i] != 0))
                    if (d[u + dx[i]][v + dy[i]] == 10000)
                        d[u + dx[i]][v + dy[i]] = d[u][v] + 1,
                        prev[u + dx[i]][v + dy[i]] = {u, v},
                        q.push(vertex(u + dx[i], v + dy[i], prevD, iAmIdiot));
            }
        }
        return vector<pair<int, int>>(0);
    };
    vector<pair<int, int>> path = getPath(si, sj, ti, tj, pd, d);
    int ai, aj, bi, bj, ci, cj, di, dj;
    while (waypointIndex + 1 < int(wp.size()))
    {
        int t = 0;
        int y = 0;
        auto zxcv = path.back();
        auto asdf = path.back();
        auto qwer = path.back();
        if (path.size() >= 2)
            zxcv = path[path.size() - 2],
            asdf = path[path.size() - 2];
        if (path.size() >= 3)
            zxcv = path[path.size() - 3];
        t = directions[make_pair(asdf.first - zxcv.first, asdf.second - zxcv.second)];
        y = directions[make_pair(qwer.first - asdf.first, qwer.second - asdf.second)];
        path.pop_back();
        int q = wp[waypointIndex][0];
        int w = wp[waypointIndex][1];
        int e = wp[waypointIndex + 1][0];
        int r = wp[waypointIndex + 1][1];
        auto temp = getPath(q, w, e, r, t, y);
        if (temp.size() == 0)
            break;
        for (auto x : temp)
            path.push_back(x);
        waypointIndex++;
    }
    for (int i = 1; i < int(path.size()); ++i)
        if (path[i] == path[i - 1])
            path.erase(path.begin() + --i);
    auto checkBonus = path;
    for (int i = 1; i < int(path.size()) - 1; ++i)
        if (abs(path[i + 1].first - path[i - 1].first) == 1 && abs(path[i + 1].second - path[i - 1].second) == 1)
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
                writeln();
                writeln(xxx);
                writeln();
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

        // cd
        //ab
        if ((ai + 1 == ci && aj - 1 == cj && bi + 1 == di && bj - 1 == dj)
        || (ai - 1 == ci && aj + 1 == cj && bi - 1 == di && bj + 1 == dj)
        || (ai + 1 == ci && aj + 1 == cj && bi + 1 == di && bj + 1 == dj)
        || (ai - 1 == ci && aj - 1 == cj && bi - 1 == di && bj - 1 == dj))
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
                bad.insert(path[0]);
                bad.insert(path[2]);
                //if (self.getDistanceTo(getCenter(path[1].first), getCenter(path[1].second)) < tileSize)
                tie(targetX, targetY) = getXX(path[1], path[2]);
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
        MAAAAAGIC = 0.3;
    double nextWaypointX = targetX;
    double nextWaypointY = targetY;

    double cornerTileOffset = MAAAAAGIC * tileSize;
    for (int i = 1; i < int(path.size()) - 1; ++i)
        if (path[i].first == ti && path[i].second == tj)
        {
            pi = path[i - 1].first;
            pj = path[i - 1].second;
            fi = path[i + 1].first;
            fj = path[i + 1].second;
            break;
        }
    //auto pathtitj = getPath(ti, tj, fi, fj);
    //if (pathtitj.size() >= 2)
        //fi = pathtitj[1].first,
        //fj = pathtitj[1].second;
    //else
        //fi = ti,
        //fj = tj;
#ifdef debug
    wr(si, sj, pi, pj, ti, tj, fi, fj);
    //writeln(pathtitj);
    //writeln();
#endif
    auto changeCoords = [&](int i, int j) {
        if (snake || drift)
            return;
        if (pj == tj)
            swap(pi, fi),
            swap(pj, fj);
        switch (TEMP[i][j]) 
        {
            case LEFT_TOP_CORNER:
lt:
                TEMP[i][j] = LEFT_TOP_CORNER;
                nextWaypointX += cornerTileOffset;
                nextWaypointY += cornerTileOffset;
                break;
            case RIGHT_TOP_CORNER:
rt:
                TEMP[i][j] = RIGHT_TOP_CORNER;
                nextWaypointX -= cornerTileOffset;
                nextWaypointY += cornerTileOffset;
                break;
            case LEFT_BOTTOM_CORNER:
lb:
                TEMP[i][j] = LEFT_BOTTOM_CORNER;
                nextWaypointX += cornerTileOffset;
                nextWaypointY -= cornerTileOffset;
                break;
            case RIGHT_BOTTOM_CORNER:
rb:
                TEMP[i][j] = RIGHT_BOTTOM_CORNER;
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
        //ppp(TEMP);
        //cout << "\n";
    };
    changeCoords(ti, tj);
    bool B = false;
    double bonusMin = 1000000;
    Bonus bonus;
    if (!snake && self.getRemainingNitroTicks() == 0 && !drift)
        for (Bonus b : world.getBonuses())
            if (self.getDistanceTo(b) < distToNext)
                if ((b.getDistanceTo(targetX, targetY) > tileSize * 2 && fabs(self.getAngleTo(b)) < PI / 27) && fabs(self.getAngleTo(targetX, targetY) < PI / 36))
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
        nextWaypointX = min(nextWaypointX, get(bbb.first + 1) - width - bonus.getWidth() / 2 - 78);
        nextWaypointX = max(nextWaypointX, get(bbb.first) + width + bonus.getWidth() / 2 + 78);
        nextWaypointY = min(nextWaypointY, get(bbb.second + 1) - height - bonus.getHeight() / 2 - 78);
        nextWaypointY = max(nextWaypointY, get(bbb.second) + height + bonus.getHeight() / 2 + 78);
    }
    //if (is32(path) && path.size() >= 4)
        //tie(nextWaypointX, nextWaypointY) = getCorner(path[2], path[3]);
    //cout << targetX << " " << targetY << "\n";
    //cout << nextWaypointX << " " << nextWaypointY << "\n\n";

    double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
    double speedModule = hypot(self.getSpeedX(), self.getSpeedY());
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
    if (!forceBack && forceRight == 0)
    {
        if (changed && fabs(prevDistance - distToNext) < eps)
        {
            countOfFails++;
            {
                if (countOfFails > COUNT_OF_FAILS)
                {
                    globalFail++;
                    countOfFails = 0;
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
            if (forceSlow)
                forceSlow--;
            countOfFails = 0;
            globalFail = 0;

            if (forceRight == 0)
                turn = getTurn(36);
            double dd = speedModule / MAX_SPEED;
            if (is32(path))
                dd *= 1.72;
            //if (is3_2(path))
                //dd *= 1.6;
            if (is212(path))
                dd *= 2;
            if (is41(path))
                dd *= 1.5;
            //cout << si << " " << sj << " " << badX << " " << badY << "\n";
            if ((!snake && distToNext < tileSize * dd && distToNext > tileSize && bad.find({si, sj}) == bad.end()) || forceSlow || (bad.find({si, sj}) != bad.end() && speedModule > 8))
                move.setBrake(true);
            power = 1.0;
        }
    }
    //else
        //if (changed && fabs(prevDistance - distToNext) < eps)
        //{
            //countOfFails++;
            //if (countOfFails > COUNT_OF_FAILS / 3)
                //forceRight = FORCE_RIGHT;
        //}
        //else
            //countOfFails = 0;
    move.setWheelTurn(turn);
    move.setEnginePower(power);
    for (auto car : world.getCars())
        if (!car.isTeammate())
        {
            if (self.getDistanceTo(car) <= tileSize * 2)
            {
                if (fabs(self.getAngleTo(car)) < ANGLE_THROW && car.getDurability() > 0 && !car.isFinishedTrack())
                    move.setThrowProjectile(true);
            }
            if (self.getDistanceTo(car) <= tileSize * 6 && isCorner(a[si][sj]))
                //if (self.getAngleTo(car) + ANGLE_THROW * 3 > PI || self.getAngleTo(car) - ANGLE_THROW * 3 < -PI)
                    move.setSpillOil(true);
        }
    //if (world.getTick() > 210 && distToNext > prevDistance)
    //{
        //forceSlow = FORCE_SLOW_DOWN;
        //if (distToNext > tileSize * 5)
            //forceSlow /= 2;
    //}
    if (self.getRemainingOiledTicks() > 0)
        forceSlow = 0;
    if (world.getTick() > 210 && (distToNext > tileSize * 5 || snake) && world.getTick() >= 300)
        move.setUseNitro(true);
    int count = 0;
    for (auto car : world.getCars())
        count += car.getRemainingNitroTicks() > 100;
    if (world.getTick() <= game.getInitialFreezeDurationTicks() && count > 1 && world.getTick() >= 150)
        move.setUseNitro(true);
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