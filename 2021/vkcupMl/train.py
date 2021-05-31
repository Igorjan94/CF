import math
import csv
from tqdm import tqdm

from sklearn.tree import DecisionTreeClassifier
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from joblib import dump, load


trainFile = './TRAIN/trainSmall.csv'
testFile = './TRAIN/testSmall.csv'

friends = {}
train = {}
X = []
y = []

def addFriends(u, v, t):
    if not u in friends:
        friends[u] = {}
    friends[u][v] = t

print('Reading friends')

with open(trainFile, 'r') as csvFile:
    reader = csv.DictReader(csvFile)
    for row in tqdm(reader):
        u = int(row['u'])
        v = int(row['v'])
        t = [int(row['t']), int(row['h'])]
        addFriends(u, v, t)
        addFriends(v, u, t)
        # if len(friends) > 300000:
            # break

# friendsCount = []
# for u, fs in friends.items():
    # friendsCount.append([len(fs), u])
# friendsCount.sort(reverse = True)
# print(friendsCount[:1000])

print('Reading answers')

with open(testFile, 'r') as csvFile:
    reader = csv.DictReader(csvFile)
    for row in tqdm(reader):
        u = int(row['u'])
        v = int(row['v'])
        if not u in train:
            train[u] = set()
        train[u].add(v)

print('Getting X and y')

for w, wsFriends in tqdm(friends.items(), total = len(friends)):
    l = len(wsFriends)
    for u, uw in wsFriends.items():
        if u % 8 != 1: continue
        if (100 - uw[0]) * uw[1] / l < 0.25: continue
        for v, vw in wsFriends.items():
            if v % 2 == 0 or v <= u or v in friends[u]: continue
            if (100 - vw[0]) * vw[1] / l < 0.25: continue
            X.append([l, *uw, *uw])
            y.append(u in train and v in train[u])

print('Predictions done')

clf = make_pipeline(StandardScaler(), DecisionTreeClassifier())
clf.fit(X, y)
dump(clf, 'filename.joblib2')

print('Classifier saved')


