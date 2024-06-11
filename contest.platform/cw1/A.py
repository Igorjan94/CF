import sys
import json
import random

f = ''.join(open(sys.argv[1]).readlines())
lm = len(json.loads(f)['monsters'])

def solve(order):
    j = json.loads(f)
    h = j['hero']
    mon = j['monsters']
    r = h['base_range']
    p = h['base_power']
    s = h['base_speed']
    level = 0
    cur = 0

    def getR():
        return int(r * (1 + level * h['level_range_coeff'] / 100))
    def getS():
        return int(s * (1 + level * h['level_speed_coeff'] / 100))
    def getP():
        return int(p * (1 + level * h['level_power_coeff'] / 100))

    x = j['start_x']
    y = j['start_y']

    n = j['width']
    m = j['height']

    answer = []
    turns = j['num_turns']
    score = 0

    def dist(mmm):
        return (mon[mmm]['x'] - x) ** 2 + (mon[mmm]['y'] - y) ** 2
    j = 0
    index = -1
    for i in range(turns):
        if not (index != -1 and dist(index) <= getR() ** 2 and mon[index]['hp'] > 0):
            found = -1
            for z in range(lm):
                if mon[z]['hp'] > 0:
                    if dist(z) <= getR() ** 2:
                        found = z
                        break
            if found == -1:
                while j < lm and mon[order[j]]['hp'] <= 0:
                    j += 1
                if j == lm:
                    answer.append({
                        'type':'move',
                        'target_x': x,
                        'target_y': y,
                    })
                    continue
                index = order[j]
            else:
                index = z

        if dist(index) <= getR() ** 2:
            mon[index]['hp'] -= getP() 
            answer.append({
                'type': 'attack',
                'target_id': index
            })
            if mon[index]['hp'] <= 0:
                cur += mon[index]['exp']
                score += mon[index]['gold']
                while cur >= 1000 + level * (level + 1) * 50:
                    cur -= 1000 + level * (level + 1) * 50
                    level += 1
        else:
            tx = mon[index]['x']
            ty = mon[index]['y']
            cs = getS()
            if x != tx:
                ty = y
                if x > tx:
                    tx = max(tx, x - cs)
                else:
                    tx = min(tx, x + cs)
            else:
                tx = x
                if y > ty:
                    ty = max(ty, y - cs)
                else:
                    ty = min(ty, y + cs)
            x = tx
            y = ty
            answer.append({
                'type':'move',
                'target_x': tx,
                'target_y': ty,
            })
    return score, answer

score = -1
cur = []
orders = [
    [i for i in range(lm)] for j in range(2000)
]
for i in range(len(orders)):
    random.shuffle(orders[i])
sys.stderr.write(f'-------------- {lm}\n')
for QQ in range(20):
    ret = []
    for i in range(len(orders)):
        cur_score, answer = solve(orders[i])
        if cur_score > score:
            score = cur_score
            cur = answer
        ret.append([-cur_score, answer, orders[i]])
    ret.sort(key=lambda x: x[0])
    ret = list(ret[:3])
    l = len(ret)
    orders = []
    for nq in range(200000 // lm):
        i = random.randint(0, l - 1)
        st = random.randint(0, min(10, lm - 1))
        fi = random.randint(0, min(10, lm - 1))
        if st == fi:
            continue
        q = ret[i][2]
        q[st], q[fi] = q[fi], q[st]
        # if st > fi: st, fi = fi, st
        # q[st:fi] = q[st:fi][::-1]
        orders.append(q)
        
    sys.stderr.write(str(QQ) + ' ' + str(score) + '\n')
sys.stderr.write('--------------')
sys.stderr.write(str(score) + '\n')
print(json.dumps({'comment': score, 'moves': cur}))
