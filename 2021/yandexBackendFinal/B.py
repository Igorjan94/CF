import json
import sys
sys.setrecursionlimit(10000000)

n = int(input())
root = {}

def dfs(root, cur, attrs):
    for k in cur.keys():
        if k in attrs:
            root[k] = cur[k]
        else:
            if not k in root:
                root[k] = {}
            dfs(root[k], cur[k], attrs)

for i in range(n):
    command = input()
    if command == "PRINT":
        print(json.dumps(root, sort_keys=True))

    else:
        attrs = input().split()
        la = int(attrs[0])
        attrs = set(attrs[1:])
        l = int(input())
        j = '\n'.join([input() for q in range(l)])
        j = json.loads(j)
        dfs(root, j, attrs)
