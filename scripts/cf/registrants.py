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
div4 = []
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
    d4 = check(r'Div. ?4')
    ed = check('Edu')
    if ed:
        toAppend = educ
    elif d3:
        toAppend = div3
    elif d4:
        toAppend = div4
    elif d1 and d2:
        toAppend = comb
    elif d1:
        toAppend = div1
    elif d2:
        toAppend = div2
    elif check(r'Global') or check(r'Hello') or check(r'Good Bye') or check(r'Beta Round') or check('Alpha Round'):
        toAppend = comb
    else:
        toAppend = othe
    for i in range(len(toAppend)):
        if toAppend[i][3] == title:
            return
    toAppend.append(round)

participants_all = loadJsonFromFile(participantsFile)
div1, div2, div3, div4, educ, comb, othe = loadJsonFromFile(filename)

def getParticipants(contestId):
    print('Getting contest', contestId)
    contest = cf('contest.standings', contestId = contestId, lang = 'en')
    time.sleep(1)
    if not contest: return
    contest = contest.result
    participants_all[contestId] = len(contest.rows)
    saveJsonInFile(contest, f'/home/igorjan/.cache/cf/contests/{contestId}.json')
    saveJsonInFile(participants_all, participantsFile)

if False:
    for i in range(1, 14):
        stop = False
        url = f'https://codeforces.com/contests/page/{i}?locale=ru'
        html = requests.get(url).text.split('\n', 2)[2]
        page = BeautifulSoup(html, 'html5lib')
        j = 0
        for tr in page.body.find('div', attrs={'class': 'contests-table'}).find('div', attrs={'class': 'datatable'}).find_all('tr'):
            j += 1
            if j == 20: break
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
        saveJsonInFile([div1, div2, div3, div4, educ, comb, othe], filename)
        if stop:
            break

from statistics import median
import plotly.graph_objects as go
import plotly

data = []
def draw(title, rounds):
    if not rounds: return
    rounds = sorted(rounds, key = lambda x: datetime.strptime(x[0], DATE_FORMAT))

    dates, counts, participants, titles, *_ = zip(*rounds)
    dates = list(map(lambda date: datetime.strptime(date, DATE_FORMAT), dates))
    print(title, len(rounds))
    nd = [dates[0]]
    nc = [counts[0]]
    np = [participants[0]]
    nt = [[titles[0]]]
    percents = [participants[0] / counts[0]]
    for i in range(1, len(dates)):
        if dates[i] == dates[i - 1]:
            nc[-1] = max(nc[-1], counts[i])
            np[-1] = max(np[-1], participants[i])
            nt[-1].append(titles[i])
        else:
            nd.append(dates[i])
            nc.append(counts[i])
            np.append(participants[i])
            nt.append([titles[i]])
            percents.append(participants[i] / counts[i] if counts[i] > 0 else 0)

    dates = nd
    counts = nc
    participants = np
    titles = list(map(lambda t: ', '.join(t), nt))

    assert(len(dates) == len(counts))
    assert(len(dates) == len(participants))

    data.append(go.Scatter(
        x = dates,
        y = participants,
        text = titles,
        mode = 'markers',
        name = title + ' participants'
    ))
    data.append(go.Scatter(
        x = dates,
        y = counts,
        text = titles,
        mode = 'markers',
        name = title + ' registrants'
    ))
    # data.append(go.Scatter(x = dates, y = percents, name = title + ' participa'))

draw('div1', div1)
draw('div2', div2)
draw('div3', div3)
draw('educ', educ)
draw('comb', comb)
# draw('othe', othe)
# draw('div4', div4)
def x(t):
    return list(map(lambda g: g.name.find(t) >= 0, data))

def getButton(t, **kwargs):
    f = kwargs['f'] if 'f' in kwargs else t
    return dict(
        label = t,
        method = 'update',
        args = [{'visible': x(f)}, {'title': t, 'annotations': []}]
    )

roundButtons = [
    getButton('All', f = ''),
    getButton('Participants', f = 'part'),
    getButton('Registrants', f = 'reg'),
    *[getButton(t) for t in ['div1', 'div2', 'div3', 'educ', 'comb', 'othe', 'div4']]
]

fig = go.Figure(data = data)
fig.update_xaxes(
    rangeslider_visible = True,
    rangeselector = dict(
        buttons = list([
            dict(count = 1, label = '1m', step = 'month', stepmode = 'backward'),
            dict(count = 6, label = '6m', step = 'month', stepmode = 'backward'),
            dict(count = 1, label = 'YTD', step = 'year', stepmode = 'todate'),
            dict(count = 1, label = '1y', step = 'year', stepmode = 'backward'),
            dict(step = 'all')
        ])
    )
)

fig.update_layout(
    legend_orientation = 'v',
    title = 'Registrants and participants',
    xaxis_title = 'Date',
    yaxis_title = 'Number',
    legend = dict(xanchor = 'center'),
    updatemenus = [
        dict(
            active = 1,
            showactive = True,
            xanchor = 'left',
            yanchor = 'top',
            y = 0,
            buttons = list([
                dict(label = 'Log Scale', method = 'update', args = [{'visible': [True] * len(data)}, {'yaxis': {'type': 'log'}}]),
                dict(label = 'Linear Scale', method = 'update', args = [{'visible': [True] * len(data)}, {'yaxis': {'type': 'linear'}}])
            ]),
        ),
        dict(
            type = 'buttons',
            xanchor = 'left',
            yanchor = 'top',
            y = 1,
            buttons = roundButtons,
        )
    ]
)
fig.update_traces(hoverinfo = 'all', hovertemplate = '%{x}, %{y}<br><a href="https://codeforces.com">%{text}</a>')
fig.update_layout(xaxis_range = [datetime(2020, 1, 1), datetime(2020, 6, 1)], hovermode = 'x')
fig.show()

graphJSON = json.dumps(fig, cls = plotly.utils.PlotlyJSONEncoder)
with open('./registrants.json', 'w') as file:
    file.write('const graphs = {};'.format(graphJSON))
