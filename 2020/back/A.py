import sys

s = input()
start, finish = input().split()

start = list(map(int, start.split('-')))
finish = list(map(int, finish.split('-')))

a = [2000, 1, 1]
if s == 'WEEK':
    a = [1999, 12, 27]
elif s == 'FEBRUARY_THE_29TH':
    a = [1996, 2, 29]

def addMonth(d, cnt):
    for i in range(cnt):
        month = d[1]
        year = d[0]
        if month == 12:
            month = 1
            year += 1
        else:
            month += 1

        d = [year, month, d[2]]
    return d

days = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

def addYears(d):
    year = d[0] + 4
    if year % 100 == 0 and year % 400 != 0:
        year += 4
    return [year, d[1], d[2]]

def addDays(d, cnt):
    year, month, day = d
    day += cnt
    now = days[month]
    if month == 2 and (year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)):
        now += 1
    if day > now:
        day -= now
        month += 1
        if month == 13:
            month = 1
            year += 1
    d = [year, month, day]
    return d

def nxt(d, what):
    if s == 'WEEK':
        return addDays(d, 7)
    elif s == 'MONTH':
        return addMonth(d, 1)
    elif s == 'QUARTER':
        return addMonth(d, 3)
    elif s == 'YEAR':
        return addMonth(d, 12)
    else:
        return addYears(d)

def prv(d):
    year, month, days = d
    days -= 1
    if days == 0:
        month -= 1
        days = 28
        if month == 0:
            year -= 1
    q = [year, month, days]
    while True:
        w = addDays(q, 1)
        if w == d:
            return q
        q = w

q = []
while a <= start:
    a = nxt(a, s)

if prv(a) >= finish:
    q.append([start, finish])
else:
    q.append([start, prv(a)])

    while True:
        b = nxt(a, s)
        if b <= finish:
            q.append([a, prv(b)])
        else:
            break
        a = b

    q.append([a, finish])

def get(x):
    return '0' + str(x) if x < 10 else str(x)

def frmt(d):
    return '-'.join([str(d[0]), get(d[1]), get(d[2])])
print(len(q))
print('\n'.join(map(lambda x: ' '.join(map(frmt, x)), q)))
