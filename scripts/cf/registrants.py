import sys
sys.path.append('/home/igorjan/206round/scripts')

from library import *
from bs4 import BeautifulSoup
import re

filename = '/home/igorjan/.cache/vk200/contests.json'

div1 = []
div2 = []
div3 = []
educ = []
comb = []
othe = []

if True:
    div1, div2, div3, educ, comb, othe = loadJsonFromFile(filename)
else:
    for i in range(1, 13):
        url = f'https://codeforces.com/contests/page/{i}?locale=ru'
        html = requests.get(url).text.split('\n', 2)[2]
        page = BeautifulSoup(html, 'html5lib')
        for tr in page.body.find('div', attrs={'class': 'contests-table'}).find('div', attrs={'class': 'datatable'}).find_all('tr'):
            cid = tr.get('data-contestid')
            if not cid: continue
            date = tr.find('span', attrs={'class': 'format-date'}).contents[0]
            title = tr.td.contents[0].strip()
            count = int(tr.find('a', attrs={'class': 'contestParticipantCountLinkMargin'}).contents[1][2:])

            round = [date, count, title]
            if re.findall(r'unrated', title) or re.findall(r'неофициальная', title):
                continue
            if re.findall(r'Edu', title):
                educ.append(round)
            elif re.findall(r'Div. ?3', title):
                div3.append(round)
            elif re.findall(r'Div. ?2', title) and re.findall(r'Div. ?1', title) or re.findall(r'Global', title) or re.findall(r'Hello', title) or re.findall(r'Good Bye', title):
                comb.append(round)
            elif re.findall(r'Div. ?1', title):
                div1.append(round)
            elif re.findall(r'Div. ?2', title):
                div2.append(round)
            else:
                othe.append(round)


from datetime import datetime
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from scipy.interpolate import make_interp_spline, BSpline
import numpy as np

fig, ax = plt.subplots(1, 1)
legend = []
plt.xlabel('Date')
plt.ylabel('Count of registrants')

def draw(title, rounds):
    if not rounds: return
    dates, counts, *_ = zip(*reversed(rounds))
    nd = [dates[0]]
    nc = [counts[0]]
    for i in range(1, len(dates)):
        if dates[i] == dates[i - 1]:
            nc[-1] = max(nc[-1], counts[i])
        else:
            nd.append(dates[i])
            nc.append(counts[i])
    dates = nd
    counts = nc
    dates = mdates.date2num(list(map(lambda date: datetime.strptime(date, '%d.%m.%Y %H:%M'), dates)))

    if len(dates) >= 2 and False:
        try:
            xnew = np.linspace(dates.min(), dates.max(), len(dates) * 5)
            spl = make_interp_spline(list(dates), list(counts), k = 1)  # type: BSpline
            countsnew = spl(xnew)
            ax.plot_date(xnew, countsnew)
            legend.append(title)
        except ValueError:
            print(title)
            print('\n'.join(nd))

    ax.plot_date(dates, counts, markersize = 4)
    legend.append(title)

# draw('div1', div1)
# draw('div2', div2)
# draw('div3', div3)
# draw('educ', educ)
# draw('comb', comb)
draw('othe', othe)

saveJsonInFile([div1, div2, div3, educ, comb, othe], filename)

ax.legend(legend)
plt.show()
