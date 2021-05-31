import math
import csv
from tqdm import tqdm

trainFile = '../SUBMIT/big.csv'

friends = {}

def addFriends(u, v, t):
    if not u in friends:
        friends[u] = {}
    friends[u][v] = t

with open(trainFile, 'r') as csvFile:
    reader = csv.DictReader(csvFile)
    for row in tqdm(reader, total = 17414510):
        u = int(row['u'])
        v = int(row['v'])
        t = [int(row['t']), int(row['h'])]
        addFriends(u, v, t)
        addFriends(v, u, t)
        # if len(friends) > 20000:
            # break

friendsCount = []
for u, fs in friends.items():
    if u % 2 == 1:
        friendsCount.append([len(fs), u])
friendsCount.sort(reverse = True)

def log(x):
    return math.log(max(2, x))

def getAA(sz, uw, vw):
    return log(100 - uw[0]) * log(100 - vw[0]) * log(uw[1]) * log(vw[1]) / log(sz)

possible = {}

def add(u, v, value):
    if value == 0: return
    if not u in possible:
        possible[u] = {}
    if not v in possible[u]:
        possible[u][v] = 0
    possible[u][v] += value

for w, wsFriends in tqdm(friends.items(), total = len(friends)):
    l = len(wsFriends)
    for u, uw in wsFriends.items():
        if u % 8 != 1: continue
        if (100 - uw[0]) * uw[1] / l < 2.9: continue
        for v, vw in wsFriends.items():
            if v % 2 == 0 or v <= u or v in friends[u]: continue
            if (100 - vw[0]) * vw[1] / l < 2.9: continue
            add(u, v, getAA(l, uw, vw))

print('Predictions done')
answers = []
for u, variants in tqdm(possible.items(), total = len(possible)):
    pos = []
    for v, value in variants.items():
        pos.append((value, v))

    if len(pos) > 0:
        pos.sort(reverse = True)
        # for (count, v) in friendsCount:
            # if len(pos) < 10:
                # if v > u:
                    # pos.append((count, v))
            # else:
                # break

        answers.append((u, ','.join(map(lambda p: str(p[1]), pos[:10]))))

answers.sort()
print('ANSWERS:', len(answers))
with open('submit.txt', 'w') as submit:
    for row in tqdm(answers, total = len(answers)):
        submit.write(f'{row[0]}: {row[1]}\n')
print('DONE');
