import vk
fn = '.zaika.date'
def writeFile(filename, date):
    with open(filename, 'w') as f:
        f.write(str(date))

def readFile(filename):
    try:
        with open(filename, 'r') as f:
            return int(f.readlines()[0])
    except:
        return 0

lastDate = readFile(fn)
nextDate = lastDate
print('CUR', lastDate)
x = vk.vk('wall.get', count=10, owner_id=-186426881)
for item in list(x['items']):
    if item.date > lastDate:
        print(item.date)
    else:
        print('EXPIRED', item.date)
    nextDate = max(nextDate, item.date)

writeFile(fn, nextDate)
