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


@completion.command()
@click.argument('contest_id', required=True, type=int, nargs=1)
@click.option('-m', '--minutes', help='Stat for last <minutes>', default=20)
@click.option('-u', '--unofficial', is_flag=True, help='Show only unofficial participants', default=False)
def plotContest(contest_id, minutes, unofficial):
    import matplotlib.pyplot as plt
    import matplotlib.dates as mdates
    contest = cf('contest.standings', **{'from': 1, 'contestId': contest_id, 'count': 1}).result.contest
    duration = contest.durationSeconds // 60
    title = contest.name
    submits = getSubmits(contest_id)

    def getDate(submit):
        return submit.relativeTimeSeconds / 60

    off = list(filter(lambda submit: submit.author.participantType == 'CONTESTANT', submits))
    unoff = list(filter(lambda submit: submit.author.participantType == 'OUT_OF_COMPETITION', submits))

    legend = []
    dates = []

    def getLast(submits, minutes):
        return len(list(filter(lambda d: d >= duration - minutes, submits))) * 100

    def add(submits, constestants):
        all_submits = list(map(getDate, filter(lambda submit: submit.verdict != 'OK', submits)))
        ok_submits = list(map(getDate, filter(lambda submit: submit.verdict == 'OK', submits)))
        dates.append(ok_submits)
        dates.append(all_submits)
        count_ok_last_minutes = getLast(ok_submits, minutes)
        count_all_last_minutes = getLast(all_submits, minutes)
        legend.append(f'{constestants} OK ({len(ok_submits)}), {count_ok_last_minutes / len(ok_submits):.0f}% in last {minutes} minutes')
        legend.append(f'{constestants} Incorrect ({len(all_submits)}), {count_all_last_minutes / len(all_submits):.0f}% in last {minutes} minutes')

    if unofficial:
        add(unoff, 'unofficial')
    else:
        add(off, 'official')

    fig, ax = plt.subplots(1, 1)
    ax.hist(dates, bins=duration, stacked=True)
    ax.legend(legend)
    # ax.xaxis.set_major_formatter(mdates.AutoDateFormatter())
    plt.xlabel('Time')
    plt.ylabel('Count of submits')
    plt.title(title)
    plt.savefig(title.replace(r'\s', '') + '.png', dpi=900);
    # plt.show()

if __name__ == "__main__":
    completion()