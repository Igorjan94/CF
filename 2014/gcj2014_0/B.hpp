#ifndef CASE_HPP
#define CASE_HPP

#include <bits/stdc++.h>
#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QTextStream>
#include <QDebug>
#define enter printf("\n")
#define pb push_back
#define ll long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define forn1(i, n) for (int i = 1; i < n; i++)
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>

using namespace std;

class Case : public QObject, public QRunnable
{
    Q_OBJECT
    double C, F, X, i, ans = 0, time = 0;

public:
    void readInput(QTextStream &in)
    {
        in >> C >> F >> X;
    }

    void writeResults(QTextStream &out)
    {
        out << "Case #" << case_number << ": ";
        out.setRealNumberPrecision(10);
        out << ans << "\n";
    }

    void solution()
    {
        i = 2;
        ans = X / i;
        while (true)
        {
            if (C / i + X / (i + F) > X / i)
                break;
            time += C / i;
            i += F;
            ans = min(ans, time + X / i);
        }
    }

    explicit Case() : QObject(0), solved(false) { setAutoDelete(false); }

    void run()
    {
        solution();
        solved = true;
        emit caseSolved(this);
    }

    inline bool is_solved() const { return solved; }
    inline void setCaseNumber(int n) { case_number = n; }

signals:
    void caseSolved(Case*);

private:
    int  case_number;
    bool solved;
};

#endif // CASE_HPP
