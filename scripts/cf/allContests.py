import sys
sys.path.append('/home/igorjan/206round/scripts')

from library import *
from plotSubmits import cf
from bs4 import BeautifulSoup
import re
from datetime import datetime
import time
from collections import defaultdict


def main():
    contests = sys.argv[1:]
    participants = dotdict()
    for contestId in contests:
        print(contestId)
        contest = cf('contest.standings', contestId = contestId, **{'from': 1}, lang = 'en', showUnofficial = True)['result']
        for participant in contest['rows']:
            name = participant.party.members[0].handle
            t = participant.party.participantType
            rank = participant.rank
            points = participant.points
            if points <= 0:
                continue
            if name not in participants:
                participants[name] = dotdict(off = 0, unoff = 0, both = 0, place = 0)
            if t == 'CONTESTANT':
                participants[name].off += 1
                participants[name].both += 1
                participants[name].place += rank
            elif t == 'OUT_OF_COMPETITION':
                participants[name].unoff += 1
                participants[name].both += 1
                participants[name].place += rank
        time.sleep(2)

    items = participants.items()
    items = list(sorted(items, key = lambda x: [x[1].both, x[1].place]))
    print('name', 'cnt', '\\sigma_place', 'off', 'unoff')
    for k, v in items:
        if v.both >= len(contests):
            print(k, v.both, v.place, v.off, v.unoff)


if __name__ == '__main__':
    main()
