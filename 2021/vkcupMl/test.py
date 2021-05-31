import math
import csv
from tqdm import tqdm

from joblib import dump, load

clf = load('filename.joblib2')
print(clf.classes_)

test = './TEST/train.csv'
output = './TEST/submit.csv'

friends = {}
possible = {}
answers = []

def addFriends(u, v, t):
    if not u in friends:
        friends[u] = {}
    friends[u][v] = t

def add(u, v, value):
    if value == 0: return
    if not u in possible:
        possible[u] = {}
    if not v in possible[u]:
        possible[u][v] = 0
    possible[u][v] += value

print('Reading data')

with open(test, 'r') as csvFile:
    reader = csv.DictReader(csvFile)
    for row in tqdm(reader):
        u = int(row['u'])
        v = int(row['v'])
        t = [int(row['t']), int(row['h'])]
        addFriends(u, v, t)
        addFriends(v, u, t)
        # if len(friends) > 300000:
            # break

print('Predicting friends')

X = []
q = []
for w, wsFriends in tqdm(friends.items(), total = len(friends)):
    l = len(wsFriends)
    for u, uw in wsFriends.items():
        if u % 8 != 1: continue
        if (100 - uw[0]) * uw[1] / l < 1: continue
        for v, vw in wsFriends.items():
            if v % 2 == 0 or v <= u or v in friends[u]: continue
            if (100 - vw[0]) * vw[1] / l < 1: continue
            X.append([l, *uw, *vw])
            q.append([u, v])
    friends[w] = []

y = clf.predict_proba(X)
for i in tqdm(range(len(y))):
    add(q[i][0], q[i][1], y[i][1])

print('Generating answers')
for u, variants in tqdm(possible.items(), total = len(possible)):
    pos = []
    for v, value in variants.items():
        pos.append((value, v))

    if len(pos) > 0:
        if len(pos) > 10:
            pos.sort(reverse = True)
        answers.append((u, list(map(lambda p: p[1], pos[:10]))))

answers.sort()

print('Writing answers:', len(answers))
with open(output, 'w') as submit:
    for row in tqdm(answers, total = len(answers)):
        submit.write(f'{row[0]}: {",".join(map(str, row[1]))}\n')

print('DONE')
