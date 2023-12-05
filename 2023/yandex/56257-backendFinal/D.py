import sys
import json
import asyncio
import aiohttp

c = open(sys.argv[1]).readlines()
config = json.loads(''.join(c))

mm = config['max_messages_to_keep']

db = 'http://localhost:9000'
mp = {}

mp['subs'] = 0
mp['events'] = 0
sessions = {}
last = 0
cache = {}
subs = []
lst = []
session = None

def debug(*args):
    return
    sys.stderr.writelines(' '.join(map(str, args)) + '\n')
    sys.stderr.flush()

async def fetch(method, isJson, site, **kwargs):
    if method == 'get':
        async with session.get(site, **kwargs) as response:
            debug(method, site, response.status)
            if response.status != 200:
                return None
            if isJson:
                return await response.json()
            else:
                return await response.text()
    if method == 'post':
        async with session.post(site, **kwargs) as response:
            debug(method, site, response.status)
            if response.status != 200:
                return None
            if isJson:
                return await response.json()
            else:
                return await response.text()

async def getFromDB(method, isJson, site, **kwargs):
    return await fetch(method, isJson, db + site, **kwargs)

async def getFile(filename):
    sz = mp[filename]
    ret = await getFromDB('get', False, f'/load?file_name={filename}&start_pos=0&count={sz}')
    return ret

async def saveFile(filename, sp, d):
    ret = await getFromDB('post', False, f'/store?file_name={filename}&start_pos={sp}', data=d, headers={'content-type': 'application/octet-stream'})
    return ret

async def send(s, i, d):
    debug("SENDING EVENT", s, i, d)
    await fetch('post', False, s + '/store_event', json={
        'id': i,
        'data': d
    })

async def rawAddSub(k, v):
    subs.append((k, v))

async def addSub(k, v):
    await rawAddSub(k, v)
    line = f'{k}={v};'
    await saveFile('subs', mp['subs'], line)
    mp['subs'] += len(line)
    for i in range(max(v, last - mm), last):
        await send(k, i, cache[i])

async def addEvent(k, v):
    cache[k] = v
    lst.append((k, v))
    d = ';'.join(f'{k}={v}' for (k, v) in lst[-mm:])
    await saveFile('events', 0, d + '$')

    tasks = []
    for (subscriber, f) in subs:
        if f <= k:
            await send(subscriber, k, v)
    # async with asyncio.TaskGroup() as tg:
        # for (subscriber, f) in subs:
            # if f <= k:
                # tg.create_task(send(subscriber, k, v))

async def main():
    global last
    s = input().split(' ')
    if s[0] == 'NEW_SUBSCRIBER':
        k = s[1]
        v = int(s[2])
        await addSub(k, v)
    if s[0] == 'EVENT':
        d = s[1]
        await addEvent(last, d)
        last += 1
    if s[0] == 'SHUTDOWN':
        sys.exit()
    print('NEXT')
    sys.stdout.flush()

async def run():
    global session
    global last
    async with aiohttp.ClientSession() as test:
        session = test

        ret = await getFromDB('get', True, '/file_sizes')
        fs = ret['files']
        for f in fs:
            mp[f['name']] = f['size']

        sub = await getFile('subs')
        if sub is not None:
            ss = sub.split(';')
            for s in ss:
                if len(s):
                    k, v = s.split('=')
                    v = int(v)
                    await rawAddSub(k, v)

        ev = await getFile('events')
        if ev is not None:
            ss = ev.split('$')[0].split(';')
            for s in ss:
                if len(s):
                    k, v = s.split('=')
                    k = int(k)
                    cache[k] = v
                    lst.append((k, v))
                    last = k + 1

        print('START')
        sys.stdout.flush()

        while True:
            try:
                await main()
            except:
                break

asyncio.run(run())
