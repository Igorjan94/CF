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
    int x = 0, y = 0, n;
    vector<double> b, c;
    set<double> a;

public:
    void readInput(QTextStream &in)
    {
        in >> n;
        b.resize(n);
        double u;
        fori(n)
            in >> b[i];
        fori(n)
            in >> u,
            a.insert(u),
            c.pb(u);
    }

    void writeResults(QTextStream &out)
    {
        out << "Case #" << case_number << ": ";
        out << y << " " << x << "\n";
    }

    void solution()
    {
        sort(b.begin(), b.end());
        sort(c.begin(), c.end());
        set<double>::iterator it;
        fori(n)
        {
            it = a.upper_bound(b[i]);
            if (it == a.end())
                x++;
            else
                a.erase(it);
        }
        int jc = n - 1;
        int ic = 0;
        forn(ib, n)
        {
            if (b[ib] < c[ic])
                jc--;
            else
                y++,
                ic++;
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
