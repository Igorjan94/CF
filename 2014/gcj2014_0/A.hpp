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
    int first, second, n = 4, x, count = 0, ans;
    set<int> s[4], d[4];

public:
    void readInput(QTextStream &in)
    {
        in >> first;
        fori(n)
            forj(n)
                in >> x,
                s[i].insert(x);
        in >> second;
        fori(n)
            forj(n)
                in >> x,
                d[i].insert(x);
    }

    void writeResults(QTextStream &out)
    {
        out << "Case #" << case_number << ": ";
        switch (count)
        {
        case 0:
            out << "Volunteer cheated!" << "\n";
            break;
        case 1:
            out << ans << "\n";
            break;
        default:
            out << "Bad magician!" << "\n";
        }
    }

    void solution()
    {
        first--;
        second--;
        fors(i, s[first])
            if (d[second].find(*i) != d[second].end())
                count++,
                ans = *i;
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
