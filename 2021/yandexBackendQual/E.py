class item:
    def __init__(self, index, start, end, t):
        self.index = index
        self.start = start
        self.end = end
        self.t = t

    def __str__(self):
        return f'{self.index},{self.start} {self.end},{self.t}'

items = []

while True:
    try:
        line = input()
        if line == '':
            break
    except:
        break
    index, dates, t = line.split(',')
    index = int(index)
    start, end = dates.split()
    if t == 'NULL':
        items.append(item(index, start, end, 'KGT'))
        items.append(item(index, start, end, 'COLD'))
        items.append(item(index, start, end, 'OTHER'))
    else:
        items.append(item(index, start, end, t))

items.sort(key = lambda x: [x.index, x.t[1], x.start])
res = [items[0]]
n = len(items)

for i in range(1, n):
    last = res[-1]
    cur = items[i]
    if last.index == cur.index and last.t == cur.t and cur.start <= last.end:
        res[-1].end = max(res[-1].end, cur.end)
    else:
        res.append(cur)

print(*res, sep = '\n')
