import json
import sys
import requests
import time
import asyncio

sys.setrecursionlimit(10000000)

f = open(sys.argv[1])
s = '\n'.join(f.readlines())
config = json.loads(s)
server = config['server']['endpoint']
headers = {'Content-type': 'application/json', 'Accept': 'application/json'}

async def get(ep):
    try:
        res = requests.get('http://' + ep + '/state', timeout = 1.1)
        if res.status_code == 200:
            return res.json()
    except:
        42
    await asyncio.sleep(0.1)
    return await get(ep)

async def submit(result):
    try:
        res = requests.post('http://' + server + '/send_measurings', json = result, timeout = 1.1)
        if res.status_code == 200:
            return res.text
    except Exception as e:
        42
    await asyncio.sleep(0.1)
    return await submit(result)

async def run(ep):
    res = await get(ep)
    ret = await submit({
        'meter_device_id': res['dmid'],
        'measurings': res['state'],
    })
    print(ret)


async def main():
    tasks = []
    async with asyncio.TaskGroup() as tg:
        for sensor in config['sensors']:
            ep = sensor['endpoint']
            tg.create_task(run(ep))

asyncio.run(main())
