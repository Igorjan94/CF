
# python 3.10
from datetime import datetime


def get(x, m, s):
    return [x, m[2], m[3], m[4], m[5] , f"{m[0]}{m[1] * s if m[1] * s >= 10 else '0' + str(m[1] * s)}:00Z", f'{s}min']


# [h, mod, start, max, min, close]
def generate_candles(a) -> str:
    ret = []
    f = {}
    for c in a:
        x, p, d = c.split(',')
        if not x in f:
            f[x] = {
                'one': [-1] * 6,
                'two': [-1] * 6,
                'five': [-1] * 6
            }
        dd = datetime.strptime(d, '%Y-%m-%dT%H:%M:%SZ')
        h = d[:14]
        mod = dd.minute

        if f[x]['one'][0] == -1 or f[x]['one'][0] != h or f[x]['one'][1] != mod:
            if f[x]['one'][0] != -1:
                ret.append(get(x, f[x]['one'], 1))
            f[x]['one'] = [h, mod, p, p, p, p]
        else:
            f[x]['one'][3] = max(f[x]['one'][3], p)
            f[x]['one'][4] = min(f[x]['one'][4], p)
            f[x]['one'][5] = p

        mod = dd.minute // 2
        if f[x]['two'][0] == -1 or f[x]['two'][0] != h or f[x]['two'][1] != mod:
            if f[x]['two'][0] != -1:
                ret.append(get(x, f[x]['two'], 2))
            f[x]['two'] = [h, mod, p, p, p, p]
        else:
            f[x]['two'][3] = max(f[x]['two'][3], p)
            f[x]['two'][4] = min(f[x]['two'][4], p)
            f[x]['two'][5] = p

        mod = dd.minute // 5
        if f[x]['five'][0] == -1 or f[x]['five'][0] != h or f[x]['five'][1] != mod:
            if f[x]['five'][0] != -1:
                ret.append(get(x, f[x]['five'], 5))
            f[x]['five'] = [h, mod, p, p, p, p]
        else:
            f[x]['five'][3] = max(f[x]['five'][3], p)
            f[x]['five'][4] = min(f[x]['five'][4], p)
            f[x]['five'][5] = p
    for x, v in f.items():
        if v['one'][0] != -1:
            ret.append(get(x, v['one'], 1))
        if v['two'][0] != -1:
            ret.append(get(x, v['two'], 2))
        if v['five'][0] != -1:
            ret.append(get(x, v['five'], 5))
        
    return '\n'.join(map(lambda x: ','.join(x), sorted(ret, key=lambda x: [x[0], x[6], x[5]])))

if __name__ == "__main__":
    a = []
    while True:
        try:
            input_str = input()
            a.append(input_str)
        except:
            break
    print(generate_candles(a))
