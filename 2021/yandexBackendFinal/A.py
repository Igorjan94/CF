n, l = map(int, input().split())

users = [[] for i in range(n)]
for _ in range(n):
    c = int(input())
    for i in range(c):
        users[_].append(input().split('-'))

def formatM(m):
    return '30' if m == 30 else '00'

count = 0
for start in range(10, 20):
    for half in range(0, 60, 30):
        endH = start + l // 60
        endM = half + (l % 60)
        if endM == 60:
            endH += 1
            endM = 0
        if endH < 20 or endH == 20 and endM == 0:
            timeStart = f'{start}:{formatM(half)}'
            timeEnd = f'{endH}:{formatM(endM)}'
            ok = True
            for i in range(n):
                can = True
                for times in users[i]:
                    if not (times[0] >= timeEnd or times[1] <= timeStart):
                        can = False
                if not can:
                    ok = False
            if ok:
                count += 1
                print(f'{timeStart}-{timeEnd}')
if count == 0:
    print('No way')
