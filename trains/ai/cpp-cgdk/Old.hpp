#include "MyStrategy.h"

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

#include <bits/stdc++.h>
#ifdef debug
#include <library.h>
#endif

using namespace model;
using namespace std;

double DIST_TO_NEXT = 750;
int COUNT_OF_FAILS = 100;
int FORCE_BACK = 130;
int FORCE_RIGHT = 60;
int FORCE = 100;
int BREAK = 30;
double MAX_SPEED = 13.8;
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
vector<int> dx = {1, 0, -1, 0};
vector<int> dy = {0, 1, 0, -1};
bool init = true;

void ppp(vector<vector<int>> a)
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

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
    if (init)
    {
        init = false;
#ifdef debug
        writeln(world.getWaypoints());
#endif
        srand(game.getRandomSeed());
    }
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
    int waypointIndex = self.getNextWaypointIndex();
    int fi, fj, pi, pj;
    if (waypointIndex < int(wp.size()) - 1)
    {
        int cx = int(self.getX() / tileSize);
        int cy = int(self.getY() / tileSize);
        int wx1 = wp[waypointIndex][0];
        int wx2 = wp[waypointIndex + 1][0];
        int wy1 = wp[waypointIndex][1];
        int wy2 = wp[waypointIndex + 1][1];
        if (
                (cx == wx1 && cx == wx2 && ((cy < wy1 && wy1 < wy2) || (cy > wy1 && wy1 > wy2)))
                ||
                (cy == wy1 && cy == wy2 && ((cx < wx1 && wx1 < wx2) || (cx > wx1 && wx1 > wx2)))
           )
            ti = wp[++waypointIndex][0],
            tj = wp[waypointIndex][1];
        if (waypointIndex + 1 < int(wp.size()))
            fi = wp[waypointIndex + 1][0],
            fj = wp[waypointIndex + 1][1];
    }
    auto tt = world.getTilesXY()[ti][tj];
    double targetX = (ti + 0.5) * tileSize;
    double targetY = (tj + 0.5) * tileSize;
        int si = self.getX() / tileSize;
        int sj = self.getY() / tileSize;
        int n = a.size();
        int m = a[0].size();
        auto ok = [&](int x, int N)
        {
            return x >= 0 && x < N;
        };

    auto getPath = [&](int si, int sj, int ti, int tj)
    {
        vector<vector<int>> d(n, vector<int>(m, 10000));
        vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(m));
        d[si][sj] = 0;
        queue<pair<int, int>> q;
        q.push({si, sj});
        while (q.size())
        {
            int u = q.front().first;
            int v = q.front().second;
            q.pop();
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
                if (ok(u + dx[i], n) && ok(v + dy[i], m) && dir[a[u][v]][i])
                    if (d[u + dx[i]][v + dy[i]] == 10000)
                        d[u + dx[i]][v + dy[i]] = d[u][v] + 1,
                        prev[u + dx[i]][v + dy[i]] = {u, v},
                        q.push({u + dx[i], v + dy[i]});
        }
        return vector<pair<int, int>>(0);
    };
    vector<pair<int, int>> path = getPath(si, sj, ti, tj);
    if (path.size() >= 2)
        pi = path[path.size() - 2].first,
        pj = path[path.size() - 2].second;
    else
        pi = si,
        pj = sj;
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
            fi = ti;
            fj = tj;
            tie(ti, tj) = path[i];
            tt = a[path[i].first][path[i].second];
            targetX = (path[i].first + 0.5) * tileSize;
            targetY = (path[i].second + 0.5) * tileSize;
            break;
        }
    double temp = self.getDistanceTo(targetX, targetY);
    double temp2 = temp / tileSize;
    prevDistance = distToNext;
    distToNext = temp;
    auto interpolation = [&](double x)
    {
        return
 + 5.28596 * pow(x, 8)
 - 49.1259 * pow(x, 7)
 + 189.037 * pow(x, 6)
 - 388.625 * pow(x, 5)
 + 458.98  * pow(x, 4)
 - 310.246 * pow(x, 3)
 + 110.424 * pow(x, 2)
 - 15.6552 * pow(x, 1)
 + 0.2;//идеально при малой скорости
        return
 + 7.16332 * pow(x, 8)
 - 67.0616 * pow(x, 7)
 + 260.855 * pow(x, 6)
 - 544.344 * pow(x, 5)
 + 655.525 * pow(x, 4)
 - 453.69  * pow(x, 3)
 + 165.888 * pow(x, 2)
 - 24.2604 * pow(x, 1)
 + 0.2; //хреново входит в поворот
        return
 + 1.68041 * pow(x, 7)
 - 14.0981 * pow(x, 6)
 + 47.7581 * pow(x, 5)
 - 82.7825 * pow(x, 4)
 + 76.7515 * pow(x, 3)
 - 36.3308 * pow(x, 2)
 + 7.15476 * pow(x, 1)
 + 0.2; //на скорости влезает, но задевает угол ~-2
        return 
            - 0.57084 * pow(x, 10)
            + 10.9758 * pow(x, 9)
            - 91.814  * pow(x, 8)
            + 438.632 * pow(x, 7)
            - 1320.67 * pow(x, 6)
            + 2608.54 * pow(x, 5)
            - 3408.95 * pow(x, 4)
            + 2898.79 * pow(x, 3)
            - 1530.02 * pow(x, 2)
            + 451.546 * pow(x, 1)
            - 56.1279; //шикарно в большие повороты
    };
    double MAAAAAGIC = interpolation(temp2);
//interpolate({0, 0.2}, {0.5, 0.4}, {0.75, 0.365}, {1, 1/3}, {1.2, 0.2}, {1.4142135624, 0}, {1.66666, -3/16}, {2, -1/4})
    if (temp2 > 2)
        MAAAAAGIC = -0.25;
    //if (temp2 > 2)
    //{
        //double angle = self.getAngleTo(targetX, targetY);
        //cout << angle << "\n";
        //if (angle > -PI / 10 && angle < PI)
            //cout << "FORCE TURN\n",
            //MAAAAAGIC = -1;
    //}
    if (temp2 < 0.5)
        MAAAAAGIC = 0.3;
    double nextWaypointX = targetX;
    double nextWaypointY = targetY;

    double cornerTileOffset = MAAAAAGIC * tileSize;
    //cout << temp / tileSize << "       " << MAAAAAGIC << "      " << cornerTileOffset << "\n";
    auto pathtitj = getPath(ti, tj, fi, fj);
#ifdef debug
    if (pathtitj.size() >= 2)
        fi = pathtitj[1].first,
        fj = pathtitj[1].second;
    writeln(si, sj, pi, pj, ti, tj, fi, fj);
    writeln(pathtitj);
    writeln();
#endif
    auto changeCoords = [&](TileType type) {
        switch (type) {
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
                if (pi == ti)
                    if (ti + 1 == fi)
                        goto lb;
                    else
                        goto rb;
                else
                    if (pj == tj && pj == fj)
                        nextWaypointY += cornerTileOffset;
                    else
                        if (ti + 1 == pi)
                            goto lb;
                        else
                            goto rb;
                //if (pathtitj.size() > 1 && pathtitj[1].first == pathtitj[0].first + 1 && pathtitj[1].second == pathtitj[0].second)
                    //goto rb;
                //if (pathtitj.size() > 1 && pathtitj[1].first == pathtitj[0].first - 1 && pathtitj[1].second == pathtitj[0].second)
                    //goto lb;

                break;
            case BOTTOM_HEADED_T:
                if (pi == ti)
                    if (ti + 1 == fi)
                        goto lt;
                    else
                        goto rt;
                else
                    if (pj == tj && pj == fj)
                        nextWaypointY -= cornerTileOffset;
                    else
                        if (ti + 1 == pi) 
                            goto lt;
                        else
                            goto rt;
                break;
            case RIGHT_HEADED_T:
                if (pathtitj.size() > 1 && pathtitj[1].first == pathtitj[0].first && pathtitj[1].second == pathtitj[0].second + 1)
                    goto lt;
                    //goto rt; 
                if (pathtitj.size() > 1 && pathtitj[1].first == pathtitj[0].first && pathtitj[1].second == pathtitj[0].second - 1)
                    goto lb;
                    //goto rb;
                break;
            case LEFT_HEADED_T:
                if (pathtitj.size() > 1 && pathtitj[1].first == pathtitj[0].first && pathtitj[1].second == pathtitj[0].second + 1)
                    goto rt;
                    //goto lt; 
                if (pathtitj.size() > 1 && pathtitj[1].first == pathtitj[0].first && pathtitj[1].second == pathtitj[0].second - 1)
                    goto rb;
                    //goto lb;
                break;
            default:
                break;
        }
    };
    changeCoords(tt);
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
    if (!forceBack)
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
                    if (isCorner(world.getTilesXY()[si][sj]))
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
            //if (speedModule * speedModule * fabs(angleToWaypoint) > 6 * PI && distToNext < DIST_TO_NEXT || 
            double dd = speedModule / MAX_SPEED;// * 1.1;
            //cout << dd << " " << distToNext << "\n";
            //if (dd > 1)
                //dd = 6;
            if ((distToNext < tileSize * dd && distToNext > tileSize) || forceSlow)
                if (isCorner(tt))
                    move.setBrake(true);
            power = max(isCorner(tt) ? 1.0 : 1.0, distToNext / DIST_TO_NEXT);
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
            //cout << self.getAngleTo(car) / PI * 180 << "\n";
            if (self.getDistanceTo(car) <= tileSize)
            {
                if (fabs(self.getAngleTo(car)) < ANGLE_THROW && car.getDurability() > 0 && !car.isFinishedTrack())
                    move.setThrowProjectile(true);
                if (self.getAngleTo(car) + ANGLE_THROW * 2 > PI || self.getAngleTo(car) - ANGLE_THROW * 2 < -PI)
                    move.setSpillOil(true);
            }
        }
    if (world.getTick() > 210 && distToNext > prevDistance)
    {
        forceSlow = FORCE_SLOW_DOWN;
        if (distToNext > tileSize * 5)
            forceSlow /= 2;
    }
    if (self.getRemainingOiledTicks() > 0)
        forceSlow = 0;
    if (world.getTick() > 210 && (distToNext > prevDistance && distToNext > tileSize * 5))
        move.setUseNitro(true);
    if (world.getTick() == 140)
        move.setUseNitro(true);
}

MyStrategy::MyStrategy() 
{
    dir[1][1]  = dir[1][3]  = true;
    dir[2][0]  = dir[2][2]  = true;

    dir[3][0]  = dir[3][1]  = true;
    dir[4][1]  = dir[4][2]  = true;
    dir[5][0]  = dir[5][3]  = true;
    dir[6][2]  = dir[6][3]  = true;

    dir[7][1]  = dir[7][2]  = dir[7][3]  = true;
    dir[8][0]  = dir[8][1]  = dir[8][3]  = true;
    dir[9][0]  = dir[9][2]  = dir[9][3]  = true;
    dir[10][0] = dir[10][1] = dir[10][2] = true;

    dir[CROSSROADS][0] = dir[11][1] = dir[11][2] = dir[11][3] = true;
    freopen("lol", "w", stdout);
}

//interpolate({0.5, 0.4}, {0.65, 0.365}, {0.85, 1/3}, {1.2, 0.2}, {1.4142135624, 0}, {1.66666, -1/8}, {2, -1/4}, {2.5, -1/3}, {3, -0.365}, {3.5, -0.365}, {3.25, -0.365})
