




//Не читайте этот код, у Вас вытекут глаза :(





//Объезжалочка
//Я умею говнокодить 2
//Это гениально и просто..... Зачем я писал столько кода
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
int COUNT_OF_FAILS = 60;
int FORCE_BACK = 120;
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

vector<double> power        = { 1,     1};
vector< bool > changed      = { false, false};
vector<double> distToNext   = {-10000,-10000};
vector<double> prevDistance = { 0,     0};
vector< int  > countOfFails = { 0,     0};
vector< int  > forceBack    = { 0,     0};
vector< int  > forceRight   = { 0,     0};
vector< int  > force        = { 0,     0};
vector< int  > prevx        = { 0,     0};
vector< int  > currx        = {-1234,  -1234};
vector< int  > forceSlow    = { 0,     0};
vector< int  > globalFail   = { 0,     0};
vector< int  > beforeTick   = { 555,   190};
vector<double> turn         = { 0.0,   0.0};
vector< bool > init         = { true,  true};
vector< bool > snake        = { false, false};
vector< bool > drift        = { false, false};
vector<double> width        = { 0,     0};
vector<double> height       = { 0,     0};
vector< int  > d            = { 0,     0};
vector< int  > pd           = { 0,     0};
vector< int  > planB        = { 0,     0};
vector<double> tickTargetX  = { 0.0,   0.0};
vector<double> tickTargetY  = { 0.0,   0.0};
vector< int  > tickTarget   = { 0,     0};
vector< int  > tickTargetI  = {-1,     -1};
vector< int  > tickTargetJ  = {-1,     -1};

vector<set<pair<int,int>>> bad;
vector<vector<pair<int,int>>> old;
vector<vector<vector<bool>>> once;

#define power        power[ct]
#define changed      changed[ct]
#define distToNext   distToNext[ct]
#define prevDistance prevDistance[ct]
#define countOfFails countOfFails[ct]
#define forceBack    forceBack[ct]
#define forceRight   forceRight[ct]
#define force        force[ct]
#define prevx        prevx[ct]
#define currx        currx[ct]
#define forceSlow    forceSlow[ct]
#define globalFail   globalFail[ct]
#define beforeTick   beforeTick[ct]
#define turn         turn[ct]
#define init         init[ct]
#define snake        snake[ct]
#define drift        drift[ct]
#define width        width[ct]
#define height       height[ct]
#define d            d[ct]
#define pd           pd[ct]
#define planB        planB[ct]
#define bad          bad[ct]
#define old          old[ct]
#define once         once[ct]
#define tickTarget   tickTarget[ct]
#define tickTargetX  tickTargetX[ct]
#define tickTargetY  tickTargetY[ct]
#define tickTargetI  tickTargetI[ct]
#define tickTargetJ  tickTargetJ[ct]

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

vector<int> ddx = {1, 0, -1, 0};
vector<int> ddy = {0, -1, 0, 1};
map<pair<int, int>, int> directions;

vector<vector<vector<int>>> goforward = { { { RIGHT, UP, DOWN, LEFT }, { RIGHT, UP, LEFT, DOWN }, { LEFT, UP, DOWN, RIGHT }, { RIGHT, DOWN, LEFT, UP } }, { { UP, RIGHT, DOWN, LEFT }, { UP, LEFT, RIGHT, DOWN }, { UP, LEFT, DOWN, RIGHT }, { DOWN, LEFT, RIGHT, UP } }, { { RIGHT, UP, DOWN, LEFT }, { LEFT, UP, RIGHT, DOWN }, { LEFT, UP, DOWN, RIGHT }, { LEFT, DOWN, RIGHT, UP } }, { { DOWN, RIGHT, UP, LEFT }, { UP, RIGHT, LEFT, DOWN }, { DOWN, LEFT, UP, RIGHT }, { DOWN, RIGHT, LEFT, UP } } };

vector<vector<vector<int>>> FUUUUU = { { { UP, DOWN, RIGHT, LEFT }, { RIGHT, UP, LEFT, DOWN }, { UP, DOWN, LEFT, RIGHT }, { RIGHT, DOWN, LEFT, UP } }, { { UP, RIGHT, DOWN, LEFT }, { LEFT, RIGHT, UP, DOWN }, { UP, LEFT, DOWN, RIGHT }, { LEFT, RIGHT, DOWN, UP } }, { { UP, DOWN, RIGHT, LEFT }, { LEFT, UP, RIGHT, DOWN }, { UP, DOWN, LEFT, RIGHT }, { LEFT, DOWN, RIGHT, UP } }, { { DOWN, RIGHT, UP, LEFT }, { RIGHT, LEFT, UP, DOWN }, { DOWN, LEFT, UP, RIGHT }, { RIGHT, LEFT, DOWN, UP } } }, FU;

int opposite(int x, int y) { return abs(x - y) == 2; }

struct vertex
{
    int x, y, qd, qpd, hasBonus;
    vertex(){}
    vertex(int x, int y, int pdd, int ddd, int hb) : x(x), y(y), qd(ddd), qpd(pdd), hasBonus(hb) {}
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

bool isCorner(TileType a) { return !(a == VERTICAL || a == HORIZONTAL || a == CROSSROADS); }

double getCenter(double xxx) { return (xxx + 0.5) * tileSize; }

double get(double xxx) { return xxx * tileSize; }

double get34(double xxx) { return (xxx + 0.9) * tileSize; }

double get14(double xxx) { return (xxx + 0.1) * tileSize; }

bool isVertical(pair<int, int> a, pair<int, int> b) { return a.first == b.first; }

bool isHorizontal(pair<int, int> a, pair<int, int> b) { return a.second == b.second; }

bool is32(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return ( isHorizontal(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isHorizontal(a[3], a[4]) &&
                !isVertical(a[1], a[4]))
            || ( isVertical(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isVertical(a[3], a[4]) &&
                !isHorizontal(a[1], a[4])); else
        return false;
}

bool is3_2(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return ( isHorizontal(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isVertical(a[1], a[4]) &&
                isHorizontal(a[3], a[4]))
            || ( isVertical(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isHorizontal(a[1], a[4]) &&
                isVertical(a[3], a[4])); else
        return false;
}

bool is212(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return ( isHorizontal(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isVertical(a[3], a[4]) &&
                isHorizontal(a[1], a[4]))
            || ( isVertical(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isHorizontal(a[3], a[4]) &&
                isVertical(a[1], a[4])); else
        return false;
}

bool is41(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return ( isHorizontal(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isVertical(a[3], a[4]))
            || ( isVertical(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isHorizontal(a[3], a[4])); else
        return false;
}

bool is4(vector<pair<int, int>>& a)
{
    if (a.size() >= 4)
        return ( isHorizontal(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isHorizontal(a[2], a[3]))
            || ( isVertical(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isVertical(a[2], a[3])); else
        return false;
}

bool is131(vector<pair<int, int>>& a)
{
    if (a.size() >= 5)
        return ( isVertical(a[0], a[1]) &&
                isHorizontal(a[1], a[2]) &&
                isHorizontal(a[2], a[3]) &&
                isVertical(a[3], a[4]))
            || ( isHorizontal(a[0], a[1]) &&
                isVertical(a[1], a[2]) &&
                isVertical(a[2], a[3]) &&
                isHorizontal(a[3], a[4])); else
        return false;
}

pair<int, int> getXX(pair<int, int>& a, pair<int, int>& b) {
    if (isVertical(a, b))
        return make_pair(getCenter(a.first), get(max(a.second, b.second)));
    else
        return make_pair(get(max(a.first, b.first)), getCenter(a.second)); }

double get(double x, double v) { return (x + v) * tileSize; }

pair<int, int> getCorner(pair<int, int>& a, pair<int, int>& b, pair<int, int>& c)
{
    double xxx = 0.35;
    if (isVertical(a, b))
        return make_pair(get(max(b.first, c.first)), get(b.second, a.second < b.second ? xxx : 1 - xxx));
    else
        return make_pair(get(b.first, a.first < b.first ? xxx : 1 - xxx), get(max(b.second, c.second)));
}

int opposite(int x) { switch (x) { case LEFT: case RIGHT: return 2 - x; default: return 4 - x; } }

bool isRightTo(pair<int, int> a, pair<int, int> b) { return a.first - 1 == b.first && a.second == b.second; }

bool isLeftTo(pair<int, int> a, pair<int, int> b) { return a.first + 1 == b.first && a.second == b.second; }

bool isUpTo(pair<int, int> a, pair<int, int> b) { return a.first == b.first && a.second + 1 == b.second; }

bool isDownTo(pair<int, int> a, pair<int, int> b) { return a.first == b.first && a.second - 1 == b.second; }

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
        return LEFT;
    return -1;
}

pair<int, int> getNextTurn(vector<pair<int, int>> path, int index = 0)
{
    for (int i = index + 1; i < int(path.size()) - 1; ++i)
        if ((abs(path[i + 1].first - path[i - 1].first) == 1 && abs(path[i + 1].second - path[i - 1].second) == 1) || path[i - 1] == path[i + 1])
            return path[i];
    return path.back();
}

pair<int, int> reflect(pair<int, int> a, pair<int, int> b)
{
    return isHorizontal(a, b) ? make_pair(a.first < b.first ? b.first + 1 : b.first - 1, b.second) : make_pair(b.first, a.second < b.second ? b.second + 1 : b.second - 1);
}

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
    CarType ct = self.getType();
    bool badMap = true;//world.getMapName() == "map07" || world.getMapName() == "map08" || world.getMapName() == "map14";
    cout << (self.getType() == BUGGY ? "BUGGY\n" : "JEEP\n");
    cout.flush();
    {
        tileSize = game.getTrackTileSize();
        auto a = world.getTilesXY();
        for (int i = 0; i < a.size(); ++i)
            for (int j = 0; j < a[0].size(); ++j)
                if (a[i][j] == UNKNOWN)
                    a[i][j] = CROSSROADS;
        if (init)
        {
            FU = goforward;

            if (world.getMapName() == "map07")// || world.getMapName() == "map08")// || world.getMapName() == "map14")
                FUUUUU = goforward;
            old.push_back({self.getX() / tileSize, self.getY() / tileSize});

            init = false;
            width = self.getWidth() / 2;
            height = self.getHeight() / 2;
            once.resize(a.size());
            for (int i = 0; i < once.size(); ++i)
                once[i].resize(a[0].size(), false);
            d = getDirectionByAngle(self.getAngle());
            pd = d;
            srand(game.getRandomSeed());
        }
        int waypointIndex = self.getNextWaypointIndex();
        int qx = self.getX() / tileSize;
        int qy = self.getY() / tileSize;
        int wx, wy;
        tie(wx, wy) = old.back();
        if ((wx != qx || wy != qy) && forceBack == 0)
        {
            old[0] = {qx, qy};
            pd = d;
            d = directions[make_pair(qx - wx, qy - wy)];
            //if (forceBack)
                //d = opposite(d);
            if (pd != d && a[self.getNextWaypointX()][self.getNextWaypointY()] != UNKNOWN && waypointIndex != 0)
                FU = FUUUUU;
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
        double targetX = getCenter(ti);
        double targetY = getCenter(tj);
        int si = self.getX() / tileSize;
        int sj = self.getY() / tileSize;
        pair<int, int> S = make_pair(si, sj);
        vector<int> qwerqsdfgsdf = {si, sj};
        if (wp[max(0, self.getNextWaypointIndex() - 1)] == qwerqsdfgsdf && !once[si][sj])
            once[si][sj] = true;
        if (bad.find(S) == bad.end())
            bad.clear();
        int n = a.size();
        int m = a[0].size();
        auto ok = [&](int x, int N)
        {
            return x >= 0 && x < N;
        };

        auto getPath = [&](int si, int sj, int tti, int ttj, int pdd, int dd, vector<vector<vector<int>>> FUUUUU, int countBonuses = 1)
        {
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
            auto bfs = [&](int si, int sj, int tti, int ttj, int pdd, int dd, vector<vector<vector<int>>> FUUUUUF)
            {
                queue<vertex> q;
                q.push(vertex(si, sj, pdd, dd, 0));
                vector<vector<int>> dist(n, vector<int>(m, 10000));
                vector<vector<vector<int>>> FUUUUU;
                vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(m));
                dist[si][sj] = 0;
                int u, v, prevD, prevprevD;
                while (q.size())
                {
                    u = q.front().x;
                    v = q.front().y;
                    prevD = q.front().qd;
                    prevprevD = q.front().qpd;
                    int hasBonus = 0;
                    for (Bonus bonus : world.getBonuses())
                        if ((bonus.getType() == PURE_SCORE || (bonus.getType() == REPAIR_KIT && self.getDurability() < 20)) && int(bonus.getX() / tileSize) == u && int(bonus.getY() / tileSize) == v
                                && fabs(bonus.getX() - getCenter(bonus.getX() / tileSize) < 0.3 * tileSize)
                                && fabs(bonus.getY() - getCenter(bonus.getY() / tileSize) < 0.3 * tileSize))
                            hasBonus++;
                    if (countBonuses == 0)
                        hasBonus = 0;
                    FUUUUU = hasBonus ? goforward : FUUUUUF;
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
                            int temp = dist[u][v] + 1 + isShpilka * 3 + isReverse * 12 - hasBonus;
                            if (dist[u + dx[i]][v + dy[i]] > temp)
                            {
                                dist[u + dx[i]][v + dy[i]] = temp;
                                prev[u + dx[i]][v + dy[i]] = {u, v};
                                q.push(vertex(u + dx[i], v + dy[i], prevD, iAmIdiot, hasBonus));
                            }
                        }
                    }
                }
                return make_pair(d, prev);
            };
            auto qqwerwer = bfs(si, sj, tti, ttj, pdd, dd, FUUUUU);
            int u, v;
            u = tti;
            v = ttj;
            auto prev = qqwerwer.second;
            auto path = fffpath(si, sj, u, v, prev);
            return path;
        };
        vector<pair<int, int>> path;
        int qqq = ti;
        int www = tj;
        path = getPath(si, sj, ti, tj, pd, d, FU);
        tie(ti, tj) = getNextTurn(path);
        targetX = getCenter(ti);
        targetY = getCenter(tj);
        if (fabs(self.getAngleTo(targetX, targetY)) > PI / 3 && forceBack == 0 && forceRight == 0 && planB == 0)
            path = getPath(si, sj, qqq, www, pd, d, goforward, 0);

        for (int i = 0; i + 4 < min(8, int(path.size())); ++i)
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
        int ai, aj, bi, bj, ci, cj, di, dj;
        while (waypointIndex + 1 < int(wp.size()))
        {
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
            if (temp.size() <= 1)
                break;
            for (auto x : temp)
                path.push_back(x);
            waypointIndex++;
        }
        for (int i = 1; i < int(path.size()); ++i)
            if (path[i] == path[i - 1])
                path.erase(path.begin() + --i);
        tie(ti, tj) = getNextTurn(path);
        targetX = getCenter(ti);
        targetY = getCenter(tj);
        for (int i = 0; i < int(path.size()); ++i)
            if (path[i].first == ti && path[i].second == tj)
            {
                pi = path[max(0, i - 1)].first;
                pj = path[max(0, i - 1)].second;
                fi = path[min(int(path.size()) - 1, i + 1)].first;
                fj = path[min(int(path.size()) - 1, i + 1)].second;
                break;
            }
        double randomName = 1;
        if (path.size() >= 3)
        {
            tie(ai, aj) = path[0];
            tie(bi, bj) = path[1];
            tie(ci, cj) = path[2];
        }
        if (path.size() >= 4)
        {
            tie(di, dj) = path[3];
            snake = true;
            if (path[0] == path[2]);
            else
            if (bad.find(S) == bad.end() && (
            (ai + 1 == ci && aj - 1 == cj && bi + 1 == di && bj - 1 == dj)
            || (ai - 1 == ci && aj + 1 == cj && bi - 1 == di && bj + 1 == dj)
            || (ai + 1 == ci && aj + 1 == cj && bi + 1 == di && bj + 1 == dj)
            || (ai - 1 == ci && aj - 1 == cj && bi - 1 == di && bj - 1 == dj)
            ))
            {
                tie(targetX, targetY) = getXX(path[1], path[2]);
                int ri, rj;
                tie(ri, rj) = getNextTurn(path, 2); 
                if (abs(ci - ri) + abs(cj - rj) >= 2)
                {
                    ////tie(targetX, targetY) = make_pair(getCenter(path[2].first), getCenter(path[2].second));
                    tie(tickTargetX, tickTargetY) = getXX(path[2], path[3]);
                    tickTargetI = bi;
                    tickTargetJ = bj;
                    ////tie(pi, pj) = path[1];
                    ////tie(ti, tj) = path[2];
                    ////tie(fi, fj) = path[3];
                    ////targetX = getCenter(ti);
                    ////targetY = getCenter(tj);
                    ////randomName = 1;
                    ////snake = false;
                }
            }
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
                    bool is33 = d == directions[make_pair(path[1].first - path[0].first, path[1].second - path[0].second)];
                    bad.insert(path[1]);

                    if (!is33)
                        bad.insert(path[0]),
                        bad.insert(path[2]),
                        tie(targetX, targetY) = getCorner(path[0], path[1], path[2]);
                    else
                        //tie(pi, pj) = reflect(path[0], path[1]),
                        //tie(fi, fj) = path[2],
                        //a[ti][tj] = CROSSROADS,
                        drift = false;
                }
                else
                    drift = false;
            }
        } else
            drift = false,
            snake = false;
        if (si == tickTargetI && sj == tickTargetJ)
        {
            if (tickTarget == -1)
                tickTarget = world.getTick() + 25 - speedModule + badMap * 20;
        }
        else
            tickTarget = -1,
            tickTargetI = -1,
            tickTargetJ = -1,
            tickTargetX = -1,
            tickTargetY = -1;
        if (world.getTick() < tickTarget)
            targetX = tickTargetX,
            targetY = tickTargetY,
            snake = true;
        double temp = self.getDistanceTo(targetX, targetY);
        double temp2 = temp / tileSize / randomName;
        prevDistance = distToNext;
        distToNext = temp;
        auto interpolation = [&](double x)
        {
            return + 5.28596 * pow(x, 8) - 49.1259 * pow(x, 7) + 189.037 * pow(x, 6) - 388.625 * pow(x, 5) + 458.98 * pow(x, 4) - 310.246 * pow(x, 3) + 110.424 * pow(x, 2) - 15.6552 * pow(x, 1) + 0.2;
            return + 7.16332 * pow(x, 8) - 67.0616 * pow(x, 7) + 260.855 * pow(x, 6) - 544.344 * pow(x, 5) + 655.525 * pow(x, 4) - 453.69 * pow(x, 3) + 165.888 * pow(x, 2) - 24.2604 * pow(x, 1) + 0.2;
            return + 1.68041 * pow(x, 7) - 14.0981 * pow(x, 6) + 47.7581 * pow(x, 5) - 82.7825 * pow(x, 4) + 76.7515 * pow(x, 3) - 36.3308 * pow(x, 2) + 7.15476 * pow(x, 1) + 0.2;
            return - 0.57084 * pow(x, 10) + 10.9758 * pow(x, 9) - 91.814 * pow(x, 8) + 438.632 * pow(x, 7) - 1320.67 * pow(x, 6) + 2608.54 * pow(x, 5) - 3408.95 * pow(x, 4) + 2898.79 * pow(x, 3) - 1530.02 * pow(x, 2) + 451.546 * pow(x, 1) - 56.1279;
        };
        double MAAAAAGIC = interpolation(temp2);
        if (temp2 > 2)
            MAAAAAGIC = -0.25;
        if (temp2 < 0.6)
            MAAAAAGIC = interpolation(0.6);

        double nextWaypointX = targetX;
        double nextWaypointY = targetY;

        double cornerTileOffset = MAAAAAGIC * tileSize;
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

                    nextWaypointX += cornerTileOffset;
                    nextWaypointY += cornerTileOffset;
                    break;
                case RIGHT_TOP_CORNER:
    rt:

                    nextWaypointX -= cornerTileOffset;
                    nextWaypointY += cornerTileOffset;
                    break;
                case LEFT_BOTTOM_CORNER:
    lb:

                    nextWaypointX += cornerTileOffset;
                    nextWaypointY -= cornerTileOffset;
                    break;
                case RIGHT_BOTTOM_CORNER:
    rb:

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
                    if ((b.getDistanceTo(targetX, targetY) > tileSize * 2 && (fabs(self.getAngleTo(b)) < PI / 27 && fabs(self.getAngleTo(targetX, targetY) < PI / 36) || (bonus.getType() == PURE_SCORE || (bonus.getType() == REPAIR_KIT && self.getDurability() < 20)) && self.getAngleTo(b) < PI / 5) && self.getDistanceTo(b) > tileSize * 0.75))
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
            if (!car.isFinishedTrack())
                if ((car.getDurability() == 0 || hypot(car.getSpeedX(), car.getSpeedY()) * 1.05 < speedModule || fabs(car.getAngleTo(self)) < PI / 2 || speedModule < 10) && world.getTick() > 300)
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
        //if ((fabs(check - PI) < PI / 6 || fabs(check + PI) < PI / 6) && planB == 0 && forceRight == 0 && forceBack == 0)
            //planB = PLANB,
            //power *= -1;
        //if (fabs(check) < PI / 3 && planB && forceRight == 0 && forceBack == 0)
            //power *= -1,
            //planB = 0;
        auto getTurn = [&](double dod)
        {
            return angleToWaypoint * dod * pow(DIST_TO_NEXT / distToNext, 0.8) / PI;
        };
        bool okSnake = false;
        int count = 0;
        if (snake && path.size() >= 3)
        {
            vector<int> fff = {
                directions[make_pair(path[0].first - path[1].first, path[0].second - path[1].second)],
                directions[make_pair(path[1].first - path[2].first, path[1].second - path[2].second)]
            };
            for (int i = 2; i + 1 < path.size(); ++i)
                if (directions[make_pair(path[i].first - path[i + 1].first, path[i].second - path[i + 1].second)] == fff[i % 2])
                    count++;
                else
                    break;

            okSnake = count >= 9;
        }
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
            if (forceRight == 0 || planB)
                planB = 0;
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
                        forceBack = FORCE_BACK;
                        turn = getTurn(32);
                        if (isCorner(a[si][sj]))
                        {
                            turn = turn > 0 ? 1 : -1;
                            if (globalFail > GLOBAL_FAIL)
                                turn *= -1;
                        }
                        else
                            if (globalFail > GLOBAL_FAIL)
                                turn = turn > 0 ? 1 : -1;
                        turn *= -1;
                        power *= -1;
                    }
                }
            }
            else
            {
                if (force)
                    force--;
                forceSlow = path.size() <= 4 ? 14 : 100;
                if (world.getTick() <= tickTarget + 200)
                    forceSlow = badMap * 20;
                if (is4(path))
                    forceSlow *= 1.5;
                countOfFails = 0;
                globalFail = 0;

                if (forceRight == 0)
                    turn = getTurn(36);
                double dd = speedModule / MAX_SPEED;
                //if (is32(path))
                    //dd *= 1.3;
                if (is3_2(path))
                    dd /= 2;
                if (is212(path))
                    dd /= 2;
                if (is41(path))
                    dd *= 1.2;
                bool fas = is131(path) && speedModule > 16.5 || world.getMapName() == "map14" && speedModule > 18 && count < 3;

                if ((!snake && distToNext < tileSize * dd && distToNext > tileSize && bad.find(S) == bad.end()) || speedModule > forceSlow || (bad.find(S) != bad.end() && speedModule > 11.5) || fas)
                    move.setBrake(true);
            }
        }
        if (forceRight == 0 && forceBack == 0 && planB)
        {
            if (angleToWaypoint > 0)
                angleToWaypoint = PI - angleToWaypoint;
            else
                angleToWaypoint = -PI + angleToWaypoint;
            turn = getTurn(32);

        }
        move.setWheelTurn(turn);
        move.setEnginePower(power);
        for (auto car : world.getCars())
            if (!car.isTeammate())
            {
                if (world.getTick() > 250 && self.getDistanceTo(car) <= tileSize * 2)
                {
                    if (fabs(self.getAngleTo(car)) < ANGLE_THROW / 2 && !car.isFinishedTrack() && (hypot(car.getSpeedX(), car.getSpeedY()) < 5 || fabs(car.getAngle() - self.getAngle()) < PI / 60 || self.getDistanceTo(car) < tileSize))
                        move.setThrowProjectile(true);
                }
                if (self.getDistanceTo(car) <= tileSize * 6 && isCorner(a[wx][wy]) && planB == 0)
                    move.setSpillOil(true);
            }

        if (forceRight == 0 && forceBack == 0 && world.getTick() > beforeTick && (distToNext > tileSize * 5 || (okSnake && bad.find(S) == bad.end() && speedModule > 20)) && planB == 0 && fabs(angleToWaypoint) < PI / 90)
            move.setUseNitro(true);
        if (ct == BUGGY)
            return;
#ifdef vis
    visual.beginPre();
        auto vvv = world.getTilesXY();
        for (int i = 0; i < vvv.size(); ++i)
            for (int j = 0; j < vvv[0].size(); ++j)
                if (vvv[i][j] == UNKNOWN)
                    visual.fillRect(get(i), get(j), get(i + 1), get(j + 1), 0xBB0000);
        auto HSVtoRgb = [](double H, double S, double V)
        {
            double f, p, q, t;
            S = (S > 1) ? S / 100 : S;
            V = (V > 1) ? V / 100 : V;
            int lH = int(H / 60);
            f = H / 60 - lH;
            p = V * (1 - S);
            q = V * (1 - S * f);
            t = 1 - (1 - f) * S;
            double R, G, B;
                        
            switch (lH)
            {
                case 0: R = V; G = t; B = p; break;
                case 1: R = q; G = V; B = p; break;
                case 2: R = p; G = V; B = t; break;
                case 3: R = p; G = q; B = V; break;
                case 4: R = t; G = p; B = V; break;
                case 5: R = V; G = p; B = q; break;
            }
            int r = R * 0xFF;
            int g = G * 0xFF;
            int b = B * 0xFF;
            return r << 16 | g << 8 | b;
        };

        int index = 0;
        auto sdjkflghsldkfj = world.getWaypoints();
        for (auto p : sdjkflghsldkfj)
            visual.fillRect(get(p[0]), get(p[1]), get(p[0] + 1), get(p[1] + 1), HSVtoRgb(index++ * 360 / sdjkflghsldkfj.size(), 1, 1));

        visual.fillCircle(getCenter(ti), getCenter(tj), 400, 0x54618f);
        visual.line(self.getX(), self.getY(), nextWaypointX, nextWaypointY);
        char sss[45];
        sprintf(sss, "%d %d  s:%.2f  a:%.2f  t:%.2f", pd, d, speedModule, angleToWaypoint, turn);
        visual.text(self.getX() + 120, self.getY() + 120, sss);
        sss[44] = 0;
        for (int i = 1; i < min(15, int(path.size())); ++i)
            visual.line(getCenter(path[i - 1].first), getCenter(path[i - 1].second), getCenter(path[i].first), getCenter(path[i].second), 0xff0000);
        visual.line(getCenter(pi), getCenter(pj), getCenter(ti), getCenter(tj), 0x00ff00);
        visual.line(getCenter(ti), getCenter(tj), getCenter(fi), getCenter(fj), 0x00ff00);
        visual.endPre();
        visual.beginPost();
        visual.endPost();
#endif
    }
}

MyStrategy::MyStrategy() 
{
#undef bad
#undef old
#undef once
    bad.resize(2);
    old.resize(2);
    once.resize(2);
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
