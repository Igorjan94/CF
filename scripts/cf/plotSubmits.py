import sys
# the mock-0.3.1 dir contains testcase.py, testutils.py & mock.py
sys.path.append('/home/igorjan/206round/scripts')

from library import *

def cf(method, **kwargs):
    params = dotdict(kwargs)
    ret = requests.get('https://codeforces.com/api/' + method, params = params).json()
    if ret.status != 'OK':
        print(f'Error in {method} {ret.status}: {ret.comment}', kwargs)
        return ret.comment
    return ret

def getSubmits(contestId):
    def getter(**kwargs):
        return cf('contest.status', **kwargs)
    return unlimited(getter, 'result', 10000, True, count_field = 'count', offset_field = 'from', starting_offset = 1, contestId = contestId)


def plotContest(contestId):
    import matplotlib.pyplot as plt
    import matplotlib.dates as mdates
    contest = cf('contest.standings', **{'from': 1, 'contestId': contestId, 'count': 1}).result.contest
    duration = contest.durationSeconds // 60
    title = contest.name
    submits = getSubmits(contestId)

    def getDate(submit):
        return submit.relativeTimeSeconds / 60

    off = list(filter(lambda submit: submit.author.participantType == 'CONTESTANT', submits))
    unoff = list(filter(lambda submit: submit.author.participantType == 'OUT_OF_COMPETITION', submits))

    legend = []
    dates = []

    def getLast(submits, minutes):
        return len(list(filter(lambda d: d >= duration - minutes, submits))) * 100

    def add(submits, constestants):
        MINUTES = 20
        all_submits = list(map(getDate, filter(lambda submit: submit.verdict != 'OK', submits)))
        ok_submits = list(map(getDate, filter(lambda submit: submit.verdict == 'OK', submits)))
        dates.append(ok_submits)
        dates.append(all_submits)
        count_ok_last_minutes = getLast(ok_submits, MINUTES)
        count_all_last_minutes = getLast(all_submits, MINUTES)
        legend.append(f'{constestants} OK ({len(ok_submits)}), {count_ok_last_minutes / len(ok_submits):.0f}% in last {MINUTES} minutes')
        legend.append(f'{constestants} Incorrect ({len(all_submits)}), {count_all_last_minutes / len(all_submits):.0f}% in last {MINUTES} minutes')

    add(off, 'official')
    # add(unoff, 'unofficial')

    fig, ax = plt.subplots(1, 1)
    ax.hist(dates, bins=duration, stacked=True)
    ax.legend(legend)
    # ax.xaxis.set_major_formatter(mdates.DateFormatter('%H:%M'))
    plt.xlabel('Time')
    plt.ylabel('Count of submits')
    plt.title(title)
    plt.show()

plotContest(1249)
