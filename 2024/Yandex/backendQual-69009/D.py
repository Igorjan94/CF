from types import SimpleNamespace
class JSON(SimpleNamespace):
    def __init__(self, dictionary, **kwargs):
        super().__init__(**kwargs)
        for key, value in dictionary.items():
            if isinstance(value, dict):
                self.__setattr__(key, JSON(value))
            elif isinstance(value, list):
                self.__setattr__(key, list(map(JSON, value)))
            else:
                self.__setattr__(key, value)
    def __getitem__(self, key):
        return getattr(self, key)
    def __setitem__(self, key, value):
        return setattr(self, key, value)

import sys
import json
import asyncio
import aiohttp
import hashlib

c = open(sys.argv[1]).readlines()
config = json.loads(''.join(c))

db = config['db_url']
caches = config['cache_urls']
lc = len(caches)
session = None
gc = {}
needsDebug = len(sys.argv) > 2

def debug(*args):
    if not needsDebug: return
    sys.stderr.writelines(' '.join(map(str, args)) + '\n')
    sys.stderr.flush()

async def fetch(method: str, isJson, site, **kwargs):
    if method == 'get':
        async with session.get(site, **kwargs) as response:
            debug(method, site, response.status)
            if response.status != 200:
                return None
            if isJson:
                return await response.json()
            else:
                return await response.text()
    if method == 'put':
        async with session.put(site, **kwargs) as response:
            debug(method, site, response.status)
            if response.status != 200:
                return None
            if isJson:
                return await response.json()
            else:
                return await response.text()

async def get(cache, s):
    return await fetch('get', False, cache + s)

async def save(cache, s, d):
    return await fetch('put', False, cache + s, data=d)

async def getValue(key):
    if key in gc: return gc[key]
    h = abs(int(hashlib.shake_256(key.encode()).hexdigest(20), 16)) % lc
    i1 = h
    i2 = (h + 1) % lc
    value = await get(caches[i1], key)
    if value is not None: return value
    value = await get(caches[i2], key)
    if value is not None: return value
    value = await get(db, key)
    gc[key] = value
    await save(caches[i1], key, value)
    await save(caches[i2], key, value)
    return value

async def main():
    s = input()
    print(await getValue(s))
    sys.stdout.flush()

async def run():
    global session
    async with aiohttp.ClientSession() as test:
        session = test
        while True:
            try:
                await main()
            except Exception as e:
                debug(e)
                break

asyncio.run(run())
