import sys
sys.path.append('/home/igorjan/206round/scripts')

from library import *
from plotSubmits import cf
from bs4 import BeautifulSoup
import re
from datetime import datetime
import time

filename = '/home/igorjan/.cache/cf/contests.json'
participantsFile = '/home/igorjan/.cache/cf/participants.json'
DATE_FORMAT = '%d.%m.%Y %H:%M'

div1 = []
div2 = []
div3 = []
educ = []
comb = []
othe = []

def addRound(round):
    title = round[3]
    def check(s):
        return re.findall(s, title)
    if check(r'unrated') or check(r'неофициальная') or check('Testing') or check('Experimental'):
        return
    d1 = check(r'Div. ?1')
    d2 = check(r'Div. ?2') or check(r'Див. ?2') or check(r'Дивизион 2')
    d3 = check(r'Div. ?3')
    ed = check('Edu')
    if ed:
        educ.append(round)
    elif d3:
        div3.append(round)
    elif d1 and d2:
        comb.append(round)
    elif d1:
        div1.append(round)
    elif d2:
        div2.append(round)
    elif check(r'Global') or check(r'Hello') or check(r'Good Bye') or check(r'Beta Round') or check('Alpha Round'):
        comb.append(round)
    else:
        othe.append(round)

participants_all = loadJsonFromFile(participantsFile)
div1, div2, div3, educ, comb, othe = loadJsonFromFile(filename)

def getParticipants(contestId):
    print('Getting contest', contestId)
    contest = cf('contest.standings', contestId = contestId, lang = 'en')
    time.sleep(1)
    if not contest: return
    contest = contest.result
    participants_all[contestId] = len(contest.rows)
    saveJsonInFile(contest, f'/home/igorjan/.cache/cf/contests/{contestId}.json')
    saveJsonInFile(participants_all, participantsFile)

for i in range(1, 14):
    stop = False
    url = f'https://codeforces.com/contests/page/{i}?locale=ru'
    html = requests.get(url).text.split('\n', 2)[2]
    page = BeautifulSoup(html, 'html5lib')
    for tr in page.body.find('div', attrs={'class': 'contests-table'}).find('div', attrs={'class': 'datatable'}).find_all('tr'):
        cid = tr.get('data-contestid')
        if not cid: continue
        if cid in participants_all:
            stop = True
            break
        getParticipants(cid)
        date = tr.find('span', attrs={'class': 'format-date'}).contents[0]
        title = tr.td.contents[0].strip()
        count = int(tr.find('a', attrs={'class': 'contestParticipantCountLinkMargin'}).contents[1][2:])
        addRound([date, count, participants_all.get(cid, 0), title])
    saveJsonInFile([div1, div2, div3, educ, comb, othe], filename)
    if stop:
        break


import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from scipy.interpolate import make_interp_spline, BSpline
import numpy as np
from statistics import median

fig, ax = plt.subplots(1, 1)
legend = []
plt.xlabel('Date')
plt.ylabel('Percent of participants')

def draw(title, rounds):
    if not rounds: return

    dates, counts, participants, titles, *_ = zip(*reversed(rounds))
    print(title, len(rounds))
    # print('\n'.join(titles))
    nd = [dates[0]]
    nc = [counts[0]]
    np = [participants[0]]
    percents = [participants[0] / counts[0]]
    for i in range(1, len(dates)):
        if dates[i] == dates[i - 1]:
            nc[-1] = max(nc[-1], counts[i])
            np[-1] = max(np[-1], participants[i])
        else:
            nd.append(dates[i])
            nc.append(counts[i])
            np.append(participants[i])
            percents.append(participants[i] / counts[i] if counts[i] > 0 else 0)
    dates = nd
    counts = nc
    participants = np
    dates = mdates.date2num(list(map(lambda date: datetime.strptime(date, DATE_FORMAT), dates)))

    ax.plot_date(dates, counts, markersize = 4)
    legend.append(title + ' registrations')
    ax.plot_date(dates, participants, markersize = 4)
    legend.append(title + ' participants')
    # ax.plot_date(dates, percents, markersize = 4, color = 'blue')
    # print(title, median(percents))

# draw('div1', div1)
# draw('div2', div2)
# draw('div3', div3)
draw('educ', educ)
# draw('comb', comb)
# draw('othe', othe)

ax.legend(legend)
plt.show()
