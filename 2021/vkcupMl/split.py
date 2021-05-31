import math
import csv
from tqdm import tqdm

ccc = 'train.csv'
test = 'testSmall.csv'
train = 'trainSmall.csv'
testTime = 10

with open(ccc, 'r') as csvFile:
    reader = csv.DictReader(csvFile)
    with open(test, 'w') as testFile:
        with open(train, 'w') as trainFile:
            trainFile.write('u,v,t,h\n')
            testFile.write('u,v\n')
            for row in tqdm(reader):
                u = int(row['u'])
                v = int(row['v'])
                t = [int(row['t']), int(row['h'])]
                if t[0] < testTime:
                    if u % 8 == 1 and v % 2 != 0 and u < v:
                        testFile.write(f'{u},{v}\n')
                else:
                    t[0] -= testTime
                    trainFile.write(f'{u},{v},{t[0]},{t[1]}\n')


