from collections import defaultdict
import re
import sys
import os
import getopt
import requests
import subprocess

def defineDays(s):
    s = s.replace('по пятницам и выходным', 'ПСВ')
    s = s.replace('по пятницам и субботам', 'ПС')
    s = s.replace('ежедневно', '')
    s = s.replace('по выходным', 'СВ')
    s = s.replace('по рабочим', 'КСВ')
    s = s.replace('по воскресеньям', 'В')
    s = s.replace('по субботам', 'С')
    s = s.replace('по пятницам', 'П')
    s = s.replace('кроме пятн. и субб.', 'КПС')
    s = s.replace('кроме пятниц и вых.', 'КПСВ')
    s = s.replace('кроме четвергов и вых.', 'КЧСВ')
    s = s.replace('кроме суббот', 'КС')
    s = s.replace('кроме воскресений', 'КВ')
    return s

def fastRepl(r):
    time = int(r.group(1))
    return ' б/о' if time < minutes else r.group(0)

def defineTime(s):
    if flag == 1:
        s = re.sub(r'00:(\d\d):\d\d', fastRepl, s)
        s = re.sub(r'\d\d:[1..9]\d:00', '', s)
        s = re.sub(r'\d\d:\d\d:\d\d', '', s)
    else:
        s = re.sub(r'00:(\d\d):00', r' \1 м', s)
        s = re.sub(r'0(\d):(\d\d):00', r' \1 ч \2 м', s)
        s = re.sub(r'(\d\d):(\d\d):00', r' \1 ч \2 м', s)
    return s

def removeRepeatingStations(s):
    if flag == 0:
        return s
    s = re.sub(r'Санкт-Петербург-.*?(\s|$)', r'\1', s)
    s = s.replace('Лигово', '')
    s = s.replace('Калище', '')
    s = s.replace('Лебяжье', '')
    s = s.replace('Ораниенбаум-1', '')
    s = s.replace('Новый Петергоф', '')
    s = s.replace('Гатчина Балтийская', 'Г')
    s = s.replace('Гатчина Варшавская', 'Г')
    s = s.replace('Зеленогорск', 'Зел')
    s = s.replace('Кирилловское', 'Кир')
    s = s.replace('Каннельярви', 'Кан')
    s = s.replace('Рощино', 'Рощ')
    s = s.replace('Выборг', 'Выб')
    s = s.replace('Гаврилово', 'Гав')
    s = s.replace('Советский', 'Сов')
    return s


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
    x = x['tra-list']
    sys.stdout = open(filename + '.out', 'w')
    for y in x:
        train = {
            'departure': y['tra']['dep']['tim'],
            'arrival': y['tra']['arr']['tim'],
            'from': removeRepeatingStations(reve[y['tra']['dep']['st']][0]),
            'to': removeRepeatingStations(reve[y['tra']['arr']['st']][0]),
            'schedule': defineDays(y['tra']['sch']) + (' ★' if y['tra']['typ'] == 'Ласточка' else '') + defineTime(y['tra']['tr-tim']),
            'change': y['tra']['cha']
        }
        if train['schedule'].find('отменен') != -1:
            continue

        if flag:
            s = '{}\t{}\t{}\t{}'.format(train['departure'], train['schedule'], train['from'], train['to'])
        else:
            s = '{}\t{}\t{}\t{}\t{}\t{}'.format(train['departure'], train['arrival'], train['schedule'], train['from'], train['to'], train['change'].replace('. Уточните дату поездки', ''))

        print(re.sub(r'\t +', '\t', s))

    sys.stdout.close()
    subprocess.Popen(['mousepad', filename + '.out'])


st = os.path.dirname(os.path.abspath(__file__)) + '/stations.in'
file = open(st, 'r')
hash = defaultdict(list)
reve = defaultdict(list)
# isBalt = False
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
            parse(directory, 'http://www.tutu.ru/spb/rasp.php?st1=' + fro + '&st2=' + to + '&json' + today)
    i += 2 + fl
