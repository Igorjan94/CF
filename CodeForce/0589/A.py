n = int(input())
a = {}
for i in range(n):
    s = input()
    t = s.lower().rsplit('@', 1)
    if t[1] == 'bmail.com':
        t[0] = t[0].replace('.', '').split('+', 1)[0]
    t = t[0] + t[1]
    if t in a:
        a[t].append(s)
    else:
        a[t] = [s]
print(len(a))
for x in a:
    q = str(len(a[x]))
    for y in a[x]:
        q += ' ' + y
    print(q)

