import csv

answers = './TEST/test.csv'
output = './TEST/submit.csv'

with open(answers, 'r') as answersFile:
    reader = csv.DictReader(answersFile)
    with open(output, 'r') as outputFile:
        tpfn = 0
        f = {}
        for row in reader:
            u = int(row['u'])
            v = int(row['v'])
            if not u in f:
                f[u] = set()
            f[u].add(v)
            tpfn += 1
        tp = 0
        for row in outputFile.readlines():
            if len(row) <= 5: continue
            u, vs = row.strip().split(': ')
            u = int(u)
            if not u in f: continue
            tp += len(set(map(int, vs.split(','))).intersection(f[u]))

        print(f'RECALL: {tp / tpfn:.5f}, {tp}/{tpfn}')

