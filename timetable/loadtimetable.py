from collections import defaultdict
import re
import sys
import os
import getopt
import requests

def defineDays(s):
    s = s.replace('ежедневно', '')
    s = s.replace('по выходным', 'СВ')
    s = s.replace('по рабочим', 'КСВ')
    s = s.replace('по воскресеньям', 'В')
    s = s.replace('по субботам', 'С')
    s = s.replace('по пятницам', 'П')
    s = s.replace('кроме пятн. и субб.', 'КПС')
    s = s.replace('кроме пятниц и вых.', 'КПСВ')
    s = s.replace('кроме воскресений', 'КВ')
    s = s.replace('по пятницам и выходным', 'ПСВ')
    s = re.sub(r'.*отменен.*', '', s)
    return s

def defineTime(s):
    if flag == 1:
        s = re.sub(r'\t\t00:[34]\d:00', ' б/о', s)
        s = re.sub(r'.*?\d\d:[1..9]\d:00.*?', '', s)
        s = re.sub(r'\d\d:\d\d:\d\d', '', s)
    else:
        s = re.sub(r'00:(\d\d):00', r'\1 м', s)
        s = re.sub(r'0(\d):(\d\d):00', r'\1 ч \2 м', s)
        s = re.sub(r'(\d\d):(\d\d):00', r'\1 ч \2 м', s)
    return s

def removeRepeatingStations(s):
    if flag == 0:
        return s
    s = re.sub(r'Санкт-Петербург-.*?(\s|$)', r'\1', s)
    s = s.replace('Зеленогорск', '')
    s = s.replace('Лигово', '')
    s = s.replace('Калище', '')
    s = s.replace('Лебяжье', '')
    s = s.replace('Ораниенбаум-1', '')
    s = s.replace('Новый Петергоф', '')
    s = s.replace('Гатчина Балтийская', 'Г')
    s = s.replace('Гатчина Варшавская', 'Г')
    return s


def parse(url):
    x = requests.get(url).json()
    filename = directory + reve[x["dep-st"]][0] + '—' + reve[x["arr-st"]][0]
    if not (x["dat"] is None):
        filename += ", " + x["dat"]
    filename = re.sub(r'(Санкт-Петербург)-.*?\.', r'\1', filename)
    x = x["tra-list"]
    sys.stdout = open(filename + ".out", 'w')
    for y in x:
        s = y["tra"]["sch"] + "\t\t" + reve[y["tra"]["dep"]["st"]][0] + "\t\t" + reve[y["tra"]["arr"]["st"]][0] + "\t\t" + y["tra"]["tr-tim"]
        s = defineDays(s)
        s = defineTime(s)
        s = removeRepeatingStations(s)
        if s != "":
            print(y["tra"]["dep"]["tim"] + "\t\t" + s)

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
flag      = sys.argv[3]
args      = sys.argv[4:]
if directory[-1] != os.sep:
    directory += os.sep
for i in range(0, len(args), 2):
    for fro in hash[args[i]]:
        for to in hash[args[i + 1]]:
            parse('http://www.tutu.ru/spb/rasp.php?st1=' + fro + '&st2=' + to + '&json' + today)
