#!/usr/bin/env python3

from collections import defaultdict
import re
import sys
import os
import getopt
import requests
import subprocess
from argparse import ArgumentParser, ArgumentTypeError
import datetime

def matcher(s, pat=re.compile(r'^all|\d\d\.\d\d\.\d\d\d\d$')):
    if not pat.match(s):
        raise ArgumentTypeError('Expected date in format "dd.MM.yyyy"')
    return s

def getArgs():
    parser = ArgumentParser()
    parser.add_argument('-o', '--output', dest='directory', default='/home/igorjan/new', help='output directory for timetable files')
    parser.add_argument('-t', '--today', dest='today', action='store_true', help='load timetable for today')
    parser.add_argument('-m', '--tomorrow', dest='tomorrow', action='store_true', help='load timetable for tomorrow')
    parser.add_argument('-d', '--date', dest='date', default='all', type=matcher, help='load timetable for date=DATE')
    parser.add_argument('-f', '--full', dest='full', action='store_true', help='do not minify')
    parser.add_argument('-c', '--collapse', dest='collapse', action='store_false', default=True, help='do not collapse trains with same departure time')
    parser.add_argument('stations', nargs='+')
    args = parser.parse_args()

    if args.directory[-1] != os.sep:
        args.directory += os.sep
    if args.today:
        args.date = datetime.date.today().strftime("%d.%m.%Y")
    if args.tomorrow:
        args.date = (datetime.date.today() + datetime.timedelta(days = 1)).strftime("%d.%m.%Y")
    if args.full:
        args.collapse = False
    if len(args.stations) % 2 == 1:
        raise ArgumentTypeError('Count of stations must be even')

    return args

def getStations():
    file = open(os.path.dirname(os.path.abspath(__file__)) + '/stations.in', 'r')
    stationById = defaultdict(list)
    idByStation = defaultdict(list)
    for string in file:
        l = string[:-1].rsplit(' ', 1)
        stationById[l[1]].append(l[0])
        idByStation[l[0]].append(l[1])
    return stationById, idByStation

def getMins(date):
    return int(date[0:2]) * 60 + int(date[3:5])

def getDate(mins):
    hours = mins // 60
    mins %= 60
    res = ''
    if hours != 0: res += str(hours) + ' ч'
    if mins != 0: res += str(mins) + ' м'
    return re.sub(r'ч(\d)', r'ч \1', res)

dayReplacers = [ ('по пятницам и выходным', 'ПСВ'), ('по пятницам и субботам', 'ПС'), ('ежедневно', ''), ('по выходным', 'СВ'), ('по рабочим', 'КСВ'), ('по воскресеньям', 'В'), ('по субботам', 'С'), ('по пятницам', 'П'), ('кроме пятн\. и субб\.', 'КПС'), ('кроме пятниц и вых\.', 'КПСВ'), ('кроме четвергов и вых\.', 'КЧСВ'), ('кроме суббот', 'КС'), ('кроме воскресений', 'КВ') ]
placeReplacers = [ ('Лигово', ''), ('Калище', ''), ('Лебяжье', ''), ('Ораниенбаум-1', ''), ('Новый Петергоф', ''), ('Гатчина Балтийская', 'Г'), ('Гатчина Варшавская', 'Г'), ('Зеленогорск', 'Зел'), ('Кирилловское', 'Кир'), ('Каннельярви', 'Кан'), ('Рощино', 'Рощ'), ('Выборг', 'Выб'), ('Гаврилово', 'Гав'), ('Советский', 'Сов'), (r'Санкт-Петербург-.*?(\s|$)', r'\1') ]

def replacer(s, repl):
    for what, how in repl: s = re.sub(what, how, s)
    return s

def getTimetable(fro, to, date):
    for idFrom in fro:
        for idTo in to:
            try:
                x = requests.get('https://www.tutu.ru/spb/rasp.php?st1={}&st2={}&json&date={}'.format(idFrom, idTo, date)).json()
                if 'error' in x:
                    print(x['error'], file = sys.stderr)
                else:
                    return x
            except:
                print('No route from {} to {}'.format(idFrom, idTo))
    raise Exception('No route found:(')

def parse(directory, fro, to, date, full, collapse, st = getStations()):
    stationById, idByStation = st
    x = getTimetable(idByStation[fro], idByStation[to], date)

    filename = directory + stationById[x['dep-st']][0] + '—' + stationById[x['arr-st']][0]
    if not (x['dat'] is None):
        filename += ', ' + x['dat']
    filename = re.sub(r'(Санкт-Петербург)-.*?\.', r'\1', filename)
    sys.stdout = open(filename + '.out', 'w')

    trains = []
    averageTime = 0
    lastTime = 0
    for y in x['tra-list']:
        train = {
            'departure': y['tra']['dep']['tim'],
            'arrival': y['tra']['arr']['tim'],
            'from': stationById[y['tra']['dep']['st']][0],
            'to': stationById[y['tra']['arr']['st']][0],
            'schedule': replacer(y['tra']['sch'], dayReplacers),
            'type': '★' if y['tra']['typ'] == 'Ласточка' else '',
            'time': getMins(y['tra']['tr-tim']),
            'change': y['tra']['cha'].replace('. Уточните дату поездки', '')
        }
        if train['schedule'].find('отменен') != -1:
            continue

        if train['departure'] == lastTime and abs(train['time'] - trains[-1]['time']) <= 2 and collapse:
            trains[-1]['from'] += '/' + train['from']
            trains[-1]['to'] += '/' + train['to']
            trains[-1]['schedule'] += '/' + train['schedule']
            trains[-1]['type'] += '/' + train['type']
        else:
            trains.append(train)
            averageTime += train['time']
            lastTime = train['departure']

    averageTime /= len(trains)
    for train in trains:
        if full:
            train['time'] = getDate(train['time'])
        else:
            if len(trains) > 10 and train['time'] + 2 < averageTime:
                train['time'] = getDate(train['time']).replace(' ', '')
            elif train['time'] - 10 > averageTime:
                train['time'] = getDate(train['time'])
            else:
                train['time'] = ''
            train['time'] = train['type'] + ' ' + train['time']
            train['time'] = re.sub(r'^\s*(.*?)\s*$', r'\1', train['time'])
            train['from'] = replacer(train['from'], placeReplacers)
            train['to'] = replacer(train['to'], placeReplacers)

        train['from'] = re.sub(r'^(\w+)(/\1)+$', r'\1', train['from'])
        train['to']   = re.sub(r'^(\w+)(/\1)+$', r'\1', train['to'])
        train['time'] = re.sub(r'^\s*/*\s*$', '', train['time'])
        train['from'] = re.sub(r'^\s*/*\s*$', '', train['from'])
        train['to'] = re.sub(r'^\s*/*\s*$', '', train['to'])
        if train['from'] == '' and train['to'] == '' and (train['schedule'] == 'КСВ/СВ' or train['schedule'] == 'СВ/КСВ'):
            train['schedule'] = ''
        train['time'] = re.sub('^/', '❤/', train['time'])
        train['time'] = re.sub('/$', '/❤', train['time'])
        train['time'] = re.sub('//', '/❤/', train['time'])

    if full:
        fields = ['departure', 'arrival', 'schedule', 'type', 'time', 'from', 'to', 'change']
    else:
        fields = ['departure', 'schedule', 'time', 'from', 'to']

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

def main():
    args = getArgs()
    for i in range(0, len(args.stations), 2):
        parse(args.directory, args.stations[i], args.stations[i + 1], args.date, args.full, args.collapse)

main()
