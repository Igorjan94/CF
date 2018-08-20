from collections import defaultdict
import re
import sys
import os
import getopt
import requests
import subprocess

def fastRepl(r):
    return 'б/о' if int(r.group(1)) < minutes else r.group(0)

dayReplacers = [ ('по пятницам и выходным', 'ПСВ'), ('по пятницам и субботам', 'ПС'), ('ежедневно', ''), ('по выходным', 'СВ'), ('по рабочим', 'КСВ'), ('по воскресеньям', 'В'), ('по субботам', 'С'), ('по пятницам', 'П'), ('кроме пятн\. и субб\.', 'КПС'), ('кроме пятниц и вых\.', 'КПСВ'), ('кроме четвергов и вых\.', 'КЧСВ'), ('кроме суббот', 'КС'), ('кроме воскресений', 'КВ') ]
placeReplacers = [ ('Лигово', ''), ('Калище', ''), ('Лебяжье', ''), ('Ораниенбаум-1', ''), ('Новый Петергоф', ''), ('Гатчина Балтийская', 'Г'), ('Гатчина Варшавская', 'Г'), ('Зеленогорск', 'Зел'), ('Кирилловское', 'Кир'), ('Каннельярви', 'Кан'), ('Рощино', 'Рощ'), ('Выборг', 'Выб'), ('Гаврилово', 'Гав'), ('Советский', 'Сов'), (r'Санкт-Петербург-.*?(\s|$)', r'\1') ]

freeReplacers = [ (r'00:(\d\d):\d\d', fastRepl), (r'\d\d:[1..9]\d:00', ''), (r'\d\d:\d\d:\d\d', '') ]
timeReplacers = [ (r'00:(\d\d):00', r'\1 м'), (r'0(\d):00:00', r'\1 ч'), (r'0(\d):(\d\d):00', r'\1 ч \2 м'), (r'(\d\d):(\d\d):00', r'\1 ч \2 м') ]

def replacer(s, repl):
    for what, how in repl:
        s = re.sub(what, how, s)
    return s

def defineTime(s):
    return replacer(s, timeReplacers if flag == 0 else freeReplacers)

def removeRepeatingStations(s):
    return s if flag == 0 else replacer(s, placeReplacers)

def parse(directory, url):
    try:
        x = requests.get(url).json()
    except:
        print('something went wrong in tutu, or just stations with same names', file=sys.stderr)
        return
    if 'error' in x:
        return

    filename = directory + reve[x['dep-st']][0] + '—' + reve[x['arr-st']][0]
    if not (x['dat'] is None):
        filename += ', ' + x['dat']
    filename = re.sub(r'(Санкт-Петербург)-.*?\.', r'\1', filename)
    sys.stdout = open(filename + '.out', 'w')

    trains = []
    for y in x['tra-list']:
        isLast = '★' if y['tra']['typ'] == 'Ласточка' else ''
        train = {
            'departure': y['tra']['dep']['tim'],
            'arrival': y['tra']['arr']['tim'],
            'from': removeRepeatingStations(reve[y['tra']['dep']['st']][0]),
            'to': removeRepeatingStations(reve[y['tra']['arr']['st']][0]),
            'schedule': replacer(y['tra']['sch'], dayReplacers),
            'time': isLast + ' ' + defineTime(y['tra']['tr-tim']),
            'change': y['tra']['cha'].replace('. Уточните дату поездки', '')
        }
        if train['schedule'].find('отменен') == -1:
            trains.append(train)

    if flag:
        fields = ['departure', 'schedule', 'time', 'from', 'to']
    else:
        fields = ['departure', 'arrival', 'schedule', 'time', 'from', 'to', 'change']
    resultedFields = []
    for f in fields:
        isNeeded = False
        for train in trains:
            isNeeded = isNeeded or train[f] != ''
        if isNeeded:
            resultedFields.append(f)

    for train in trains:
        print('\t'.join(map(lambda f: train[f], resultedFields)))

    sys.stdout.close()
    subprocess.Popen(['mousepad', filename + '.out'])


st = os.path.dirname(os.path.abspath(__file__)) + '/stations.in'
file = open(st, 'r')
hash = defaultdict(list)
reve = defaultdict(list)
for string in file:
    l = string[:-1].rsplit(' ', 1)
    hash[l[0]].append(l[1])
    reve[l[1]].append(l[0])

directory = sys.argv[1]
today     = sys.argv[2]
flag      = int(sys.argv[3])
minutes   = int(sys.argv[4])
args      = sys.argv[5:]
if directory[-1] != os.sep:
    directory += os.sep
i = 0
while i < len(args):
    arg1 = args[i]
    if hash[arg1] == []:
        arg1 += ' ' + args[i + 1]
        i += 1
    fl = 0
    for fro in hash[arg1]:
        arg2 = args[i + 1]
        if hash[arg2] == []:
            arg2 += ' ' + args[i + 2]
            fl = 1
        for to in hash[arg2]:
            parse(directory, 'https://www.tutu.ru/spb/rasp.php?st1=' + fro + '&st2=' + to + '&json' + today)
    i += 2 + fl
