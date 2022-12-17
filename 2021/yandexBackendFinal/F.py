import requests

def get(url):
    return requests.get('http://127.0.0.1:7777/start/session?login=' + url).json()
def post(data):
    r = requests.post('http://127.0.0.1:7777/ls/batch', json=data)
    return r.json()['listings']


login = input()
bs = get(login)['max_batch_size']

root = [{
    'ok': False,
    'path': '',
    'type': 'Folder',
    'children': [],
    'size': 1
}]

def getPath(p1, p2):
    return (p1 + '/' + p2) if not p1.endswith('/') else (p1 + p2)

r = []
p = []
sz = 0

def dfs(root, path):
    global r
    global p
    global sz
    for i in range(len(root)):
        k = root[i]
        if 'ok' in k and k['type'] == 'Folder' and k['size'] > 0 and sz + k['size'] <= bs:
            sz += k['size']
            cur = getPath(path, k['path'])
            if not k['ok']:
                p.append(cur)
                r.append(k)
            dfs(k['children'], cur)

while True:
    dfs(root, '/')
    if len(r) == 0:
        break
    read = post({'paths': p})
    for i in range(len(read)):
        r[i]['ok'] = True
        r[i]['children'] = list(map(lambda x: {'ok': False, 'children': [], 'path': x['name'], 'type': x['type'], 'size': x['size']}, read[i]))

    p = []
    r = []
    sz = 0

s = []
def dfs2(root, path):
    global s
    for i in range(len(root)):
        k = root[i]
        cur = getPath(path, k['path'])
        s.append(cur)
        if 'ok' in k and k['type'] == 'Folder' and k['size'] > 0:
            dfs2(k['children'], cur)
dfs2(root, '/')

print(len(s))
print(*sorted(s), sep = '\n')
